// PROJECT FILES
// 8 BIT 2'S COMPLEMENT SUBTRACTOR ON BASYS3
module my_full_subtractor_8bit(A,B,Cin,S,Cout);
    parameter N = 8; // bit width
   
    input [N-1:0] A, B;
    input Cin; // carry adder output at LSB
    output [N-1:0] S;
    output Cout; // carry output at MSB
    
    wire [N-1:0] C; // connect 8 bit full adder + 8 bit adder (with bits forced to 1)
    
    my_full_adder_8bit fa0 (
    .A(A[N-1:0]),
    .B(~B[N-1:0]),
    .Cin(0),
    .S(C[N-1:0]),
    .Cout());
    
    my_full_adder_8bit fa1 (
    .A(C[N-1:0]),
    .B(1),
    .Cin(0),
    .S(S[N-1:0]),
    .Cout(Cout));   
    
endmodule

// 8 BIT CARRY ADDER ON BASYS3
module my_full_adder_8bit(A,B,Cin,S,Cout); //8 bit carry adder
    parameter N = 8; // parameterized bit width
    
    input [7:0]A, B;
    input Cin; // Cin is the carry adder bit
    output [N-1:0] S;
    output Cout; // Cout is the carry adder output at MSB
    wire [N:0] C; // Carry inputs of all full adders + carry output of last one
    
    assign C[0] = Cin;
    assign Cout = C[N];
    
    genvar i; // temp variable used in for loop
        generate for(i=0; i<N; i=i+1) begin
            my_full_adder fa (.S(S[i]),.Cout(C[i+1]),.A(A[i]),.B(B[i]),.Cin(C[i]));
            end
        endgenerate
endmodule

// FULL ADDER ON BASYS3
module my_full_adder(
    input A,
    input B,
    input Cin,
    output S,
    output Cout
    );
    
    assign S = A ^ B ^ Cin;
    assign Cout = (A & B) | Cin & (A ^ B);
    
endmodule

// SIMULATION FILE FOR FULL SUBTRACTOR
module test_my_full_subtractor_8bit(

    );
    
    // simulation inputs
    reg [7:0] A;
    reg [7:0] B;
    reg Cin;
    
    // simulation outputs
    wire [7:0] S;
    wire Cout;
    
    //integer i;
    
    // instantiation of module to be simulated 
    my_full_subtractor_8bit dut(A, B, Cin, S, Cout);
    
    // stimuli
    initial begin
        A = 8'b11111111; // test case 1
        B = 8'b00000000; 
        Cin = 1'b0; #100;
        
        A = 8'b00000000; // test case 2
        B = 8'b11111111;
        Cin = 1'b0; #100;
        
        A = 8'b11111111; // test case 3
        B = 8'b11110000;
        Cin = 1'b0; #100;
        
        A = 8'b11111111; // test case 4
        B = 8'b00001111;
        Cin = 1'b0; #100;
        
        A = 8'b10101010; // test case 5
        B = 8'b01010101;
        Cin = 1'b0; #100;
        
        A = 8'b01010101; // test case 6
        B = 8'b10101010;
        Cin = 1'b0; #100;
        
        A = 8'b11001100; // test case 7
        B = 8'b00110011;
        Cin = 1'b0; #100;
        
        A = 8'b00110011; // test case 8
        B = 8'b11001100;
        Cin = 1'b0; #100;
        
        A = 8'b10001000; // test case 9
        B = 8'b10101010;
        Cin = 1'b0; #100;
        
        A = 8'b01100110; // test case 10
        B = 8'b10101011;
        Cin = 1'b0; #100;
    end
        
endmodule

// SIMULATION FOR FULL ADDER
module my_full_adder_sim(

    );
    
    // simulation inputs
    reg A;
    reg B;
    reg Cin;
    
    // simulation outputs
    wire Cout;
    wire S;
    
    // instantiation of module to be simulated 
    my_full_adder dut(A, B, Cin, S, Cout);
    
    // stimuli
    initial begin
        A = 0; B = 0; Cin = 0; #10;
        A = 0; B = 0; Cin = 1; #10;
        A = 0; B = 1; Cin = 0; #10;
        A = 0; B = 1; Cin = 1; #10;
        A = 1; B = 0; Cin = 0; #10;
        A = 1; B = 0; Cin = 1; #10;
        A = 1; B = 1; Cin = 0; #10;
        A = 1; B = 1; Cin = 1; #10;
     end
     
endmodule

// SIMULATION FILE FOR 8 BIT FULL ADDER TESTING
module test_my_full_adder_8bit(

    );
    
    // simulation inputs
    reg [7:0] A;
    reg [7:0] B;
    reg Cin;
    
    // simulation outputs
    wire [7:0] S;
    wire Cout;
    
    //integer i;
    
    // instantiation of module to be simulated 
    my_full_adder_8bit dut(A, B, Cin, S, Cout);
    
    // stimuli
    initial begin
        A = 8'b00000000; B = 8'b00000000; Cin = 1'b0; #10;
        A = 8'b11111111; B = 8'b11111111; Cin = 1'b0; #10;
    end
        
endmodule
