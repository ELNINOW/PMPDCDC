//system_defines.h

#define PWM_FREQUENCY (140) //140kHz
#define PWM_PERIOD ((250000/PWM_FREQUENCY) << 4)

#define EVT_UPDATE_WINDOW (72 << 4) //72ns

#define min(a,b)	(((a)>(b)) ? (b):(a))

#define ENABLE 	(1)
#define DISABLE (0)

#define UNKNOWN	   (0)
#define BUCK	   (1)
#define BUCK_BOOST (2)
#define BOOST	   (3)

//global GPIO
#define MASK_DPWM0A 		(1)
#define MASK_DPWM0B 		(1 << 1)
#define MASK_DPWM1A 		(1 << 2)
#define MASK_DPWM1B 		(1 << 3)
#define MASK_DPWM2A 		(1 << 4)
#define MASK_DPWM2B 		(1 << 5)
#define MASK_DPWM3A 		(1 << 6)
#define MASK_DPWM3B 		(1 << 7)
#define MASK_DPWMS	 		(0xFF)
#define MASK_CTRL_PIN 		(1 << 14)
#define MASK_TDI 			(1 << 24)
#define MASK_TMS   	 		(1 << 25)
#define MASK_TDO   	 		(1 << 26)
#define MASK_FAULT2	 		(1 << 11)

//==========================================================================================
// Memory allocation constants
//==========================================================================================
// ****VOYAGER#define MFBALR2_HALF0_DATA_FLASH_BASE_ADDRESS 0x8800
#define DATA_FLASH_START_ADDRESS 	(0x18800)
#define DATA_FLASH_END_ADDRESS 		(0x18fff)
#define DATA_FLASH_LENGTH			(DATA_FLASH_END_ADDRESS - DATA_FLASH_START_ADDRESS + 1)
#define	DATA_FLASH_SEGMENT_SIZE		(32)
#define	DATA_FLASH_NUM_SEGMENTS		(DATA_FLASH_LENGTH / DATA_FLASH_SEGMENT_SIZE) 

// This limitation check is required because the flash access routines in flash.c make the
// assumption that the size of the segments of the data flash are an integral power of two.
#if (DATA_FLASH_SEGMENT_SIZE & (DATA_FLASH_SEGMENT_SIZE - 1)) != 0
#error "DATA_FLASH_SEGMENT_SIZE must be defined as an integral power of two"
#endif

#define MFBALR2_HALF0_DATA_FLASH_BASE_ADDRESS (0x8800)
#define MFBALRX_BYTE0_BLOCK_SIZE_2K     	(0x20) 		
#define MFBALRX_BYTE0_RONLY					(0x02)		   //Read-only protection
#define MFBALRX_BYTE0_BLOCK_SIZE_32K    	(0x60)
#define UART_RX_SIZE (10) //total number of bytes for received data packet
#define UART_TX_SIZE (10) //total number of bytes for transmitted data packet
#define UART_TX_TIME (10000) //number of timer interrupts between transmissions on serial port

// Flash Error codes
#define FLASH_SUCCESS 				(0)
#define FLASH_INVALID_SEGMENT 		(1)
#define	FLASH_INVALID_ADDRESS		(2)
#define	FLASH_MISCOMPARE			(3)

#define NULL						(0)

#define DCDC_PAGE_NUMS (1)

//Vbus measurement defines
#define VBUS_SCALER 		(0.026 * 10) //(R1/(R1+R2)
#define VBUS_DAC_SCALER  	((Uint32)(VBUS_SCALER * 16384 / 1.6))//high res
#define VBUS_COMP_SCALER 	((Uint32)(VBUS_SCALER * 4096 / 2.5))//left shifted 5-bit more for accuracy
#define VBUS_AD12_SCALER 	((Uint32)(VBUS_SCALER * 4096 / 2.5))
#define VBUS_BACKUP_LIMIT	(0.5)//1V
#define VBUS_OVP_LIMIT 		(5)//5V
#define VBUS_UVP_LIMIT		(3)//3V
#define VBUS_OVP_FAULT 		(adc_values_avg.v_bus_sense > (vbus_norminal + ((VBUS_OVP_LIMIT * VBUS_AD12_SCALER) / 10)))
#define VBUS_NO_FAULT 		(adc_values_avg.v_bus_sense < (vbus_norminal + ((VBUS_OVP_LIMIT * VBUS_AD12_SCALER) / 10)))
#define VBUS_VOLTAGE_LOW	(adc_values_avg.v_bus_sense < ((35 * VBUS_AD12_SCALER) / 10)) //35V
#define MODE_THRESHOLD      (4)//4V
#define MODE_HYSTERESIS     (1.5)//1.5V
#define BOUNDARY			((Uint32)((MODE_THRESHOLD  * VBUS_AD12_SCALER) / 10))
#define HYSTERESIS			((Uint32)((MODE_HYSTERESIS * VBUS_AD12_SCALER) / 10))

