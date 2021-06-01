#include <stdio.h>
#include "MKL25Z4.h"
#include <stdint.h>
#include <TPM_sensors.h>
#include "PWM_Buzzer.h"

#define BUZZER_PIN 8U   //buzzer is attached to PORTC pin 8

#define min(x,y) (((x)<(y))?(x):(y))
extern sensor sensor1, sensor2, sensor3;

//initializes PWM for for buzzer intensity on output compare mode of TPM0 channel 4
//takes and returns void
void PWM_init(){
	//providing clock to port c and TPM0 timer
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//set MUX to TPM0 channel 4
	PORTC->PCR[BUZZER_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[BUZZER_PIN] |= PORT_PCR_MUX(3);

	//select the clock of 48MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//MOD of full capacity, prescalar of 8
	TPM0->MOD = PWM_PERIOD-1;
	TPM0->SC = TPM_SC_PS(3);

	//toggle on compare match on channel 4 of TPM0 and set CnV
	TPM0->CONTROLS[4].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM0->CONTROLS[4].CnV = 0;

	//start the timer
	TPM0->SC |= TPM_SC_CMOD(1);
}

//Calculates the distance of the obstruction
//sets buzzer intensity
//prints minimum distance
//takes and returns void
void buzzer_n_distance(){
	uint32_t min_distance;
	//the formula for distance is (speed of sound * time taken by wave to travel back)/2
	//converted and solved for us time as input the below given formula gives the distance
	//40 is the offset value that is subtracted
    sensor2.distance = ((float) (sensor2.count) * (128))/ 48;
	sensor2.distance /= 58;
	sensor2.distance -= 40;
    sensor3.distance = ((float) (sensor3.count) * (128)) / 48;
    sensor3.distance /= 58;
    sensor3.distance -= 40;
    sensor1.distance = ((float) (sensor1.count) * (128)) / 48;
    sensor1.distance /= 58;
    sensor1.distance -= 40;
    //calculating the minimum distance of obstruction for the buzzer intensity
    min_distance = min(sensor1.distance, sensor2.distance);
    min_distance = min(min_distance, sensor3.distance);
    //setting buzzer intensity
    TPM0->CONTROLS[4].CnV = min(PWM_PERIOD-1,(min_distance*(PWM_PERIOD)/50));
    printf("\n\rminimum distance = %u", min_distance);
}


