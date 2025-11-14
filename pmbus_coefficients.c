#include "include.h"

extern volatile const FILTER_PMBUS_REGS filter0_pmbus_regs_constants;
extern volatile const FILTER_PMBUS_REGS filter0_pmbus_regs_constants_b;
extern volatile const FILTER_PMBUS_REGS filter1_pmbus_regs_constants;
extern volatile const FILTER_PMBUS_REGS filter1_pmbus_regs_constants_b;
extern volatile const Uint32 pmbus_checksum;
extern volatile const Uint32 pmbus_checksum_b;
extern volatile const PMBUS_DCDC_CONFIG pmbus_dcdc_config_constants[DCDC_PAGE_NUMS];
extern volatile const PMBUS_DCDC_CONFIG pmbus_dcdc_config_constants_b[DCDC_PAGE_NUMS];
extern volatile const PMBUS_DCDC_CONFIG_NONPAGED pmbus_dcdc_config_nonpaged_constants;
extern volatile const PMBUS_DCDC_CONFIG_NONPAGED pmbus_dcdc_config_nonpaged_constants_b;
extern volatile const PMBUS_DCDC_CAL pmbus_dcdc_cal_constants[DCDC_PAGE_NUMS];
extern volatile const PMBUS_DCDC_CAL pmbus_dcdc_cal_constants_b[DCDC_PAGE_NUMS];
extern volatile const PMBUS_DCDC_CAL_NONPAGED pmbus_dcdc_cal_nonpaged_constants;
extern volatile const PMBUS_DCDC_CAL_NONPAGED pmbus_dcdc_cal_nonpaged_constants_b;


void copy_coefficients_to_filter(volatile struct FILTER_REGS *dest, 
								 const FILTER_PMBUS_REGS *source)
{
	dest->COEFCONFIG.all    	 = source->COEFCONFIG.all;
	dest->FILTERKPCOEF0.all 	 = source->FILTERKPCOEF0.all;
	dest->FILTERKPCOEF1.all 	 = source->FILTERKPCOEF1.all;
	dest->FILTERKICOEF0.all 	 = source->FILTERKICOEF0.all;
	dest->FILTERKICOEF1.all 	 = source->FILTERKICOEF1.all;
	dest->FILTERKDCOEF0.all 	 = source->FILTERKDCOEF0.all;
	dest->FILTERKDCOEF1.all  	 = source->FILTERKDCOEF1.all;
	dest->FILTERKDALPHA.all 	 = source->FILTERKDALPHA.all;
	dest->FILTERNL0.all     	 = source->FILTERNL0.all;
	dest->FILTERNL1.all     	 = source->FILTERNL1.all;
	dest->FILTERNL2.all     	 = source->FILTERNL2.all;
	dest->FILTERKICLPHI.all 	 = source->FILTERKICLPHI.all;
	dest->FILTERKICLPLO.all 	 = source->FILTERKICLPLO.all;
	dest->FILTERYNCLPHI.all 	 = source->FILTERYNCLPHI.all;
	dest->FILTERYNCLPLO.all 	 = source->FILTERYNCLPLO.all;
	dest->FILTERCTRL.bit.NL_MODE = source->FILTER_MISC.bit.NL_MODE;
}

