#include "include.h"

void init_pmbus(void)
{
	int32 pmbus_address = 0x58;
	//pmbus initialization code.  Much of this is unnecessary after a reset, but is put
	//in for completeness, and in case code is entered after some other program uses
	//PMBus interface

	PMBusRegs.PMBINTM.all = 0x1FF; //disable all PMBus interrupts
	PMBusRegs.PMBCTRL2.all = PMBCTRL2_HALF0_PEC_ENA 
							 + pmbus_address 
							 + PMBCTRL2_HALF0_SLAVE_ADDRESS_MASK_DISABLE
							 + PMBCTRL2_ALL_RX_BYTE_ACK_CNT; 
	pmbus_state = PMBUS_STATE_IDLE;  //initialize state to no message in progress 
}

void init_timer_interrupt(void)
{
	TimerRegs.T16PWM0CMP0DAT.all = 1587;  //approx 10KHz. by spec
	TimerRegs.T16PWM0CMP1DAT.all = 0xffff;
	TimerRegs.T16PWM0CMPCTRL.all = 2;
	TimerRegs.T16PWM0CNTCTRL.all = 0x00c;

	disable_fast_interrupt(); //make sure fast interrupt is disabled
	disable_interrupt();
	write_firqpr (0x02000000); //make them all irqs except FAULT_INT
	write_reqmask(0x02020000); //enable FAULT_INT and PWM0_INT
	enable_interrupt();
	enable_fast_interrupt(); //enabled in Idle state
}

void init_gpio(void)
{
	// Set outputs to 0.
	MiscAnalogRegs.GLBIOVAL.all = 0;

	// 1 - Output, 0 - Input
	MiscAnalogRegs.GLBIOOE.all = MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B | MASK_DPWM2A | MASK_DPWM3A | MASK_DPWM3B | MASK_FAULT2;

	// 1 - GPIO, 0 - other functions
	MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2;
}

void init_miscellaneous(void)
{
	pmbus_status_word = 0;

	MiscAnalogRegs.CLKTRIM.bit.HFO_LN_FILTER_EN = 0;

	LoopMuxRegs.GLBEN.all = 0;//gloable disable all PE and DPWM

	charge_state = UNKNOWN;
	buck_hysteresis = BOUNDARY;
	boost_hysteresis = BOUNDARY;
	supply_state = STATE_IDLE;
}

void delay(void)
{
	volatile int i,j;
	for(i=0;i<100000;i++)
	{
		j++;
		pmbus_handler();
		poll_adc();
	}
}
