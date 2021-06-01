#include <stdio.h>
#include "MKL25Z4.h"
#include "testing.h"
#include "systick.h"
#include "PWM_buzzer.h"

//initializes all the GPIOs for testing and working
//takes and returns void
void GPIO_init(){
	//provide clock to portA
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//used for testing with LED
	PORTA->PCR[LED_PIN_OUT] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[LED_PIN_OUT] |= PORT_PCR_MUX(1);

	//set MUX value to 1 for GPIO
	PORTA->PCR[SENSOR1_TRIG] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SENSOR1_TRIG] |= PORT_PCR_MUX(1);

	PORTA->PCR[PIN_IN] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[PIN_IN] |= PORT_PCR_MUX(1);
	PORTA->PCR[PIN_IN] |= PORT_PCR_PE_MASK | PORT_PCR_PS(0);


	//set direction
	PTA->PDDR &= ~PIN_IN_MASK;
	PTA->PDDR |= LED_PIN_OUT_MASK;
	PTA->PDDR |= 1<<SENSOR1_TRIG;
}

//turns the signal(led) off (used in active high)
void out_off(){
	GPIOA->PCOR |= LED_PIN_OUT_MASK;
}

//turns the signal(led) on (used in active high)
void out_on(){
	GPIOA->PSOR |= LED_PIN_OUT_MASK;
}

//A way of testing the input detection using LED, for a continuous pulse
void test_input(int pin){
	ticktime_t pulse_period=0;
	reset_time();
	while(PTA->PDIR & PIN_IN_MASK){
		out_off();
	}
	pulse_period = get_time();
	//else
	ticktime_t dist = 340 * pulse_period/2;
	printf("\r\ndistance = %u", dist);
		out_on();
}

//testing buzzer by playing it from low to high and then high to low intensity
void test_buzzer(){
	uint32_t i;
	for(uint32_t i=0; i<PWM_PERIOD; i++){
	TPM0->CONTROLS[4].CnV =  i;
	delay(10);
	}
	for(i=PWM_PERIOD-1; i>0; i--){
	TPM0->CONTROLS[4].CnV = i;
	delay(10);
	}
}