void copy_coefficients_to_ram(volatile FILTER_PMBUS_REGS *dest, 
							  volatile struct FILTER_REGS *source)
{
	dest->COEFCONFIG.all 	  	  = source->COEFCONFIG.all;
	dest->FILTERKPCOEF0.all 	  = source->FILTERKPCOEF0.all;
	dest->FILTERKPCOEF1.all 	  = source->FILTERKPCOEF1.all;
	dest->FILTERKICOEF0.all 	  = source->FILTERKICOEF0.all;
	dest->FILTERKICOEF1.all 	  = source->FILTERKICOEF1.all;
	dest->FILTERKDCOEF0.all 	  = source->FILTERKDCOEF0.all;
	dest->FILTERKDCOEF1.all 	  = source->FILTERKDCOEF1.all;
	dest->FILTERKDALPHA.all 	  = source->FILTERKDALPHA.all;
	dest->FILTERNL0.all 		  = source->FILTERNL0.all;
	dest->FILTERNL1.all 	  	  = source->FILTERNL1.all;
	dest->FILTERNL2.all 		  = source->FILTERNL2.all;
	dest->FILTERKICLPHI.all 	  = source->FILTERKICLPHI.all;
	dest->FILTERKICLPLO.all 	  = source->FILTERKICLPLO.all;
	dest->FILTERYNCLPHI.all 	  = source->FILTERYNCLPHI.all;
	dest->FILTERYNCLPLO.all 	  = source->FILTERYNCLPLO.all;
	dest->FILTER_MISC.bit.NL_MODE = source->FILTERCTRL.bit.NL_MODE;
}

void pmbus_data_translation(void)
{
//	pmbus_dcdc_config_translated[0].vout_cmd 			= ((Uint32)pmbus_dcdc_config[0].vout_cmd * VOUT_DAC_SCALER) >> VOUT_MODE_EXP;
//	pmbus_dcdc_config_translated[0].vout_ov_fault_limit = ((Uint32)pmbus_dcdc_config[0].vout_ov_fault_limit * VOUT_COMP_SCALER) >> (VOUT_MODE_EXP + 5);
//	pmbus_dcdc_config_translated[0].iout_oc_fault_limit = (linear11_translation(pmbus_dcdc_config[0].iout_oc_fault_limit, 0) * IOUT_COMP_SCALER) >> 5;
//	pmbus_dcdc_config_translated[0].iin_oc_fault_limit  = (linear11_translation(pmbus_dcdc_config[0].iin_oc_fault_limit, 0) * IIN_COMP_SCALER);
//	pmbus_dcdc_config_translated[0].temp_ot_fault_limit = (linear11_translation(pmbus_dcdc_config[0].temp_ot_fault_limit, 0) * TEMP_AD12_SCALER) + TEMP_AD12_OFFSET;
//	pmbus_dcdc_config_translated[0].cpcc_imax = linear11_translation(pmbus_dcdc_config[0].cpcc_imax, 0) * IOUT_DAC_SCALER;
//	pmbus_dcdc_config_translated[0].cpcc_pmax = (linear11_translation(pmbus_dcdc_config[0].cpcc_pmax, 0) * POUT_SCALER);
}

void restore_filter0(void)
{
	copy_coefficients_to_filter(&Filter0Regs, &filter0_pmbus_regs);

	FeCtrl0Regs.EADCCTRL.bit.AFE_GAIN = filter0_pmbus_regs.FILTER_MISC.bit.AFE_GAIN;

	Dpwm0Regs.DPWMCTRL2.bit.SAMPLE_TRIG1_OVERSAMPLE = filter0_pmbus_regs.FILTER_MISC.bit.SAMPLE_TRIG1_OVERSAMPLE;
}

void restore_filter1(void)
{
	copy_coefficients_to_filter(&Filter1Regs, &filter1_pmbus_regs);

	FeCtrl1Regs.EADCCTRL.bit.AFE_GAIN = filter1_pmbus_regs.FILTER_MISC.bit.AFE_GAIN;

	Dpwm1Regs.DPWMCTRL2.bit.SAMPLE_TRIG1_OVERSAMPLE = filter1_pmbus_regs.FILTER_MISC.bit.SAMPLE_TRIG1_OVERSAMPLE;
}