//Ibus measurement defines
#define IBUS_SCALER 		(0.24)
#define IBUS_SCALER_DAC 	(0.15556)
#define IBUS_DAC_SCALER  	((Uint32)(IBUS_SCALER_DAC * 16384 / 1.6)) //high res
#define IBUS_COMP_SCALER 	((Uint32)(IBUS_SCALER * 4096 / 2.5)) //left shifted 5-bit more for accuracy
#define IBUS_AD12_SCALER 	((Uint32)(IBUS_SCALER * 4096 / 2.5))
#define IBUS_CBC_LIMIT 		(15)//15A
#define IBUS_OCP_LIMIT 		(12)//12A
#define IBUS_FAULT 			(adc_values.i_bus_sense > (IBUS_OCP_LIMIT * IBUS_AD12_SCALER))
#define IBUS_NO_FAULT 		(adc_values.i_bus_sense < (IBUS_OCP_LIMIT * IBUS_AD12_SCALER))

//Vbat measurement defines
#define VBAT_SCALER 		(0.026 * 10) //(R1/(R1+R2), multiply 10 for accuracy
#define VBAT_DAC_SCALER  	((Uint32)(VBAT_SCALER * 16384 / 1.6)) //high res
#define VBAT_COMP_SCALER 	((Uint32)(VBAT_SCALER * 4096 / 2.5))//left shifted 5-bit more for accuracy
#define VBAT_AD12_SCALER 	((Uint32)(VBAT_SCALER * 4096 / 2.5))
#define VBAT_SETPOINT 		(55)//55V
#define VBAT_OVP_LIMIT 		(57)//57V
#define VBAT_OVP_FAULT 		(adc_values_avg.v_bat_sense > ((VBAT_OVP_LIMIT * VBAT_AD12_SCALER) / 10))
#define VBAT_NO_FAULT 		(adc_values_avg.v_bat_sense < ((VBAT_OVP_LIMIT * VBAT_AD12_SCALER) / 10))
#define VBAT_VOLTAGE_LOW 	(adc_values_avg.v_bat_sense < ((38 * VBAT_AD12_SCALER) / 10)) //38V
#define VBAT_NEED_CHARGE	(adc_values_avg.v_bat_sense < ((53 * VBAT_AD12_SCALER) / 10)) //53V

//Ibat measurement defines
#define IBAT_SCALER 		(0.24)
#define IBAT_SCALER_DAC 	(0.15556)
#define IBAT_DAC_SCALER  	((Uint32)(IBAT_SCALER_DAC  * 16384 / 1.6)) //high res
#define IBAT_COMP_SCALER 	((Uint32)(IBAT_SCALER * 4096 / 2.5)) //left shifted 5-bit more for accuracy
#define IBAT_AD12_SCALER 	((Uint32)(IBAT_SCALER * 4096 / 2.5))
#define IBAT_CHARGE_CURRENT (2) //2A
#define IBAT_CBC_LIMIT 		(10)//10A
#define IBAT_OCP_LIMIT 		(7)//7A
#define IBAT_SATURATION_LIMIT	((IBAT_CHARGE_CURRENT * IBAT_AD12_SCALER * 3) / 100)
#define IBAT_OCP_FAULT 			(adc_values.i_bat_sense > (IBAT_OCP_LIMIT * IBAT_AD12_SCALER))
#define IBAT_NO_FAULT 		(adc_values.i_bat_sense < (IBAT_OCP_LIMIT * IBAT_AD12_SCALER))

