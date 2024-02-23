#include <ShiftOutX.h>
#include <ShiftPinNo.h>

//**************************************************************//
//  Name    : shiftOutX, Hello World                                
//  Author  : Juan Hernandez 
//  Date    : 02 Jan 2011    
//  Modified:                                  
//  Version : 1.0                                             
//  Notes   : Code for using four 74HC595 Shift Registers           //
//          : with shiftOutX class                           
//****************************************************************

//_latchPin connected to ST_CP of 74HC595
//_dataPin connected to DS of 74HC595
//_clockPin connected to SH_CP of 74HC595
//_bitOrder is the order in which the bits are send to the register
//values are the constants MSBFIRST for most significant bits first
//or LSBFIRST for least significant bit first, the way I see it is 
//do you want Q0 to be shPin1 or do you want Q7 to be shPin1, 
//Q0 and Q7 are pin on the 74HC595 shift register.
//number of registers is how many registers you have in series
//so if you have 2 you will shift 16 bits or 24 and 32 if you
//have 3 or 4 registers
//this is how you input the parameters to the class constructor
//shiftOutX(_latchPin, _dataPin, _clockPin, _bitOrder, _NofRegisters);
shiftOutX regOne(8, 11, 12, MSBFIRST, 4); 

//_bitString is the class member that holds the string of ones and zeros
//it is just a 4 byte unsigned integer and though all these members are 
//public I just use the functions to modify them but you can modify them 
//as you like.
//so to access it you would do it like this
//regOne._bitString = xx;

void setup() {
  
}

void loop() {
  int delayT = 16;  
  regOne.pinOn(shPin1);
  delay(delayT);
  regOne.pinOn(shPin2);
  delay(delayT);
  regOne.pinOn(shPin3);
  delay(delayT);
  regOne.pinOn(shPin4);
  delay(delayT);
  regOne.pinOn(shPin5);
  delay(delayT);
  regOne.pinOn(shPin6);
  delay(delayT);
  regOne.pinOn(shPin7);
  delay(delayT);
  regOne.pinOn(shPin8);
  delay(delayT);
  regOne.pinOn(shPin9);
  delay(delayT);
  regOne.pinOn(shPin10);
  delay(delayT);
  regOne.pinOn(shPin11);
  delay(delayT);
  regOne.pinOn(shPin12);
  delay(delayT);
  regOne.pinOn(shPin13);
  delay(delayT);
  regOne.pinOn(shPin14);
  delay(delayT);
  regOne.pinOn(shPin15);
  delay(delayT);
  regOne.pinOn(shPin16);
  delay(delayT);
  regOne.pinOn(shPin17);
  delay(delayT);
  regOne.pinOn(shPin18);
  delay(delayT);
  regOne.pinOn(shPin19);
  delay(delayT);
  regOne.pinOn(shPin20);
  delay(delayT);
  regOne.pinOn(shPin21);
  delay(delayT);
  regOne.pinOn(shPin22);
  delay(delayT);
  regOne.pinOn(shPin23);
  delay(delayT);
  regOne.pinOn(shPin24);
  delay(delayT);
  regOne.pinOn(shPin25);
  delay(delayT);
  regOne.pinOn(shPin26);
  delay(delayT);
  regOne.pinOn(shPin27);
  delay(delayT);
  regOne.pinOn(shPin28);
  delay(delayT);
  regOne.pinOn(shPin29);
  delay(delayT);
  regOne.pinOn(shPin30);
  delay(delayT);
  regOne.pinOn(shPin31);
  delay(delayT);
  regOne.pinOn(shPin32);
  delay(delayT);
  
  regOne.pinOff(shPin1);
  delay(delayT);
  regOne.pinOff(shPin2);
  delay(delayT);
  regOne.pinOff(shPin3);
  delay(delayT);
  regOne.pinOff(shPin4);
  delay(delayT);
  regOne.pinOff(shPin5);
  delay(delayT);
  regOne.pinOff(shPin6);
  delay(delayT);
  regOne.pinOff(shPin7);
  delay(delayT);
  regOne.pinOff(shPin8);
  delay(delayT);
  regOne.pinOff(shPin9);
  delay(delayT);
  regOne.pinOff(shPin10);
  delay(delayT);
  regOne.pinOff(shPin11);
  delay(delayT);
  regOne.pinOff(shPin12);
  delay(delayT);
  regOne.pinOff(shPin13);
  delay(delayT);
  regOne.pinOff(shPin14);
  delay(delayT);
  regOne.pinOff(shPin15);
  delay(delayT);
  regOne.pinOff(shPin16);
  delay(delayT);
  regOne.pinOff(shPin17);
  delay(delayT);
  regOne.pinOff(shPin18);
  delay(delayT);
  regOne.pinOff(shPin19);
  delay(delayT);
  regOne.pinOff(shPin20);
  delay(delayT);
  regOne.pinOff(shPin21);
  delay(delayT);
  regOne.pinOff(shPin22);
  delay(delayT);
  regOne.pinOff(shPin23);
  delay(delayT);
  regOne.pinOff(shPin24);
  delay(delayT);
  regOne.pinOff(shPin25);
  delay(delayT);
  regOne.pinOff(shPin26);
  delay(delayT);
  regOne.pinOff(shPin27);
  delay(delayT);
  regOne.pinOff(shPin28);
  delay(delayT);
  regOne.pinOff(shPin29);
  delay(delayT);
  regOne.pinOff(shPin30);
  delay(delayT);
  regOne.pinOff(shPin31);
  delay(delayT);
  regOne.pinOff(shPin32);
  delay(delayT);
}


