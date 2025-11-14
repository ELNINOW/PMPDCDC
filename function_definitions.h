#include "pmbus_coefficients.h"

void char_out(char data);

void init_Filter0(void);
void init_Filter1(void);
void init_front_end0(void);
void init_front_end1(void);
void init_uart0(void);
void init_uart1(void);
void zero_out_integrity_word(void);
int pmbus_write_rom_mode(void);
void watchdog_reset(void);
void init_timer_interrupt(void);
void init_gpio(void);
void init_filter0(void);
void init_filter1(void);
void init_adc12(void);
void poll_adc(void);
void clear_faults(void);
void uart_transmit_data(void);
void translate_raw_to_text(void);
void uart_process_rx_data(void);
char translate_nybble_out(char byte,char * pchar2 );
char translate_nybble_in(char nyb);
void translate_text_to_raw(void);
inline void uart_receive_data(void);
int pmbus_write_light_load_enable(void);
Uint8 pmbus_read_light_load_enable(void);

int pmbus_write_pfc_zvs_enable(void);
Uint8 pmbus_read_pfc_zvs_enable(void);
int pmbus_write_pfc_os_enable(void);
Uint8 pmbus_read_pfc_os_enable(void);
void cpcc_init(void);
void cpcc_enable(void);
void cpcc_disable(void);
void filter1_jam(void);
void send_string(const Uint8 string_to_send[], Uint8 num_bytes);
int pmbus_mfr_model_handler(void);
int pmbus_mfr_revision_handler(void);
int pmbus_mfr_id_handler(void);
int32 pmbus_read_two_byte_handler(Uint16 value);
int32 pmbus_read_one_byte_handler(Uint8 value);
Uint8 start_erase_task(const void* dest_ptr, Uint16 byte_count);
Uint32 calculate_dflash_checksum(Uint8 *start_addr, Uint8 *end_addr);
inline Uint8 calc_flash_segments(const void* dest_ptr, Uint16 byte_count, Uint8* first_segment);
void clear_program_flash(void);
Uint8 pmbus_write_store_default_all(void);
Uint8 pmbus_write_restore_default_all(void);
void init_pmbus_variables(void);
void translate_data_from_literal_to_translated( Uint16 *raw_data, Uint16 *translated_data, Uint8 shift_exponent, Uint16 numerator_factor, Uint16 denominator_factor);
void write_program_flash_word(int * address, int data);
void look_for_interrupted_dflash_erase(void);
Uint8 update_data_flash(void* dest_ptr, const void* src_ptr, Uint16 byte_count);
void erase_task(void);
void erase_one_section(int first_segment, int byte_count);
Uint8 pmbus_write_dflash_test(void);
void copy_coefficients_to_filter(volatile struct FILTER_REGS *dest, const FILTER_PMBUS_REGS *source);
void copy_coefficients_to_ram(volatile FILTER_PMBUS_REGS *dest, volatile struct FILTER_REGS *source);
Uint8 pmbus_write_vout_transition_rate(void);
Uint8 pmbus_read_vout_transition_rate(void);
Uint8 pmbus_write_vout_cmd(void);
Uint8 pmbus_read_vout_cmd(void);
Uint8 pmbus_write_ton_rise(void);
Uint8 pmbus_read_ton_rise(void);
void configure_ton_rise(void);
int8 unpack_literal_11(Uint16 *raw_data, Uint16 *mantissa, Uint8 *shift_exponent);
unsigned short unsigned_short_q_multiply(unsigned short multiplier,unsigned short multiplicand);
int32 handle_running_faults(void);
void transition_to_idle_state(void);
void control_sr_on_off(void);
void cccp_dac_adjust(void);
int pmbus_mfr_date_handler(void);
int pmbus_mfr_location_handler(void);
int pmbus_mfr_serial_handler(void);
Uint8 pmbus_read_vout_ov_fault_limit(void);

Uint8 pmbus_read_iout_oc_fault_limit(void);

Uint8 pmbus_read_temp_ot_fault_limit(void);

Uint8 pmbus_read_iin_oc_fault_limit(void);

Uint8 pmbus_write_vout_ov_fault_limit(void);

Uint8 pmbus_write_iout_oc_fault_limit(void);

Uint8 pmbus_write_temp_ot_fault_limit(void);

Uint8 pmbus_write_iin_oc_fault_limit(void);

Uint8 pmbus_read_vout(void);
int32 pmbus_read_vout_handler(Uint32 vout);
Uint8 pmbus_read_vin(void);
Uint8 pmbus_read_iout(void);
Uint8 pmbus_read_temperature1(void);
Uint8 pmbus_write_clear_faults(void);
Uint8 above_vin_on_limit(void);
Uint8 below_vin_off_limit(void);

int16 linear11_multiply_fit(int16 x, int16 y, int16 bits_limit, int8 *err_flag);
int16 linear11_multiply_fit7(int16 x, int16 y, int8 *err_flag);
int16 linear11_multiply_fit14(int16 x, int16 y, int8 *err_flag);
int16 linear11_multiply(int16 x, int16 y);
void initialize_dpwm_timing(void);

