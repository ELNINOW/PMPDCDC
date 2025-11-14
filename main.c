//main.c

#define MAIN (1)//Declaring MAIN forces the EXTERN variables to be defined
#include "include.h"  

void main()
{
	MiscAnalogRegs.IOMUX.all = 0; //enable JTAG

	init_gpio();

	//Check to see if pin22 is pulled low,or flash trim checksum is bad, if yes then go to ROM.
	if((MiscAnalogRegs.GLBIOREAD.bit.TDO_IO_READ == 0) || (PMBusRegs.PMBCTRL1.bit.SLAVE_ADDR == 0x7e))
	{
//		pmbus_write_rom_mode();
	}

	init_adc12();

	init_pmbus();

	poll_adc();

	while((adc_values_avg.v_bat_sense < 800) || VBUS_VOLTAGE_LOW)//no battery or bus too low
	{
		pmbus_handler();
		poll_adc();
	}

	vbus_norminal = adc_values_avg.v_bus_sense;
	delay();

	while(abs(adc_values_avg.v_bus_sense - vbus_norminal) > 10)//vin not stable yet
	{
		pmbus_handler();
		vbus_norminal = adc_values_avg.v_bus_sense;
		delay();
		delay();
		poll_adc();
	}

	ibat_adc_offset = adc_values_avg.i_bat_sense;

	init_bus_voltage_loop();

	init_dpwms();

	init_bat_current_loop();

	init_miscellaneous();

	init_protection();

	init_timer_interrupt();

	vbus_filtered = adc_values.v_bus_sense << 9;

	for(;;)
	{
		pmbus_handler();

		buck_duty = (((Uint64)adc_values_avg.v_bat_sense) << 23) / adc_values_avg.v_bus_sense;
		buckboost_duty = (((Uint64)adc_values_avg.v_bat_sense) << 23) / (adc_values_avg.v_bat_sense + adc_values.v_bus_sense);
		boost_duty = (((Uint64)(adc_values_avg.v_bat_sense - adc_values_avg.v_bus_sense)) << 23) / adc_values_avg.v_bat_sense;

		if((supply_state != STATE_BACKUP))// && (supply_state != STATE_FAULT))
		{
			vbus_norminal = vbus_filtered >> 9;
			FeCtrl2Regs.EADCDAC.all = ((vbus_norminal * 100) >> 4) - ((VBUS_BACKUP_LIMIT * VBUS_DAC_SCALER) / 10);
			vbus_backup_voltage = vbus_norminal - ((VBUS_BACKUP_LIMIT * VBUS_AD12_SCALER) / 20);

			Filter2Regs.FILTERPRESET.all = (1<<27) + (1<<24) + ((1<<23) - buckboost_duty);
			Filter2Regs.FILTERPRESET.all = (1<<27) + (3<<24) + ((1<<23) - buckboost_duty);
		}
	}
}

//#pragma INTERRUPT(c_int00,RESET)     // CCS 5.4 and up will give a compile time error for interrupt handlers not compiled in ARM mode
void c_int00(void)
{
	main();
}
