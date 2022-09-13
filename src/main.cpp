#include "pico/stdlib.h"
#include "Vtop.h"
#include "io.h"

// Design instance
Vtop *top;

// Clock signal
volatile CData clock;

// Clock frequency
extern uint freq;

// Number of inputs and outputs in the design
extern uint NUM_INPUTS;
extern uint NUM_OUTPUTS;

// Input and output mappings arrays
inputMapping ins[15];
outputMapping outs[15];

// Initialize input pins
void initInPins()
{
    for (int i = 0; i < NUM_INPUTS; i++)
    {
        gpio_init(ins[i].pin);
        gpio_set_dir(ins[i].pin, GPIO_IN);
        if (ins[i].pull == PULLUP)
            gpio_pull_up(ins[i].pin);
        else if (ins[i].pull == PULLDN)
            gpio_pull_down(ins[i].pin);
        else
            gpio_disable_pulls(ins[i].pin);
    }
}

// Initialize output pins
void initOutPins()
{
    for (int i = 0; i < NUM_OUTPUTS; i++)
    {
        gpio_init(outs[i].pin);
        gpio_set_dir(outs[i].pin, GPIO_OUT);
    }
}

// Read inputs
inline void readInputs()
{
    for (int i = 0; i < NUM_INPUTS; i++)
        *(ins[i].label) = gpio_get(ins[i].pin);
}

// Read outputs
inline void updateOutputs()
{
    for (int i = 0; i < NUM_OUTPUTS; i++)
        gpio_put(outs[i].pin, *(outs[i].label));
}

// Clock timer callback
static bool clockTimer_callback(struct repeating_timer *t)
{
    clock = !clock;
    return true;
}

int main()
{
    // Instantiate design
    top = new Vtop;

    // Map inputs and outputs to pins
    mapInputs();
    mapOutputs();

    // Initialize pins
    initInPins();
    initOutPins();

    // Create clock timer
    repeating_timer clockTimer;
    add_repeating_timer_us((1.0 / (2*freq)) * 1000000, clockTimer_callback, NULL, &clockTimer);

    // Main simulation loop
    while (true)
    {
        top->i_clk = clock;
        readInputs();
        top->eval();
        updateOutputs();
    }
}
