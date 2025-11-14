#include "include.h"

extern const Uint32 parm_mem_start[NUM_MEMORY_SEGMENTS];
extern const Uint16 parm_mem_length[NUM_MEMORY_SEGMENTS];

const Uint8 cmd_pfc[]            = CMD_PFC;
const Uint8 cmd_dcdc_paged[]     = CMD_DCDC_PAGED;
const Uint8 cmd_dcdc_nonpaged[]  = CMD_DCDC_NONPAGED;

// Base address table used by the PARM_INFO command
#if NUM_MEMORY_SEGMENTS == 19
	       const Uint32	parm_mem_start[19] = {	RAM_START_ADDRESS, 
												REG_START_ADDRESS,  
												DFLASH_START_ADDRESS,	
												PFLASH_CONST_START_ADDRESS,
												PFLASH_PROG_START_ADDRESS,
												LOOP_MUX_START_ADDRESS,
												FAULT_MUX_START_ADDRESS,
												ADC_START_ADDRESS,
												DPWM3_START_ADDRESS,
												FILTER2_START_ADDRESS,
												DPWM2_START_ADDRESS,
												FE_CTRL2_START_ADDRESS,
												FILTER1_START_ADDRESS,
												DPWM1_START_ADDRESS,
												FE_CTRL1_START_ADDRESS,
												FILTER0_START_ADDRESS,
												DPWM0_START_ADDRESS,
												FE_CTRL0_START_ADDRESS,
												SYSTEM_REGS_START_ADDRESS	};

	       const Uint16	parm_mem_length[19] = {	RAM_LENGTH, 
												REG_LENGTH,  
												DFLASH_LENGTH,	
												PFLASH_CONST_LENGTH,
												PFLASH_PROG_LENGTH,
												LOOP_MUX_LENGTH,
												FAULT_MUX_LENGTH,
												ADC_LENGTH,
												DPWM3_LENGTH,
												FILTER2_LENGTH,
												DPWM2_LENGTH,
												FE_CTRL2_LENGTH,
												FILTER1_LENGTH,
												DPWM1_LENGTH,
												FE_CTRL1_LENGTH,
												FILTER0_LENGTH,
												DPWM0_LENGTH,
												FE_CTRL0_LENGTH,
												SYSTEM_REGS_LENGTH	};
#elif NUM_MEMORY_SEGMENTS == 5
	       const Uint32	parm_mem_start[5] = {	RAM_START_ADDRESS, 
												REG_START_ADDRESS,  
												DFLASH_START_ADDRESS,	
												PFLASH_CONST_START_ADDRESS,
												PFLASH_PROG_START_ADDRESS	};
	       const Uint16	parm_mem_length[5] = {	RAM_LENGTH, 
												REG_LENGTH,  
												DFLASH_LENGTH,	
												PFLASH_CONST_LENGTH,
												PFLASH_PROG_LENGTH		};
#else // Use only 4 memory segments -- Not Program	
	       const Uint32	parm_mem_start[4] = {	RAM_START_ADDRESS, 
												REG_START_ADDRESS,  
												DFLASH_START_ADDRESS,	
												PFLASH_CONST_START_ADDRESS};
	       const Uint16	parm_mem_length[4] = {	RAM_LENGTH, 
												REG_LENGTH,  
												DFLASH_LENGTH,	
												PFLASH_CONST_LENGTH	};
#endif

const Uint8 status_bit_mask[]    = PFC_STATUS_BIT_MASK;
const Uint8 debug_0_text[] = DEBUG_0_TEXT;
const Uint8 debug_1_text[] = DEBUG_1_TEXT;
const Uint8 debug_2_text[] = DEBUG_2_TEXT;
const Uint8 debug_3_text[] = DEBUG_3_TEXT;
const Uint8 debug_4_text[] = DEBUG_4_TEXT;
const Uint8 debug_5_text[] = DEBUG_5_TEXT;
const Uint8 debug_6_text[] = DEBUG_6_TEXT;
const Uint8 debug_7_text[] = DEBUG_7_TEXT;
const Uint8 vbus_full_range_text[] = VBUS_FULL_RANGE_TEXT;
#define NA_TEXT "N/A"
const Uint8 na_text[] = NA_TEXT;

#define YES_TEXT "Yes"
const Uint8 yes_text[] = YES_TEXT;

//==========================================================================================
//pmbus_read_cmd_dcdc_paged
//==========================================================================================
Uint8 pmbus_read_cmd_dcdc_paged(void)
{
  	Uint8 byte;
 	pmbus_number_of_bytes = 32 + 1;
   
    for(byte = 0; byte < 32; byte ++)
	   {
	    pmbus_buffer[byte+1] = (Uint8) cmd_dcdc_paged[byte];
	   }	
    pmbus_buffer[0] = 32;
	return 0;
}

