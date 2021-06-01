# PES_FINAL_PROJECT
Technologies Used:

Following Technologies have been used:

•	TPM Input capture and detailed configuration:

All the three timers TPM0,1 and 2 have ben used in the project. TPM1 is used for the input capture of sensor 1, TPM2, for the input capture of sensors 2 and 3, and TPM0 for PWM for buzzer operation.
TPM1 and 2 are made to work on interrupts.

•	PWM:

PWM is used for the variation in intensity of the buzzer with distance. Timer 0’s channel 4 is used for the purpose.

•	Systick:

Sysitck timer is used to keep track of the time and produce delays. It operates with the resolution of 1us.
•	Interrupts:

TPM1,2 and Systick, all three work on interrupts. In this project, this was one of the major challenge to synchronize the race conditions between the interrupts.

•	GPIOs:

GPIOs are used for testing and all other connections. The output to sensors is given through GPIO pins. The buzzer and LED tests are performed on GPIOs.


The Code:

The code consists of five .c and their corresponding .h files as follows:

PES_PROJECT_SOCIAL_DISTANCING.c: Contains the main function which calls the init functions.

PWM_buzzer.c: Contains PWM_init() function for the initialization of PWM with TPM0 on channel 4. This file also contains the buzzer_n_distance() function which calculates the distance of the obstacle from the sensor and also sets the buzzer intensity accordingly.

Systick.c: 

This file contains the initialization of systick timer at 1us resolution. The timer is used for all the timings in the project and producing delays. The API also has functions for retrieving current time, resetting the time, and delaying.

TPM_sensors:

this file is the crux of the project where main thing lies. The project contains initialization of the TPM1 and 2 timers for the input capture mode used for capture the input by sensors through interrupts. This file contains the interrupt handlers of the two timers. One timer is used for the input capture of sensor1 and the second is used for the input capture of sensors 2 and 3 on different channels.

Testing.c: 

This file contains the functions used during the progression of the code for testing purposes. Functions that help test the input and output through a pin. A GPIO init function is also present.

Apart from this, the TPM_sensors.h file contains the structure which where the variables used to manage the sensors are present.
