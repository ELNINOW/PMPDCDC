//init_protection
#include "include.h"

//inline void init_bus_ovp(void) //analog comparator B for bus ovp
//{
//    FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_THRESH = (((VBUS_OVP_LIMIT * VBUS_COMP_SCALER) / 10 + adc_values_avg.v_bus_sense) >> 5) - 1;
//
//    FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_SEL = 0;        //Use threshold register for trip
//    FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_POL = 1;        //Above thresh to trip
//
//    FaultMuxRegs.DPWM0FLTABDET.bit.ACOMP_B_EN = 1;  //must enable to detect
//	FaultMuxRegs.DPWM1FLTABDET.bit.ACOMP_B_EN = 1;
//}

inline void init_bus_uvp(void) //EADC2 for bus uvp to trigger fast interrupt
{
	FeCtrl2Regs.EADCDAC.all = (((vbus_filtered >> 9) * 100) >> 4) - ((VBUS_BACKUP_LIMIT * VBUS_DAC_SCALER) / 10);
	FaultMuxRegs.DCOMPCTRL0.bit.FE_SEL = 5;
	FaultMuxRegs.DCOMPCTRL0.bit.COMP_POL = 1;
	FaultMuxRegs.DCOMPCTRL0.bit.CNT_THRESH = 3;
	FaultMuxRegs.DCOMPCTRL0.bit.CNT_CLR = 0;
	FaultMuxRegs.DCOMPCTRL0.bit.CNT_CONFIG = 1;
	FaultMuxRegs.DCOMPCTRL0.bit.THRESH = 5;
	FaultMuxRegs.DCOMPCTRL0.bit.COMP_EN = 1;
}

//inline void init_bat_ocp(void) //analog comparator E for ocp
//{
//    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_THRESH = (IBAT_OCP_LIMIT * 2 * IBAT_COMP_SCALER) >> 5;
//
//    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_SEL = 0;        //Configures reference of analog comparator E to ACOMP_E_THRESH
//    FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_POL = 1;        //Polarity of comparator when an event is detected.
//
//    FaultMuxRegs.DPWM0FLTABDET.bit.ACOMP_E_EN = 1;
//	FaultMuxRegs.DPWM1FLTABDET.bit.ACOMP_E_EN = 1;
//
//    Dpwm0Regs.DPWMFLTCTRL.bit.AB_MAX_COUNT = 0;
//    Dpwm1Regs.DPWMFLTCTRL.bit.AB_MAX_COUNT = 0;
//}

inline void enable_protection(void)
{
	Dpwm0Regs.DPWMFLTCTRL.bit.ALL_FAULT_EN = 1;
	Dpwm1Regs.DPWMFLTCTRL.bit.ALL_FAULT_EN = 1;

	FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_EN = 1;  // Global enable to start all ACOMPS (REQUIRED)
} 

void init_protection(void)
{
//	init_bus_ovp();
	init_bus_uvp();
//	init_bat_ocp();
	enable_protection();
}