//==========================================================================================
//pmbus_read_cmd_dcdc_non_paged
//==========================================================================================
Uint8 pmbus_read_cmd_dcdc_nonpaged(void)
{
  	Uint8 byte;
 	pmbus_number_of_bytes = 32 + 1;
   
    for(byte = 0; byte < 32; byte ++)
	   {
	    pmbus_buffer[byte+1] = (Uint8) cmd_dcdc_nonpaged[byte];
	   }	
    pmbus_buffer[0] = 32;
	return 0;
}

Uint8 pmbus_read_cmd_pfc(void)
{
  	Uint8 byte;
 	pmbus_number_of_bytes = 32 + 1;
   
    for(byte = 0; byte < 32; byte ++)
	   {
	    pmbus_buffer[byte+1] = (Uint8) cmd_pfc[byte];
	   }	
    pmbus_buffer[0] = 32;
	return 0;
}

Uint8 pmbus_read_debug_buffer(void)
{
 	Uint8 byte;
 	pmbus_number_of_bytes = 8 + 1;

    for(byte = 0; byte < 8; byte ++)
	{
	    pmbus_buffer[byte+1] = debug_buffer[byte];
	}
    pmbus_buffer[0] = 8;

 	return PMBUS_SUCCESS;
}

Uint8 pmbus_write_gui_constant(void)
{
	gui_constant_pointer = pmbus_buffer[2] ;
	return PMBUS_SUCCESS;
}

Uint8 pmbus_write_user_ram_00(void)
{
	user_ram_00 = pmbus_buffer[1];

	return PMBUS_SUCCESS;
}
	
Uint8 pmbus_read_user_ram_00(void)
{
	pmbus_buffer[0] = user_ram_00;
	pmbus_number_of_bytes = 1;

	return PMBUS_SUCCESS;
}

//==========================================================================================
// pmbus_write_rom_mode() 
//	Erases the program integrity word in FLASH, then waits for watchdog timer to reset the 
// CPU.  There is no return code or return from this function.  
//==========================================================================================
int pmbus_write_rom_mode(void)
{
	clear_integrity_word();			// Call a SWI to clear the integrity word.

	watchdog_reset();				// Wait for watchdog to expire and force CPU reset.
							
	return PMBUS_SUCCESS;			// Note: This line is never reached.  
}

//==========================================================================================
// pmbus_write_parm_info() checks for a valid input then assigns value to
//	parm_index, parm_offset and parm_length.  These values are needed to uniquely identify
//	a variable or register location in the system that will be queried or modified by the
//	parm_value command. 
//
// Global Inputs: 
//	pmbus_buffer[2]		parm_index. 0=RAM, 1=Registers, 2=DFlash, 3=PFlash Consts, {4=PFlash Program}
//	pmbus_buffer[3:4]	signed offset added to base address pointed to by parm_index
//	pmbus_buffer[5]		number of elements to transfer
//  pmbus_buffer[6]		size, in bytes, of the elements to tranfer (1, 2 or 4 bytes)
//
// modified globals
//	parm_index		Index to a memory section base address
//	parm_offset		Offset added to memory section base address, in multiples of parm_size bytes.
//  parm_count		Number of values to be transferred
//	parm_size		Number of bytes for each value (1, 2, or 4)
//==========================================================================================
Uint8 pmbus_write_parm_info(void)
{
	Uint8	temp_index;
	int16	temp_offset;	
	Uint8	temp_count;		
	Uint8	temp_size;	
	Uint8	temp_length;	

	temp_index  = pmbus_buffer[2];
	temp_offset = pmbus_buffer[3] + (pmbus_buffer[4]<<8);
	temp_count	= pmbus_buffer[5];
	temp_size   = pmbus_buffer[6];
	temp_length = temp_count * temp_size; 


	// ----- Validate the incoming arguments -----

	// ----- VALIDATE DATA -----
	// Verify that the specified base is valid
	// 0 (RAM)  and 1 (REGS) are valid for reading or writing.
	// 2 (DFLASH), 3 (PFLASH_CONST), and 4 (PFLASH_PROG) are read-only.
	// They will be flagged in pmbus_write_parm_value() if a write to them is attempted.
  	if(temp_index > NUM_MEMORY_SEGMENTS)  // Unsigned.    
		{
			return PMBUS_INVALID_DATA;	// Error: Invalid Index
		}

		// Verify that the message is short enough to fit
	if(temp_length > 32)
		{
			return PMBUS_INVALID_DATA;	// Error: Length greater than SAA capabilities.
		}

		// Verify that the size is 1, 2, or 4 bytes 
	if ((temp_size != 1) && (temp_size != 2) && (temp_size != 4))
		{
			return PMBUS_INVALID_DATA;	// Error: Invalid size
		}
		

	// ----- EXECUTE COMMAND -----
	// Arguments valid, assign values.
	parm_index	= temp_index;
	parm_offset	= temp_offset;
	parm_count	= temp_count;
	parm_size   = temp_size;

	return PMBUS_SUCCESS;
}

