#include "include.h"

int32 pmbus_read_one_byte_handler(Uint8 value) 
{
	pmbus_number_of_bytes = 1;
	pmbus_buffer[0] = value;  

	return PMBUS_SUCCESS;
}

int32 pmbus_read_two_byte_handler(Uint16 value) 
{
	pmbus_number_of_bytes = 2;
	pmbus_buffer[1] = value >> 8;
	pmbus_buffer[0] = value & 0xff;

	return PMBUS_SUCCESS;
}

Uint8 pmbus_write_vout_cmd(void)
{
//	pmbus_dcdc_config[0].vout_cmd = pmbus_buffer[1] + (pmbus_buffer[2] << 8);
//	if(supply_state == STATE_IDLE)
//	{
//		pmbus_dcdc_config_translated[0].vout_cmd = ((Uint32)pmbus_dcdc_config[0].vout_cmd * VOUT_DAC_SCALER) >> VOUT_MODE_EXP;
//
//		return PMBUS_SUCCESS;
//	}
//	else if(supply_state == STATE_REGULATED)
//	{
//		pmbus_dcdc_config_translated[0].vout_cmd = ((Uint32)pmbus_dcdc_config[0].vout_cmd * VOUT_DAC_SCALER) >> VOUT_MODE_EXP;
//		FeCtrl0Regs.EADCDAC.bit.DAC_VALUE = pmbus_dcdc_config_translated[0].vout_cmd;
//		FeCtrl0Regs.RAMPDACEND.bit.RAMP_DAC_VALUE  = pmbus_dcdc_config_translated[0].vout_cmd;
//
//		//for current sharing
//		eadc_dac_target = (pmbus_dcdc_config_translated[0].vout_cmd << 3); //Q14<<3=Q17
//		eadc_dac_min =  (eadc_dac_target * 15) >> 4;//11.25V
//		eadc_dac_max =  (eadc_dac_target * 17) >> 4;//12.75V
//
//		return PMBUS_SUCCESS;
//	}
//	else //if it is not in idle or regulation, NACK
	{
		return PMBUS_FAIL; 
	}
}

