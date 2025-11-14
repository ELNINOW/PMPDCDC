//standard_interrupt.c
#include "include.h"

void preset_filter0(void)
{
	//PRESET KI_YN
	Filter0Regs.FILTERPRESET.all = (1<<27) + (1<<24) + 0x100000;
	//PRESET YN
	Filter0Regs.FILTERPRESET.all = (1<<27) + (3<<24) + 0x100000;
	//PRESET 18 bit filter duty register (after multiplication)
	Filter0Regs.FILTERPRESET.all = (1<<27) + (4<<24) + 0x100000;

	Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 1;
	Filter0Regs.FILTERCTRL.bit.FORCE_START = 1;

	Filter0Regs.FILTERCTRL.bit.FORCE_START = 0;
	Filter0Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 0;
}

void preset_filter1(void)
{
	//PRESET KI_YN to 0
	Filter1Regs.FILTERPRESET.all = (1<<27) + (1<<24);
	//PRESET YN to 0
	Filter1Regs.FILTERPRESET.all = (1<<27) + (3<<24);
	//PRESET 18 bit filter duty register (after multiplication) to 0
	Filter1Regs.FILTERPRESET.all = (1<<27) + (4<<24);

	Filter1Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 1;
	Filter1Regs.FILTERCTRL.bit.FORCE_START = 1;

	Filter1Regs.FILTERCTRL.bit.FORCE_START = 0;
	Filter1Regs.FILTERCTRL.bit.USE_CPU_SAMPLE = 0;
}

void shut_down(void)
{
	LoopMuxRegs.GLBEN.all = 0; 		//gloable disable all PE and DPWM
	MiscAnalogRegs.GLBIOVAL.all = 0;

	FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP
}

void poll_adc(void)
{
	adc_values.v_bus_sense = AdcRegs.ADCRESULT[VBUS].bit.RESULT;
//	adc_values.i_bus_sense = AdcRegs.ADCRESULT[IBUS].bit.RESULT;
	adc_values.v_bat_sense = AdcRegs.ADCRESULT[VBAT].bit.RESULT;
	adc_values.i_bat_sense = AdcRegs.ADCRESULT[IBAT].bit.RESULT;

	adc_values_avg.v_bus_sense = AdcRegs.ADCAVGRESULT[VBUS].bit.RESULT;
//	adc_values_avg.i_bus_sense = AdcRegs.ADCAVGRESULT[IBUS].bit.RESULT;
	adc_values_avg.v_bat_sense = AdcRegs.ADCAVGRESULT[VBAT].bit.RESULT;
	adc_values_avg.i_bat_sense = AdcRegs.ADCAVGRESULT[IBAT].bit.RESULT;

	vbus_filtered = vbus_filtered + adc_values.v_bus_sense - (vbus_filtered >> 9);
}

inline void idle_state_handler(void)
{
	if(VBUS_VOLTAGE_LOW)//if Vbus too low
	{

	}
	else
	{
		volatile int32 i;

		preset_filter0();
		preset_filter1();

		interrupt_counter1 = 0;
		interrupt_counter2 = 0;
		interrupt_counter3 = 0;
		fault_type = NO_FAULT;
		charge_state = UNKNOWN;
		buck_hysteresis = BOUNDARY;
		boost_hysteresis = BOUNDARY;

		LoopMuxRegs.DPWMMUX.bit.DPWM0_FILTER_SEL = 1; //CLA1 is providing input to DPWM0
		LoopMuxRegs.DPWMMUX.bit.DPWM1_FILTER_SEL = 1; //CLA1 is providing input to DPWM1

		Dpwm0Regs.DPWMCTRL0.all &= ~0xFF000000; //0A->0A, 0B->0B
		Dpwm1Regs.DPWMCTRL0.all |= 0x33000000; //swap 1A->1B, 1B->1A

		MiscAnalogRegs.GLBIOVAL.all = 0;
		MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;

		//set up for hardware ramp up
		FeCtrl1Regs.RAMPCYCLE.bit.SWITCH_CYC_PER_STEP = 1;// Number of switching cycles pre DAC step
		FeCtrl1Regs.RAMPCTRL.bit.RAMP_EN = 1; // Ramp by Hardware
		FeCtrl1Regs.EADCDAC.bit.DAC_VALUE = 0;//starting point
		FeCtrl1Regs.RAMPDACEND.bit.RAMP_DAC_VALUE = IBAT_CHARGE_CURRENT * IBAT_DAC_SCALER;
		FeCtrl1Regs.DACSTEP.bit.DAC_STEP = 1000;//40ms ramp up time
		FeCtrl1Regs.RAMPCTRL.bit.FIRMWARE_START = 1; //Initiate soft start ramp

		if(VBAT_NEED_CHARGE)
		{
			LoopMuxRegs.GLBEN.all = 0x70F;//gloable enable all PE and DPWM
			supply_state = STATE_RAMP_UP;
		}
		else
		{
			MiscAnalogRegs.GLBIOVAL.all = 0;
			MiscAnalogRegs.GLBIOEN.all = MASK_DPWM0A | MASK_DPWM0B;
			LoopMuxRegs.GLBEN.all = 0x401; //gloable enable EAP2 and DPWM0 for bus UVP detection
			supply_state = STATE_TOPPING_CHARGE;
		}

		i = FaultMuxRegs.FAULTMUXINTSTAT.all; 		//read to clear the interrupt flag

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
//		FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_INT_EN = 1;	//enable BAT OCP
	}
}

