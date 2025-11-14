//pmbus_coefficients.h

//DC/DC configuration
#define VOUT_MODE_EXP	 	(9)	//fixed
#define VOUT 				(12 << VOUT_MODE_EXP) //12V
#define VOUT_OV_FAULT_LIMIT (14 << VOUT_MODE_EXP) //14V
#define IOUT_OC_FAULT_LIMIT (41) //41A
#define TEMP_OT_FAULT_LIMIT (70) //70C
#define IIN_OC_FAULT_LIMIT	(9) //9A
#define TURN_ON_THRESHOLD	(40000)
#define TURN_OFF_THRESHOLD	(30000)
#define LL_ENABLE			(1)
#define CPCC_PMAX			(400)  //400W
#define CPCC_IMAX			(36)   //36A
#define CPCC_TON			(100)
#define CPCC_ENABLE			(0)
#define CPCC_TIME_OUT_EN	(0)

//FILTER 0 pmbus controlled coefficients  
#define INIT_FILTER_0_BIN0_ALPHA  (0)           // 3      Bin0 Alpha Configuration
#define INIT_FILTER_0_BIN0_CONFIG (0)           // 2:0    Bin0 Configuration
#define INIT_FILTER_0_BIN1_ALPHA  (1)           // 7      Bin1 Alpha Configuration
#define INIT_FILTER_0_BIN1_CONFIG (1)           // 6:4    Bin1 Configuration
#define INIT_FILTER_0_BIN2_ALPHA  (1)           // 11     Bin2 Alpha Configuration
#define INIT_FILTER_0_BIN2_CONFIG (1)           // 10:8   Bin2 Configuration
#define INIT_FILTER_0_BIN3_ALPHA  (1)           // 15     Bin3 Alpha Configuration
#define INIT_FILTER_0_BIN3_CONFIG (1)           // 14:12  Bin3 Configuration
#define INIT_FILTER_0_BIN4_ALPHA  (1)           // 19     Bin4 Alpha Configuration
#define INIT_FILTER_0_BIN4_CONFIG (1)           // 18:16  Bin4 Configuration
#define INIT_FILTER_0_BIN5_ALPHA  (1)           // 23     Bin5 Alpha Configuration
#define INIT_FILTER_0_BIN5_CONFIG (1)           // 22:20  Bin5 Configuration
#define INIT_FILTER_0_BIN6_ALPHA  (1)           // 27     Bin6 Alpha Configuration
#define INIT_FILTER_0_BIN6_CONFIG (1)           // 26:24  Bin6 Configuration

#define INIT_FILTER_0_KP_COEF_0 (31095)//(9000)            //17000 // 15:0   KP Coefficient 0
#define INIT_FILTER_0_KP_COEF_1 (20000)             // 31:16  KP Coefficient 1 //14000
#define INIT_FILTER_0_KP_COEF_2 (20000)             // 15:0   KP Coefficient 2

#define INIT_FILTER_0_KI_COEF_0 (672)//(50)             // 15:0   KI Coefficient 0
#define INIT_FILTER_0_KI_COEF_1 (150)             // 31:16  KI Coefficient 1
#define INIT_FILTER_0_KI_COEF_2 (150)             // 15:0   KI Coefficient 2
#define INIT_FILTER_0_KI_COEF_3 (150)             // 31:16  KI Coefficient 3

#define INIT_FILTER_0_KD_COEF_0 (9464)//(5000)             // 15:0   KD Coefficient 0
#define INIT_FILTER_0_KD_COEF_1 (22000)             // 31:16  KD Coefficient 1
#define INIT_FILTER_0_KD_COEF_2 (22000)             // 15:0   KD Coefficient 2

#define INIT_FILTER_0_KD_ALPHA_0 (151)//(150)             // 24:16  KD Alpha 1 Value
#define INIT_FILTER_0_KD_ALPHA_1 (20)             // 8:0    KD Alpha 0 Value

#define INIT_FILTER_0_LIMIT0 (25)              // 8:0    Non-Linear Limit 0 Value //
#define INIT_FILTER_0_LIMIT1 (31)              // 24:16  Non-Linear Limit 1 Value
#define INIT_FILTER_0_LIMIT2 (31)              // 8:0    Non-Linear Limit 2 Value
#define INIT_FILTER_0_LIMIT3 (31)              // 24:16  Non-Linear Limit 3 Value
#define INIT_FILTER_0_LIMIT4 (31)              // 8:0    Non-Linear Limit 4 Value
#define INIT_FILTER_0_LIMIT5 (31)              // 24:16  Non-Linear Limit 5 Value

