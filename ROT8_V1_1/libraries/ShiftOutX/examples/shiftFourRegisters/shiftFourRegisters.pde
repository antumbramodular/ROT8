//**************************************************************//
//  Name    : shiftFourRegisters                                
//  Author  : Juan Hernandez 
//  Date    : 02 Jan 2011    
//  Modified:                                  
//  Version : 1.0                                             
//  Notes   : Code for using four 74HC595 Shift Registers           //
//          : with shiftOutX class                           
//****************************************************************
#include <ShiftOutX.h>
#include <ShiftPinNo.h>
//_latchPin connected to ST_CP of 74HC595
//_dataPin connected to DS of 74HC595
//_clockPin connected to SH_CP of 74HC595
//_bitOrder is the order in which the bits are send to the register
//values are the constants MSBFIRST for most significant bits first
//or LSBFIRST for least significant bit first they are declared in 
//wiring.h and arduino.h
//the way I see it is do you want Q0 to be shPin1 
//or do you want Q7 to be shPin1, 
//Q0 and Q7 are pin on the 74HC595 shift register.
//number of registers is how many registers you have in series
//so if you have 2 you will shift 16 bits or 24 and 32 if you
//have 3 or 4 registers and so on
//this is how you input the parameters to the class constructor
//shiftOutX(_latchPin, _dataPin, _clockPin, _bitOrder, _NofRegisters);
shiftOutX regOne(8, 11, 12, MSBFIRST, 4); 

//there are four shiftOut functions shiftOut16, shiftOut24, shiftOut32
//and shiftOut_X, of all these the first three are used the same as shiftOut
//with the exception that they shift to 2, 3, and 4 registers.
//the fourth one shiftOut_X can shift from 1 to 8 registers and it takes 
//one more parameter than the other three which is NofRegisters 
//so the syntax is as follows
//shiftOut_X(byte dataPin, byte clockPin, byte bitOrder, byte NofRegisters, uint64_t val);

//_bitString is the class member that holds the string of ones and zeros
//it is just an 8 byte unsigned integer and it is the only one that is not 
//public I just use the functions to modify it

void setup() {
  
}

void loop() {  
  regOne.pinOff(shPin28);
  delay(200);
  regOne.pinOn(shPin28);
  delay(200);   
  regOne.pinOff(shPin7);
  delay(200);
  regOne.pinOn(shPin7);
  delay(200); 
  regOne.pinOff(shPin13);
  delay(200);
  regOne.pinOn(shPin13);
  delay(200);
  regOne.pinOff(shPin20);
  delay(200);
  regOne.pinOn(shPin20);
  delay(200);

  if (regOne.pinState(shPin20) == true)
  {
    regOne.pinOn(shPin32);
    delay(1000);
    regOne.pinOff(shPin32);
  }
  delay(1000);
  regOne.allOn();
  delay(1000);
  regOne.allOff();
  delay(1000);
   
}


