#define PIN_IN  12U
#define SENSOR1_TRIG 4U
#define LED_PIN_OUT 5U
#define LED_PIN_OUT_MASK  (1<<LED_PIN_OUT)
#define PIN_IN_MASK   (1<<PIN_IN)

//initializes all the GPIOs for testing and working
//takes and returns void
void GPIO_init();

//turns the signal(led) off (used in active high)
void out_on();

//turns the signal(led) on (used in active high)
void out_off();

//A way of testing the input detection using LED, for a continuous pulse
//the function tells whether the input has been received or not by switching LED logic
void test_input(int);

//testing buzzer by playing it from low to high and then high to low intensity
void test_buzzer();


