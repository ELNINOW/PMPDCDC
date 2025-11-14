#ifdef MAIN 					// If it is the main routine
	#define EXTERN	 			// If it isn't extern, so define it as nothing
#else 							// If it isn't the main routine
	#define EXTERN extern 		// If it is extern
#endif

typedef void (*FUNC_PTR)(); 	//used for zeroing instruction word.

typedef struct  
{
	Uint32 v_bus_sense; 		//Value from adc for Vin
	Uint32 i_bus_sense; 			//Value from adc for Ishare
	Uint32 v_bat_sense; 		//Value from adc for Vout
	Uint32 i_bat_sense; 			//Value from adc for primary current sense
}ADC_VALUES_STRUCT;

typedef enum
{
	STATE_IDLE,
	STATE_RAMP_UP,
	STATE_CC_CHARGE,
	STATE_CV_CHARGE,
	STATE_TOPPING_CHARGE,
	STATE_BACKUP,
	STATE_FAULT
}SUPPLY_STATE;

typedef enum
{
	NO_FAULT,
	BUS_OVP,
	BUS_UVP,
	BUS_OCP,
	BAT_OVP,
	BAT_UVP,
	BAT_OCP,
}FAULT_TYPE;

EXTERN ADC_VALUES_STRUCT adc_values; 	//ADC Readings
EXTERN ADC_VALUES_STRUCT adc_values_avg;//ADC Readings Averaged
EXTERN SUPPLY_STATE supply_state; 		//Supply state enum for state machine
EXTERN FAULT_TYPE fault_type;

EXTERN Uint8 erase_segment_counter;	// Number of DFlash segment remaining to be erased
EXTERN Uint8 erase_segment_number;	// DFlash segment number being erased
EXTERN Uint8 flash_write_status;	// Global status while attempting to write to Data Flash.

EXTERN Uint32 interrupt_counter1, interrupt_counter2, interrupt_counter3;
EXTERN Uint32 hiccup_counter_oc;
EXTERN Uint32 hiccup_counter_ov;

EXTERN int32 current_share_kp;
EXTERN int32 current_error;
EXTERN int32 eadc_dac_target;
EXTERN int32 eadc_dac_max;
EXTERN int32 eadc_dac_min;
EXTERN int32 vloop_filter;
EXTERN int32 iloop_filter;
EXTERN Uint32 pout;

EXTERN	Uint8	parm_index;
EXTERN	int16	parm_offset;	
EXTERN	Uint8	parm_count;		
EXTERN	Uint8	parm_size;	

EXTERN Uint8 pmbus_buffer[40] ;
EXTERN Uint8 pmbus_state;
EXTERN Uint8 pmbus_number_of_bytes;
EXTERN Uint8 pmbus_buffer_position;
EXTERN Uint16 pmbus_status_half_word_0_value; //save pmbus status, since cleared on read.
EXTERN Uint16 pmbus_status_half_word_0_value_ored; //for debug

/////////////////////////////////////////////////////////
//non-paged variables
//the same for both PFC and DCDC
////////////////////////////////////////////////////////// 

EXTERN Uint8 				debug_buffer[8];
EXTERN Uint8  				page;
EXTERN Uint8                pmbus_status_temperature;
EXTERN Uint8                pmbus_status_input;
EXTERN Uint8                pmbus_status_cml;
EXTERN Uint8                pmbus_status_fans_1_2;
EXTERN Uint8                pmbus_status_fans_3_4;
EXTERN Uint16               pmbus_status_word;
EXTERN Uint16               second_pmbus_status_word;
EXTERN Uint8                setup_id_length;

EXTERN Uint8 gui_constant_pointer;
EXTERN Uint8 user_ram_00;
EXTERN char	status_cml;	 // STATUS_CML (Communication, Logic, and Memory) for entire board

EXTERN Uint32 debug1,debug2;

EXTERN Uint32 charge_state;
EXTERN Uint32 buck_hysteresis, boost_hysteresis;
EXTERN Uint32 pulse_state;
EXTERN Uint32 backup_duty;
EXTERN Uint32 vbus_filtered, vbus_backup_voltage, vbus_norminal;
EXTERN Uint32 buck_duty, buckboost_duty, boost_duty;
EXTERN Uint32 ibat_adc_offset;