//Status Word aliases
#define PMBUS_STATUS_WORD_HIGH_BYTE			(0x1)
#define PMBUS_STATUS_WORD_CML 				(0x2)
#define PMBUS_STATUS_WORD_TEMPERATURE 		(0x4)
#define PMBUS_STATUS_WORD_VIN_UV 			(0x8)
#define PMBUS_STATUS_WORD_IOUT_OC 			(0x10)
#define PMBUS_STATUS_WORD_VOUT_OV 			(0x20)
#define PMBUS_STATUS_WORD_OFF 				(0x40)
#define PMBUS_STATUS_WORD_BUSY 				(0x80)
#define PMBUS_STATUS_WORD_UNKNOWN 			(0x100)
#define PMBUS_STATUS_WORD_OTHER 			(0x200)
#define PMBUS_STATUS_WORD_FAN	 			(0x400)
#define PMBUS_STATUS_WORD_POWER_GOOD_NOT 	(0x800)
#define PMBUS_STATUS_WORD_MFR   			(0x1000)
#define PMBUS_STATUS_WORD_INPUT 			(0x2000)
#define PMBUS_STATUS_WORD_IOUT  			(0x4000)
#define PMBUS_STATUS_WORD_VOUT  			(0x8000)

#define ACOMPA_INT_STATUS_MASK 	(0x01)
#define ACOMPB_INT_STATUS_MASK 	(0x02)
#define ACOMPC_INT_STATUS_MASK 	(0x04)
#define ACOMPD_INT_STATUS_MASK 	(0x08)
#define ACOMPE_INT_STATUS_MASK 	(0x10)
#define ACOMPF_INT_STATUS_MASK 	(0x20)
#define ACOMPG_INT_STATUS_MASK 	(0x40)
#define COMP_INT_STATUS_MASK	(ACOMPB_INT_STATUS_MASK | ACOMPE_INT_STATUS_MASK)

#define DPWM_FAULT_AB_STATUS_MASK (0x2)

//=========================================================================================
// CIM module definitions
//=========================================================================================
// FIRQPR, INTREQ, REQMASK Registers
// interrupts listed highest priority to lowest priority:
#define CIMINT_ALL_SYS_SOFT		(0x80000000)	// 31	System Software Interrupt					
#define CIMINT_ALL_FAULT_PIN	(0x40000000)	// 30	Fault Pin Interrupt		
#define CIMINT_ALL_DPWM0		(0x20000000)	// 29	Every(1-16)DPWM0 switching cycles or CLF flag shutdown Interrupt		
#define CIMINT_ALL_DPWM1		(0x10000000)	// 28	Every(1-16)DPWM1 switching cycles or CLF flag shutdown Interrupt			 						
#define CIMINT_ALL_DPWM2		(0x08000000)	// 27	Every(1-16)DPWM2 switching cycles or CLF flag shutdown Interrupt			 						
#define CIMINT_ALL_DPWM3		(0x04000000)	// 26	Every(1-16)DPWM3 switching cycles or CLF flag shutdown Interrupt		 						
#define CIMINT_ALL_FAULT_MUX	(0x02000000)	// 25	Fault Mux Interrupt			 				
#define CIMINT_ALL_ADC_CONV		(0x01000000)	// 24	ADC-12 End of Conversion Interrupt			 						
#define CIMINT_ALL_CPCC			(0x00800000)	// 23	CPCC Interrupt, Mode switched in CPCC module Flag needs to be read for details			 			
#define CIMINT_ALL_TMR_COMP0	(0x00400000)	// 22	24-bit Timer Compare 0 interrupt			 			
#define CIMINT_ALL_TMR_CAPT0	(0x00200000)	// 21	24-bit Timer Capture 0 interrupt									
#define CIMINT_ALL_TMR_COMP1	(0x00100000)	// 20	24-bit Timer Compare 1 interrupt		
#define CIMINT_ALL_TMR_CAPT1	(0x00080000)	// 19	24-bit Timer Capture 1 interrupt	
#define CIMINT_ALL_TMR_OVFL		(0x00040000)	// 18	24-bit Timer counter overflow interrupt							
#define CIMINT_ALL_PWM0_COMP	(0x00020000)	// 17	16-bit Timer PWM0 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_PWM1_COMP	(0x00010000)	// 16	16-bit Timer PWM1 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_PWM2_COMP	(0x00008000)	// 15	16-bit Timer PWM2 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_PWM3_COMP	(0x00004000)	// 14	16-bit Timer PWM3 counter overflow or Compare interrupt			 					
#define CIMINT_ALL_FRONT_END2	(0x00002000)	// 13	Front End 2 Interrupt			 					
#define CIMINT_ALL_FRONT_END1	(0x00001000)	// 12	Front End 1 Interrupt			 					
#define CIMINT_ALL_FRONT_END0	(0x00000800)	// 11	Front End 0 Interrupt				
#define CIMINT_ALL_DIGI_COMP 	(0x00000400)	// 10	Digital comparator interrupt		
#define CIMINT_ALL_PMBUS		(0x00000200)	// 9	PMBus related interrupt			 				
#define CIMINT_ALL_UART2_TX		(0x00000100)	// 8	UART2 TX buffer empty			 						
#define CIMINT_ALL_UART2_RX		(0x00000080)	// 7	UART2 RX buffer has a byte			 				
#define CIMINT_ALL_UART1_TX		(0x00000040)	// 6	UART1 TX buffer empty			 		
#define CIMINT_ALL_UART1_RX		(0x00000020)	// 5	UART1 RX buffer has a byte 		
#define CIMINT_ALL_UART_ERR		(0x00000010)	// 4	UART or SCI error Interrupt. Frame, parity or Overrun			 	
#define CIMINT_ALL_WTDG_WAKE	(0x00000008)	// 3	Wakeup interrupt when watchdog equals half of set watch time			 	
#define CIMINT_ALL_WTDG_RSET	(0x00000004)	// 2	Interrupt from watchdog exceeded (reset)			 	
#define CIMINT_ALL_EXT_INT	    (0x00000002)	// 1	Interrupt on one or all external input pins			 					
#define CIMINT_ALL_BRWN_OUT		(0x00000001)	// 0	Brown Out Interrupt			 					