#define INIT_FILTER_0_KI_CLAMP_HIGH (0x32FFFF) //(0x70FFF0)       // 23:0   KI Clamp High
#define INIT_FILTER_0_KI_CLAMP_LOW  (0xE00010)       // 23:0   KI Clamp Low

#define INIT_FILTER_0_YN_CLAMP_HIGH (0x7FFFF0)		//Set to 2^23-1;)       // 23:0   Output Clamp High
#define INIT_FILTER_0_YN_CLAMP_LOW  (30000)       // 23:0   Output Clamp Low //30000

#define INIT_FILTER_0_NL_MODE 	 (1)                // written to FILTERCTRL
#define INIT_FILTER_0_AFE_GAIN 	 (3)
#define INIT_FILTER_0_OVERSAMPLE (1)

//FILTER 1 pmbus controlled coefficients  
#define INIT_FILTER_1_BIN0_ALPHA  (0)           // 3      Bin0 Alpha Configuration
#define INIT_FILTER_1_BIN0_CONFIG (0)           // 2:0    Bin0 Configuration
#define INIT_FILTER_1_BIN1_ALPHA  (0)           // 7      Bin1 Alpha Configuration
#define INIT_FILTER_1_BIN1_CONFIG (0)           // 6:4    Bin1 Configuration
#define INIT_FILTER_1_BIN2_ALPHA  (0)           // 11     Bin2 Alpha Configuration
#define INIT_FILTER_1_BIN2_CONFIG (0)           // 10:8   Bin2 Configuration
#define INIT_FILTER_1_BIN3_ALPHA  (0)           // 15     Bin3 Alpha Configuration
#define INIT_FILTER_1_BIN3_CONFIG (0)           // 14:12  Bin3 Configuration
#define INIT_FILTER_1_BIN4_ALPHA  (0)           // 19     Bin4 Alpha Configuration
#define INIT_FILTER_1_BIN4_CONFIG (0)           // 18:16  Bin4 Configuration
#define INIT_FILTER_1_BIN5_ALPHA  (0)           // 23     Bin5 Alpha Configuration
#define INIT_FILTER_1_BIN5_CONFIG (0)           // 22:20  Bin5 Configuration
#define INIT_FILTER_1_BIN6_ALPHA  (0)           // 27     Bin6 Alpha Configuration
#define INIT_FILTER_1_BIN6_CONFIG (0)           // 26:24  Bin6 Configuration

#define INIT_FILTER_1_KP_COEF_0 (4000)//(5000) //(12000)           // 15:0   KP Coefficient 0
#define INIT_FILTER_1_KP_COEF_1 (0)             // 31:16  KP Coefficient 1
#define INIT_FILTER_1_KP_COEF_2 (0)             // 15:0   KP Coefficient 2

#define INIT_FILTER_1_KI_COEF_0 (400)//(30) //(200)            // 15:0   KI Coefficient 0
#define INIT_FILTER_1_KI_COEF_1 (0)             // 31:16  KI Coefficient 1
#define INIT_FILTER_1_KI_COEF_2 (0)             // 15:0   KI Coefficient 2
#define INIT_FILTER_1_KI_COEF_3 (0)             // 31:16  KI Coefficient 3

#define INIT_FILTER_1_KD_COEF_0 (8000) //(8000)             // 15:0   KD Coefficient 0
#define INIT_FILTER_1_KD_COEF_1 (0)             // 31:16  KD Coefficient 1
#define INIT_FILTER_1_KD_COEF_2 (0)             // 15:0   KD Coefficient 2

#define INIT_FILTER_1_KD_ALPHA_0 (255)            // 24:16  KD Alpha 1 Value
#define INIT_FILTER_1_KD_ALPHA_1 (0)            // 8:0    KD Alpha 0 Value