//==========================================================================================
// pmbus_read_parm_info() returns the value of the parm_index variable.
//==========================================================================================
Uint8 pmbus_read_parm_info(void)		                                                               
{                                                                                                                                                          
	// return a block of data with parm_index, parm_offset and parm_length   
	Uint8	num_bytes = 5;                                                                                                
	pmbus_buffer[0] = num_bytes;
	pmbus_buffer[1] = (Uint8)(parm_index);	
	pmbus_buffer[2] = (Uint8)(parm_offset & 0xff); 		//low byte of value
	pmbus_buffer[3] = (Uint8)(parm_offset >> 8); 		//high byte of value    
	pmbus_buffer[4] = (Uint8)(parm_count);
	pmbus_buffer[5] = (Uint8)(parm_size);    
	pmbus_number_of_bytes = num_bytes+1;                                                            
	return PMBUS_SUCCESS;                                                               
}                                                                                                                                                          
 
//==========================================================================================
// pmbus_write_parm_value()  This command gives the host a way to write virtually any
//	memory address in the system.
//	The host issues a parm_info command to set-up the parm_index, parm_offset
//	and parm_length parameters that determine how this command will	handle the incoming 
//	data. 
//
// modified globals
//	The memory pointed to by the combination of parm_index, parm_offset, and parm_size
//==========================================================================================
Uint8 pmbus_write_parm_value(void)
{
	Uint8	buffer_index;	// index into pmbus_buffer
	Uint16	start_offset;	// Byte Offset into selected memory segment
	Uint8	length;			// Total number of bytes to transfer
	Uint32	start_address;	// Starting byte address in selected memory segment
	Uint32	i;				// generic loop counter

	length = parm_count * parm_size;	// Total number of bytes to transfer
	start_offset = parm_offset * parm_size;

	// ----- VALIDATE DATA -----
		// Verify that the message is short enough to fit and that 
		// the number of bytes sent in this PARM_VALUE command matches the number
		// of bytes requested in the previous PARM_INFO command.
		if( (length > 32) || (length != pmbus_buffer[1]) )
		{
			return	PMBUS_INVALID_DATA;		// Error: Length greater than SAA capabilities
											//     or Lengths don't match
		}

		// ----- Validate the parm arguments -----
		// These should have already been checked by the PARM_INFO command, 
		// but because writing to invalid locations could cause so much havoc,
		// we will check them again here.

		// Verify that the index is valid for writing
		if ((parm_index == 2) || (parm_index == 3) || (parm_index == 4) || parm_index == 18)
			 // don't allow writes to any flash or to system registers.
		{
			return PMBUS_INVALID_DATA;	// Error: Invalid Index
		}

		// Verify that the starting and ending offsets are both within the valid memory range
		if (  ( start_offset		 > parm_mem_length[parm_index])	
			||((start_offset+length) > parm_mem_length[parm_index])  )
		{
			return PMBUS_INVALID_DATA;	// Error: Starting or ending addr out of range
		}
		
 

	// ----- EXECUTE COMMAND -----
	// Else it is a valid address.
	start_address = parm_mem_start[parm_index] + start_offset; 


	buffer_index = 2;	// Data starts in 3rd byte of buffer (for C the third byte is index=2)

	// Verification that the size is 1, 2, or 4 bytes is handled by the 'default' case in
	// the switch statement below.

	// Fill the transmit buffer with the requested data in 1, 2, or 4 byte chunks.
	switch (parm_size)
	{
	case 1:			// Transfer 1 byte at a time
		{	
			Uint8*	dest_ptr = (Uint8*)start_address;	

			for (i=0; i<parm_count; i++)
			{
				// Copy from the pmbus_buffer to the destination 1 byte at a time
				Uint8 val= pmbus_buffer[buffer_index];	
				*dest_ptr++ = val;
				buffer_index += parm_size;
			}
			break;
		}

	case 2:		// Transfer 2 bytes at a time
		{
			Uint16*	dest_ptr = (Uint16*)start_address;	

			for (i=0; i<parm_count; i++)
			{
				// Copy from the pmbus_buffer to the destination 2 bytes at a time
				Uint16 val=   (pmbus_buffer[buffer_index+0] << 0)
				        + (pmbus_buffer[buffer_index+1] << 8);		    
				*dest_ptr++ = val;
				buffer_index += parm_size;
			}
			break;
		}

	case 4:		// Transfer 4 bytes at a time
		{
			Uint32*	dest_ptr = (Uint32*)start_address;	

			for (i=0; i<parm_count; i++)
			{
				// Copy from the pmbus_buffer to the destination 4 bytes at a time
				Uint32 val=  (pmbus_buffer[buffer_index+0] << 0 )
				           + (pmbus_buffer[buffer_index+1] << 8 )		    
				           + (pmbus_buffer[buffer_index+2] << 16)
				           + (pmbus_buffer[buffer_index+3] << 24);
				*dest_ptr++ = val;
				buffer_index += parm_size;
			}
			break;
		}
	default:
		{
			// Should never get here since size should have been checked by parm_info cmd
			return	PMBUS_INVALID_DATA;		// Error: Invalid size
		}
	}	// end switch (parm_size)

	return PMBUS_SUCCESS;
}
                                                                                                                                                           