//=========================================================================================
// Global I/O definitions
//=========================================================================================
//Bit positions:
#define FAULT3_GLBIO_BIT_POSITION                (29)
#define ADC_EXT_TRIG_GLBIO_BIT_POSITION          (28)
#define TCK_GLBIO_BIT_POSITION                   (27)
#define TDO_GLBIO_BIT_POSITION                   (26)
#define TMS_GLBIO_BIT_POSITION                   (25)
#define TDI_GLBIO_BIT_POSITION                   (24)
#define SCI_TX1_GLBIO_BIT_POSITION               (23)
#define SCI_TX0_GLBIO_BIT_POSITION               (22)
#define SCI_RX1_GLBIO_BIT_POSITION               (21)
#define SCI_RX0_GLBIO_BIT_POSITION               (20)
#define TMR_CAP_GLBIO_BIT_POSITION               (19)
#define TMR_PWM1_GLBIO_BIT_POSITION              (18)
#define TMR_PWM0_GLBIO_BIT_POSITION              (17)
#define PMBUS_CLK_GLBIO_BIT_POSITION             (16)
#define PMBUS_DATA_GLBIO_BIT_POSITION            (15)
#define CONTROL_GLBIO_BIT_POSITION               (14)
#define ALERT_GLBIO_BIT_POSITION                 (13)
#define EXT_INT_GLBIO_BIT_POSITION               (12)
#define FAULT2_GLBIO_BIT_POSITION                (11)
#define FAULT1_GLBIO_BIT_POSITION                (10)
#define FAULT0_GLBIO_BIT_POSITION                 (9)
#define SYNC_GLBIO_BIT_POSITION                   (8)
#define DPWM3B_GLBIO_BIT_POSITION                 (7)
#define DPWM3A_GLBIO_BIT_POSITION                 (6)
#define DPWM2B_GLBIO_BIT_POSITION                 (5)
#define DPWM2A_GLBIO_BIT_POSITION                 (4)
#define DPWM1B_GLBIO_BIT_POSITION                 (3)
#define DPWM1A_GLBIO_BIT_POSITION                 (2)
#define DPWM0B_GLBIO_BIT_POSITION                 (1)
#define DPWM0A_GLBIO_BIT_POSITION                 (0)

