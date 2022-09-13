#ifndef _IO_H
#define _IO_H

#include "pico/stdlib.h"
#include "Vtop.h"

//macros which make io config file a bit nicer
#define INPUTS void mapInputs()
#define OUTPUTS void mapOutputs()

// macro which makes accessing top design easier
#define TOP &top->

// macro which makes addding inputs and outputs easier
#define ADD_IN ins[NUM_INPUTS++]=
#define ADD_OUT outs[NUM_OUTPUTS++]=

// macro which makes setting the clock freq a bit easier
#define CLOCK_FREQ int freq=

// Definitions for pin pull configs
#define NOPULL 0
#define PULLUP 1
#define PULLDN 2

// Input port mapping structure
struct inputMapping
{
    CData *label;
    uint pin;
    uint pull;
};

// Output port mapping structure
struct outputMapping
{
    CData *label;
    uint pin;
};

// I/O mapping functions
void mapInputs();
void mapOutputs();

#endif