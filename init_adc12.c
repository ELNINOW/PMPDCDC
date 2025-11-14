#include "include.h"

void init_adc12(void)
{
	AdcRegs.ADCCTRL.bit.MAX_CONV = NUMBER_OF_ADC_CHANNELS_ACTIVE - 1; 

    AdcRegs.ADCCTRL.bit.SINGLE_SWEEP = 0; //Use continous mode
   	AdcRegs.ADCCTRL.bit.SAMPLING_SEL = 6;//267KS/s

	AdcRegs.ADCSEQSEL0.bit.SEQ0  = 3; 	//VBUS
	AdcRegs.ADCSEQSEL0.bit.SEQ1  = 1;	//VBAT
	AdcRegs.ADCSEQSEL0.bit.SEQ2  = 0; 	//IBUS
	AdcRegs.ADCSEQSEL0.bit.SEQ3  = 13; 	//IBAT

	AdcRegs.ADCAVGCTRL.bit.AVG0_EN = 1;	//Enable averaging
	AdcRegs.ADCAVGCTRL.bit.AVG1_EN = 1;	//Enable averaging 
	AdcRegs.ADCAVGCTRL.bit.AVG2_EN = 1;	//Enable averaging
	AdcRegs.ADCAVGCTRL.bit.AVG3_EN = 1;	//Enable averaging

	AdcRegs.ADCAVGCTRL.bit.AVG0_CONFIG = 1;//0-4x average, 1-8x average, 2-16x average, 3-32x average
	AdcRegs.ADCAVGCTRL.bit.AVG1_CONFIG = 1;//0-4x average, 1-8x average, 2-16x average, 3-32x average
	AdcRegs.ADCAVGCTRL.bit.AVG2_CONFIG = 3;//0-4x average, 1-8x average, 2-16x average, 3-32x average
	AdcRegs.ADCAVGCTRL.bit.AVG3_CONFIG = 3;//0-4x average, 1-8x average, 2-16x average, 3-32x average

	AdcRegs.ADCCTRL.bit.ADC_EN   = 1;	//Enable ADC
	AdcRegs.ADCCTRL.bit.SW_START = 1;	//Send start bit high
	AdcRegs.ADCCTRL.bit.SW_START = 0;	//Send start bit low
}
