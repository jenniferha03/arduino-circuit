/*
Assignment: 1-bit ALU
Student Name: Jennifer (Khue) Ha
*/

//  Setup input pins
int buttonCin_pin = 12;   //  Stores value for the Carry in input
int buttonINVA_pin = 11;  //  Stores value for the ENB input
int buttonA_pin = 10;     //  Stores value for the ENA input
int buttonENA_pin = 9;    //  Stores value for the INVA input
int buttonB_pin = 8;      //  Stores value for the ENA input
int buttonENB_pin = 7;    //  Stores value for the ENA input
int buttonF0_pin = 6;     //  Stores value for the F1 input
int buttonF1_pin = 5;     //  Stores value for the F0 input

//  Setup output pins
int Output_Pin = 4;   //  Represents the 1-bit Output
int CarryOutPin = 3;  // Represents the 1-bit Carry out output


//  Temporary variables
int Cin;    // 1 bit input value for Carry in
int INVA;   // 1 bit input value for INVA
int A;      // 1 bit input value for A
int ENA;    // 1 bit input value for ENA
int B;      // 1 bit input value for B
int ENB;    // 1 bit input value for ENB
int F0;     // 1 bit input value for F0
int F1;     // 1 bit input value for F1
int Output; // 1-bit Output
int Cout01; // First input value of Cout - Carry out 01
int Cout02; // Second input value of Cout - Carry out 02
int Cout;   // 1-bit output value Carry out
int input1; // The first variable for INVA, ENA, A input
int input2; // The first variable for ENB, B input
int Sum;    // Sum of 1-bit full Adder
int a0;     // First input value of Output
int a1;     // Second input value of Output
int a2;     // Thrid input value of Output

void setup() 
{
  //  Tie input variables to board pins
  pinMode(buttonCin_pin, INPUT_PULLUP);
  pinMode(buttonINVA_pin, INPUT_PULLUP); 
  pinMode(buttonA_pin, INPUT_PULLUP);
  pinMode(buttonENA_pin, INPUT_PULLUP);
  pinMode(buttonB_pin, INPUT_PULLUP); 
  pinMode(buttonENB_pin, INPUT_PULLUP);
  pinMode(buttonENB_pin, INPUT_PULLUP);
  pinMode(buttonF0_pin, INPUT_PULLUP);
  pinMode(buttonF1_pin, INPUT_PULLUP);

  //  Tie output variables to board pins
  pinMode(Output_Pin, OUTPUT);
  pinMode(CarryOutPin, OUTPUT);
}

