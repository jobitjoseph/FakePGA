module blinker (input i_clk, output o_led);

reg [31:0] counter;
reg state;

assign o_led = state;

always @ (posedge i_clk) begin
    counter <= counter + 1;
    state <= counter[9]; //
end

endmodule 