//Bit masks:
#define FAULT3_GLBIO_BIT_MASK                 (1 << FAULT3_GLBIO_BIT_POSITION) 
#define ADC_EXT_TRIG_GLBIO_BIT_MASK           (1 << ADC_EXT_TRIG_GLBIO_BIT_POSITION)          
#define TCK_GLBIO_BIT_MASK                    (1 << TCK_GLBIO_BIT_POSITION)                   
#define TDO_GLBIO_BIT_MASK                    (1 << TDO_GLBIO_BIT_POSITION)                   
#define TMS_GLBIO_BIT_MASK                    (1 << TMS_GLBIO_BIT_POSITION)                   
#define TDI_GLBIO_BIT_MASK                    (1 << TDI_GLBIO_BIT_POSITION)                   
#define SCI_TX1_GLBIO_BIT_MASK                (1 << SCI_TX1_GLBIO_BIT_POSITION)               
#define SCI_TX0_GLBIO_BIT_MASK                (1 << SCI_TX0_GLBIO_BIT_POSITION)              
#define SCI_RX1_GLBIO_BIT_MASK                (1 << SCI_RX1_GLBIO_BIT_POSITION)               
#define SCI_RX0_GLBIO_BIT_MASK                (1 << SCI_RX0_GLBIO_BIT_POSITION)               
#define TMR_CAP_GLBIO_BIT_MASK                (1 << TMR_CAP_GLBIO_BIT_POSITION)               
#define TMR_PWM1_GLBIO_BIT_MASK               (1 << TMR_PWM1_GLBIO_BIT_POSITION)              
#define TMR_PWM0_GLBIO_BIT_MASK               (1 << TMR_PWM0_GLBIO_BIT_POSITION)              
#define PMBUS_CLK_GLBIO_BIT_MASK              (1 << PMBUS_CLK_GLBIO_BIT_POSITION)             
#define PMBUS_DATA_GLBIO_BIT_MASK             (1 << PMBUS_DATA_GLBIO_BIT_POSITION)            
#define CONTROL_GLBIO_BIT_MASK                (1 << CONTROL_GLBIO_BIT_POSITION)               
#define ALERT_GLBIO_BIT_MASK                  (1 << ALERT_GLBIO_BIT_POSITION)                 
#define EXT_INT_GLBIO_BIT_MASK                (1 << EXT_INT_GLBIO_BIT_POSITION)               
#define FAULT2_GLBIO_BIT_MASK                 (1 << FAULT2_GLBIO_BIT_POSITION)                
#define FAULT1_GLBIO_BIT_MASK                 (1 << FAULT1_GLBIO_BIT_POSITION)                
#define FAULT0_GLBIO_BIT_MASK                 (1 << FAULT0_GLBIO_BIT_POSITION)                
#define SYNC_GLBIO_BIT_MASK                   (1 << SYNC_GLBIO_BIT_POSITION)                   
#define DPWM3B_GLBIO_BIT_MASK                 (1 << DPWM3B_GLBIO_BIT_POSITION)                 
#define DPWM3A_GLBIO_BIT_MASK                 (1 << DPWM3A_GLBIO_BIT_POSITION)                 
#define DPWM2B_GLBIO_BIT_MASK                 (1 << DPWM2B_GLBIO_BIT_POSITION)                 
#define DPWM2A_GLBIO_BIT_MASK                 (1 << DPWM2A_GLBIO_BIT_POSITION)                 
#define DPWM1B_GLBIO_BIT_MASK                 (1 << DPWM1B_GLBIO_BIT_POSITION)                 
#define DPWM1A_GLBIO_BIT_MASK                 (1 << DPWM1A_GLBIO_BIT_POSITION)                 
#define DPWM0B_GLBIO_BIT_MASK                 (1 << DPWM0B_GLBIO_BIT_POSITION)                 
#define DPWM0A_GLBIO_BIT_MASK                 (1 << DPWM0A_GLBIO_BIT_POSITION)   

//ADC results assignment
#define VBUS 		(0)
#define VBAT	 	(1)
#define IBUS 		(2)
#define IBAT 		(3)
#define NUMBER_OF_ADC_CHANNELS_ACTIVE (4)//how many ADC channels are used









