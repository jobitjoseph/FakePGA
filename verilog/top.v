`include "sr_latch.v"
`include "blinker.v"

module top (
    input i_clk, 
    input i_s,
    input i_r,
    output o_led
    );

wire latchQ;
wire latchNotQ;
sr_latch myLatch(i_s, i_r, latchQ, latchNotQ);

wire blinkOut;
blinker myBlinker(i_clk, blinkOut);

assign o_led = blinkOut * latchQ;

endmodule 
