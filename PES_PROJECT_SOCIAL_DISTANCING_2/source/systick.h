#include "stdint.h"

typedef uint32_t ticktime_t;

//Systick timer initialization for 1 us resolution at 3Mhz external frequency
void systick_init();

//interrupt handler
void SysTick_Handler();

//resets the time to 0
void reset_time();

//return current time
ticktime_t get_time();

//produces the delay in microseconds
//takes number of microseconds to be delayed as argument
//returns void
void delay(ticktime_t);