Uint8 pmbus_read_debug_buffer(void);
Uint8 pmbus_read_user_ram_00(void);
Uint8 pmbus_write_user_ram_00(void);

Uint8 pmbus_read_parm_value(void);
Uint8 pmbus_write_parm_value(void);
Uint8 pmbus_read_parm_info(void);
Uint8 pmbus_write_parm_info(void);

int pmbus_mfr_ic_device_handler(void);
int pmbus_mfr_ic_device_rev_handler(void);

float linear11_to_float (int16 linear11);
int16 float_to_linear11 (float x);
void float_out(float x);
void float_word_out(Uint32 x);
void linear_11_out(Uint16 x);
Uint16 float_to_linear16 (float x,int8 vout_mode);
float linear16_to_float(Uint16 x, int8 vout_mode);
float signed_linear16_to_float(int16 x, int8 vout_mode);

void jeff_init(void);

Uint8 pmbus_write_vout_scale_loop(void);
Uint8 pmbus_read_vout_scale_loop(void);

Uint8 pmbus_write_vout_cal_offset(void);
Uint8 pmbus_read_vout_cal_offset(void);

int16 dac_target_calculate(void);

void restore_default_all(void);
void pmbus_data_translation(void);
void configure_cpcc(void);
void configure_burst_mode(void);
void disable_current_sharing(void);
void init_syncfet_soft_onoff(void);
void init_flux_balancing(void);
void preset_filter0(void);
void preset_filter1(void);
void deadtime_adjust(void);
Uint8 pmbus_write_deadband_config(void);
Uint8 pmbus_read_deadband_config(void);
void shut_down(void);







//device_id.c
int pmbus_read_device_id(void);


void init_current_loop_mux(void);
void init_bat_current_loop(void);


//init_dpwm.c
void init_dpwm0(void);
void init_dpwm1(void);
void init_dpwm2(void);
void init_dpwm3(void);
void init_dpwm_loop_mux(void);
void init_dpwms(void);
void init_dpwm0_open_loop(void);
void init_dpwm1_open_loop(void);
void init_dpwm2_open_loop(void);
void init_dpwm3_open_loop(void);
void init_dpwm_loop_mux_open_loop(void);
void init_dpwms_open_loop(void);


//init_miscellaneous.c
void init_pmbus(void);
void init_light_load_configuration(void);
void init_miscellaneous(void);


//init_protection.c
void init_protection(void);


void init_voltage_loop_mux(void);
void init_bus_voltage_loop(void);


//interrupts.c
void undefined_instruction_exception(void);
void software_interrupt(Uint32 arg1, Uint32 arg2, Uint32 arg3, Uint8 swi_number);
void abort_prefetch_exception(void);
void abort_data_fetch_exception(void);
void fast_interrupt(void);


//main.c
void main();
void c_int00(void);


//pmbus.c
Uint8 pmbus_read_frequency(void);
int32 sign_extend(int value, int number_of_bits);
int32 pmbus_write_message(void);
int32 pmbus_read_message(void);


//pmbus_coefficients.c
void restore_filter0(void);
void restore_filter1(void);
void restore_configuration(void);


//pmbus_handler.c
void pmbus_write_block_handler(void);
void pmbus_idle_handler();
void pmbus_read_block_handler(void);
void pmbus_read_wait_for_eom_handler(void);
void pmbus_handler(void);


//pmbus_manuf_info_commands.c
int pmbus_read_setup_id(void);


//pmbus_manuf_specific_commands.c
Uint8 pmbus_read_cmd_dcdc_paged(void);
Uint8 pmbus_read_cmd_dcdc_nonpaged(void);
Uint8 pmbus_read_cmd_pfc(void);
Uint8 pmbus_write_gui_constant(void);
Uint8 pmbus_write_light_load_config(void);
Uint8 pmbus_read_light_load_config(void);
Uint8 pmbus_write_cpcc_config(void);
Uint8 pmbus_read_cpcc_config(void);


//pmbus_tools.c
Uint32 linear11_translation(Uint32 raw_data, Uint8 shift_exponent);


//standard_interrupt.c
void go_to_idle_state(void);
void standard_interrupt(void);


//uart.c
void nybble_out(char nybble);
void decimal_out_cursor_digits(int32 data);
void decimal_out_4_digits(int32 data);
void decimal_out_5_digits(int32 data);
void decimal_out_8_digits(int32 data);
void decimal_out_3_digits(int32 data);
void string_out(char* string);
void byte_out(char data);
void three_nybble_out(unsigned short data);
void short_out(unsigned short data);
void word_out(unsigned int data);
void init_uart(void);

void send_string(const Uint8 string_to_send[], Uint8 num_bytes);

//void configure_charge_buck(void);
//void configure_charge_boost(void);
//void configure_charge_buck_boost(void);
void delay(void);



