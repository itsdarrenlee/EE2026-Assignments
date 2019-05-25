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
