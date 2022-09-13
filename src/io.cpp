#include "pico/stdlib.h"
#include "Vtop.h"
#include "io.h"
IO_CONFIG

/* ///////////////////////
Simulator I/O configuration
*/ ///////////////////////

// Clock frequency in Hz
CLOCK_FREQ 5000;

// Input mapping
INPUTS
{
    ADD_IN{TOP i_s, 14, PULLUP}; // Maps port i_s to GPIO14 and pulls it up
    ADD_IN{TOP i_r, 15, PULLUP}; // Maps port i_r to GPIO15 and pulls it up
}

// Output mapping
OUTPUTS
{
    ADD_OUT{TOP o_led, PICO_DEFAULT_LED_PIN}; // Maps port o_led to the default LED pin
}
