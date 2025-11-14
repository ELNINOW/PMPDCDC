#include "include.h"

void clear_program_flash(void)
{
	DecRegs.PFLASHCTRL.bit.MASS_ERASE = 1; //erase it all

	while(DecRegs.PFLASHCTRL.bit.BUSY != 0)
	{
		; //do nothing while it programs
	}
	
	//now reset processor.
//	TimerRegs.WDCTRL.bit.CPU_RESET_EN = 1;  // Make sure the watchdog is enabled.
//	TimerRegs.WDCTRL.bit.WD_PERIOD = 1;		// Set WD period to timeout faster.

	return;
}

