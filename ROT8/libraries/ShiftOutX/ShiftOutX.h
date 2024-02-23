//**************************************************************//
//  Name    : shiftOutX library                              
//  Author  : Juan Hernandez 
//  Date    : March 3 2011    
//  Modified: December 26 2011                                 
//  Version : 1.0                                             
//  Notes   : free as in libre not gratis, although it's also gratis.
//          : it only shifts out to four shift registers, though you 
//			: can shift out to more registers I believe that if you 
//			: need more pins than that you should get a Mega with 
//			: more outputs. that is just me though. use it as you like.
//			: or unless you already have a mega and still need more 
//			: just modify to use 64 bits to shift to 8 registers
//			: or sacrifice three more pins to get 29 more and so on 
//			: juanh0238@yahoo.com   please send any suggestions 
//****************************************************************
/*  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/
#ifndef ShiftOutX_h
#define ShiftOutX_h
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #else
  #include "WProgram.h"
  #endif

 
#define ON  1
#define OFF 0
#define ALL_BITS_ON 0XFFFFFFFFFFFFFFFFLL //18446744073709551615LL //B11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 that is a long string of unos

//shiftOut 16, 24 and 32 bits if you prefer to do it manually but below are functions to 
void shiftOut_16(byte dataPin, byte clockPin, byte bitOrder, uint16_t val);
void shiftOut_24(byte dataPin, byte clockPin, byte bitOrder, uint32_t val);
void shiftOut_32(byte dataPin, byte clockPin, byte bitOrder, uint32_t val);
void shiftOut_X(byte dataPin, byte clockPin, byte bitOrder, byte NofRegisters, uint64_t val);


//shiftOutX class
class shiftOutX{
				private:
				uint64_t _bitString;  // just an eight byte integer I see it as a string of ones and zeros
				//hence the name _bitString. shiftOut and shiftOut_16 use byte and uint16_t as parameters variables
				//for val, this class uses an eight byte integer as mentioned above, when passed as a parameter 
				//shiftOut and ShiftOut_16 simply chop off the excess bits, actually they are just not read
				//so be carefull with bitOrder because you will be shifting out only the high or the low bits.
				//capisce?
				public:
				byte _latchPin;
				byte _dataPin;
				byte _clockPin;
				byte _bitOrder;
				byte _NofRegisters; //1 to 4 registers
								
	shiftOutX(byte latchPin, byte dataPin, byte clockPin, byte bitOrder, byte NofRegisters);
	//function to setup shiftOut like setting pins to output, and populate members of the class as well.			
	void init(byte latchPin, byte dataPin, byte clockPin, byte bitOrder, byte NofRegisters);
	
	//turn on and off specific pins
	//self explanatory these functions turn on and off individual shift register pins by number
	//the numbers are defined in shiftPinNo.h and are named shPin1 through shPin32 				
	void pinOn(uint64_t shPin);
	void pinOff(uint64_t shPin);
	void allOn(void);
	void allOff(void);
	//this following function returns true if the pin is on or false if not, it does not check the register state
	//though it only checks if the bit is set or not in the _bitString
	bool pinState(uint64_t shPin);
				
	}; //shiftOutX class
							
// è tutto per oggi

#endif