inline void ramp_up_state_handler(void)
{
	int i;

	if(adc_values.v_bus_sense > (adc_values.v_bat_sense + buck_hysteresis))//buck
	{
		if(charge_state != BUCK)
		{
			MiscAnalogRegs.GLBIOVAL.all = 0;

			FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

			if(supply_state != STATE_BACKUP)//fast interrupt may change the state to back up
			{
				MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
				Filter1Regs.COEFCONFIG.all = 0;//use coefficient set A
				for(i=0;i<40;i++)
				{
					asm(" nop");
				}
				MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM1A | MASK_DPWM1B;//Q3 off to prevent reverse current
				charge_state = BUCK;
			}

			FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

			buck_hysteresis = BOUNDARY;
			boost_hysteresis = BOUNDARY + HYSTERESIS;
		}
	}
	else if(adc_values.v_bus_sense > (adc_values.v_bat_sense - boost_hysteresis))//buck-boost
	{
		if(charge_state != BUCK_BOOST)
		{
			FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP
			if(supply_state != STATE_BACKUP)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;
				MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
				Filter1Regs.COEFCONFIG.all = 0x09999999;//use coefficient set B
				Filter1Regs.FILTERPRESET.all = (1<<27) + (1<<24) + buckboost_duty;
				Filter1Regs.FILTERPRESET.all = (1<<27) + (3<<24) + buckboost_duty;
				for(i=0;i<40;i++)
				{
					asm(" nop");
				}
				MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2;
				charge_state = BUCK_BOOST;
			}
			FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

			buck_hysteresis = BOUNDARY + HYSTERESIS;
			boost_hysteresis = BOUNDARY + HYSTERESIS;
		}
	}
	else //boost
	{
		if(charge_state != BOOST)
		{
			MiscAnalogRegs.GLBIOVAL.all = 0;

			FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP
			if(supply_state != STATE_BACKUP)
			{
				MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
				Filter1Regs.FILTERPRESET.all = (1<<27) + (1<<24) + boost_duty;
				Filter1Regs.FILTERPRESET.all = (1<<27) + (3<<24) + boost_duty;
				Filter1Regs.COEFCONFIG.all = 0x02222222;//use coefficient set C
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0B;	//turn on Q2
				for(i=0;i<40;i++)
				{
					asm(" nop");
				}
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q2
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1
				MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B;
				charge_state = BOOST;
			}
			FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

			interrupt_counter1 = 0;
			buck_hysteresis = BOUNDARY;
			boost_hysteresis = BOUNDARY;
		}

		interrupt_counter1 ++;
		if(interrupt_counter1 > 19)
		{
			MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q1
			asm(" nop");//about 120ns
			MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0B;	//turn on Q2
			asm(" nop");
			MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q2
			MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1
			interrupt_counter1 = 0;
		}
	}

	if(FeCtrl1Regs.RAMPSTAT.bit.RAMP_COMP_INT_STATUS == 1)//if ramp up complete, bit read and clear
	{
		FeCtrl1Regs.EADCDAC.all = IBAT_CHARGE_CURRENT * IBAT_DAC_SCALER;

		interrupt_counter1 = 0;

		supply_state = STATE_CC_CHARGE;
	}
}

