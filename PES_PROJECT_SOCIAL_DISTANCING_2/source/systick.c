#include <stdio.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include "core_cm0plus.h"
#include "systick.h"
#include "testing.h"

ticktime_t tick = 0;
ticktime_t temp = 0;
//extern uint16_t buffer[STEPS];
//extern uint16_t samples;

//Systick timer initialization
void systick_init()
{
	SysTick->LOAD = (48L/16);		//1 us resolution

	SysTick->VAL = 0;							//Initial value of counter
	SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk); 		//frequency = 3Mhz (ext clock)
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; //enable interrupt
	NVIC_ClearPendingIRQ(SysTick_IRQn); //for 10us res
	NVIC_SetPriority (SysTick_IRQn, 1);
}

//interrupt handler
int a;
void SysTick_Handler()
{
	if(tick==6)
		a = 5;
	tick++;
}

//resets the time
void reset_time(){
	tick=0;
}

//returns the current time
ticktime_t get_time(){
	return tick;
}

//produces the delay in microseconds
//takes number of microseconds to be delayed as argument
//returns void
void delay(ticktime_t us){
	reset_time();
	while(tick!=us){
		__asm volatile ("nop");
	}

}



