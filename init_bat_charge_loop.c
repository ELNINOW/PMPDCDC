#include "include.h"

void init_front_end0(void)
{
	FeCtrl0Regs.EADCCTRL.bit.AFE_GAIN = 1;

	FeCtrl0Regs.EADCDAC.all = (VBAT_SETPOINT * VBAT_DAC_SCALER) / 10;
}

void init_filter0(void)//for CV
{
	//for buck
	Filter0Regs.FILTERKPCOEF0.bit.KP_COEF_0 = 30000;//20000;//8000;
	Filter0Regs.FILTERKICOEF0.bit.KI_COEF_0 = 200;
	Filter0Regs.FILTERKDCOEF0.bit.KD_COEF_0 = 30000;//20000;//12000;
	Filter0Regs.FILTERKDALPHA.bit.KD_ALPHA_0 = 100;//50;

	//for busk-boost
	Filter0Regs.FILTERKPCOEF0.bit.KP_COEF_1 = 30000;//20000;//10000;
	Filter0Regs.FILTERKICOEF0.bit.KI_COEF_1 = 200;
	Filter0Regs.FILTERKDCOEF0.bit.KD_COEF_1 = 30000;//20000;//18000;
	Filter0Regs.FILTERKDALPHA.bit.KD_ALPHA_1 = 200;//180;

	//for boost
	Filter0Regs.FILTERKPCOEF1.bit.KP_COEF_2 = 30000;//10000;
	Filter0Regs.FILTERKICOEF1.bit.KI_COEF_2 = 300;//400;
	Filter0Regs.FILTERKDCOEF1.bit.KD_COEF_2 = 20000;//1000;

	Filter0Regs.FILTERCTRL.bit.OUTPUT_MULT_SEL = 1;//PID output multiply with period
	Filter0Regs.FILTERCTRL.bit.OUTPUT_SCALE = 0;//no scale

	Filter0Regs.FILTERKICLPHI.bit.KI_CLAMP_HIGH = 0x7FFFF0;
	Filter0Regs.FILTERKICLPLO.bit.KI_CLAMP_LOW 	= 0x800010;

	Filter0Regs.FILTERYNCLPHI.all = 0x785000;//clamp to 94%
	Filter0Regs.FILTERYNCLPLO.all = 0x3D70A;//3% 0x7AE14;//6%
//	Filter0Regs.FILTERYNCLPHI.all = 0x733333;//clamp to 90%
//	Filter0Regs.FILTERYNCLPLO.all = 0xCCCCC;//10%

	Filter0Regs.FILTERCTRL.bit.FILTER_EN = 1;//enable OK here, because nothing will happen until DPWM and front end are globally enabled
}

void init_front_end1(void)
{
	FeCtrl1Regs.EADCCTRL.bit.AFE_GAIN = 1;

	FeCtrl1Regs.EADCDAC.all = 0;//IBAT_CHARGE_CURRENT * IBAT_DAC_SCALER;
}

void init_filter1(void)//for CC
{
	//for Buck
	Filter1Regs.FILTERKPCOEF0.bit.KP_COEF_0 = 500;
	Filter1Regs.FILTERKICOEF0.bit.KI_COEF_0 = 10;
	Filter1Regs.FILTERKDCOEF0.bit.KD_COEF_0 = 2000;
	Filter1Regs.FILTERKDALPHA.bit.KD_ALPHA_0 = 50;

	//for Buck-Boost
	Filter1Regs.FILTERKPCOEF0.bit.KP_COEF_1 = 500;
	Filter1Regs.FILTERKICOEF0.bit.KI_COEF_1 = 10;
	Filter1Regs.FILTERKDCOEF0.bit.KD_COEF_1 = 2000;
	Filter1Regs.FILTERKDALPHA.bit.KD_ALPHA_1 = 50;

	//for boost
	Filter1Regs.FILTERKPCOEF1.bit.KP_COEF_2 = 500;
	Filter1Regs.FILTERKICOEF1.bit.KI_COEF_2 = 5;
	Filter1Regs.FILTERKDCOEF1.bit.KD_COEF_2 = 1500;

	Filter1Regs.FILTERCTRL.bit.OUTPUT_MULT_SEL = 1;//PID output multiply with period
	Filter1Regs.FILTERCTRL.bit.OUTPUT_SCALE = 0;//no scale

	Filter1Regs.FILTERKICLPHI.bit.KI_CLAMP_HIGH = 0x7FFFF0;
	Filter1Regs.FILTERKICLPLO.bit.KI_CLAMP_LOW 	= 0x800010;

	Filter1Regs.FILTERYNCLPHI.all = 0x785000;//clamp to 94%
	Filter1Regs.FILTERYNCLPLO.all = 0x3D70A;//3% 0x7AE14;//6%
//	Filter1Regs.FILTERYNCLPHI.all = 0x666666;//80%//0x785000;//clamp to 94%
//	Filter1Regs.FILTERYNCLPLO.all = 0;//0x4CCCCC;//0;

	Filter1Regs.FILTERCTRL.bit.FILTER_EN = 1;//enable OK here, because nothing will happen until DPWM and front end are globally enabled
}

void init_battery_loop_mux(void)
{
	LoopMuxRegs.SAMPTRIGCTRL.bit.FE0_TRIG_DPWM1_EN = 1; //use DPWM1 for FE0 sample trigger
	LoopMuxRegs.FILTERMUX.bit.FILTER0_FE_SEL = 0; //use FE0 to drive CLA0
	LoopMuxRegs.FILTERMUX.bit.FILTER0_PER_SEL = 1;//CLA0 switching period select from DPWM1

	LoopMuxRegs.SAMPTRIGCTRL.bit.FE1_TRIG_DPWM1_EN = 1; //use DPWM1 for FE1 sample trigger
	LoopMuxRegs.FILTERMUX.bit.FILTER1_FE_SEL = 1; //use FE1 to drive CLA1
	LoopMuxRegs.FILTERMUX.bit.FILTER1_PER_SEL = 1;//CLA1 switching period select from DPWM1
	LoopMuxRegs.DPWMMUX.bit.DPWM0_FILTER_SEL = 1; //CLA1 is providing input to DPWM0
	LoopMuxRegs.DPWMMUX.bit.DPWM1_FILTER_SEL = 1; //CLA1 is providing input to DPWM1

	LoopMuxRegs.DPWMMUX.bit.DPWM1_SYNC_SEL = 0; //DPWM1 sync to DPWM0

	LoopMuxRegs.FECTRL1MUX.bit.DPWM1_FRAME_SYNC_EN = 1;//use DPWM0 to trigger FE1 soft start
}

void init_bat_current_loop(void)
{
	init_front_end0();
	init_filter0();
	init_front_end1();
	init_filter1();
	init_battery_loop_mux();
}