inline void cc_charge_state_handler(void)
{
	int i;

	if(VBAT_OVP_FAULT)
	{
		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

		if(supply_state != STATE_BACKUP)
		{
			MiscAnalogRegs.GLBIOVAL.all = 0;
			MiscAnalogRegs.GLBIOEN.all = MASK_DPWM0A | MASK_DPWM0B;
			LoopMuxRegs.GLBEN.all = 0x401; //gloable enable EAP2 and DPWM0 for bus UVP detection
			supply_state = STATE_TOPPING_CHARGE;
		}

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
	}
	else if(IBAT_OCP_FAULT)
	{
		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

		if(supply_state != STATE_BACKUP)
		{
			shut_down();
			fault_type = BAT_OCP;
			supply_state = STATE_FAULT;
		}

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
	}
	else if(Filter0Regs.FILTERYNREAD.bit.YN < Filter1Regs.FILTERYNREAD.bit.YN)
	{
		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

		if(supply_state != STATE_BACKUP)
		{
			LoopMuxRegs.GLBEN.all = 0; //gloable disable all PE and DPWM

			LoopMuxRegs.DPWMMUX.bit.DPWM0_FILTER_SEL = 0; //CLA0 is providing input to DPWM0
			LoopMuxRegs.DPWMMUX.bit.DPWM1_FILTER_SEL = 0; //CLA0 is providing input to DPWM1

			LoopMuxRegs.GLBEN.all = 0x70F;//gloable enable all PE and DPWM

			supply_state = STATE_CV_CHARGE;
		}

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
	}
	else
	{
		if(adc_values.v_bus_sense > (adc_values.v_bat_sense + buck_hysteresis))//buck
		{
			if(charge_state != BUCK)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

				if(supply_state != STATE_BACKUP)//fast interrupt may change the state to back up
				{
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter1Regs.FILTERPRESET.all = (1<<27) + (1<<24) + buck_duty;
					Filter1Regs.FILTERPRESET.all = (1<<27) + (3<<24) + buck_duty;
					Filter1Regs.COEFCONFIG.all = 0;//use coefficient set A
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM1A | MASK_DPWM1B;
					charge_state = BUCK;
				}
				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1A;	//turn on Q3

				interrupt_counter1 = 0;
				buck_hysteresis = BOUNDARY;
				boost_hysteresis = BOUNDARY + HYSTERESIS;
			}

			interrupt_counter1 ++;
			if(interrupt_counter1 > 19)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q3
				asm(" nop");//about 120ns
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1B;	//turn on Q4
				asm(" nop");
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q4
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1A;	//turn on Q3
				interrupt_counter1 = 0;
			}
		}
		else if(adc_values.v_bus_sense > (adc_values.v_bat_sense - boost_hysteresis))//buck-boost
		{
			if(charge_state != BUCK_BOOST)
			{
				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

				if(supply_state != STATE_BACKUP)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter1Regs.COEFCONFIG.all = 0x09999999;//use coefficient set B
					Filter1Regs.FILTERPRESET.all = (1<<27) + (1<<24) + buckboost_duty;
					Filter1Regs.FILTERPRESET.all = (1<<27) + (3<<24) + buckboost_duty;
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2;

					charge_state = BUCK_BOOST;
				}

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

				buck_hysteresis = BOUNDARY + HYSTERESIS;
				boost_hysteresis = BOUNDARY + HYSTERESIS;
			}
		}
		else //boost
		{
			if(charge_state != BOOST)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

				if(supply_state != STATE_BACKUP)
				{
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter1Regs.FILTERPRESET.all = (1<<27) + (1<<24) + boost_duty;
					Filter1Regs.FILTERPRESET.all = (1<<27) + (3<<24) + boost_duty;
					Filter1Regs.COEFCONFIG.all = 0x02222222;//use coefficient set C
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B;

					charge_state = BOOST;
				}

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1

				interrupt_counter1 = 0;
				buck_hysteresis = BOUNDARY;
				boost_hysteresis = BOUNDARY;
			}

			interrupt_counter1 ++;
			if(interrupt_counter1 > 19)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q1
				asm(" nop");//about 120ns
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0B;	//turn on Q2
				asm(" nop");
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q2
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1
				interrupt_counter1 = 0;
			}
		}
	}
}

