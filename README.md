# FakePGA
Simulating Verilog designs on a microcontroller

## What does it do?
This project aims to simulate Verilog HDL designs on a Raspberry Pi Pico (or any other RP2040-based board). It achieves this by using [Verilator](https://www.veripool.org/verilator/) to compile the RTL into a cycle-accurate C++ model of your design which can then be executed on the microcontroller. This allows you to access the signals of the simulated design through the GPIO pins of the board, which gives a more hands-on experience than simulating on a computer. It is many orders of magnitude slower than a real FPGA (max clock speed is 5kHz, and it goes down as the complexity of your design increases), but it can still be used as an educational tool. In terms of user experience, it feels like using a slower FPGA (at least for simpler designs), hence the name of the project: _FakePGA_.

## What do I need in order to use it?
Hardware-wise, you're going to need an RP2040-based dev board. The included Verilog example makes use of the on-board LED and two pushbuttons. This example blinks the LED, stopping and starting the blinking when the buttons are pressed.

Software-wise, you're going to need a Linux system to compile on. This could work on Windows, but I only tested it with Ubuntu (running in WSL). You need to have the [pico-sdk](https://github.com/raspberrypi/pico-sdk) installed and working, as well as Verilator.

After cloning this repository, you'll need to set the path of the Verilator library sources in the [CMakeLists.txt](CMakeLists.txt) file, on the 12th line. Out of the box, it is set to the default path for the Ubuntu install of Verilator. 

## How do I use it?
The Verilog design files reside in the _verilog_ folder. The top module resides in the [top.v](verilog/top.v) file and it **must** be named _top_. It **must** have an input port named *i_clk*, which coresponds to the clock source for the design, no matter if it's used or not.

The simulation is configured in the [src/io.cpp](src/io.cpp) file. This is the only C++ source file you'll have to edit. The input clock frequency can be set from there. Just like when using an actual FPGA, you'll need to map the ports of your design to real pins on the device.
```cpp
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
```

Before building the project for the first time, or after deleting the _build_ folder, you must run the _preBuild.sh_ script, in order to create some dummy files that the build system expects to exist. Afterwards, you can simply build it with _CMake_:

```
cd build
cmake ..
make
```


