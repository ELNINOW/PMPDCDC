#include "include.h"

void init_dpwm0(void) //DPWM0 for Q1 and Q2
{
	Dpwm0Regs.DPWMCTRL0.bit.PWM_EN = 0;   //disable everything
	Dpwm0Regs.DPWMCTRL0.bit.CLA_EN = 0;	  //open loop
	Dpwm0Regs.DPWMCTRL0.bit.PWM_MODE = 0; //normal mode

	Dpwm0Regs.DPWMCTRL1.bit.GPIO_A_EN = 1; //turn off DPWM0A
	Dpwm0Regs.DPWMCTRL1.bit.GPIO_B_EN = 1; //turn off DPWM0B
	Dpwm0Regs.DPWMCTRL1.bit.HIRES_DIS = 0;
	Dpwm0Regs.DPWMCTRL1.bit.ALL_PHASE_CLK_ENA = 1; //enable high resolution
	Dpwm0Regs.DPWMCTRL1.bit.PWM_HR_MULTI_OUT_EN = 1;

	Dpwm0Regs.DPWMSAMPTRIG1.all = (PWM_PERIOD/2) - (600*4); // close to end of period
	Dpwm0Regs.DPWMCTRL2.bit.SAMPLE_TRIG_1_EN = 1; //enable sample trigger1

	Dpwm0Regs.DPWMPRD.all = PWM_PERIOD; 
	Dpwm0Regs.DPWMEV1.all = 72 * 4; //aviod 72ns events update window
	Dpwm0Regs.DPWMEV2.all = PWM_PERIOD >> 1;
	Dpwm0Regs.DPWMEV3.all = Dpwm0Regs.DPWMEV2.all + 800; //200ns deadtime
	Dpwm0Regs.DPWMEV4.all = PWM_PERIOD - 400;

	Dpwm0Regs.DPWMPHASETRIG.all = 0; //trigger next phase by 0 degrees.

	Dpwm0Regs.DPWMCTRL1.bit.GPIO_A_EN = 0; //turn on DPWM0A
	Dpwm0Regs.DPWMCTRL1.bit.GPIO_B_EN = 0; //turn on DPWM0B

	Dpwm0Regs.DPWMCTRL0.bit.CLA_EN = 1;	//close loop
	Dpwm0Regs.DPWMCTRL0.bit.PWM_EN = 1; //enable OK here, because nothing will happen until DPWM and front end are globally enabled
}

void init_dpwm1(void)
{
	Dpwm1Regs.DPWMCTRL0.bit.PWM_EN = 0;   //disable everything
	Dpwm1Regs.DPWMCTRL0.bit.CLA_EN = 0;	  //open loop
	Dpwm1Regs.DPWMCTRL0.bit.PWM_MODE = 0; //normal mode

	Dpwm1Regs.DPWMCTRL1.bit.GPIO_A_EN = 1; //turn off DPWM1A for now
	Dpwm1Regs.DPWMCTRL1.bit.GPIO_B_EN = 1; //turn off DPWM1B for now
	Dpwm1Regs.DPWMCTRL1.bit.HIRES_DIS = 0;
	Dpwm1Regs.DPWMCTRL1.bit.ALL_PHASE_CLK_ENA = 1; //enable high resolution
	Dpwm1Regs.DPWMCTRL1.bit.PWM_HR_MULTI_OUT_EN = 1;

	Dpwm1Regs.DPWMPRD.all = PWM_PERIOD; 
	Dpwm1Regs.DPWMEV1.all = 72 * 4; //aviod 72ns events update window
	Dpwm1Regs.DPWMEV2.all = PWM_PERIOD >> 1;
	Dpwm1Regs.DPWMEV3.all = Dpwm1Regs.DPWMEV2.all + 800;//900; //225ns deadtime
	Dpwm1Regs.DPWMEV4.all = PWM_PERIOD - 400;

	Dpwm1Regs.DPWMCTRL0.bit.MSYNC_SLAVE_EN = 1;//enable sync

	Dpwm1Regs.DPWMCTRL1.bit.GPIO_A_EN = 0; //turn on DPWM1A
	Dpwm1Regs.DPWMCTRL1.bit.GPIO_B_EN = 0; //turn on DPWM1B

	Dpwm1Regs.DPWMCTRL0.bit.CLA_EN = 1;	//close loop
	Dpwm1Regs.DPWMCTRL0.bit.PWM_EN = 1; //enable OK here, because nothing will happen until DPWM and front end are globally enabled
}

void init_dpwms(void)
{
	init_dpwm0();
	init_dpwm1();
}