inline void cv_charge_state_handler(void)
{
	int i;

	if((adc_values_avg.i_bat_sense < (IBAT_SATURATION_LIMIT + ibat_adc_offset)) || (VBAT_OVP_FAULT))
	{
		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

		if(supply_state != STATE_BACKUP)
		{
			MiscAnalogRegs.GLBIOVAL.all = 0;
			MiscAnalogRegs.GLBIOEN.all = MASK_DPWM0A | MASK_DPWM0B;
			LoopMuxRegs.GLBEN.all = 0x401; //gloable enable EAP2 and DPWM0 for bus UVP detection
			supply_state = STATE_TOPPING_CHARGE;
		}

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

	}
	else if(IBAT_OCP_FAULT)
	{
		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

		if(supply_state != STATE_BACKUP)
		{
			shut_down();
			fault_type = BAT_OCP;
			supply_state = STATE_FAULT;
		}

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
	}
	else if(Filter0Regs.FILTERYNREAD.bit.YN > (Filter1Regs.FILTERYNREAD.bit.YN + 2000))
	{
		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

		if(supply_state != STATE_BACKUP)
		{
			LoopMuxRegs.GLBEN.all = 0; //gloable disable all PE and DPWM

			LoopMuxRegs.DPWMMUX.bit.DPWM0_FILTER_SEL = 1; //CLA1 is providing input to DPWM0
			LoopMuxRegs.DPWMMUX.bit.DPWM1_FILTER_SEL = 1; //CLA1 is providing input to DPWM1

			LoopMuxRegs.GLBEN.all = 0x70F;//gloable enable all PE and DPWM

			supply_state = STATE_CC_CHARGE;
		}

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
	}
	else
	{
		if(adc_values.v_bus_sense > (adc_values.v_bat_sense + buck_hysteresis))//buck
		{
			if(charge_state != BUCK)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

				if(supply_state != STATE_BACKUP)//fast interrupt may change the state to back up
				{
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter0Regs.FILTERPRESET.all = (1<<27) + (1<<24) + buck_duty;
					Filter0Regs.FILTERPRESET.all = (1<<27) + (3<<24) + buck_duty;
					Filter0Regs.COEFCONFIG.all = 0;//use coefficient set A
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM1A | MASK_DPWM1B;
					charge_state = BUCK;
				}
				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1A;	//turn on Q3

				interrupt_counter1 = 0;
				buck_hysteresis = BOUNDARY;
				boost_hysteresis = BOUNDARY + HYSTERESIS;
			}

			interrupt_counter1 ++;
			if(interrupt_counter1 > 19)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q3
				asm(" nop");//about 120ns
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1B;	//turn on Q4
				asm(" nop");
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q4
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1A;	//turn on Q3
				interrupt_counter1 = 0;
			}
		}
		else if(adc_values.v_bus_sense > (adc_values.v_bat_sense - boost_hysteresis))//buck-boost
		{
			if(charge_state != BUCK_BOOST)
			{
				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

				if(supply_state != STATE_BACKUP)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter0Regs.COEFCONFIG.all = 0x09999999;//use coefficient set B
					Filter0Regs.FILTERPRESET.all = (1<<27) + (1<<24) + buckboost_duty;
					Filter0Regs.FILTERPRESET.all = (1<<27) + (3<<24) + buckboost_duty;
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2;

					charge_state = BUCK_BOOST;
				}

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

				buck_hysteresis = BOUNDARY + HYSTERESIS;
				boost_hysteresis = BOUNDARY + HYSTERESIS;
			}
		}
		else //boost
		{
			if(charge_state != BOOST)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

				if(supply_state != STATE_BACKUP)
				{
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter0Regs.FILTERPRESET.all = (1<<27) + (1<<24) + boost_duty;
					Filter0Regs.FILTERPRESET.all = (1<<27) + (3<<24) + boost_duty;
					Filter0Regs.COEFCONFIG.all = 0x02222222;//use coefficient set C
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B;

					charge_state = BOOST;
				}

				FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP

				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1

				interrupt_counter1 = 0;
				buck_hysteresis = BOUNDARY;
				boost_hysteresis = BOUNDARY;
			}

			interrupt_counter1 ++;
			if(interrupt_counter1 > 19)
			{
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q1
				asm(" nop");//about 120ns
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0B;	//turn on Q2
				asm(" nop");
				MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q2
				MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1
				interrupt_counter1 = 0;
			}
		}
	}
}