#define INIT_FILTER_1_LIMIT0 (1)              // 8:0    Non-Linear Limit 0 Value
#define INIT_FILTER_1_LIMIT1 (2)              // 24:16  Non-Linear Limit 1 Value
#define INIT_FILTER_1_LIMIT2 (3)              // 8:0    Non-Linear Limit 2 Value
#define INIT_FILTER_1_LIMIT3 (4)              // 24:16  Non-Linear Limit 3 Value
#define INIT_FILTER_1_LIMIT4 (5)              // 8:0    Non-Linear Limit 4 Value
#define INIT_FILTER_1_LIMIT5 (6)              // 24:16  Non-Linear Limit 5 Value

#define INIT_FILTER_1_KI_CLAMP_HIGH (0x42FFFF) //(0x7FFFF0)  // 23:0   KI Clamp High
#define INIT_FILTER_1_KI_CLAMP_LOW  (0xE00010)       	// 23:0   KI Clamp Low

#define INIT_FILTER_1_YN_CLAMP_HIGH (0x7FFFF0)//Set to 2^23-1;)       // 23:0   Output Clamp High
#define INIT_FILTER_1_YN_CLAMP_LOW  (30000)       // 23:0   Output Clamp Low

#define INIT_FILTER_1_NL_MODE    (1)                // written to FILTERCTRL
#define INIT_FILTER_1_AFE_GAIN   (3)
#define INIT_FILTER_1_OVERSAMPLE (0)

typedef struct
{
	Uint16 vout_cal_offset;
	Uint16 iout_cal_gain;
	Uint16 iout_cal_offset;
	Uint16 temperature_cal_offset;
	Uint16 temperature_cal_gain;
	Uint16 vout_cal_monitor;
}PMBUS_DCDC_CAL;//must be even number of int16

//first rail
#define DEFAULT_PMBUS_DCDC_1_CAL {0, 0, 0, 0, 0, 0}

//second rail default value
#define DEFAULT_PMBUS_DCDC_2_CAL  {0, 0, 0, 0, 0, 0}        

typedef struct
{
	Uint16 vin_scale;
	Uint16 vin_offset;
}PMBUS_DCDC_CAL_NONPAGED; //must be even number of int16

typedef struct 
{
	Uint16 vout_cmd;
	Uint16 vout_ov_fault_limit;
	Uint16 iout_oc_fault_limit;
	Uint16 temp_ot_fault_limit;
	Uint16 iin_oc_fault_limit;
	Uint32 ll_turn_on_thresh;
	Uint32 ll_turn_off_thresh;
	Uint8  ll_en;
	Uint32 cpcc_pmax;
	Uint16 cpcc_imax;
	Uint16 cpcc_ton;
	Uint8  cpcc_enable;
	Uint8  cpcc_time_out_en;
	Uint8  rsvd1;
	Uint16 rsvd2;
}PMBUS_DCDC_CONFIG; //must be even number of int16
  
#define DEFAULT_PMBUS_DCDC_1_CONFIG  {\
VOUT, \
VOUT_OV_FAULT_LIMIT, \
IOUT_OC_FAULT_LIMIT,\
TEMP_OT_FAULT_LIMIT,\
IIN_OC_FAULT_LIMIT,\
TURN_ON_THRESHOLD,\
TURN_OFF_THRESHOLD,\
LL_ENABLE,\
CPCC_PMAX,\
CPCC_IMAX,\
CPCC_TON,\
CPCC_ENABLE,\
CPCC_TIME_OUT_EN,\
0,\
0}

typedef struct
{
	Uint16 ot_limit_DCDC_1;
	Uint16 ot_limit_DCDC_2;
	Uint16 ot_limit_DCDC_3;
	Uint16 ot_limit_DCDC_4;
	int16  deadband_config[8];
	Uint16 vin_ov_fault_limit;
	Uint16 vin_uv_fault_limit;
	Uint16 vin_uv_warn_limit;
	char  mfr_date[14];
}PMBUS_DCDC_CONFIG_NONPAGED; //must be even number int16


//EXTERN PMBUS_DCDC_READING            pmbus_dcdc_reading[DCDC_PAGE_NUMS];
EXTERN PMBUS_DCDC_CONFIG             pmbus_dcdc_config[DCDC_PAGE_NUMS];
EXTERN PMBUS_DCDC_CONFIG             pmbus_dcdc_config_translated[DCDC_PAGE_NUMS];
EXTERN PMBUS_DCDC_CAL                pmbus_dcdc_cal[DCDC_PAGE_NUMS]; 

