//**************************************************************//
//  Name    : shiftOutX library                              
//  Author  : Juan Hernandez 
//  Date    : March 3 2011    
//  Modified: December 26 2011                                 
//  Version : 1.0                                             
//  Notes   : free as in libre not gratis although it's also gratis
//          : this functions are just modified versions of the 
//			: shiftOut function in wiring_shift.c                           
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
#include "ShiftOutX.h"

//for 2 shift registers
void shiftOut_16(byte dataPin, byte clockPin, byte bitOrder, uint16_t val)
{
	byte i;
	for (i = 0; i < 16; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else	
			digitalWrite(dataPin, !!(val & (1 << (15 - i)))); 
			
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);		
	}
}
//for 3 shift registers
void shiftOut_24(byte dataPin, byte clockPin, byte bitOrder, uint32_t val)
{
	byte i;
	byte i1;
	byte Sbyte;
	byte shiftNo;
	if (bitOrder == LSBFIRST){
				Sbyte = val;
				for (i1 = 0; i1 < 3; i1++) {
					for (i = 0; i < 8; i++)  {
						digitalWrite(dataPin, !!(Sbyte & (1 << i)));
						digitalWrite(clockPin, HIGH);
						digitalWrite(clockPin, LOW);
					}
					shiftNo += 8;
					Sbyte = val >> shiftNo;
				}
			}
			else if (bitOrder == MSBFIRST){
				shiftNo = 16;
				for (i1 = 0; i1 < 3; i1++) {
					Sbyte = val >> shiftNo;
					for (i = 0; i < 8; i++)  {
						digitalWrite(dataPin, !!(Sbyte & (1 << (7 - i))));
						digitalWrite(clockPin, HIGH);
						digitalWrite(clockPin, LOW);
					}
					shiftNo -= 8;
				}
			}
}
//for 4 shift registers
void shiftOut_32(byte dataPin, byte clockPin, byte bitOrder, uint32_t val)
{
	byte i;
	byte i1;
	byte Sbyte;
	byte shiftNo;				
			if (bitOrder == LSBFIRST){
				Sbyte = val;
				for (i1 = 0; i1 < 4; i1++) {
					for (i = 0; i < 8; i++)  {
						digitalWrite(dataPin, !!(Sbyte & (1 << i)));
						digitalWrite(clockPin, HIGH);
						digitalWrite(clockPin, LOW);
					}
					shiftNo += 8;
					Sbyte = val >> shiftNo;
				}
			}
			else if (bitOrder == MSBFIRST){
				shiftNo = 24;
				for (i1 = 0; i1 < 4; i1++) {
					Sbyte = val >> shiftNo;
					for (i = 0; i < 8; i++)  {
						digitalWrite(dataPin, !!(Sbyte & (1 << (7 - i))));
						digitalWrite(clockPin, HIGH);
						digitalWrite(clockPin, LOW);
					}
					shiftNo -= 8;
				}
			}
				
}

void shiftOut_X(byte dataPin, byte clockPin, byte bitOrder, byte NofRegisters, uint64_t val)
{
	byte i;
	byte i1;
	byte Sbyte;
	byte shiftNo;
			if (bitOrder == LSBFIRST){
				Sbyte = val;
				for (i1 = 0; i1 < NofRegisters; i1++) {
					for (i = 0; i < 8; i++)  {
						digitalWrite(dataPin, !!(Sbyte & (1 << i)));
						digitalWrite(clockPin, HIGH);
						digitalWrite(clockPin, LOW);
					}
					shiftNo += 8;
					Sbyte = val >> shiftNo;
				}
			}
			else if (bitOrder == MSBFIRST){
				shiftNo = (NofRegisters - 1) * 8;
				for (i1 = 0; i1 < NofRegisters; i1++) {
					Sbyte = val >> shiftNo;
					for (i = 0; i < 8; i++)  {
						digitalWrite(dataPin, !!(Sbyte & (1 << (7 - i))));
						digitalWrite(clockPin, HIGH);
						digitalWrite(clockPin, LOW);
					}
					shiftNo -= 8;
				}
			}
			
}


 shiftOutX::shiftOutX(byte latchPin, byte dataPin, byte clockPin, byte bitOrder, byte NofRegisters)
{
	init(latchPin, dataPin, clockPin, bitOrder, NofRegisters);
}

void shiftOutX::init(byte latchPin, byte dataPin, byte clockPin, byte bitOrder, byte NofRegisters)
{
	//populate info
	_latchPin = latchPin;
	_dataPin = dataPin;
	_clockPin = clockPin;
	_bitOrder = bitOrder;
	_NofRegisters = NofRegisters;
	_bitString = 0; //initialize to "3EPO" Credo che sia ucraino per zero
	//set needed pins to output
	pinMode(_latchPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);
}

void shiftOutX::pinOn(uint64_t shPin)
{
	_bitString |= shPin; //set shPin bit on even if it is on already
	// take the latchPin low so 
	digitalWrite(_latchPin, LOW);
	// shift out the bits:
	//if(_NofRegisters == 1)
	shiftOut_X(_dataPin, _clockPin, _bitOrder, _NofRegisters, _bitString);
	//take the latch pin high so the LEDs will light on or off
	digitalWrite(_latchPin, HIGH);
							
}					
				
void shiftOutX::pinOff(uint64_t shPin)
{
	
	uint64_t temp;
	temp = ALL_BITS_ON ^ shPin; //set for temp all bits on except for the bit in shPin
	_bitString &= temp;	//leave all bits in their state except for bit in shPin 
	// take the latchPin low so 
	digitalWrite(_latchPin, LOW);
	// shift out the bits:
	shiftOut_X(_dataPin, _clockPin, _bitOrder, _NofRegisters, _bitString);
	//take the latch pin high so the LEDs will light on or off.
	digitalWrite(_latchPin, HIGH);			
}

void shiftOutX::allOn()
{
	_bitString = ALL_BITS_ON;	//set all bits on 
	// take the latchPin low so 
	digitalWrite(_latchPin, LOW);
	// shift out the bits:
	shiftOut_X(_dataPin, _clockPin, _bitOrder, _NofRegisters, _bitString);
	//take the latch pin high so the LEDs will light on or off.
	digitalWrite(_latchPin, HIGH);
}

void shiftOutX::allOff()
{
	_bitString &= 0;	//set all bits on 
	// take the latchPin low so 
	digitalWrite(_latchPin, LOW);
	// shift out the bits:
	shiftOut_X(_dataPin, _clockPin, _bitOrder, _NofRegisters, _bitString);
	//take the latch pin high so the LEDs will light on or off.
	digitalWrite(_latchPin, HIGH);
}

bool shiftOutX::pinState(uint64_t shPin)
{
	uint64_t temp;
	temp = _bitString & shPin; //set temp all bits off except for shPin, if shPin is not set 
	//in _bitString then temp bits will be all off so when compared in next if the function 
	//will return false if not set or true if it is set
	if(temp == shPin)
	{
		return true;
	}
	else
	{
		return false;
	}
}