Uint8 pmbus_read_vout_cmd(void)
{
    pmbus_read_two_byte_handler(pmbus_dcdc_config[0].vout_cmd);
 
	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_vout(void) 
{
//	Uint16 temp;
//
//	temp = (adc_values.vo_sense << VOUT_MODE_EXP) / VOUT_AD12_SCALER;
//	pmbus_read_two_byte_handler(temp);

	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_iout(void)
{
//	Uint16 temp;

//	temp = 0xE000 + (((adc_values.io_sense << 4) / IOUT_AD12_SCALER) & 0x7FF);//exponent -4
//	temp = (((adc_values.io_sense  + IOUT_OFFSET) / IOUT_AD12_SCALER) & 0x7FF);//exponent -4
//
//	pmbus_read_two_byte_handler(temp);

	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_frequency(void)
{
	pmbus_read_two_byte_handler(PWM_FREQUENCY);

	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_temperature1(void)
{
//	int16 temp;

//	temp = (((int32)adc_values.temp - (int32)TEMP_AD12_OFFSET) / (int32)TEMP_AD12_SCALER) & 0x7FF;
//	pmbus_read_two_byte_handler(temp);

	return PMBUS_SUCCESS;
} 

Uint8 pmbus_write_clear_faults(void)
{
	pmbus_status_word = 0;

	return PMBUS_SUCCESS;
}

//OV Fault
Uint8 pmbus_write_vout_ov_fault_limit(void)
{
	pmbus_dcdc_config[0].vout_ov_fault_limit = pmbus_buffer[1] + (pmbus_buffer[2] << 8);
	pmbus_dcdc_config_translated[0].vout_ov_fault_limit = ((Uint32)pmbus_dcdc_config[0].vout_ov_fault_limit * VBUS_COMP_SCALER) >> (VOUT_MODE_EXP + 5);
	FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_THRESH = pmbus_dcdc_config_translated[0].vout_ov_fault_limit;

	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_vout_ov_fault_limit(void)
{
	pmbus_read_two_byte_handler(pmbus_dcdc_config[0].vout_ov_fault_limit);

	return PMBUS_SUCCESS;
}

//OC Fault
Uint8 pmbus_write_iout_oc_fault_limit(void)
{
	pmbus_dcdc_config[0].iout_oc_fault_limit = pmbus_buffer[1] + (pmbus_buffer[2] << 8);
	pmbus_dcdc_config_translated[0].iout_oc_fault_limit = (linear11_translation(pmbus_dcdc_config[0].iout_oc_fault_limit, 0) * IBUS_COMP_SCALER) >> 5;
	FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_THRESH = pmbus_dcdc_config_translated[0].iout_oc_fault_limit;

	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_iout_oc_fault_limit(void)
{
	pmbus_read_two_byte_handler(pmbus_dcdc_config[0].iout_oc_fault_limit);

	return PMBUS_SUCCESS;
}

//OT Fault
Uint8 pmbus_write_temp_ot_fault_limit(void)
{
//	pmbus_dcdc_config[0].temp_ot_fault_limit = pmbus_buffer[1] + (pmbus_buffer[2] << 8);
//	pmbus_dcdc_config_translated[0].temp_ot_fault_limit = (linear11_translation(pmbus_dcdc_config[0].temp_ot_fault_limit, 0) * TEMP_AD12_SCALER) + TEMP_AD12_OFFSET;

	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_temp_ot_fault_limit(void)
{
	pmbus_read_two_byte_handler(pmbus_dcdc_config[0].temp_ot_fault_limit);

	return PMBUS_SUCCESS;
}

//IIN OC Fault
Uint8 pmbus_write_iin_oc_fault_limit(void)
{
//	pmbus_dcdc_config[0].iin_oc_fault_limit = pmbus_buffer[1] + (pmbus_buffer[2] << 8);
//	pmbus_dcdc_config_translated[0].iin_oc_fault_limit  = ((linear11_translation(pmbus_dcdc_config[0].iin_oc_fault_limit, 4) * IIN_COMP_SCALER) >> 4);
//	FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_F_THRESH = pmbus_dcdc_config_translated[0].iin_oc_fault_limit;

	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_iin_oc_fault_limit(void)
{
	pmbus_read_two_byte_handler(pmbus_dcdc_config[0].iin_oc_fault_limit);

	return PMBUS_SUCCESS;
}

int32 sign_extend(int value, int number_of_bits) //sign extends value in lsbits to an int
{
	int32 temp = (int)(value << (32 - number_of_bits)); //shift it up to put sign bit in place
	return temp >> (32 - number_of_bits);
}

Uint8 pmbus_write_deadband_config(void)
{
	return PMBUS_SUCCESS;
}

Uint8 pmbus_read_deadband_config(void)
{
	return PMBUS_SUCCESS;
}
  
// look at command byte from a write perspective
int32 pmbus_write_message(void)
{
	switch (pmbus_buffer[0]) 			
	{
		case PMBUS_CMD_MFR_SPECIFIC_02:
			return pmbus_write_light_load_config();
		case PMBUS_CMD_MFR_SPECIFIC_36:
			return pmbus_write_cpcc_config();
		case PMBUS_CMD_VOUT_OV_FAULT_LIMIT: 
			return pmbus_write_vout_ov_fault_limit();
		case PMBUS_CMD_IOUT_OC_FAULT_LIMIT: 
			return pmbus_write_iout_oc_fault_limit();
		case PMBUS_CMD_OT_FAULT_LIMIT: 
			return pmbus_write_temp_ot_fault_limit();
		case PMBUS_CMD_IIN_OC_FAULT_LIMIT: 
			return pmbus_write_iin_oc_fault_limit();
		case PMBUS_CMD_CLEAR_FAULTS: 
			return pmbus_write_clear_faults();
		case PMBUS_CMD_ROM_MODE: 
			return pmbus_write_rom_mode();
		case PMBUS_CMD_STORE_DEFAULT_ALL: 
			return pmbus_write_store_default_all();
		case PMBUS_CMD_RESTORE_DEFAULT_ALL: 
			return pmbus_write_restore_default_all();
		case PMBUS_CMD_VOUT_COMMAND: 
			return pmbus_write_vout_cmd();
		case PMBUS_CMD_USER_RAM_00: 
			return pmbus_write_user_ram_00();
        case PMBUS_CMD_MFR_PARM_INFO: 
        	return pmbus_write_parm_info();
		case PMBUS_CMD_MFR_PARM_VALUE: 
			return pmbus_write_parm_value();	
		case PMBUS_CMD_MFR_SPECIFIC_42: 
			return pmbus_write_pfc_zvs_enable();
		case PMBUS_CMD_MFR_SPECIFIC_43: 
			return pmbus_write_pfc_os_enable();
		case PMBUS_CMD_MFR_DEADBAND_CONFIG: 
		    return pmbus_write_deadband_config();


		default:
			break;
	}
	return 0; 
}

// look at command byte from a read perspective
int32 pmbus_read_message(void)
{
	switch (pmbus_buffer[0]) 			
	{
		case PMBUS_CMD_MFR_SPECIFIC_02:
			return pmbus_read_light_load_config();
		case PMBUS_CMD_MFR_SPECIFIC_36:
			return pmbus_read_cpcc_config();
		case PMBUS_CMD_VOUT_OV_FAULT_LIMIT: 
			return pmbus_read_vout_ov_fault_limit();
		case PMBUS_CMD_IOUT_OC_FAULT_LIMIT: 
			return pmbus_read_iout_oc_fault_limit();
		case PMBUS_CMD_OT_FAULT_LIMIT: 
			return pmbus_read_temp_ot_fault_limit();
		case PMBUS_CMD_IIN_OC_FAULT_LIMIT: 
			return pmbus_read_iin_oc_fault_limit();
		case PMBUS_CMD_VOUT_MODE: 
			return pmbus_read_one_byte_handler((32 - VOUT_MODE_EXP));
		case PMBUS_CMD_STATUS_BYTE: 
			return pmbus_read_one_byte_handler((Uint8) (pmbus_status_word & 0xFF));
		case PMBUS_CMD_STATUS_WORD: 
			return pmbus_read_two_byte_handler(pmbus_status_word); 
		case PMBUS_CMD_VOUT_COMMAND: 
			return pmbus_read_vout_cmd();
		case PMBUS_CMD_READ_VOUT: 
			return pmbus_read_vout();
		case PMBUS_CMD_READ_IOUT: 
			return pmbus_read_iout();
		case PMBUS_CMD_READ_TEMPERATURE_1: 
			return pmbus_read_temperature1();
        case PMBUS_CMD_MFR_CMDS_DCDC_PAGED: 
        	return pmbus_read_cmd_dcdc_paged();
		case PMBUS_CMD_READ_FREQUENCY: 
			return pmbus_read_two_byte_handler(PWM_FREQUENCY);	
        case PMBUS_CMD_MFR_CMDS_DCDC_NONPAGED: 
        	return pmbus_read_cmd_dcdc_nonpaged();
        case PMBUS_CMD_MFR_CMDS_PFC: 
        	return pmbus_read_cmd_pfc();
		case PMBUS_CMD_MFR_SETUP_ID: 
			return pmbus_read_setup_id();
		case PMBUS_CMD_MFR_DEVICE_ID: 
			return pmbus_read_device_id();	
        case PMBUS_CMD_PMBUS_REVISION: 
        	return pmbus_read_one_byte_handler(0x42); //version 1.2 for both		
		case PMBUS_CMD_MFR_ID: 
			return pmbus_mfr_id_handler(); 
		case PMBUS_CMD_MFR_MODEL: 
			return pmbus_mfr_model_handler(); 
		case PMBUS_CMD_MFR_REVISION: 
			return pmbus_mfr_revision_handler(); 
		case PMBUS_CMD_MFR_LOCATION: 
			return pmbus_mfr_location_handler();
		case PMBUS_CMD_MFR_DATE: 
			return pmbus_mfr_date_handler();
		case PMBUS_CMD_MFR_SERIAL: 
			return pmbus_mfr_serial_handler();
		case PMBUS_CMD_MFR_IC_DEVICE: 
			return pmbus_mfr_ic_device_handler();
		case PMBUS_CMD_MFR_IC_DEVICE_REV: 
			return pmbus_mfr_ic_device_rev_handler();
		case PMBUS_CMD_MFR_DEBUG_BUFFER: 
			return pmbus_read_debug_buffer();
		case PMBUS_CMD_USER_RAM_00: 
			return pmbus_read_user_ram_00();
		case PMBUS_CMD_MFR_PARM_INFO: 
			return pmbus_read_parm_info();
		case PMBUS_CMD_MFR_PARM_VALUE: 
			return pmbus_read_parm_value();
		case PMBUS_CMD_MFR_SPECIFIC_42: 
			return pmbus_read_pfc_zvs_enable();
		case PMBUS_CMD_MFR_SPECIFIC_43: 
			return pmbus_read_pfc_os_enable();
		case PMBUS_CMD_MFR_DEADBAND_CONFIG: 
		    return pmbus_read_deadband_config();

		default:
			pmbus_number_of_bytes = 16;
			pmbus_buffer[0] = 0x0f;
			pmbus_buffer[1] = 0x22;
			pmbus_buffer[2] = 0x33;
			pmbus_buffer[3] = 0x44;
			pmbus_buffer[4] = 0x55;
			pmbus_buffer[5] = 0x66;
			pmbus_buffer[6] = 0x77;
			pmbus_buffer[7] = 0x88;
			pmbus_buffer[8] = 0x99;
			pmbus_buffer[9] = 0xaa;
			pmbus_buffer[10] = 0xbb;
			pmbus_buffer[11] = 0xcc;
			pmbus_buffer[12] = 0xdd;
			pmbus_buffer[13] = 0xee;
			pmbus_buffer[14] = 0xff;
			pmbus_buffer[15] = 0x01;
			return 0;
	}
}