EXTERN PMBUS_DCDC_CONFIG_NONPAGED    pmbus_dcdc_config_nonpaged;
EXTERN PMBUS_DCDC_CONFIG_NONPAGED    pmbus_dcdc_config_nonpaged_translated;
EXTERN PMBUS_DCDC_CAL_NONPAGED       pmbus_dcdc_cal_nonpaged;

struct FILTER_MISC_REG_BITS
{
    Uint32 rsvd0:27;                	// 31:5  Reserved
    Uint32 NL_MODE:1;          			// 4     NL_MODE - stored in Filter Control Register
	Uint32 AFE_GAIN:2;					// 3:2	`AFE Gain
	Uint32 SAMPLE_TRIG1_OVERSAMPLE:2;  	// 1:0   Configures Oversampling function
};

union FILTER_MISC_REG
{
    struct FILTER_MISC_REG_BITS bit;
    Uint32                 		all;
};

  //=============================================================================
  // Filter Module Register File
  //=============================================================================
typedef struct  {
    union COEFCONFIG_REG        COEFCONFIG;         // Coefficient Configuration Register
    union FILTERKPCOEF0_REG     FILTERKPCOEF0;      // Filter KP Coefficient 0 Register
    union FILTERKPCOEF1_REG     FILTERKPCOEF1;      // Filter KP Coefficient 1 Register
    union FILTERKICOEF0_REG     FILTERKICOEF0;      // Filter KI Coefficient 0 Register
    union FILTERKICOEF1_REG     FILTERKICOEF1;      // Filter KI Coefficient 1 Register
    union FILTERKDCOEF0_REG     FILTERKDCOEF0;      // Filter KD Coefficient 0 Register
    union FILTERKDCOEF1_REG     FILTERKDCOEF1;      // Filter KD Coefficient 1 Register
    union FILTERKDALPHA_REG     FILTERKDALPHA;      // Filter KD Alpha Register
    union FILTERNL0_REG         FILTERNL0;          // Filter Non-Linear Limit 0 Register
    union FILTERNL1_REG         FILTERNL1;          // Filter Non-Linear Limit 1 Register
    union FILTERNL2_REG         FILTERNL2;          // Filter Non-Linear Limit 2 Register
    union FILTERKICLPHI_REG     FILTERKICLPHI;      // Filter KI Feedback Clamp High Register
    union FILTERKICLPLO_REG     FILTERKICLPLO;      // Filter KI Feedback Clamp Low Register
    union FILTERYNCLPHI_REG     FILTERYNCLPHI;       // Filter Output Clamp High Register
    union FILTERYNCLPLO_REG     FILTERYNCLPLO;       // Filter Output Clamp Low Register
	union FILTER_MISC_REG		FILTER_MISC;
  }FILTER_PMBUS_REGS;

#define DEFAULT_PMBUS_DCDC_CONFIG_NONPAGED {81, 82, 83, 84, {1 ,400 ,400 ,400 ,400 , 0, 0, 0}, 55, 32, 38,{'1','1','/','1','2','/','2','0','0','9',0,0,0,0}}
                                         
#define DEFAULT_PMBUS_DCDC_CAL_NONPAGED    {0, 0}