void restore_configuration(void)
{
	//config Vout
//	if(supply_state == STATE_REGULATED)
//	{
//		FeCtrl0Regs.EADCDAC.bit.DAC_VALUE = pmbus_dcdc_config_translated[0].vout_cmd;
//	}
//	FeCtrl0Regs.RAMPDACEND.bit.RAMP_DAC_VALUE  = pmbus_dcdc_config_translated[0].vout_cmd;
//
//	//config protection
//	FaultMuxRegs.ACOMPCTRL0.bit.ACOMP_B_THRESH = pmbus_dcdc_config_translated[0].vout_ov_fault_limit;
//	FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_E_THRESH = pmbus_dcdc_config_translated[0].iout_oc_fault_limit;
//	FaultMuxRegs.ACOMPCTRL2.bit.ACOMP_F_THRESH = pmbus_dcdc_config_translated[0].iin_oc_fault_limit;
}


Uint8 pmbus_write_restore_default_all(void)//load configuartion from data flash to registers
{
	restore_default_all();

	restore_filter0();

	restore_filter1();

	restore_configuration();

	return PMBUS_SUCCESS; 
}

//==========================================================================================
// pmbus_write_store_default_all()
//	Store all PMBus-configurable variables from RAM to Data Flash.   
//==========================================================================================
Uint8 pmbus_write_store_default_all(void)
{
	Uint8	status;
	Uint32	checksum;

	volatile const  FILTER_PMBUS_REGS*	   		   dest_address_filter0_pmbus_regs;
	volatile const  FILTER_PMBUS_REGS*	   		   dest_address_filter1_pmbus_regs;
	volatile const  PMBUS_DCDC_CONFIG*             dest_address_dcdc_config;
	volatile const  PMBUS_DCDC_CONFIG_NONPAGED*    dest_address_dcdc_config_nonpaged;
	volatile const  PMBUS_DCDC_CAL*                dest_address_dcdc_cal;
	volatile const  PMBUS_DCDC_CAL_NONPAGED*       dest_address_dcdc_cal_nonpaged;

	volatile const Uint32*						   dest_checksum;

	volatile const FILTER_PMBUS_REGS*	   		   opposite_bank_start;

	// Number of bytes to erase is the total size of all the blocks, including the checksum.
	// Assumes that the _a and _b structures are the same size.
	volatile const	Uint32	bytes_to_erase =    
		  sizeof(filter0_pmbus_regs_constants)
		+ sizeof(filter1_pmbus_regs_constants)
		+ sizeof(pmbus_dcdc_config_constants)
		+ sizeof(pmbus_dcdc_config_nonpaged_constants)
		+ sizeof(pmbus_dcdc_cal_constants)
		+ sizeof(pmbus_dcdc_cal_nonpaged_constants)
		+ sizeof(pmbus_checksum);

	// NOTE: This is a SEND BYTE command that requires no additional data validation.
	// ----- EXECUTE COMMAND -----
	// Check for DFlash erase operations in progress
	if (erase_segment_counter > 1)
	{
		// There are multiple segments that still need to be erased.  There is no way to 
		// get them erased in time to avoid a PMBus timeout so we will just report an error
		// and return.
		return PMBUS_OTHER_FAULT;	// CML - Other memory or logic fault has occurred

	}

	// There are one or zero segments left to erase.
	// Wait for any erase that might be in progress to complete.
	// IMPORTANT!  This must be done before attempting to access any DFlash location, 
	// even if it is not in the segment being erased.
	while(DecRegs.DFLASHCTRL.bit.BUSY != 0)
	{
		; //do nothing while busy erasing DFlash
	}

	copy_coefficients_to_ram(&filter0_pmbus_regs, &Filter0Regs);
	filter0_pmbus_regs.FILTER_MISC.bit.AFE_GAIN = FeCtrl0Regs.EADCCTRL.bit.AFE_GAIN;
	filter0_pmbus_regs.FILTER_MISC.bit.SAMPLE_TRIG1_OVERSAMPLE = Dpwm0Regs.DPWMCTRL2.bit.SAMPLE_TRIG1_OVERSAMPLE;

	copy_coefficients_to_ram(&filter1_pmbus_regs, &Filter1Regs);
	filter1_pmbus_regs.FILTER_MISC.bit.AFE_GAIN = FeCtrl1Regs.EADCCTRL.bit.AFE_GAIN;
	filter1_pmbus_regs.FILTER_MISC.bit.SAMPLE_TRIG1_OVERSAMPLE = Dpwm1Regs.DPWMCTRL2.bit.SAMPLE_TRIG1_OVERSAMPLE;

	// Test that the selected bank is completely erased by checking the first and last word.
	// If both are all F's, the bank is completeley erased so use it.
	// (Assumes that all words in between are erased; usually a reasonable assumption.)
	if ((pmbus_checksum == 0xFFFFFFFF)&&(filter0_pmbus_regs_constants.FILTERKDCOEF0.bit.KD_COEF_0 == (signed short)0xFFFF))	// Test Dflash A 
	{	
		// DFlash A is blank. 
		//Store new values in DFlash A and erase DFlash B when done.
		dest_address_filter0_pmbus_regs    = &filter0_pmbus_regs_constants;
		dest_address_filter1_pmbus_regs    = &filter1_pmbus_regs_constants;
		dest_address_dcdc_config          = &pmbus_dcdc_config_constants[0];
		dest_address_dcdc_config_nonpaged = &pmbus_dcdc_config_nonpaged_constants;
		dest_address_dcdc_cal             = &pmbus_dcdc_cal_constants[0];
		dest_address_dcdc_cal_nonpaged    = &pmbus_dcdc_cal_nonpaged_constants;
		dest_checksum			          = &pmbus_checksum;

			opposite_bank_start		= &filter0_pmbus_regs_constants_b;
	}
	else if ((pmbus_checksum_b == 0xFFFFFFFF)&&(filter0_pmbus_regs_constants_b.FILTERKDCOEF0.bit.KD_COEF_0 == (signed short)0xFFFF))	// Test DFlash B 
	{
		// DFlash B is blank.
		// Store new values in DFlash B and erase DFlash A when done.
		dest_address_filter0_pmbus_regs   = &filter0_pmbus_regs_constants_b;
		dest_address_filter1_pmbus_regs   = &filter1_pmbus_regs_constants_b;
		dest_address_dcdc_config          = &pmbus_dcdc_config_constants_b[0];
		dest_address_dcdc_config_nonpaged = &pmbus_dcdc_config_nonpaged_constants_b;
		dest_address_dcdc_cal             = &pmbus_dcdc_cal_constants_b[0];
		dest_address_dcdc_cal_nonpaged    = &pmbus_dcdc_cal_nonpaged_constants_b;
		dest_checksum			          = &pmbus_checksum_b;

			opposite_bank_start		= &filter0_pmbus_regs_constants;
	}
	else
	{
		// Neither bank is blank.  Erase one of them so it will be ready for next time
		// and report a Flash failure.
		if (pmbus_checksum_b == 0xFFFFFFFF)
		{
			// We got here because DFlash B was only partially erased, probably because
			// of a power failure during the erase process.  Re-erase bank B and leave 
			// bank A intact since it might have valid values.
			dest_address_filter0_pmbus_regs	= &filter0_pmbus_regs_constants_b;

		}
		else
		{
			// We got here because DFlash A was partly erased and B was intact,
			// or because both banks were never erased.
			// Either way, we will now erase bank A.
			dest_address_filter0_pmbus_regs	= &filter0_pmbus_regs_constants;
		}
		goto flash_write_failed;	// Fail: Destination bank not erased.
	}


	// --------------- CLA GAINS  ---------------
	// Call Update Flash to write the necessary segments of Data Flash
	status = update_data_flash((void*)dest_address_filter0_pmbus_regs, &filter0_pmbus_regs, sizeof(filter0_pmbus_regs));
	if (status != FLASH_SUCCESS)
	{
		goto flash_write_failed;	// Clean up after flash write failure
	}
	status = update_data_flash((void*)dest_address_filter1_pmbus_regs, &filter1_pmbus_regs, sizeof(filter1_pmbus_regs));
	if (status != FLASH_SUCCESS)
	{
		goto flash_write_failed;	// Clean up after flash write failure
	}
	// --------------- PMBUS CONFIG PER PAGE---------------
	// Call Update Flash to write the necessary segments of Data Flash
	status = update_data_flash((void*)dest_address_dcdc_config, &pmbus_dcdc_config[0], sizeof(pmbus_dcdc_config)); 
	if (status != FLASH_SUCCESS)
	{
		goto flash_write_failed;	// Clean up after flash write failure
	}

	// --------------- PMBUS CONFIG NONPAGED -----------------------
	// Call Update Flash to write the necessary segments of Data Flash
	status = update_data_flash((void*)dest_address_dcdc_config_nonpaged, &pmbus_dcdc_config_nonpaged, sizeof(pmbus_dcdc_config_nonpaged)); 
	if (status != FLASH_SUCCESS)
	{
		goto flash_write_failed;	// Clean up after flash write failure
	}

	// --------------- PMBUS CAL PER PAGE ---------------
	// Call Update Flash to write the necessary segments of Data Flash
	status = update_data_flash((void*)dest_address_dcdc_cal, &pmbus_dcdc_cal[0], sizeof(pmbus_dcdc_cal)); 
	if (status != FLASH_SUCCESS)
	{
		goto flash_write_failed;	// Clean up after flash write failure
	}

	// --------------- PMBUS CAL NONPAGED ---------------
	// Call Update Flash to write the necessary segments of Data Flash
	status = update_data_flash((void*)dest_address_dcdc_cal_nonpaged, &pmbus_dcdc_cal_nonpaged, sizeof(pmbus_dcdc_cal_nonpaged)); 
	if (status != FLASH_SUCCESS)
	{
		goto flash_write_failed;	// Clean up after flash write failure
	}

	// --------------- CHECKSUM ---------------
	// Calculate checksum for selected Data Flash segment and write to Data Flash

	checksum = calculate_dflash_checksum((Uint8*)dest_address_filter0_pmbus_regs, (Uint8*)dest_checksum);
	status = update_data_flash((void*)dest_checksum, &checksum, sizeof(checksum));
	if (status != FLASH_SUCCESS)
	{
		goto flash_write_failed;	// Clean up after flash write failure
	}

	{

		// ----- Bank written successfully.  Erase opposite bank. -----
		start_erase_task((void*)opposite_bank_start, bytes_to_erase);	
		// If everything works, return success.
		return PMBUS_SUCCESS;
	}

	flash_write_failed:		// <--- Destination for several goto's above.
	{
		// ----- This bank write failed.  Erase present bank and report the failure.
		start_erase_task((void*)dest_address_filter0_pmbus_regs, bytes_to_erase);	
		return (PMBUS_MEMORY_FAULT);		// Flash write failed
	}
}

