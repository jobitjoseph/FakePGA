#include "pico/stdlib.h"
#include "Vtop.h"
#include "io.h"

/////////////////////////////
/// No need to edit these
extern Vtop *top;
extern inputMapping ins[];
extern outputMapping outs[];
/////////////////////////////

////////////////////////////////////////////////////
///Below is what you should edit to suit your design
////////////////////////////////////////////////////

// Clock frequency in Hz
int freq = 5000;

// Number of inputs
uint NUM_INPUTS = 2;

// Number of outputs
uint NUM_OUTPUTS = 1;

// Input mapping
void mapInputs()
{
    ins[0] = {TOP i_s, 14, PULLUP}; // Maps port i_s to GPIO14 and pulls it up
    ins[1] = {TOP i_r, 15, PULLUP}; // Maps port i_r to GPIO15 and pulls it up
}

// Output mapping
void mapOutputs()
{
    outs[0] = {TOP o_led, PICO_DEFAULT_LED_PIN}; // Maps port o_led to the default LED pin
}
