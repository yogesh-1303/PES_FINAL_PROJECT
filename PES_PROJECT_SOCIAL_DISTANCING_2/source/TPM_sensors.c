#include <TPM_sensors.h>
#include "MKL25Z4.h"
#include "testing.h"
#include "systick.h"
#include "testing.h"

//#define S3

extern ticktime_t tick;

int test_sensor, use_both;
int last_sensor_flag;

sensor sensor1={0}, sensor2={0}, sensor3={0};

//tpm1 initializtion function: works on Input capture mode on channel 0
//used for capturing Input from Sensor 1
//works using channel and overflow interrupts
//takes and returns void
void tpm1_init(){

	//provide clock to TPM1 and PORTE
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//select the clock
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;

	//select MOD value
	TPM1->MOD = 20000-1;

	//set the CnSC values for falling edge capture with interrupt
	TPM1->CONTROLS[0].CnSC = TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA(0) | TPM_CnSC_CHIE_MASK;

	//set MUX value for input capture
	PORTE->PCR[SENSOR1_IN] &= ~PORT_PCR_MUX(7);
	PORTE->PCR[SENSOR1_IN] |= PORT_PCR_MUX(3);

	//prescalar of 128, overflow Interrupt enable, start the timer
	TPM1->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7)  | TPM_SC_TOIE_MASK | TPM_SC_CPWMS(0);

	//set priority, clear pending interrupts, and enable interrupt
	NVIC_SetPriority(TPM1_IRQn, 2);
	NVIC_ClearPendingIRQ(TPM1_IRQn);
	NVIC_EnableIRQ(TPM1_IRQn);
}

//IRQ Handler for TPM1
void TPM1_IRQHandler() {
	//out_off();
	//when overflow occurs, adjust the offset as the count will reset
	if(TPM1->STATUS & TPM_STATUS_TOF_MASK){
		sensor1.ovflow_offset = 20000 - sensor1.prev_count;
		sensor1.prev_count = 0;
	}
	//when the capture occurs, take count and store this value for next cycle
	if(TPM1->STATUS & TPM_STATUS_CH0F_MASK) {
		sensor1.last_ovf_count = TPM1->CONTROLS[0].CnV;
		sensor1.count = TPM1->CONTROLS[0].CnV - sensor1.prev_count + sensor1.ovflow_offset;
		sensor1.prev_count = TPM1->CONTROLS[0].CnV;
		//trigger the sensor for next capture
		GPIOA->PSOR |= 1<<SENSOR1_TRIG;
		delay(10);
		GPIOA->PCOR |= 1<<SENSOR1_TRIG;
		sensor1.ovflow_offset = 0;
	}
	//Reset all the flags
	TPM1->STATUS |=  TPM_STATUS_TOF_MASK | TPM_STATUS_CH0F_MASK;
	//out_on();
}

//tpm1 initializtion function: works on Input capture mode on channels 0 and 1
//used for capturing Input from Sensors 2 and 3
//works using channel and overflow interrupts
//takes and returns void
void tpm2_init() {
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;

	TPM2->MOD = 20000-1;

	//if call is for sensor 2 only, this block initializes the sensor 2 and leads to its IRQ
	if((test_sensor==2)||(use_both==1)) {
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA(0) | TPM_CnSC_CHIE_MASK;
	PORTE->PCR[SENSOR2_IN] &= ~PORT_PCR_MUX(7);
	PORTE->PCR[SENSOR2_IN] |= PORT_PCR_MUX(3);
	}

	//if call is for sensor 3 only, this block initializes the sensor 2 and leads to its IRQ
	if((test_sensor==3)||(use_both==1)){
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA(0) | TPM_CnSC_CHIE_MASK;
	PORTE->PCR[SENSOR3_IN] &= ~PORT_PCR_MUX(7);
	PORTE->PCR[SENSOR3_IN] |= PORT_PCR_MUX(3);
	}
	//prescalar of 128, overflow Interrupt enable, start the timer
	TPM2->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7)  | TPM_SC_TOIE_MASK | TPM_SC_CPWMS(0);

	//set priority, clear pending interrupts, and enable interrupt
	NVIC_SetPriority(TPM2_IRQn, 2);
	NVIC_ClearPendingIRQ(TPM2_IRQn);
	NVIC_EnableIRQ(TPM2_IRQn);
}

//TPM2 Interrupt Handler
void TPM2_IRQHandler() {
	//out_on();
	//when overflow occurs, adjust the offset as the count will reset
	//to keep the track of last active sensor, a variable is used
	if(TPM2->STATUS & TPM_STATUS_TOF_MASK){
		if(last_sensor_flag==3){
		sensor3.ovflow_offset = 20000 - sensor3.prev_count;
		sensor3.prev_count = 0;
		}
		if(last_sensor_flag==2){
			sensor2.ovflow_offset = 20000 - sensor2.prev_count;
			sensor2.prev_count = 0;
		}
	}

	//if called for sensor 3 or both sensor 2 and 3
	if((test_sensor==3)||(use_both==1)){
		//when the capture occurs, take count and store this value for next cycle
		if(TPM2->STATUS & TPM_STATUS_CH1F_MASK) {
		last_sensor_flag = 3;
		sensor3.last_ovf_count = TPM2->CONTROLS[1].CnV;
		sensor3.count = TPM2->CONTROLS[1].CnV - sensor3.prev_count + sensor3.ovflow_offset;
		sensor3.prev_count = TPM2->CONTROLS[1].CnV;
		//trigger the sensor for next capture
		GPIOA->PSOR |= 1<<SENSOR3_TRIG;
		delay(10);
		GPIOA->PCOR |= 1<<SENSOR3_TRIG;
		sensor3.ovflow_offset = 0;
	}
	}
	//if called for sensor 2 or both 2 and 3
	if((test_sensor==2)||(use_both==1)){
		//when the capture occurs, take count and store this value for next cycle
		if(TPM2->STATUS & TPM_STATUS_CH0F_MASK){
		last_sensor_flag = 2;
		sensor2.last_ovf_count = TPM2->CONTROLS[0].CnV;
		sensor2.count = TPM2->CONTROLS[0].CnV - sensor2.prev_count + sensor2.ovflow_offset;
		sensor2.prev_count = TPM2->CONTROLS[0].CnV;
		//trigger the sensor for next capture
		GPIOA->PSOR |= 1<<SENSOR2_TRIG;
			delay(10);
		GPIOA->PCOR |= 1<<SENSOR2_TRIG;
		sensor2.ovflow_offset = 0;
		}
	}
	//Reset all the flags
	TPM2->STATUS |=  TPM_STATUS_TOF_MASK | TPM_STATUS_CH0F_MASK | TPM_STATUS_CH1F_MASK;
	//out_off;
}