void loop() 
{
  //  Read 8 inputs
  Cin = digitalRead(buttonCin_pin);
  INVA = digitalRead(buttonINVA_pin);
  A = digitalRead(buttonA_pin);
  ENA = digitalRead(buttonENA_pin);
  B = digitalRead(buttonB_pin);
  ENB = digitalRead(buttonENB_pin);
  F0 = digitalRead(buttonF0_pin);
  F1 = digitalRead(buttonF1_pin);
  

  //  1. 1-bit ALU inputs
  /* 
  After inputing A and ENA to the AND gate operation, the output which represents as input1 and the INVA input value 
  go to the next XOR operation. The output is 0 when INVA and AND gate values are similar and 1 when its input value
  are different. The output of this XOR gate will become the first input for the Logical Unit.

  At the same time, the inputs of B and ENB represents the input2, as an AND of inputs. input2 is 1 when both B and 
  ENB are all 1s. In other cases, input2 is 0.

  input1 will be the input for the Logical Unit AND gate, OR gate. Also, input1 represents as the second input for 
  the XOR operation and one of the inputs for Cout01 AND operation of the 1-bit Full Adder.

  input2 will be the input for the Logical Unit AND gate, OR gate, and the inverter. Also, input2 represents as the 
  first input for the XOR operation and one of the inputs for Cout01 AND operation of the 1-bit Full Adder.
  */
  input1 = (A & ENA) ^ INVA;
  input2 = (B & ENB);


  //  2. Decoder 
  //  Decoder has 2 input F0 and F1. Decoder has 4 AND gates D0, D1, D2, D3. F0 and F1 are the inputs of 4 gates. 

  /* D0:
  D0 inputs are the negation of both F0 and F1. The output is only 1 when both F0 anf F1 are 0s. The outputs for 
  the rest cases are 0s. D0 is the second output of the first AND operation which is a0.
  */
  !F0 & !F1;

  /* D1:
  D1 inputs are the negation of F0 only. The output is only 1 when F0 is 0 and F1 is 1. The outputs for the rest
  cases are 0s. D1 is the second output of the first AND operation which is a1.
  */
  !F0 & F1;

  /* D2:
  D2 inputs are the negation of F1 only. The output is only 1 when F0 is 1 and F1 is 0. The outputs for the rest
  cases are 0s. D2 is the second output of the first AND operation which is a2.
  */
  F0 & !F1;

  /* D3:
  D3 inputs are F0 and F1. The output is only 1 when both F0 anf F1 are 1s. The outputs for the rest cases are 0s.
  D3 is the one of the inputs of Cout01, Cout02, and Sum.
  */
  F0 & F1;


  //  3. Logical Unit 
  //  AB (AND Gate) is the operation of input1 and input2. It is next the first input of the first AND operation which is a0.
  input1 ^ input2;
  //  A+B (OR Gate) is the operation of input1 and input2. It is next the first input of the second AND operation which is a1.
  input1 | input2;
  //  Not B (Inverter) is the operation of input2 only. It is next the first input of the third AND operation which is a2.
  !input2;

  //  a0 - the first AND operation has AB and D0 as its inputs. The output then will be the input of the ALU's first output.
  a0 = (input1 & input2) & (!F0 & !F1);
  //  a1 - the second AND operation has A+B and D1 as its inputs. The output then will be the input of the ALU's second output.
  a1 = (input1 | input2) & (!F0 & F1);
  //  a2 - the second AND operation has !B and D2 as its inputs. The output then will be the input of the ALU's third output.
  a2 = !input2 & (F0 & !F1);

  //  4. 1-bit Full Adder
  /* 
  When summing input1, input2, Cin, the Sum receives them and D3 as an inputs and represents as an AND operation. 
  
  Cout01 represent as an AND gate has D3, input1, and input2 as the inputs. The output of Cout01 then is the 
  first input of the Carry Out (Cout). 

  Cout02 represent as an AND gate has D3, the sum of input1 and input2, and the Carry In (Cin) as the inputs. 
  The output of Cout01 then is the second input of the Carry Out (Cout). 
  */
  Sum = ((input2 ^ input1) ^ Cin) & (F0 & F1); 
  Cout01 = (F0 & F1) & input1 & input2;
  Cout02 = (F0 & F1) & (input2 ^ input1) & Cin;


  //  5. 1-bit ALU
  /* Carry Out output of 1-bit ALU:
  The Carry Out (Cout) represents as an OR operation of Cout01 and Cout02. The Carry Out output is 0 and the LED is off 
  when only both Cout01 and Cout02 values are 0s. In the rest cases, its output is 1 and the LED is on. 
  */
  Cout = Cout01 | Cout02;

  /* The Output of the ALU:
  The Output represents as an OR operation of a0, a1, a2, and Sum. The Output is 0 and the LED is off when only
  all four a0, a1, a2, and Sum values are 0s. In the rest cases, its output is 1 and the LED is on. 
  */
  Output = a0 | a1 | a2 | Sum;


  //  Write 2 outputs
  digitalWrite(Output_Pin, Output); //  Write output, Output, to the Output_Pin to light up the Output LED
  digitalWrite(CarryOutPin, Cout);  //  Write carry out output, Cout, to the CarryOutPin to light up the Carry Out LED
}

/*
Bit-wise operators
c = a & b ; AND
c = a | b ; OR
c = a ^ b ; XOR
c = !a ;   NOT
*/