#define DEFAULT_FILTER_0_PMBUS_REGS \
{\
	{\
		0,\
	    INIT_FILTER_0_BIN6_ALPHA,\
	    INIT_FILTER_0_BIN6_CONFIG,\
	    INIT_FILTER_0_BIN5_ALPHA,\
	    INIT_FILTER_0_BIN5_CONFIG,\
	    INIT_FILTER_0_BIN4_ALPHA,\
	    INIT_FILTER_0_BIN4_CONFIG,\
	    INIT_FILTER_0_BIN3_ALPHA,\
	    INIT_FILTER_0_BIN3_CONFIG,\
	    INIT_FILTER_0_BIN2_ALPHA,\
	    INIT_FILTER_0_BIN2_CONFIG,\
	    INIT_FILTER_0_BIN1_ALPHA,\
	    INIT_FILTER_0_BIN1_CONFIG,\
	    INIT_FILTER_0_BIN0_ALPHA,\
	    INIT_FILTER_0_BIN0_CONFIG\
	},\
	{\
		INIT_FILTER_0_KP_COEF_1,\
	    INIT_FILTER_0_KP_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_KP_COEF_2\
	},\
	{\
		INIT_FILTER_0_KI_COEF_1,\
	    INIT_FILTER_0_KI_COEF_0\
	},\
	{\
		INIT_FILTER_0_KI_COEF_3,\
	    INIT_FILTER_0_KI_COEF_2\
	},\
	{\
		INIT_FILTER_0_KD_COEF_1,\
	    INIT_FILTER_0_KD_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_0_KD_COEF_2\
	},\
	{\
		0,\
		INIT_FILTER_0_KD_ALPHA_1,\
		0,\
	    INIT_FILTER_0_KD_ALPHA_0\
	},\
	{\
		0,\
		INIT_FILTER_0_LIMIT1,\
		0,\
	    INIT_FILTER_0_LIMIT0\
	},\
	{\
		0,\
		INIT_FILTER_0_LIMIT3,\
		0,\
	    INIT_FILTER_0_LIMIT2\
	},\
	{\
		0,\
		INIT_FILTER_0_LIMIT5,\
		0,\
	    INIT_FILTER_0_LIMIT4\
	},\
	{\
		0,\
	    INIT_FILTER_0_KI_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_KI_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_YN_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_0_YN_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_0_NL_MODE,\
		INIT_FILTER_0_AFE_GAIN,\
		INIT_FILTER_0_OVERSAMPLE\
	},\
}

#define DEFAULT_FILTER_1_PMBUS_REGS \
{\
	{\
		0,\
	    INIT_FILTER_1_BIN6_ALPHA,\
	    INIT_FILTER_1_BIN6_CONFIG,\
	    INIT_FILTER_1_BIN5_ALPHA,\
	    INIT_FILTER_1_BIN5_CONFIG,\
	    INIT_FILTER_1_BIN4_ALPHA,\
	    INIT_FILTER_1_BIN4_CONFIG,\
	    INIT_FILTER_1_BIN3_ALPHA,\
	    INIT_FILTER_1_BIN3_CONFIG,\
	    INIT_FILTER_1_BIN2_ALPHA,\
	    INIT_FILTER_1_BIN2_CONFIG,\
	    INIT_FILTER_1_BIN1_ALPHA,\
	    INIT_FILTER_1_BIN1_CONFIG,\
	    INIT_FILTER_1_BIN0_ALPHA,\
	    INIT_FILTER_1_BIN0_CONFIG\
	},\
	{\
		INIT_FILTER_1_KP_COEF_1,\
	    INIT_FILTER_1_KP_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_1_KP_COEF_2\
	},\
	{\
		INIT_FILTER_1_KI_COEF_1,\
	    INIT_FILTER_1_KI_COEF_0\
	},\
	{\
		INIT_FILTER_1_KI_COEF_3,\
	    INIT_FILTER_1_KI_COEF_2\
	},\
	{\
		INIT_FILTER_1_KD_COEF_1,\
	    INIT_FILTER_1_KD_COEF_0\
	},\
	{\
		0,\
	    INIT_FILTER_1_KD_COEF_2\
	},\
	{\
		0,\
		INIT_FILTER_1_KD_ALPHA_1,\
		0,\
	    INIT_FILTER_1_KD_ALPHA_0\
	},\
	{\
		0,\
		INIT_FILTER_1_LIMIT1,\
		0,\
	    INIT_FILTER_1_LIMIT0\
	},\
	{\
		0,\
		INIT_FILTER_1_LIMIT3,\
		0,\
	    INIT_FILTER_1_LIMIT2\
	},\
	{\
		0,\
		INIT_FILTER_1_LIMIT5,\
		0,\
	    INIT_FILTER_1_LIMIT4\
	},\
	{\
		0,\
	    INIT_FILTER_1_KI_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_1_KI_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_1_YN_CLAMP_HIGH\
	},\
	{\
		0,\
	    INIT_FILTER_1_YN_CLAMP_LOW\
	},\
	{\
		0,\
	    INIT_FILTER_1_NL_MODE,\
		INIT_FILTER_1_AFE_GAIN,\
		INIT_FILTER_1_OVERSAMPLE\
	},\
}

EXTERN FILTER_PMBUS_REGS filter0_pmbus_regs;
EXTERN FILTER_PMBUS_REGS filter1_pmbus_regs;

