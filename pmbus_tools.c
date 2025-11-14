#include "include.h"

Uint32 linear11_translation(Uint32 raw_data, Uint8 shift_exponent)
{
	Uint8 exponent;
	Uint32 mantissa;
	Uint32 result;

	mantissa = raw_data & 0x07FF; // mantisa. mantisa is also in 2's complement
	exponent = raw_data >> 11; // exponent
	         
	if(exponent & 0x10) // exponent is negative
	{
		exponent = 16 - (exponent & 0x0F); // to shift # of bits right
		if (exponent >= shift_exponent)
		{ 
		 	result = mantissa >> (exponent - shift_exponent); 
		}
		else
		{ 
		 	result = mantissa << (shift_exponent - exponent);  
		} 
	}
	else //exponent is positive
	{
		result = mantissa << (exponent + shift_exponent);
	}

	return result;
}

