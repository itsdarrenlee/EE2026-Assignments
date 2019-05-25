// structural level modelling of seven segment flasher with 'hello darren'
module assignment_3(
    input clock,
    input speed_sw,
    input master_sw,
    input direction_sw,
    output [3:0] AN,
    output [7:0] CA
    );
    
    wire new_clock, new_clock_2, mux_1_out, mux_2_out;
    
    // structural modelling of F1 clock module
    my_clock_gen dut1(clock, new_clock);
    
    // structural modelling of F2 clock module
    my_clock_gen_2 dut2(clock, new_clock_2);
    
    // structural modelling of mux 1 module
    mux_1 dut3(new_clock, new_clock_2, speed_sw, mux_1_out);
    
    // structural modelling of mux 2 module
    mux_2 dut4(mux_1_out, master_sw, mux_2_out);
    
    // structural modelling of seven seg display module
    seven_seg_display dut5(mux_2_out, direction_sw, AN, CA);
    
endmodule

// basic clock generator for F1 0.75hz
module my_clock_gen(
    input clock,
    output reg new_clock
    );
    
    reg[25:0] count = 26'b0; // defining an internal counter
    
    initial begin
        new_clock = 0;
    end
    
    always @ (posedge clock) begin
        count <= count + 1;
        new_clock <= (count == 0)? ~new_clock: new_clock;
    end
endmodule

// basic clock generator for F2 12hz
module my_clock_gen_2(
    input clock,
    output reg new_clock_2
    );
    
    reg[23:0] count = 24'b0; // defining an internal counter
    
    initial begin
        new_clock_2 = 0;
    end
    
    always @ (posedge clock) begin
        count <= count + 1;
        new_clock_2 <= (count == 0)? ~new_clock_2: new_clock_2;
    end
endmodule

// mux to toggle between both clock generators
module mux_1(
    my_clock_gen,
    my_clock_gen_2,
    speed_sw,
    mux_1_out
    );
    // input
    input my_clock_gen, my_clock_gen_2, speed_sw;
    
    // outputs
    output mux_1_out;
    
    // internal variables
    reg mux_1_out;

    // main
    always @ (my_clock_gen or my_clock_gen_2 or speed_sw)
    begin: MUX
        if (speed_sw == 1'b0) begin
            mux_1_out = my_clock_gen;
        end else begin
            mux_1_out = my_clock_gen_2;
        end
    end
endmodule

// mux to suspend animation of 7 segment flasher
module mux_2(
    mux_1_out,
    master_sw,
    mux_2_out
    );
    // input
    input mux_1_out, master_sw;
    
    // outputs
    output mux_2_out;
    
    // internal variables
    reg mux_2_out;

    // main
    always @ (mux_1_out or master_sw)
    begin: MUX
        if (master_sw == 1'b0) begin
            mux_2_out = mux_1_out;
        end else begin
            mux_2_out = 1'b0;
        end
    end
endmodule

// seven segment flashing module with forward and reverse functions
module seven_seg_display(
    input mux_2_out, // final clock value
    input direction_sw, 
    output wire [3:0] AN, // anodes
    output reg [7:0] CA // cathodes
    );
    
    // declaring 13 * 8 bit array  for refresh signal
    wire [7:0] memory [0:12]; 
    
    // setting up 4 bit counter for loop
    reg [3:0] count; 
    
    // filling up memory array with values
    assign memory[0] = 8'b11001000; // display H
    assign memory[1] = 8'b10110000; // display E
    assign memory[2] = 8'b11110001; // display L
    assign memory[3] = 8'b11110001; // display L
    assign memory[4] = 8'b10000001; // display O
    assign memory[5] = 8'b11111110; // display -
    assign memory[6] = 8'b11000010; // display d
    assign memory[7] = 8'b10001000; // display A
    assign memory[8] = 8'b11111010; // display r
    assign memory[9] = 8'b11111010; // display r
    assign memory[10] = 8'b10110000; // display E
    assign memory[11] = 8'b11101010; // display n
    assign memory[12] = 8'b01111111; // display .
    
    always @ (posedge mux_2_out) 
        begin 
            if (direction_sw == 0) // forward direction sequence
                begin
                    CA <= memory[count];
                    count <= (count == 4'b1101) ? 4'b0000 : (count + 1); // tenary conditional to increment the loop
                end
            else // reverse direction sequence
                begin
                    CA <= memory[count]; // sending signals to constraint from memory array
                    count <= (count == 4'b0000) ? 4'b1101: (count - 1); // tenary conditional to decrement the loop
                end
        end
    
    // anode
    assign AN = 4'b0100;
endmodule

// simulation file of an asynchronous clock gen (D flip flop)
module my_clock_gen_sim();

    // simulation inputs
    reg clock;
    
    // simulation outputs
    wire new_clock;
    
    // instantiation of the module to be simulated
    my_clock_gen dut(clock, new_clock);
    
    // simuli
    initial begin
        clock = 0;
    end
    
    always begin
        #5 clock = ~clock;
    end
endmodule
