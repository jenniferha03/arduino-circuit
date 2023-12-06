/*
Assignment: 2-bit Full Adder
Student Name: Jennifer (Khue) Ha
*/

//  Setup input pins
int buttonCin_pin = 12;   //  Stores value for the Carry in input
int buttonA0_pin = 11;    //  Stores value for the A0 input
int buttonB0_pin = 10;    //  Stores value for the B0 input
int buttonA1_pin = 9;     //  Stores value for the A1 input
int buttonB1_pin = 8;     //  Stores value for the B1 input

//  Setup output pins
int Sum0_Pin = 5;     // Represents the 1-bit sum 0
int Sum1_Pin = 4;     // Represents the 1-bit sum 1
int CarryOutPin = 3;  // Represents the 1-bit output


//  Temporary variables
int ci;   // 1 bit input value for Carry in
int a0;   // 1 bit input value for A0
int b0;   // 1 bit input value for B0
int s0;   // Sum out 0 of 1-bit
int co0;  // 1-bit Carry out 0
int a1;   // 1 bit input value for A1
int b1;   // 1 bit input value for B1
int s1;   // Sum out 1 of 1-bit
int co1;  // 1-bit Carry out 1


void setup() 
{
  //  Tie input and output variables to board pins
  pinMode(buttonCin_pin, INPUT_PULLUP);
  pinMode(buttonA0_pin, INPUT_PULLUP); 
  pinMode(buttonB0_pin, INPUT_PULLUP);
  pinMode(Sum0_Pin, OUTPUT); 
  pinMode(buttonA1_pin, INPUT_PULLUP); 
  pinMode(buttonB1_pin, INPUT_PULLUP);
  pinMode(Sum1_Pin, OUTPUT);
  pinMode(CarryOutPin, OUTPUT);
}

void loop() 
{
  // Read inputs
  ci = digitalRead(buttonCin_pin);
  a0 = digitalRead(buttonA0_pin);
  b0 = digitalRead(buttonB0_pin);
  a1 = digitalRead(buttonA1_pin);
  b1 = digitalRead(buttonB1_pin);
  
  //  Summing 3 single bits a0, b0, and the Carry in and assigns the output to Sum 0
  s0 = (a0 ^ b0) ^ ci;

  /* 
  When summing 3 single bits, in the first 1-bit adder, the carry out 0 is 0 for all cases 
  except when two or more inputs are 1. This output is similar in operation to an AND gate. 
  Therefore, we can represent the Carry out 0, co0, as an AND of inputs.
  */
  co0 = (a0 & b0) | ((a0 ^ b0) & ci);
  
  //  Summing 3 single bits a1, b1 and the Carry out 0 and assigns the output to Sum 1
  s1 = (a1 ^ b1) ^ co0;

  /* 
  When summing 3 single bits, in the second 1-bit adder, the carry out 1 is 0 for all cases
  except when two or more inputs are 1. This output is similar in operation to an AND gate. 
  Therefore, we can represent the Carry out 1, co1, as an AND of inputs.
  */ 
  co1 = (a1 & b1) | ((a1 ^ b1) & co0); 


  //  Write 3 outputs
  //  Write sum output, s0, to the sumPin to light up the Sum LED
  digitalWrite(Sum0_Pin, s0);       
  //  Write sum output, s1, to the sumPin to light up the Sum LED
  digitalWrite(Sum1_Pin, s1);       
  //  Write carry out output, co1, to the sumPin to light up the Carry Out LED
  digitalWrite(CarryOutPin, co1);   
}

/*
Bit-wise operators
c = a & b ; AND
c = a | b ; OR
c = a ^ b ; XOR
c = !a ;   NOT
*/
