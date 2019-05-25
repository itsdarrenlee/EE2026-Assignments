// PROJECT FILE
module Darren_src_mod(
    input [9:0] SW,
    output [3:0] AN,
    output [7:0] CA
    );
    
    
    /* Program overview:
    
    Assigning anodes and cathodes of 7 seg LED to only activate according to prearranged
    configurations only if SW is flipped in correct order (using ? conditional operator). 
    When switches are released, they revert to non operational condition, i.e. 1111 for 
    anodes. Use of a bus (array) enables easy manipulation of switch, anode and cathode
    values w/o declaring many variables. */
    
    // anode is assigned with AN[3] on extreme left to AN[0] on extreme right
    assign AN=(SW==10'b1001010010)? 4'b1001:4'b1111;
    
    // cathode is assigned with with DP on extreme left to CA[0] on the extreme right
    assign CA=(SW==10'b1001010010)? 8'b10101111:8'b11111111;
endmodule



// SIMULATION FILE
module assign_one_mod_sim(

    );
    
    // simulation inputs
    reg SW;
    
    // simulation outputs
    wire AN;
    wire CA;
    
    // instantiation of the module to be simulated
    Darren_src_mod dut(SW, AN, CA);
    
    // stimuli
    initial begin
        SW=10'b1001010010;
    end
    
endmodule