inline void topping_charge_state_handler(void)
{
	if(VBAT_NEED_CHARGE)
	{
		preset_filter0();
		preset_filter1();

		interrupt_counter1 = 0;
		charge_state = UNKNOWN;
		buck_hysteresis = BOUNDARY;
		boost_hysteresis = BOUNDARY;

		//set up for hardware ramp up
		FeCtrl1Regs.RAMPCYCLE.bit.SWITCH_CYC_PER_STEP = 1;// Number of switching cycles pre DAC step
		FeCtrl1Regs.RAMPCTRL.bit.RAMP_EN = 1; // Ramp by Hardware
		FeCtrl1Regs.EADCDAC.bit.DAC_VALUE = 0;//starting point
		FeCtrl1Regs.RAMPDACEND.bit.RAMP_DAC_VALUE = IBAT_CHARGE_CURRENT * IBAT_DAC_SCALER;
		FeCtrl1Regs.DACSTEP.bit.DAC_STEP = 1000;//40ms ramp up time
		FeCtrl1Regs.RAMPCTRL.bit.FIRMWARE_START = 1; //Initiate soft start ramp

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 0; //disable BUS UVP

		if(supply_state != STATE_BACKUP)
		{
			LoopMuxRegs.DPWMMUX.bit.DPWM0_FILTER_SEL = 1; //CLA1 is providing input to DPWM0
			LoopMuxRegs.DPWMMUX.bit.DPWM1_FILTER_SEL = 1; //CLA1 is providing input to DPWM1
			MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
			LoopMuxRegs.GLBEN.all = 0x70F;//gloable enable all PE and DPWM
			supply_state = STATE_RAMP_UP;
		}

		FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
	}
}

inline void backup_state_handler(void)
{
	if(VBUS_OVP_FAULT)
	{
		shut_down();
		fault_type = BUS_OVP;
		interrupt_counter1 = 0;
		supply_state = STATE_FAULT;
	}
	else if(VBAT_VOLTAGE_LOW)
	{
		shut_down();
		fault_type = BAT_UVP;
		interrupt_counter1 = 0;
		supply_state = STATE_FAULT;
	}
	else
	{
		if(interrupt_counter3 <= 1000)//wait for 100ms
		{
			interrupt_counter3 ++;
		}
		else
		{
			Uint32 i;

			if(adc_values.v_bus_sense > (adc_values.v_bat_sense + buck_hysteresis))//backup boost (charge buck)
			{
				if(charge_state != BUCK)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter2Regs.FILTERPRESET.all = (1<<27) + (1<<24) + ((1<<23) - buck_duty);
					Filter2Regs.FILTERPRESET.all = (1<<27) + (3<<24) + ((1<<23) - buck_duty);
					Filter2Regs.COEFCONFIG.all = 0;//use coefficient set A
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM1A | MASK_DPWM1B;
					charge_state = BUCK;

					MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1A;	//turn on Q3

					interrupt_counter1 = 0;
					buck_hysteresis = BOUNDARY;
					boost_hysteresis = BOUNDARY + HYSTERESIS;
				}

				interrupt_counter1 ++;
				if(interrupt_counter1 > 19)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q3
					asm(" nop");//about 120ns
					MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1B;	//turn on Q4
					asm(" nop");
					MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q4
					MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM1A;	//turn on Q3
					interrupt_counter1 = 0;
				}
			}
			else if(adc_values.v_bus_sense > (adc_values.v_bat_sense - boost_hysteresis))//buck-boost
			{
				if(charge_state != BUCK_BOOST)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter2Regs.COEFCONFIG.all = 0x09999999;//use coefficient set B
					Filter2Regs.FILTERPRESET.all = (1<<27) + (1<<24) + ((1<<23) - buckboost_duty);
					Filter2Regs.FILTERPRESET.all = (1<<27) + (3<<24) + ((1<<23) - buckboost_duty);
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2;

					charge_state = BUCK_BOOST;

					buck_hysteresis = BOUNDARY + HYSTERESIS;
					boost_hysteresis = BOUNDARY + HYSTERESIS;
				}
			}
			else //backup buck (charge boost)
			{
				if(charge_state != BOOST)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;

					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B | MASK_DPWM1A | MASK_DPWM1B;
					Filter2Regs.FILTERPRESET.all = (1<<27) + (1<<24) + ((1<<23) - boost_duty);
					Filter2Regs.FILTERPRESET.all = (1<<27) + (3<<24) + ((1<<23) - boost_duty);
					Filter2Regs.COEFCONFIG.all = 0x02222222;//use coefficient set C
					for(i=0;i<40;i++)
					{
						asm(" nop");
					}
					MiscAnalogRegs.GLBIOEN.all = MASK_TDO | MASK_TDI | MASK_TMS | MASK_FAULT2 | MASK_DPWM0A | MASK_DPWM0B;

					charge_state = BOOST;

					MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1

					interrupt_counter1 = 0;
					buck_hysteresis = BOUNDARY;
					boost_hysteresis = BOUNDARY;
				}

				interrupt_counter1 ++;
				if(interrupt_counter1 > 19)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q1
					asm(" nop");//about 120ns
					MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0B;	//turn on Q2
					asm(" nop");
					MiscAnalogRegs.GLBIOVAL.all = 0;	//turn off Q2
					MiscAnalogRegs.GLBIOVAL.all = MASK_DPWM0A;	//turn on Q1
					interrupt_counter1 = 0;
				}
			}