//==========================================================================================
// pmbus_read_parm_value() returns the value of the parm_index variable.
//
//	Assumptions: This function assumes that write_parm_info has ensured these conditions. 
//		* parm_index is pointing to a valid memory segment
//		* transfer length (==parm_count*parm_size) is <= 32 bytes
//==========================================================================================
Uint8 pmbus_read_parm_value(void)		                                                               
{   
	Uint16	start_offset;	// Byte Offset into selected memory segment
	Uint8 	length;			// Total number of bytes to transfer
	Uint8*	start_address; 	// Starting byte address in selected memory segment
    Uint8   i;

	// Verify that the starting and ending offsets are both within the valid memory range
	start_offset = parm_offset * parm_size;
	length       = parm_count  * parm_size;
	if (  ( start_offset 		 > parm_mem_length[parm_index])	
	  	||((start_offset+length) > parm_mem_length[parm_index])  )
	{
		return PMBUS_INVALID_DATA;	// Error: Starting or ending addr out of range
	}

	// Else it is a valid address.
	start_address = (Uint8*)parm_mem_start[parm_index] + start_offset; 
	
	pmbus_number_of_bytes = length + 1;
	
	for (i = 0; i < length; i++)
	{
		if(start_address == (Uint8*)0xfff7f040) //fake Cyclone 2
			{
				pmbus_buffer[i + 1] = 1;
				start_address++;
			}
		else 
			{                                              
				pmbus_buffer[i + 1] = *start_address++;
			}
	}
	pmbus_buffer[0] = length;
	
    return PMBUS_SUCCESS;
}                   

int pmbus_write_pfc_zvs_enable(void)
{
		return PMBUS_SUCCESS;
}

Uint8 pmbus_read_pfc_zvs_enable(void)
{
	return PMBUS_SUCCESS;
}

int pmbus_write_pfc_os_enable(void)
{
		return PMBUS_SUCCESS;
}

Uint8 pmbus_read_pfc_os_enable(void)
{
	return PMBUS_SUCCESS;
}

void watchdog_reset(void)
{
	//turn off all PWM outputs
	Dpwm0Regs.DPWMCTRL1.bit.GPIO_A_EN = 1;
	Dpwm0Regs.DPWMCTRL1.bit.GPIO_B_EN = 1;
	Dpwm1Regs.DPWMCTRL1.bit.GPIO_A_EN = 1; 
	Dpwm1Regs.DPWMCTRL1.bit.GPIO_B_EN = 1;
	Dpwm2Regs.DPWMCTRL1.bit.GPIO_A_EN = 1;
	Dpwm2Regs.DPWMCTRL1.bit.GPIO_B_EN = 1;
	Dpwm3Regs.DPWMCTRL1.bit.GPIO_A_EN = 1; 
	Dpwm3Regs.DPWMCTRL1.bit.GPIO_B_EN = 1; 
	//Make sure the watchdog is enabled.
	TimerRegs.WDCTRL.bit.CPU_RESET_EN = 1;
	//Set WD period to timeout faster
	TimerRegs.WDCTRL.bit.WD_PERIOD = 1;

	// This will never test true, but it prevents a compiler warning about unreachable code.
	while(1);	
}

Uint8 pmbus_write_light_load_config(void)
{
 	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_light_load_config(void)
{
 	return PMBUS_SUCCESS;
}

Uint8 pmbus_write_cpcc_config(void)
{
 	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_cpcc_config(void)
{
 	return PMBUS_SUCCESS;
}