void restore_default_all(void)
{
	Uint32 	checksum;

	// Pointers to structures in Data Flash 

	volatile const  FILTER_PMBUS_REGS*	           filter0_pmbus_regs_ptr;
	volatile const  FILTER_PMBUS_REGS*	           filter1_pmbus_regs_ptr;
	volatile const  PMBUS_DCDC_CONFIG*             dcdc_config_ptr;
	volatile const  PMBUS_DCDC_CONFIG_NONPAGED*    dcdc_config_nonpaged_ptr;
	volatile const  PMBUS_DCDC_CAL*                dcdc_cal_ptr;
	volatile const  PMBUS_DCDC_CAL_NONPAGED*       dcdc_cal_nonpaged_ptr;

	// ----- Look for a copy of default values in Data FLASH that looks valid. -----
	// If none found, use the hard-coded values from Program FLASH.

	// Wait for any erase that might be in progress to complete.
	// IMPORTANT!  This must be done before attempting to access any DFlash location, 
	// even if it is not in the segment being erased.
	while(DecRegs.DFLASHCTRL.bit.BUSY != 0)
	{
		; //do nothing while busy erasing DFlash
	}	

	// Clear latching status bits except MFR_CONFIG_CHANGED which only gets reset by reset.  
	// Each condition will be tested and set as needed below.
	// 	status_mfr_flags &= (1<<MFR_CONFIG_CHANGED);

	// Look in Data Flash A for valid values.
	checksum = calculate_dflash_checksum((Uint8*)&filter0_pmbus_regs_constants, (Uint8*)&pmbus_checksum);
	// A zero checksum only occurs when the segment is all zeroes, which is not valid.
	// If the calculated checksum is nonzero and matches the checksum in the DFlash,  
	// that segment is good, so use it.

	if(   (pmbus_checksum == 0x87654321)	// Hardcoded exception for parms written directly to data flash
		// (GUI download tool does not calculate checksum)
		||((checksum != 0) && (checksum == pmbus_checksum)) )	// Checksum is valid and matches.
	{
		// Checksum A Good: Use default values from DFlash A
		filter0_pmbus_regs_ptr	 = &filter0_pmbus_regs_constants;
		filter1_pmbus_regs_ptr	 = &filter1_pmbus_regs_constants;
		dcdc_config_ptr          = &pmbus_dcdc_config_constants[0];
		dcdc_config_nonpaged_ptr = &pmbus_dcdc_config_nonpaged_constants;
		dcdc_cal_ptr             = &pmbus_dcdc_cal_constants[0];
		dcdc_cal_nonpaged_ptr 	 = &pmbus_dcdc_cal_nonpaged_constants;
	}
	else
	{
		// Look in Data Flash B for valid values
		checksum = calculate_dflash_checksum((Uint8*)&filter0_pmbus_regs_constants_b, (Uint8*)&pmbus_checksum_b);
		// A zero checksum only occurs when the segment is all zeroes, which is not valid.
		// If the calculated checksum is nonzero and matches the checksum in the DFlash,  
		// that segment is good, so use it.
		if ((checksum != 0) && (checksum == pmbus_checksum_b))
		{
			// Checksum B Good: Use default values from DFlash B
			filter0_pmbus_regs_ptr	 = &filter0_pmbus_regs_constants_b;
			filter1_pmbus_regs_ptr	 = &filter1_pmbus_regs_constants_b;
			dcdc_config_ptr          = &pmbus_dcdc_config_constants_b[0];
			dcdc_config_nonpaged_ptr = &pmbus_dcdc_config_nonpaged_constants_b;
			dcdc_cal_ptr             = &pmbus_dcdc_cal_constants_b[0];
			dcdc_cal_nonpaged_ptr 	 = &pmbus_dcdc_cal_nonpaged_constants_b;
		}	
	}

	// ----- Copy default variables from Flash to RAM -----
	memcpy((void *)&filter0_pmbus_regs,    	    (void *)filter0_pmbus_regs_ptr,   sizeof(filter0_pmbus_regs_constants));
	memcpy((void *)&filter1_pmbus_regs,    	    (void *)filter1_pmbus_regs_ptr,   sizeof(filter1_pmbus_regs_constants));
	memcpy((void *)&pmbus_dcdc_config[0],       (void *)dcdc_config_ptr,          sizeof(pmbus_dcdc_config_constants));
	memcpy((void *)&pmbus_dcdc_config_nonpaged, (void *)dcdc_config_nonpaged_ptr, sizeof(pmbus_dcdc_config_nonpaged_constants));
	memcpy((void *)&pmbus_dcdc_cal[0],          (void *)dcdc_cal_ptr,             sizeof(pmbus_dcdc_cal_constants));
	memcpy((void *)&pmbus_dcdc_cal_nonpaged,    (void *)dcdc_cal_nonpaged_ptr,    sizeof(pmbus_dcdc_cal_nonpaged_constants));	

	pmbus_data_translation();//translate PMBus data to real value
}


