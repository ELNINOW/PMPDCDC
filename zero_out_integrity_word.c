#include "include.h"

#define program_flash_integrity_word (*((volatile unsigned long *) 0x7ffc))
//last word in flash, when executing from Flash.  used to store integrity code

void zero_out_integrity_word(void)
{
	DecRegs.FLASHILOCK.all = 0x42DC157E;// Write key to Program Flash Interlock Register
	DecRegs.MFBALR1.all = MFBALRX_BYTE0_BLOCK_SIZE_32K; //enable program flash write
	program_flash_integrity_word = 0;
	DecRegs.MFBALR1.all = MFBALRX_BYTE0_BLOCK_SIZE_32K + //expand program flash out to 4x real size
							MFBALRX_BYTE0_RONLY;

	while(DecRegs.PFLASHCTRL.bit.BUSY != 0)
	{
		; //do nothing while it programs
	}
		//now reset processor.
//	TimerRegs.WDCTRL.bit.CPU_RESET_EN = 1;  // Make sure the watchdog is enabled.
//	TimerRegs.WDCTRL.bit.WD_PERIOD = 1;		// Set WD period to timeout faster.

	// This will never test true, but it prevents a compiler warning about unreachable code.
//	while(1);						// Wait for the watchdog.
	return;
}
