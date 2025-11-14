#include "include.h"

void init_front_end2(void)
{
	FeCtrl2Regs.EADCCTRL.bit.AFE_GAIN = 1;
}

void init_filter2(void)
{
	//for buck
	Filter2Regs.FILTERKPCOEF0.bit.KP_COEF_0 = 30000;//20000;//8000;
	Filter2Regs.FILTERKICOEF0.bit.KI_COEF_0 = 200;
	Filter2Regs.FILTERKDCOEF0.bit.KD_COEF_0 = 30000;//20000;//12000;
	Filter2Regs.FILTERKDALPHA.bit.KD_ALPHA_0 = 100;//50;

	//for buck-boost
	Filter2Regs.FILTERKPCOEF0.bit.KP_COEF_1 = 30000;//20000;//10000;
	Filter2Regs.FILTERKICOEF0.bit.KI_COEF_1 = 200;
	Filter2Regs.FILTERKDCOEF0.bit.KD_COEF_1 = 30000;//20000;//18000;
	Filter2Regs.FILTERKDALPHA.bit.KD_ALPHA_1 = 200;//180;

	//for boost
	Filter2Regs.FILTERKPCOEF1.bit.KP_COEF_2 = 30000;//10000;
	Filter2Regs.FILTERKICOEF1.bit.KI_COEF_2 = 300;//400;
	Filter2Regs.FILTERKDCOEF1.bit.KD_COEF_2 = 20000;//1000;

	Filter2Regs.FILTERCTRL.bit.OUTPUT_MULT_SEL = 1;//PID output multiply with period
	Filter2Regs.FILTERCTRL.bit.OUTPUT_SCALE = 0;//no scale

	Filter2Regs.FILTERKICLPHI.bit.KI_CLAMP_HIGH = 0x7FFFF0;
	Filter2Regs.FILTERKICLPLO.bit.KI_CLAMP_LOW 	= 0x800010;

	Filter2Regs.FILTERYNCLPHI.all = 0x785000;//clamp to 94%
	Filter2Regs.FILTERYNCLPLO.all = 0x3D70A;//3% 0x7AE14;//6%
//	Filter2Regs.FILTERYNCLPHI.all = 0x733333;//clamp to 90%
//	Filter2Regs.FILTERYNCLPLO.all = 0xCCCCC;//10%

    Filter2Regs.FILTERCTRL.bit.FILTER_EN = 1; //enable OK here, because nothing will happen until DPWM and front end are globally enabled
}

void init_voltage_loop_mux(void)
{
	LoopMuxRegs.SAMPTRIGCTRL.bit.FE2_TRIG_DPWM0_EN = 1; //use DPWM0 for FE2 sample trigger

	LoopMuxRegs.FILTERMUX.bit.FILTER2_FE_SEL = 2; //use FE2 to drive CLA2
	LoopMuxRegs.FILTERMUX.bit.FILTER2_PER_SEL = 0;//CLA0 switching period select from DPWM0
}

void init_bus_voltage_loop(void)
{
	init_front_end2();
	init_filter2();
	init_voltage_loop_mux();
}