//			if(adc_values.v_bus_sense > vbus_backup_voltage)//VBUS is back
			if(adc_values.i_bat_sense > (200 + ibat_adc_offset))//VBUS is back
			{
				MiscAnalogRegs.GLBIOEN.all |= MASK_DPWM2A;
				MiscAnalogRegs.GLBIOVAL.all |= MASK_DPWM2A;
				interrupt_counter2 ++;
				if(interrupt_counter2 >= 4)
				{
					MiscAnalogRegs.GLBIOVAL.all = 0;
					LoopMuxRegs.GLBEN.all = 0; //gloable disable all PE and DPWM
					FaultMuxRegs.DCOMPCTRL0.bit.CNT_CLR = 0;
					FaultMuxRegs.DCOMPCTRL0.bit.INT_EN = 1; //enable BUS UVP
					supply_state = STATE_IDLE;
				}
			}
			else
			{
				interrupt_counter2 = 0;
			}
		}
	}
}

inline void fault_state_handler(void)
{
	switch(fault_type)
	{
		case BUS_OVP:
			break;

		case BUS_UVP:
			break;

		case BUS_OCP:
			break;

		case BAT_OVP:
			break;

		case BAT_UVP:
			if(adc_values_avg.v_bus_sense > vbus_backup_voltage)//VBUS is back
			{
				interrupt_counter1 ++;
			}
			else
			{
				interrupt_counter1 = 0;
			}

			if(interrupt_counter1 > 10)
			{
				supply_state = STATE_IDLE;
			}
			break;

		case BAT_OCP:
			break;

		default:
			break;
	}
}

#pragma INTERRUPT(standard_interrupt,IRQ)
void standard_interrupt(void)
{
	poll_adc();

	switch(supply_state)
	{
		case STATE_IDLE :
			idle_state_handler();
			break;

		case STATE_RAMP_UP :
			ramp_up_state_handler();
			break;

		case STATE_CC_CHARGE :
			cc_charge_state_handler();
			break;

		case STATE_CV_CHARGE :
			cv_charge_state_handler();
			break;

		case STATE_TOPPING_CHARGE :
			topping_charge_state_handler();
			break;

		case STATE_BACKUP:
			backup_state_handler();
			break;

		case STATE_FAULT:
			fault_state_handler();
			break;

		default:
			break;
	}
	TimerRegs.T16PWM0CMPCTRL.all = 3; //clear interrupt bit by a read/write.
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

