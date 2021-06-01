#include "systick.h"

#define SENSOR1_IN 20
#define SENSOR2_IN 22
#define SENSOR3_IN 23
#define SENSOR2_TRIG 2
#define SENSOR3_TRIG 5

//structure conatining all the needed variables for the sensor management and working
typedef struct SENSOR_VARS{
	ticktime_t count, prev_count;
	ticktime_t ovflow_offset, last_ovf_count;
	float distance;
}sensor;

//tpm1 initializtion function: works on Input capture mode on channel 0
//used for capturing Input from Sensor 1
//works using channel and overflow interrupts
//takes and returns void
void tpm1_init();

//tpm1 initializtion function: works on Input capture mode on channels 0 and 1
//used for capturing Input from Sensors 2 and 3
//works using channel and overflow interrupts
//takes and returns void
void tpm2_init();


