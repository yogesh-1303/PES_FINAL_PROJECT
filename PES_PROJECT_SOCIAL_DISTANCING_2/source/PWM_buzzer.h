#define PWM_PERIOD 0xffff

//initializes PWM for for buzzer intensity on output compare mode of TPM0 channel 4
//takes and returns void
void PWM_init();

//Calculates the distance of the obstruction
//sets buzzer intensity
//prints minimum distance
//takes and returns void
void buzzer_n_distance();
