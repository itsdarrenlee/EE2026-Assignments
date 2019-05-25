// Assignment 4
// Task A

// slow clock 3hz
module slow_clock(
    input clock,
    output reg slow_clock_gen
    );
    
    reg[21:0] count = 22'b0; // defining an internal counter 3hz
        
    initial begin
        slow_clock_gen = 0;
    end
    
    always @ (posedge clock) begin
        count <= count + 1;
        slow_clock_gen <= (count == 0)? ~slow_clock_gen: slow_clock_gen;
    end
endmodule

// left pulse of PB (top level)
module left_pulse(
    input clock,
    input left_pb,
    output BTNL,
    output left_q
    );
    
    wire X1, X2;
    
    // instantiate 2 D flip flops
    my_dff DFF1 (clock, left_pb, X1);
    my_dff DFF2 (clock, X1, X2);
    
    assign left_q = X1;
    assign BTNL = X1 & ~X2;
    
endmodule

// right pulse of PB (top level)
module right_pulse(
    input clock,
    input right_pb,
    output BTNR,
    output right_q
    );
    
    wire X1, X2;
    
    // instantiate 2 D flip flops
    my_dff DFF3 (clock, right_pb, X1);
    my_dff DFF4 (clock, X1, X2);
    
    assign right_q = X1;
    assign BTNR = X1 & ~X2;
    
endmodule

// d flip flop module for pulse
module my_dff(
    input clock,
    input D,
    output reg Q
    );
    
    always @ (posedge clock) begin
        Q <= D;
    end
endmodule

// counter module
module counter_module(
    input slow_clock_gen,
    input BTNL,
    input BTNR,
    input left_q,
    input right_q,
    output [2:0] LED,
    output left_LED,
    output right_LED
    );
    
    // 2 corner LEDs always switched on
    assign left_LED = 1;
    assign right_LED = 1;
    
    // count for LED display
    reg [2:0] count = 3'b010;
    
    // main sequential logic
    always @ (posedge slow_clock_gen) 
    begin 
        if (BTNR == 1)
        begin
            count <= (count != 3'b001) & (left_q == 0) ? (count >> 1) : count;                      
        end
        
        if (BTNL == 1)
        begin
            count <= (count != 3'b100) & (right_q == 0) ? (count << 1) : count;
        end              
    end
    
    assign LED = count;
        
endmodule

// Task B TOP LEVEL
module task_B(
    // initial clock
    input clock,
    
    // task A inputs
    input left_pb,
    input right_pb,
    
    // task A outputs
    output [2:0] LED,
    output left_LED,
    output right_LED,
    
    // seven seg outputs
    output [3:0] AN,
    output [7:0] CA    
    );
    
    // defining wires
    wire mux_out;
    wire clock_F1_gen, clock_F2_gen, clock_F3_gen;
    wire [2:0] count;
    
    assign count = LED;
    
    // clock speed generators
    clock_F1 task_b1a(clock, clock_F1_gen); // 0.1863hz
    clock_F2 task_b1b(clock, clock_F2_gen); // 5.9616hz
    clock_F3 task_b1c(clock, clock_F3_gen); // 1526.1696hz
    
    // task A
    task_A task_b2(clock, left_pb, right_pb, LED, left_LED, right_LED);
    
    // 3 to 1 mux
    three_to_one_mux task_b3(clock_F1_gen, clock_F2_gen, clock_F3_gen,
    count, mux_out);
    
    // seven seg module
    seven_seg_module task_b4(mux_out, AN, CA);
       
endmodule

// clock F1
module clock_F1(
    input clock,
    output reg clock_F1_gen
    );
    
    reg[27:0] count = 28'b0; // defining an internal counter 3hz
        
    initial begin
        clock_F1_gen = 0;
    end
    
    always @ (posedge clock) begin
        count <= count + 1;
        clock_F1_gen <= (count == 0)? ~clock_F1_gen: clock_F1_gen;
    end
endmodule

// clock F2
module clock_F2(
    input clock,
    output reg clock_F2_gen
    );
    
    reg[22:0] count = 23'b0; // defining an internal counter 3hz
        
    initial begin
        clock_F2_gen = 0;
    end
    
    always @ (posedge clock) begin
        count <= count + 1;
        clock_F2_gen <= (count == 0)? ~clock_F2_gen: clock_F2_gen;
    end
endmodule

// clock F3
module clock_F3(
    input clock,
    output reg clock_F3_gen
    );
    
    reg[14:0] count = 15'b0; // defining an internal counter 3hz
        
    initial begin
        clock_F3_gen = 0;
    end
    
    always @ (posedge clock) begin
        count <= count + 1;
        clock_F3_gen <= (count == 0)? ~clock_F3_gen: clock_F3_gen;
    end
endmodule

// 3 to 1 multiplexer
module three_to_one_mux(
    clock_F1_gen,
    clock_F2_gen,
    clock_F3_gen,
    count,
    mux_out
    );
    
    // input
    input clock_F1_gen, clock_F2_gen, clock_F3_gen;
    input [2:0] count;
    
    // outputs
    output mux_out;
    
    // internal variables
    reg mux_out;

    // main
    always @ (clock_F1_gen, clock_F2_gen, clock_F3_gen)
    begin: MUX
        if (count == 3'b010) 
        begin
            mux_out = clock_F2_gen;
        end 
        else if (count == 3'b100) 
        begin
            mux_out = clock_F1_gen;
        end
        else
        begin
            mux_out = clock_F3_gen;
        end
    end
endmodule

// seven segment module
module seven_seg_module(
    input mux_out, // final clock value 
    output reg [3:0] AN, // anodes
    output reg [7:0] CA // cathodes
    );
    
    // declaring 8 bit array  for refresh signal
    wire [7:0] memory [3:0];
    
    // setting up 4 bit counter for loop
    reg [3:0] count = 4'b0000; 
    
    // assigning array for anodes
    wire [3:0] arr_a [3:0];
    
    // filling up memory array with values
    assign memory[0] = 8'b11110001; // display L
    assign memory[1] = 8'b10000001; // display O
    assign memory[2] = 8'b10110001; // display C
    assign memory[3] = 8'b11001000; // display H
    
    assign arr_a[0] = 4'b0111; // first anode
    assign arr_a[1] = 4'b1011; // second anode
    assign arr_a[2] = 4'b1101; // third anode
    assign arr_a[3] = 4'b1110; // fourth anode
    
    always @ (posedge mux_out) 
    begin      
        AN <= arr_a[count];
        CA <= memory[count];
        
        count <= (count == 2'b11) ? 2'b00 : (count + 1);
    end   
    
endmodule
