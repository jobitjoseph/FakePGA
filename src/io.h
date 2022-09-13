#ifndef _IO_H
#define _IO_H

#include "pico/stdlib.h"
#include "Vtop.h"

// hack which makes editing the I/O mappings a bit nicer
#define TOP &top->

#define NOPULL 0
#define PULLUP 1
#define PULLDN 2

struct inputMapping
{
    CData *label;
    uint pin;
    uint pull;
};

struct outputMapping
{
    CData *label;
    uint pin;
};

void mapInputs();
void mapOutputs();

#endif