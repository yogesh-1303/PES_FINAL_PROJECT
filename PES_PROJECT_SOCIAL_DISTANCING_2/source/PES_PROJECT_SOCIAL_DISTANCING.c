/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    PES_PROJECT_SOCIAL_DISTANCING.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <TPM_sensors.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "testing.h"
#include "systick.h"
#include "PWM_buzzer.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */


extern int test_sensor, use_both;
extern sensor sensor1, sensor2, sensor3;
int main(void) {


  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    //initilialization of GPIOs used (including sensors),
    //systick and PWM
    GPIO_init();
    systick_init();
    PWM_init();

    //tests the buzzer by playint it once from high to low sound and vice versa
    test_buzzer();

    //thses two variables are used to test the working of sensors throughout the coding
    //when test_sensor is 2, SENSOR 2 is tested (initialized and then IRQ handling)
    //when test sensor is 3,  SENSOR 2 is tested (initialized and then IRQ handling)
    //when use_both is 1, both are initilized irrespective of the value of test_sensor
    test_sensor=2;
    use_both=1;

    //trigger the sensors by giving a 10 us pulse (note: the pin used is active high)
    GPIOA->PSOR |= 1<<SENSOR2_TRIG | 1<<SENSOR3_TRIG | 1<<SENSOR1_TRIG;
    delay(10);
    GPIOA->PCOR |= 1<<SENSOR2_TRIG | 1<<SENSOR3_TRIG | 1<<SENSOR1_TRIG;

    //TPM1 and TPM2 initialization
    tpm2_init();
    tpm1_init();

    while(1) {
    	//calculate the distance and buzzer intensity according to the distance of a body from sensors
    	buzzer_n_distance();
       printf("\r\ndistance S2=%f\t , distance S3=%f\t, distance S1=%f  cm", sensor2.distance, sensor3.distance, sensor1.distance);
       	 // test_input(PIN_IN);
    }
    return 0 ;
}
