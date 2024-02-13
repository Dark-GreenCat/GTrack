#ifndef __BMA253_H__
#define __BMA253_H__

/****************************************************************/
/**\name	DATA TYPES INCLUDES		*/
/************************************************************/
/*!
* @brief The following definition uses for define the data types
*
* @note While porting the API please consider the following
* @note Please check the version of C standard
* @note Are you using Linux platform
*/

/*!
* @brief For the Linux platform support
* Please use the types.h for your data types definitions
*/
#ifdef	__KERNEL__

#include <linux/types.h>
/* singed integer type*/
typedef	int8_t s8;/**< used for signed 8bit */
typedef	int16_t s16;/**< used for signed 16bit */
typedef	int32_t s32;/**< used for signed 32bit */
typedef	int64_t s64;/**< used for signed 64bit */

typedef	u_int8_t u8;/**< used for unsigned 8bit */
typedef	u_int16_t u16;/**< used for unsigned 16bit */
typedef	u_int32_t u32;/**< used for unsigned 32bit */
typedef	u_int64_t u64;/**< used for unsigned 64bit */



#else /* ! __KERNEL__ */
/**********************************************************
* These definition uses for define the C
* standard version data types
***********************************************************/
# if !defined(__STDC_VERSION__)

/************************************************
 * compiler is C11 C standard
************************************************/
#if (__STDC_VERSION__ == 201112L)

/************************************************/
#include <stdint.h>
/************************************************/

/*unsigned integer types*/
typedef	uint8_t u8;/**< used for unsigned 8bit */
typedef	uint16_t u16;/**< used for unsigned 16bit */
typedef	uint32_t u32;/**< used for unsigned 32bit */
typedef	uint64_t u64;/**< used for unsigned 64bit */

/*signed integer types*/
typedef	int8_t s8;/**< used for signed 8bit */
typedef	int16_t s16;/**< used for signed 16bit */
typedef	int32_t s32;/**< used for signed 32bit */
typedef	int64_t s64;/**< used for signed 64bit */
/************************************************
 * compiler is C99 C standard
************************************************/

#elif (__STDC_VERSION__ == 199901L)

/* stdint.h is a C99 supported c library.
which is used to fixed the integer size*/
/************************************************/
#include <stdint.h>
/************************************************/

/*unsigned integer types*/
typedef	uint8_t u8;/**< used for unsigned 8bit */
typedef	uint16_t u16;/**< used for unsigned 16bit */
typedef	uint32_t u32;/**< used for unsigned 32bit */
typedef	uint64_t u64;/**< used for unsigned 64bit */

/*signed integer types*/
typedef int8_t s8;/**< used for signed 8bit */
typedef	int16_t s16;/**< used for signed 16bit */
typedef	int32_t s32;/**< used for signed 32bit */
typedef	int64_t s64;/**< used for signed 64bit */
/************************************************
 * compiler is C89 or other C standard
************************************************/

#else /*  !defined(__STDC_VERSION__) */
/*!
* @brief By default it is defined as 32 bit machine configuration
*	define your data types based on your
*	machine/compiler/controller configuration
*/
#define  MACHINE_32_BIT

/*! @brief
 *	If your machine support 16 bit
 *	define the MACHINE_16_BIT
 */
#ifdef MACHINE_16_BIT
#include <limits.h>
/*signed integer types*/
typedef	signed char  s8;/**< used for signed 8bit */
typedef	signed short int s16;/**< used for signed 16bit */
typedef	signed long int s32;/**< used for signed 32bit */

#if defined(LONG_MAX) && LONG_MAX == 0x7fffffffffffffffL
typedef long int s64;/**< used for signed 64bit */
typedef unsigned long int u64;/**< used for unsigned 64bit */
#elif defined(LLONG_MAX) && (LLONG_MAX == 0x7fffffffffffffffLL)
typedef long long int s64;/**< used for signed 64bit */
typedef unsigned long long int u64;/**< used for unsigned 64bit */
#else
#warning Either the correct data type for signed 64 bit integer \
could not be found, or 64 bit integers are not supported in your environment.
#warning If 64 bit integers are supported on your platform, \
please set s64 manually.
#endif

/*unsigned integer types*/
typedef	unsigned char u8;/**< used for unsigned 8bit */
typedef	unsigned short int u16;/**< used for unsigned 16bit */
typedef	unsigned long int u32;/**< used for unsigned 32bit */

/* If your machine support 32 bit
define the MACHINE_32_BIT*/
#elif defined MACHINE_32_BIT
/*signed integer types*/
typedef	signed char  s8;/**< used for signed 8bit */
typedef	signed short int s16;/**< used for signed 16bit */
typedef	signed int s32;/**< used for signed 32bit */
typedef	signed long long int s64;/**< used for signed 64bit */

/*unsigned integer types*/
typedef	unsigned char u8;/**< used for unsigned 8bit */
typedef	unsigned short int u16;/**< used for unsigned 16bit */
typedef	unsigned int u32;/**< used for unsigned 32bit */
typedef	unsigned long long int u64;/**< used for unsigned 64bit */

/* If your machine support 64 bit
define the MACHINE_64_BIT*/
#elif defined MACHINE_64_BIT
/*signed integer types*/
typedef	signed char  s8;/**< used for signed 8bit */
typedef	signed short int s16;/**< used for signed 16bit */
typedef	signed int s32;/**< used for signed 32bit */
typedef	signed long int s64;/**< used for signed 64bit */

/*unsigned integer types*/
typedef	unsigned char u8;/**< used for unsigned 8bit */
typedef	unsigned short int u16;/**< used for unsigned 16bit */
typedef	unsigned int u32;/**< used for unsigned 32bit */
typedef	unsigned long int u64;/**< used for unsigned 64bit */

#else
#warning The data types defined above which not supported \
define the data types manually
#endif
#endif

/*** This else will execute for the compilers
 *	which are not supported the C standards
 *	Like C89/C99/C11***/
#else
/*!
* @brief By default it is defined as 32 bit machine configuration
*	define your data types based on your
*	machine/compiler/controller configuration
*/
#define  MACHINE_32_BIT

/* If your machine support 16 bit
define the MACHINE_16_BIT*/
#ifdef MACHINE_16_BIT
#include <limits.h>
/*signed integer types*/
typedef	signed char  s8;/**< used for signed 8bit */
typedef	signed short int s16;/**< used for signed 16bit */
typedef	signed long int s32;/**< used for signed 32bit */

#if defined(LONG_MAX) && LONG_MAX == 0x7fffffffffffffffL
typedef long int s64;/**< used for signed 64bit */
typedef unsigned long int u64;/**< used for unsigned 64bit */
#elif defined(LLONG_MAX) && (LLONG_MAX == 0x7fffffffffffffffLL)
typedef long long int s64;/**< used for signed 64bit */
typedef unsigned long long int u64;/**< used for unsigned 64bit */
#else
#warning Either the correct data type for signed 64 bit integer \
could not be found, or 64 bit integers are not supported in your environment.
#warning If 64 bit integers are supported on your platform, \
please set s64 manually.
#endif

/*unsigned integer types*/
typedef	unsigned char u8;/**< used for unsigned 8bit */
typedef	unsigned short int u16;/**< used for unsigned 16bit */
typedef	unsigned long int u32;/**< used for unsigned 32bit */

/*! @brief If your machine support 32 bit
define the MACHINE_32_BIT*/
#elif defined MACHINE_32_BIT
/*signed integer types*/
typedef	signed char  s8;/**< used for signed 8bit */
typedef	signed short int s16;/**< used for signed 16bit */
typedef	signed int s32;/**< used for signed 32bit */
typedef	signed long long int s64;/**< used for signed 64bit */

/*unsigned integer types*/
typedef	unsigned char u8;/**< used for unsigned 8bit */
typedef	unsigned short int u16;/**< used for unsigned 16bit */
typedef	unsigned int u32;/**< used for unsigned 32bit */
typedef	unsigned long long int u64;/**< used for unsigned 64bit */

/* If your machine support 64 bit
define the MACHINE_64_BIT*/
#elif defined MACHINE_64_BIT
/*signed integer types*/
typedef	signed char  s8;/**< used for signed 8bit */
typedef	signed short int s16;/**< used for signed 16bit */
typedef	signed int s32;/**< used for signed 32bit */
typedef	signed long int s64;/**< used for signed 64bit */

/*unsigned integer types*/
typedef	unsigned char u8;/**< used for unsigned 8bit */
typedef	unsigned short int u16;/**< used for unsigned 16bit */
typedef	unsigned int u32;/**< used for unsigned 32bit */
typedef	unsigned long int u64;/**< used for unsigned 64bit */

#else
#warning The data types defined above which not supported \
define the data types manually
#endif
#endif
#endif

/**************************************************************/
/**\name	I2C ADDRESS DEFINITIONS    */
/**************************************************************/
#define BMA253_I2C_ADDR1                (0x18)
#define BMA253_I2C_ADDR2                (0x19)

/**************************************************************/
/**\name	CONSTANTS DEFINITION    */
/**************************************************************/
#define         BMA253_INIT_VALUE                       ((u8)0)
#define         BMA253_GEN_READ_WRITE_LENGTH            ((u8)1)
#define		BMA253_INTERFACE_IDLE_TIME_DELAY	((u8)1)
#define         BMA253_LSB_MSB_READ_LENGTH		((u8)2)
	/**	BIT SHIFT DEFINITIONS    */
#define         BMA253_SHIFT_TWO_BITS                   ((u8)2)
#define         BMA253_SHIFT_FOUR_BITS                  ((u8)4)
#define         BMA253_SHIFT_FIVE_BITS                  ((u8)5)
#define         BMA253_SHIFT_SIX_BITS                   ((u8)6)
#define         BMA253_SHIFT_EIGHT_BITS                 ((u8)8)
	/**	FIFO DEFINITIONS    */
#define		BMA253_FIFO_MODE_STATUS_RANGE		((u8)2)
#define		BMA253_FIFO_DATA_SELECT_RANGE		((u8)4)
#define		BMA253_FIFO_MODE_RANGE			((u8)4)
#define         BMA253_FIFO_WML_RANGE                   ((u8)32)

#define         BMA253_FIFO_XYZ_DATA_ENABLED          (0x00)
#define         BMA253_FIFO_X_DATA_ENABLED          (0x01)
#define         BMA253_FIFO_Y_DATA_ENABLED          (0x02)
#define         BMA253_FIFO_Z_DATA_ENABLED          (0x03)
#define         BMA253_FIFO_DATA_ENABLED_MASK         (0x03)
#define         BMA253_FIFO_XYZ_AXES_FRAME_SIZE       ((u8)6)
#define         BMA253_FIFO_SINGLE_AXIS_FRAME_SIZE    ((u8)2)
	/**	MODE RANGES    */
#define         BMA253_ACCEL_BW_MIN_RANGE               ((u8)7)
#define         BMA253_ACCEL_BW_1000HZ_RANGE            ((u8)15)
#define         BMA253_ACCEL_BW_MAX_RANGE               ((u8)16)
#define		BMA253_SLEEP_DURN_MIN_RANGE		((u8)4)
#define		BMA253_SLEEP_TIMER_MODE_RANGE		((u8)2)
#define		BMA253_SLEEP_DURN_MAX_RANGE		((u8)16)
#define		BMA253_POWER_MODE_RANGE			((u8)6)
#define		BMA253_SELF_TEST_AXIS_RANGE		((u8)4)
#define		BMA253_SELF_TEST_SIGN_RANGE		((u8)2)

/**************************************************************/
/**\name	BMA253_ERROR CODE DEFINITIONS    */
/**************************************************************/
#define E_OUT_OF_RANGE          ((s8)-2)
#define E_BMA253_NULL_PTR       ((s8)-127)
#define BMA253_NULL             ((void *)0)
#define BMA253_ERROR			((s8)-1)
#define	BMA253_SUCCESS			((u8)0)
/**************************************************************/
/**\name	RETURN TYPE DEFINITION    */
/**************************************************************/
#define	BMA253_RETURN_FUNCTION_TYPE        s8
/**< This refers BMA253 return type as char */

/**************************************************************/
/**\name	REGISTER ADDRESS DEFINITIONS    */
/**************************************************************/
#define BMA253_EEP_OFFSET                       (0x16)
#define BMA253_IMAGE_BASE                       (0x38)
#define BMA253_IMAGE_LEN                        (22)
#define BMA253_CHIP_ID_ADDR			(0x00)
/** DATA ADDRESS DEFINITIONS */
#define BMA253_X_AXIS_LSB_ADDR                  (0x02)
#define BMA253_X_AXIS_MSB_ADDR                  (0x03)
#define BMA253_Y_AXIS_LSB_ADDR                  (0x04)
#define BMA253_Y_AXIS_MSB_ADDR                  (0x05)
#define BMA253_Z_AXIS_LSB_ADDR                  (0x06)
#define BMA253_Z_AXIS_MSB_ADDR                  (0x07)
#define BMA253_TEMP_ADDR			(0x08)
/**STATUS ADDRESS DEFINITIONS */
#define BMA253_STAT1_ADDR			(0x09)
#define BMA253_STAT2_ADDR			(0x0A)
#define BMA253_STAT_TAP_SLOPE_ADDR		(0x0B)
#define BMA253_STAT_ORIENT_HIGH_ADDR		(0x0C)
#define BMA253_STAT_FIFO_ADDR			(0x0E)
/**STATUS ADDRESS DEFINITIONS */
#define BMA253_RANGE_SELECT_ADDR		(0x0F)
#define BMA253_BW_SELECT_ADDR                   (0x10)
#define BMA253_MODE_CTRL_ADDR                   (0x11)
#define BMA253_LOW_NOISE_CTRL_ADDR              (0x12)
#define BMA253_DATA_CTRL_ADDR                   (0x13)
#define BMA253_RST_ADDR                         (0x14)
/**INTERUPT ADDRESS DEFINITIONS */
#define BMA253_INTR_ENABLE1_ADDR                (0x16)
#define BMA253_INTR_ENABLE2_ADDR                (0x17)
#define BMA253_INTR_SLOW_NO_MOTION_ADDR         (0x18)
#define BMA253_INTR1_PAD_SELECT_ADDR            (0x19)
#define BMA253_INTR_DATA_SELECT_ADDR            (0x1A)
#define BMA253_INTR2_PAD_SELECT_ADDR            (0x1B)
#define BMA253_INTR_SOURCE_ADDR                 (0x1E)
#define BMA253_INTR_SET_ADDR                    (0x20)
#define BMA253_INTR_CTRL_ADDR                   (0x21)
/** FEATURE ADDRESS DEFINITIONS */
#define BMA253_LOW_DURN_ADDR                     (0x22)
#define BMA253_LOW_THRES_ADDR                    (0x23)
#define BMA253_LOW_HIGH_HYST_ADDR                (0x24)
#define BMA253_HIGH_DURN_ADDR                    (0x25)
#define BMA253_HIGH_THRES_ADDR                   (0x26)
#define BMA253_SLOPE_DURN_ADDR                   (0x27)
#define BMA253_SLOPE_THRES_ADDR                  (0x28)
#define BMA253_SLOW_NO_MOTION_THRES_ADDR         (0x29)
#define BMA253_TAP_PARAM_ADDR                    (0x2A)
#define BMA253_TAP_THRES_ADDR                    (0x2B)
#define BMA253_ORIENT_PARAM_ADDR                 (0x2C)
#define BMA253_THETA_BLOCK_ADDR                  (0x2D)
#define BMA253_THETA_FLAT_ADDR                   (0x2E)
#define BMA253_FLAT_HOLD_TIME_ADDR               (0x2F)
#define BMA253_SELFTEST_ADDR                     (0x32)
#define BMA253_EEPROM_CTRL_ADDR                  (0x33)
#define BMA253_SERIAL_CTRL_ADDR                  (0x34)
/**OFFSET ADDRESS DEFINITIONS */
#define BMA253_OFFSET_CTRL_ADDR                  (0x36)
#define BMA253_OFFSET_PARAMS_ADDR                (0x37)
#define BMA253_OFFSET_X_AXIS_ADDR                (0x38)
#define BMA253_OFFSET_Y_AXIS_ADDR                (0x39)
#define BMA253_OFFSET_Z_AXIS_ADDR                (0x3A)
/**GP ADDRESS DEFINITIONS */
#define BMA253_GP0_ADDR                          (0x3B)
#define BMA253_GP1_ADDR                          (0x3C)
/**FIFO ADDRESS DEFINITIONS */
#define BMA253_FIFO_MODE_ADDR                    (0x3E)
#define BMA253_FIFO_DATA_OUTPUT_ADDR             (0x3F)
#define BMA253_FIFO_WML_TRIG                     (0x30)

/**************************************************************/
/**\name	ACCEL RESOLUTION DEFINITION   */
/**************************************************************/
#define BMA253_12_RESOLUTION                    (0)
#define BMA253_10_RESOLUTION                    (1)
#define BMA253_14_RESOLUTION                    (2)

/**************************************************************/
/**\name	ACCEL DELAY DEFINITION   */
/**************************************************************/
/* register write and read delays */
#define BMA253_MDELAY_DATA_TYPE                 u32
#define BMA253_EE_W_DELAY                       (28)

/*********************************************************************/
/**\name REGISTER BIT MASK, BIT LENGTH, BIT POSITION DEFINITIONS  */
/********************************************************************/
/******************************/
/**\name CHIP ID  */
/******************************/
#define BMA253_CHIP_ID_POS             (0)
#define BMA253_CHIP_ID_MSK             (0xFF)
#define BMA253_CHIP_ID_LEN             (8)
#define BMA253_CHIP_ID_REG             BMA253_CHIP_ID_ADDR

/******************************/
/**\name DATA REGISTER-X  */
/******************************/
#define BMA253_NEW_DATA_X_POS          (0)
#define BMA253_NEW_DATA_X_LEN          (1)
#define BMA253_NEW_DATA_X_MSK          (0x01)
#define BMA253_NEW_DATA_X_REG          BMA253_X_AXIS_LSB_ADDR

#define BMA253_ACCEL_X14_LSB_POS          (2)
#define BMA253_ACCEL_X14_LSB_LEN          (6)
#define BMA253_ACCEL_X14_LSB_MSK          (0xFC)
#define BMA253_ACCEL_X14_LSB_REG           BMA253_X_AXIS_LSB_ADDR

#define BMA253_ACCEL_X12_LSB_POS           (4)
#define BMA253_ACCEL_X12_LSB_LEN           (4)
#define BMA253_ACCEL_X12_LSB_MSK           (0xF0)
#define BMA253_ACCEL_X12_LSB_REG           BMA253_X_AXIS_LSB_ADDR

#define BMA253_ACCEL_X10_LSB_POS           (6)
#define BMA253_ACCEL_X10_LSB_LEN           (2)
#define BMA253_ACCEL_X10_LSB_MSK           (0xC0)
#define BMA253_ACCEL_X10_LSB_REG           BMA253_X_AXIS_LSB_ADDR

#define BMA253_ACCEL_X8_LSB_POS           (0)
#define BMA253_ACCEL_X8_LSB_LEN           (0)
#define BMA253_ACCEL_X8_LSB_MSK           (0x00)
#define BMA253_ACCEL_X8_LSB_REG           BMA253_X_AXIS_LSB_ADDR

#define BMA253_ACCEL_X_MSB_POS           (0)
#define BMA253_ACCEL_X_MSB_LEN           (8)
#define BMA253_ACCEL_X_MSB_MSK           (0xFF)
#define BMA253_ACCEL_X_MSB_REG           BMA253_X_AXIS_MSB_ADDR
/******************************/
/**\name DATA REGISTER-Y  */
/******************************/
#define BMA253_NEW_DATA_Y_POS          (0)
#define BMA253_NEW_DATA_Y_LEN          (1)
#define BMA253_NEW_DATA_Y_MSK          (0x01)
#define BMA253_NEW_DATA_Y_REG          BMA253_Y_AXIS_LSB_ADDR

#define BMA253_ACCEL_Y14_LSB_POS           (2)
#define BMA253_ACCEL_Y14_LSB_LEN           (6)
#define BMA253_ACCEL_Y14_LSB_MSK           (0xFC)
#define BMA253_ACCEL_Y14_LSB_REG           BMA253_Y_AXIS_LSB_ADDR

#define BMA253_ACCEL_Y12_LSB_POS           (4)
#define BMA253_ACCEL_Y12_LSB_LEN           (4)
#define BMA253_ACCEL_Y12_LSB_MSK           (0xF0)
#define BMA253_ACCEL_Y12_LSB_REG           BMA253_Y_AXIS_LSB_ADDR

#define BMA253_ACCEL_Y10_LSB_POS           (6)
#define BMA253_ACCEL_Y10_LSB_LEN           (2)
#define BMA253_ACCEL_Y10_LSB_MSK           (0xC0)
#define BMA253_ACCEL_Y10_LSB_REG           BMA253_Y_AXIS_LSB_ADDR

#define BMA253_ACCEL_Y8_LSB_POS           (0)
#define BMA253_ACCEL_Y8_LSB_LEN           (0)
#define BMA253_ACCEL_Y8_LSB_MSK           (0x00)
#define BMA253_ACCEL_Y8_LSB_REG           BMA253_Y_AXIS_LSB_ADDR

#define BMA253_ACCEL_Y_MSB_POS           (0)
#define BMA253_ACCEL_Y_MSB_LEN           (8)
#define BMA253_ACCEL_Y_MSB_MSK           (0xFF)
#define BMA253_ACCEL_Y_MSB_REG           BMA253_Y_AXIS_MSB_ADDR
/******************************/
/**\name DATA REGISTER-Z  */
/******************************/
#define BMA253_NEW_DATA_Z_POS          (0)
#define BMA253_NEW_DATA_Z_LEN          (1)
#define BMA253_NEW_DATA_Z_MSK          (0x01)
#define BMA253_NEW_DATA_Z_REG          BMA253_Z_AXIS_LSB_ADDR

#define BMA253_ACCEL_Z14_LSB_POS           (2)
#define BMA253_ACCEL_Z14_LSB_LEN           (6)
#define BMA253_ACCEL_Z14_LSB_MSK           (0xFC)
#define BMA253_ACCEL_Z14_LSB_REG           BMA253_Z_AXIS_LSB_ADDR

#define BMA253_ACCEL_Z12_LSB_POS           (4)
#define BMA253_ACCEL_Z12_LSB_LEN           (4)
#define BMA253_ACCEL_Z12_LSB_MSK           (0xF0)
#define BMA253_ACCEL_Z12_LSB_REG           BMA253_Z_AXIS_LSB_ADDR

#define BMA253_ACCEL_Z10_LSB_POS           (6)
#define BMA253_ACCEL_Z10_LSB_LEN           (2)
#define BMA253_ACCEL_Z10_LSB_MSK           (0xC0)
#define BMA253_ACCEL_Z10_LSB_REG           BMA253_Z_AXIS_LSB_ADDR

#define BMA253_ACCEL_Z8_LSB_POS           (0)
#define BMA253_ACCEL_Z8_LSB_LEN           (0)
#define BMA253_ACCEL_Z8_LSB_MSK           (0x00)
#define BMA253_ACCEL_Z8_LSB_REG           BMA253_Z_AXIS_LSB_ADDR

#define BMA253_ACCEL_Z_MSB_POS           (0)
#define BMA253_ACCEL_Z_MSB_LEN           (8)
#define BMA253_ACCEL_Z_MSB_MSK           (0xFF)
#define BMA253_ACCEL_Z_MSB_REG           BMA253_Z_AXIS_MSB_ADDR

/******************************/
/**\name TEMPERATURE */
/******************************/
#define BMA253_ACCEL_TEMP_MSB_POS           (0)
#define BMA253_ACCEL_TEMP_MSB_LEN           (8)
#define BMA253_ACCEL_TEMP_MSB_MSK           (0xFF)
#define BMA253_ACCEL_TEMP_MSB_REG           BMA253_TEMPERATURE_REG

/***************************************/
/**\name INTERRUPT STATUS OF LOW-G */
/**************************************/
#define BMA253_LOW_G_INTR_STAT_POS          (0)
#define BMA253_LOW_G_INTR_STAT_LEN          (1)
#define BMA253_LOW_G_INTR_STAT_MSK          (0x01)
#define BMA253_LOW_G_INTR_STAT_REG          BMA253_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF HIGH-G */
/**************************************/
#define BMA253_HIGH_G_INTR_STAT_POS          (1)
#define BMA253_HIGH_G_INTR_STAT_LEN          (1)
#define BMA253_HIGH_G_INTR_STAT_MSK          (0x02)
#define BMA253_HIGH_G_INTR_STAT_REG          BMA253_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF SLOPE */
/**************************************/
#define BMA253_SLOPE_INTR_STAT_POS          (2)
#define BMA253_SLOPE_INTR_STAT_LEN          (1)
#define BMA253_SLOPE_INTR_STAT_MSK          (0x04)
#define BMA253_SLOPE_INTR_STAT_REG          BMA253_STAT1_ADDR
/*******************************************/
/**\name INTERRUPT STATUS OF SLOW NO MOTION*/
/*******************************************/
#define BMA253_SLOW_NO_MOTION_INTR_STAT_POS          (3)
#define BMA253_SLOW_NO_MOTION_INTR_STAT_LEN          (1)
#define BMA253_SLOW_NO_MOTION_INTR_STAT_MSK          (0x08)
#define BMA253_SLOW_NO_MOTION_INTR_STAT_REG          BMA253_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF DOUBLE TAP */
/**************************************/
#define BMA253_DOUBLE_TAP_INTR_STAT_POS     (4)
#define BMA253_DOUBLE_TAP_INTR_STAT_LEN     (1)
#define BMA253_DOUBLE_TAP_INTR_STAT_MSK     (0x10)
#define BMA253_DOUBLE_TAP_INTR_STAT_REG     BMA253_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF SINGLE TAP */
/**************************************/
#define BMA253_SINGLE_TAP_INTR_STAT_POS     (5)
#define BMA253_SINGLE_TAP_INTR_STAT_LEN     (1)
#define BMA253_SINGLE_TAP_INTR_STAT_MSK     (0x20)
#define BMA253_SINGLE_TAP_INTR_STAT_REG     BMA253_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF ORIENT*/
/**************************************/
#define BMA253_ORIENT_INTR_STAT_POS         (6)
#define BMA253_ORIENT_INTR_STAT_LEN         (1)
#define BMA253_ORIENT_INTR_STAT_MSK         (0x40)
#define BMA253_ORIENT_INTR_STAT_REG         BMA253_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF FLAT */
/**************************************/
#define BMA253_FLAT_INTR_STAT_POS           (7)
#define BMA253_FLAT_INTR_STAT_LEN           (1)
#define BMA253_FLAT_INTR_STAT_MSK           (0x80)
#define BMA253_FLAT_INTR_STAT_REG           BMA253_STAT1_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF FIFO FULL */
/**************************************/
#define BMA253_FIFO_FULL_INTR_STAT_POS           (5)
#define BMA253_FIFO_FULL_INTR_STAT_LEN           (1)
#define BMA253_FIFO_FULL_INTR_STAT_MSK           (0x20)
#define BMA253_FIFO_FULL_INTR_STAT_REG           BMA253_STAT2_ADDR
/*******************************************/
/**\name INTERRUPT STATUS OF FIFO WATERMARK*/
/******************************************/
#define BMA253_FIFO_WM_INTR_STAT_POS           (6)
#define BMA253_FIFO_WM_INTR_STAT_LEN           (1)
#define BMA253_FIFO_WM_INTR_STAT_MSK           (0x40)
#define BMA253_FIFO_WM_INTR_STAT_REG           BMA253_STAT2_ADDR
/***************************************/
/**\name INTERRUPT STATUS OF DATA */
/**************************************/
#define BMA253_DATA_INTR_STAT_POS           (7)
#define BMA253_DATA_INTR_STAT_LEN           (1)
#define BMA253_DATA_INTR_STAT_MSK           (0x80)
#define BMA253_DATA_INTR_STAT_REG           BMA253_STAT2_ADDR
/*********************************************/
/**\name INTERRUPT STATUS SLOPE XYZ AND SIGN */
/*********************************************/
#define BMA253_SLOPE_FIRST_X_POS        (0)
#define BMA253_SLOPE_FIRST_X_LEN        (1)
#define BMA253_SLOPE_FIRST_X_MSK        (0x01)
#define BMA253_SLOPE_FIRST_X_REG        BMA253_STAT_TAP_SLOPE_ADDR

#define BMA253_SLOPE_FIRST_Y_POS        (1)
#define BMA253_SLOPE_FIRST_Y_LEN        (1)
#define BMA253_SLOPE_FIRST_Y_MSK        (0x02)
#define BMA253_SLOPE_FIRST_Y_REG        BMA253_STAT_TAP_SLOPE_ADDR

#define BMA253_SLOPE_FIRST_Z_POS        (2)
#define BMA253_SLOPE_FIRST_Z_LEN        (1)
#define BMA253_SLOPE_FIRST_Z_MSK        (0x04)
#define BMA253_SLOPE_FIRST_Z_REG        BMA253_STAT_TAP_SLOPE_ADDR

#define BMA253_SLOPE_SIGN_STAT_POS         (3)
#define BMA253_SLOPE_SIGN_STAT_LEN         (1)
#define BMA253_SLOPE_SIGN_STAT_MSK         (0x08)
#define BMA253_SLOPE_SIGN_STAT_REG         BMA253_STAT_TAP_SLOPE_ADDR
/*********************************************/
/**\name INTERRUPT STATUS TAP XYZ AND SIGN */
/*********************************************/
#define BMA253_TAP_FIRST_X_POS        (4)
#define BMA253_TAP_FIRST_X_LEN        (1)
#define BMA253_TAP_FIRST_X_MSK        (0x10)
#define BMA253_TAP_FIRST_X_REG        BMA253_STAT_TAP_SLOPE_ADDR

#define BMA253_TAP_FIRST_Y_POS        (5)
#define BMA253_TAP_FIRST_Y_LEN        (1)
#define BMA253_TAP_FIRST_Y_MSK        (0x20)
#define BMA253_TAP_FIRST_Y_REG        BMA253_STAT_TAP_SLOPE_ADDR

#define BMA253_TAP_FIRST_Z_POS        (6)
#define BMA253_TAP_FIRST_Z_LEN        (1)
#define BMA253_TAP_FIRST_Z_MSK        (0x40)
#define BMA253_TAP_FIRST_Z_REG        BMA253_STAT_TAP_SLOPE_ADDR

#define BMA253_TAP_SIGN_STAT_POS         (7)
#define BMA253_TAP_SIGN_STAT_LEN         (1)
#define BMA253_TAP_SIGN_STAT_MSK         (0x80)
#define BMA253_TAP_SIGN_STAT_REG         BMA253_STAT_TAP_SLOPE_ADDR
/*********************************************/
/**\name INTERRUPT STATUS HIGH_G XYZ AND SIGN */
/*********************************************/
#define BMA253_HIGH_G_FIRST_X_POS        (0)
#define BMA253_HIGH_G_FIRST_X_LEN        (1)
#define BMA253_HIGH_G_FIRST_X_MSK        (0x01)
#define BMA253_HIGH_G_FIRST_X_REG        BMA253_STAT_ORIENT_HIGH_ADDR

#define BMA253_HIGH_G_FIRST_Y_POS        (1)
#define BMA253_HIGH_G_FIRST_Y_LEN        (1)
#define BMA253_HIGH_G_FIRST_Y_MSK        (0x02)
#define BMA253_HIGH_G_FIRST_Y_REG        BMA253_STAT_ORIENT_HIGH_ADDR

#define BMA253_HIGH_G_FIRST_Z_POS        (2)
#define BMA253_HIGH_G_FIRST_Z_LEN        (1)
#define BMA253_HIGH_G_FIRST_Z_MSK        (0x04)
#define BMA253_HIGH_G_FIRST_Z_REG        BMA253_STAT_ORIENT_HIGH_ADDR

#define BMA253_HIGH_G_SIGN_STAT_POS         (3)
#define BMA253_HIGH_G_SIGN_STAT_LEN         (1)
#define BMA253_HIGH_G_SIGN_STAT_MSK         (0x08)
#define BMA253_HIGH_G_SIGN_STAT_REG         BMA253_STAT_ORIENT_HIGH_ADDR
/*********************************************/
/**\name INTERRUPT STATUS ORIENT */
/*********************************************/
#define BMA253_ORIENT_STAT_POS             (4)
#define BMA253_ORIENT_STAT_LEN             (3)
#define BMA253_ORIENT_STAT_MSK             (0x70)
#define BMA253_ORIENT_STAT_REG             BMA253_STAT_ORIENT_HIGH_ADDR
/*********************************************/
/**\name INTERRUPT STATUS FLAT */
/*********************************************/
#define BMA253_FLAT_STAT_POS               (7)
#define BMA253_FLAT_STAT_LEN               (1)
#define BMA253_FLAT_STAT_MSK               (0x80)
#define BMA253_FLAT_STAT_REG               BMA253_STAT_ORIENT_HIGH_ADDR

/*********************************************/
/**\name INTERRUPT STATUS OF FIFO FRAME COUNT */
/*********************************************/
#define BMA253_FIFO_FRAME_COUNT_STAT_POS             (0)
#define BMA253_FIFO_FRAME_COUNT_STAT_LEN             (7)
#define BMA253_FIFO_FRAME_COUNT_STAT_MSK             (0x7F)
#define BMA253_FIFO_FRAME_COUNT_STAT_REG             BMA253_STAT_FIFO_ADDR
/*********************************************/
/**\name INTERRUPT STATUS OF FIFO OVERRUN */
/*********************************************/
#define BMA253_FIFO_OVERRUN_STAT_POS             (7)
#define BMA253_FIFO_OVERRUN_STAT_LEN             (1)
#define BMA253_FIFO_OVERRUN_STAT_MSK             (0x80)
#define BMA253_FIFO_OVERRUN_STAT_REG             BMA253_STAT_FIFO_ADDR
/****************************/
/**\name RANGE */
/****************************/
#define BMA253_RANGE_SELECT_POS             (0)
#define BMA253_RANGE_SELECT_LEN             (4)
#define BMA253_RANGE_SELECT_MSK             (0x0F)
#define BMA253_RANGE_SELECT_REG             BMA253_RANGE_SELECT_ADDR
/****************************/
/**\name BANDWIDTH */
/****************************/
#define BMA253_BW_POS             (0)
#define BMA253_BW_LEN             (5)
#define BMA253_BW_MSK             (0x1F)
#define BMA253_BW_REG             BMA253_BW_SELECT_ADDR
/****************************/
/**\name SLEEP DURATION */
/****************************/
#define BMA253_SLEEP_DURN_POS             (1)
#define BMA253_SLEEP_DURN_LEN             (4)
#define BMA253_SLEEP_DURN_MSK             (0x1E)
#define BMA253_SLEEP_DURN_REG             BMA253_MODE_CTRL_ADDR
/****************************/
/**\name POWER MODEPOWER MODE */
/****************************/
#define BMA253_MODE_CTRL_POS             (5)
#define BMA253_MODE_CTRL_LEN             (3)
#define BMA253_MODE_CTRL_MSK             (0xE0)
#define BMA253_MODE_CTRL_REG             BMA253_MODE_CTRL_ADDR
/****************************/
/**\name SLEEP TIMER */
/****************************/
#define BMA253_SLEEP_TIMER_POS          (5)
#define BMA253_SLEEP_TIMER_LEN          (1)
#define BMA253_SLEEP_TIMER_MSK          (0x20)
#define BMA253_SLEEP_TIMER_REG          BMA253_LOW_NOISE_CTRL_ADDR
/****************************/
/**\name LOWPOWER MODE */
/****************************/
#define BMA253_LOW_POWER_MODE_POS          (6)
#define BMA253_LOW_POWER_MODE_LEN          (1)
#define BMA253_LOW_POWER_MODE_MSK          (0x40)
#define BMA253_LOW_POWER_MODE_REG          BMA253_LOW_NOISE_CTRL_ADDR
/*******************************************/
/**\name DISABLE MSB SHADOWING PROCEDURE  */
/*******************************************/
#define BMA253_DIS_SHADOW_PROC_POS       (6)
#define BMA253_DIS_SHADOW_PROC_LEN       (1)
#define BMA253_DIS_SHADOW_PROC_MSK       (0x40)
#define BMA253_DIS_SHADOW_PROC_REG       BMA253_DATA_CTRL_ADDR
/***************************************************/
/**\name FILTERED OR UNFILTERED ACCELERATION DATA   */
/***************************************************/
#define BMA253_ENABLE_DATA_HIGH_BW_POS         (7)
#define BMA253_ENABLE_DATA_HIGH_BW_LEN         (1)
#define BMA253_ENABLE_DATA_HIGH_BW_MSK         (0x80)
#define BMA253_ENABLE_DATA_HIGH_BW_REG         BMA253_DATA_CTRL_ADDR
/***************************************************/
/**\name SOFT RESET VALUE   */
/***************************************************/
#define BMA253_ENABLE_SOFT_RESET_VALUE        (0xB6)
/**********************************************/
/**\name INTERRUPT ENABLE OF SLOPE-XYZ   */
/**********************************************/
#define BMA253_ENABLE_SLOPE_X_INTR_POS         (0)
#define BMA253_ENABLE_SLOPE_X_INTR_LEN         (1)
#define BMA253_ENABLE_SLOPE_X_INTR_MSK         (0x01)
#define BMA253_ENABLE_SLOPE_X_INTR_REG         BMA253_INTR_ENABLE1_ADDR

#define BMA253_ENABLE_SLOPE_Y_INTR_POS         (1)
#define BMA253_ENABLE_SLOPE_Y_INTR_LEN         (1)
#define BMA253_ENABLE_SLOPE_Y_INTR_MSK         (0x02)
#define BMA253_ENABLE_SLOPE_Y_INTR_REG         BMA253_INTR_ENABLE1_ADDR

#define BMA253_ENABLE_SLOPE_Z_INTR_POS         (2)
#define BMA253_ENABLE_SLOPE_Z_INTR_LEN         (1)
#define BMA253_ENABLE_SLOPE_Z_INTR_MSK         (0x04)
#define BMA253_ENABLE_SLOPE_Z_INTR_REG         BMA253_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF DOUBLE TAP   */
/**********************************************/
#define BMA253_ENABLE_DOUBLE_TAP_INTR_POS      (4)
#define BMA253_ENABLE_DOUBLE_TAP_INTR_LEN      (1)
#define BMA253_ENABLE_DOUBLE_TAP_INTR_MSK      (0x10)
#define BMA253_ENABLE_DOUBLE_TAP_INTR_REG      BMA253_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF SINGLE TAP   */
/**********************************************/
#define BMA253_ENABLE_SINGLE_TAP_INTR_POS      (5)
#define BMA253_ENABLE_SINGLE_TAP_INTR_LEN      (1)
#define BMA253_ENABLE_SINGLE_TAP_INTR_MSK      (0x20)
#define BMA253_ENABLE_SINGLE_TAP_INTR_REG      BMA253_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF ORIENT  */
/**********************************************/
#define BMA253_ENABLE_ORIENT_INTR_POS          (6)
#define BMA253_ENABLE_ORIENT_INTR_LEN          (1)
#define BMA253_ENABLE_ORIENT_INTR_MSK          (0x40)
#define BMA253_ENABLE_ORIENT_INTR_REG          BMA253_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FLAT  */
/**********************************************/
#define BMA253_ENABLE_FLAT_INTR_POS            (7)
#define BMA253_ENABLE_FLAT_INTR_LEN            (1)
#define BMA253_ENABLE_FLAT_INTR_MSK            (0x80)
#define BMA253_ENABLE_FLAT_INTR_REG            BMA253_INTR_ENABLE1_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF HIGH_G-XYZ   */
/**********************************************/
#define BMA253_ENABLE_HIGH_G_X_INTR_POS         (0)
#define BMA253_ENABLE_HIGH_G_X_INTR_LEN         (1)
#define BMA253_ENABLE_HIGH_G_X_INTR_MSK         (0x01)
#define BMA253_ENABLE_HIGH_G_X_INTR_REG         BMA253_INTR_ENABLE2_ADDR

#define BMA253_ENABLE_HIGH_G_Y_INTR_POS         (1)
#define BMA253_ENABLE_HIGH_G_Y_INTR_LEN         (1)
#define BMA253_ENABLE_HIGH_G_Y_INTR_MSK         (0x02)
#define BMA253_ENABLE_HIGH_G_Y_INTR_REG         BMA253_INTR_ENABLE2_ADDR

#define BMA253_ENABLE_HIGH_G_Z_INTR_POS         (2)
#define BMA253_ENABLE_HIGH_G_Z_INTR_LEN         (1)
#define BMA253_ENABLE_HIGH_G_Z_INTR_MSK         (0x04)
#define BMA253_ENABLE_HIGH_G_Z_INTR_REG         BMA253_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF LOW_G  */
/**********************************************/
#define BMA253_ENABLE_LOW_G_INTR_POS            (3)
#define BMA253_ENABLE_LOW_G_INTR_LEN            (1)
#define BMA253_ENABLE_LOW_G_INTR_MSK            (0x08)
#define BMA253_ENABLE_LOW_G_INTR_REG            BMA253_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF DATA   */
/**********************************************/
#define BMA253_ENABLE_NEW_DATA_INTR_POS        (4)
#define BMA253_ENABLE_NEW_DATA_INTR_LEN        (1)
#define BMA253_ENABLE_NEW_DATA_INTR_MSK        (0x10)
#define BMA253_ENABLE_NEW_DATA_INTR_REG        BMA253_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FIFO FULL   */
/**********************************************/
#define BMA253_INTR_FIFO_FULL_ENABLE_INTR_POS        (5)
#define BMA253_INTR_FIFO_FULL_ENABLE_INTR_LEN        (1)
#define BMA253_INTR_FIFO_FULL_ENABLE_INTR_MSK        (0x20)
#define BMA253_INTR_FIFO_FULL_ENABLE_INTR_REG        BMA253_INTR_ENABLE2_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF FIFO WATER MARK   */
/**********************************************/
#define BMA253_INTR_FIFO_WM_ENABLE_INTR_POS        (6)
#define BMA253_INTR_FIFO_WM_ENABLE_INTR_LEN        (1)
#define BMA253_INTR_FIFO_WM_ENABLE_INTR_MSK        (0x40)
#define BMA253_INTR_FIFO_WM_ENABLE_INTR_REG        BMA253_INTR_ENABLE2_ADDR
/************************************************/
/**\name INTERRUPT ENABLE OF SLOW NO MOTION-XYZ */
/*************************************************/
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_POS        (0)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_LEN        (1)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_MSK        (0x01)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_X_INTR_REG        \
BMA253_INTR_SLOW_NO_MOTION_ADDR

#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_POS        (1)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_LEN        (1)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_MSK        (0x02)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Y_INTR_REG        \
BMA253_INTR_SLOW_NO_MOTION_ADDR

#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_POS        (2)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_LEN        (1)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_MSK        (0x04)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_Z_INTR_REG        \
BMA253_INTR_SLOW_NO_MOTION_ADDR
/**********************************************/
/**\name INTERRUPT ENABLE OF SLOW NO MOTION SELECT */
/**********************************************/
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_POS        (3)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_LEN        (1)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_MSK        (0x08)
#define BMA253_INTR_SLOW_NO_MOTION_ENABLE_SELECT_INTR_REG        \
BMA253_INTR_SLOW_NO_MOTION_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD LOW_G */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_LOW_G_POS        (0)
#define BMA253_ENABLE_INTR1_PAD_LOW_G_LEN        (1)
#define BMA253_ENABLE_INTR1_PAD_LOW_G_MSK        (0x01)
#define BMA253_ENABLE_INTR1_PAD_LOW_G_REG        BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD HIGH_G */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_HIGH_G_POS       (1)
#define BMA253_ENABLE_INTR1_PAD_HIGH_G_LEN       (1)
#define BMA253_ENABLE_INTR1_PAD_HIGH_G_MSK       (0x02)
#define BMA253_ENABLE_INTR1_PAD_HIGH_G_REG       BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD SLOPE */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_SLOPE_POS       (2)
#define BMA253_ENABLE_INTR1_PAD_SLOPE_LEN       (1)
#define BMA253_ENABLE_INTR1_PAD_SLOPE_MSK       (0x04)
#define BMA253_ENABLE_INTR1_PAD_SLOPE_REG       BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF SLOW NO MOTION  */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_SLOW_NO_MOTION_POS        (3)
#define BMA253_ENABLE_INTR1_PAD_SLOW_NO_MOTION_LEN        (1)
#define BMA253_ENABLE_INTR1_PAD_SLOW_NO_MOTION_MSK        (0x08)
#define BMA253_ENABLE_INTR1_PAD_SLOW_NO_MOTION_REG        \
BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD DOUBLE_TAP */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_DOUBLE_TAP_POS      (4)
#define BMA253_ENABLE_INTR1_PAD_DOUBLE_TAP_LEN      (1)
#define BMA253_ENABLE_INTR1_PAD_DOUBLE_TAP_MSK      (0x10)
#define BMA253_ENABLE_INTR1_PAD_DOUBLE_TAP_REG      BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD SINGLE_TAP */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_SINGLE_TAP_POS     (5)
#define BMA253_ENABLE_INTR1_PAD_SINGLE_TAP_LEN     (1)
#define BMA253_ENABLE_INTR1_PAD_SINGLE_TAP_MSK     (0x20)
#define BMA253_ENABLE_INTR1_PAD_SINGLE_TAP_REG     BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD ORIENT*/
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_ORIENT_POS      (6)
#define BMA253_ENABLE_INTR1_PAD_ORIENT_LEN      (1)
#define BMA253_ENABLE_INTR1_PAD_ORIENT_MSK      (0x40)
#define BMA253_ENABLE_INTR1_PAD_ORIENT_REG      BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF PAD FLAT */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_FLAT_POS        (7)
#define BMA253_ENABLE_INTR1_PAD_FLAT_LEN        (1)
#define BMA253_ENABLE_INTR1_PAD_FLAT_MSK        (0x80)
#define BMA253_ENABLE_INTR1_PAD_FLAT_REG        BMA253_INTR1_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD LOW_G */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_LOW_G_POS        (0)
#define BMA253_ENABLE_INTR2_PAD_LOW_G_LEN        (1)
#define BMA253_ENABLE_INTR2_PAD_LOW_G_MSK        (0x01)
#define BMA253_ENABLE_INTR2_PAD_LOW_G_REG        BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD HIGH_G */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_HIGH_G_POS       (1)
#define BMA253_ENABLE_INTR2_PAD_HIGH_G_LEN       (1)
#define BMA253_ENABLE_INTR2_PAD_HIGH_G_MSK       (0x02)
#define BMA253_ENABLE_INTR2_PAD_HIGH_G_REG       BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SLOPE */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_SLOPE_POS       (2)
#define BMA253_ENABLE_INTR2_PAD_SLOPE_LEN       (1)
#define BMA253_ENABLE_INTR2_PAD_SLOPE_MSK       (0x04)
#define BMA253_ENABLE_INTR2_PAD_SLOPE_REG       BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SLOW NO MOTION */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_SLOW_NO_MOTION_POS        (3)
#define BMA253_ENABLE_INTR2_PAD_SLOW_NO_MOTION_LEN        (1)
#define BMA253_ENABLE_INTR2_PAD_SLOW_NO_MOTION_MSK        (0x08)
#define BMA253_ENABLE_INTR2_PAD_SLOW_NO_MOTION_REG        \
BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DOUBLE_TAP */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_DOUBLE_TAP_POS      (4)
#define BMA253_ENABLE_INTR2_PAD_DOUBLE_TAP_LEN      (1)
#define BMA253_ENABLE_INTR2_PAD_DOUBLE_TAP_MSK      (0x10)
#define BMA253_ENABLE_INTR2_PAD_DOUBLE_TAP_REG      BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD SINGLE_TAP */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_SINGLE_TAP_POS     (5)
#define BMA253_ENABLE_INTR2_PAD_SINGLE_TAP_LEN     (1)
#define BMA253_ENABLE_INTR2_PAD_SINGLE_TAP_MSK     (0x20)
#define BMA253_ENABLE_INTR2_PAD_SINGLE_TAP_REG     BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD ORIENT */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_ORIENT_POS      (6)
#define BMA253_ENABLE_INTR2_PAD_ORIENT_LEN      (1)
#define BMA253_ENABLE_INTR2_PAD_ORIENT_MSK      (0x40)
#define BMA253_ENABLE_INTR2_PAD_ORIENT_REG      BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FLAT */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_FLAT_POS        (7)
#define BMA253_ENABLE_INTR2_PAD_FLAT_LEN        (1)
#define BMA253_ENABLE_INTR2_PAD_FLAT_MSK        (0x80)
#define BMA253_ENABLE_INTR2_PAD_FLAT_REG        BMA253_INTR2_PAD_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DATA */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_NEWDATA_POS     (0)
#define BMA253_ENABLE_INTR1_PAD_NEWDATA_LEN     (1)
#define BMA253_ENABLE_INTR1_PAD_NEWDATA_MSK     (0x01)
#define BMA253_ENABLE_INTR1_PAD_NEWDATA_REG     BMA253_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF FIFO WATER MARK */
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_FIFO_WM_POS     (1)
#define BMA253_ENABLE_INTR1_PAD_FIFO_WM_LEN     (1)
#define BMA253_ENABLE_INTR1_PAD_FIFO_WM_MSK     (0x02)
#define BMA253_ENABLE_INTR1_PAD_FIFO_WM_REG     BMA253_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT1 ENABLE OF FIFO FULL*/
/**********************************************/
#define BMA253_ENABLE_INTR1_PAD_FIFO_FULL_POS     (2)
#define BMA253_ENABLE_INTR1_PAD_FIFO_FULL_LEN     (1)
#define BMA253_ENABLE_INTR1_PAD_FIFO_FULL_MSK     (0x04)
#define BMA253_ENABLE_INTR1_PAD_FIFO_FULL_REG     BMA253_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FIFO FULL */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_FIFO_FULL_POS     (5)
#define BMA253_ENABLE_INTR2_PAD_FIFO_FULL_LEN     (1)
#define BMA253_ENABLE_INTR2_PAD_FIFO_FULL_MSK     (0x20)
#define BMA253_ENABLE_INTR2_PAD_FIFO_FULL_REG     BMA253_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD FIFO WATERMARK*/
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_FIFO_WM_POS     (6)
#define BMA253_ENABLE_INTR2_PAD_FIFO_WM_LEN     (1)
#define BMA253_ENABLE_INTR2_PAD_FIFO_WM_MSK     (0x40)
#define BMA253_ENABLE_INTR2_PAD_FIFO_WM_REG     BMA253_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name INTERRUPT2 ENABLE OF PAD DATA */
/**********************************************/
#define BMA253_ENABLE_INTR2_PAD_NEWDATA_POS     (7)
#define BMA253_ENABLE_INTR2_PAD_NEWDATA_LEN     (1)
#define BMA253_ENABLE_INTR2_PAD_NEWDATA_MSK     (0x80)
#define BMA253_ENABLE_INTR2_PAD_NEWDATA_REG     BMA253_INTR_DATA_SELECT_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF LOW_G*/
/**********************************************/
#define BMA253_UNFILT_INTR_SOURCE_LOW_G_POS        (0)
#define BMA253_UNFILT_INTR_SOURCE_LOW_G_LEN        (1)
#define BMA253_UNFILT_INTR_SOURCE_LOW_G_MSK        (0x01)
#define BMA253_UNFILT_INTR_SOURCE_LOW_G_REG        BMA253_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF HIGH_G*/
/**********************************************/
#define BMA253_UNFILT_INTR_SOURCE_HIGH_G_POS       (1)
#define BMA253_UNFILT_INTR_SOURCE_HIGH_G_LEN       (1)
#define BMA253_UNFILT_INTR_SOURCE_HIGH_G_MSK       (0x02)
#define BMA253_UNFILT_INTR_SOURCE_HIGH_G_REG       BMA253_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF SLOPE*/
/**********************************************/
#define BMA253_UNFILT_INTR_SOURCE_SLOPE_POS       (2)
#define BMA253_UNFILT_INTR_SOURCE_SLOPE_LEN       (1)
#define BMA253_UNFILT_INTR_SOURCE_SLOPE_MSK       (0x04)
#define BMA253_UNFILT_INTR_SOURCE_SLOPE_REG       BMA253_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF SLOW NO MOTION*/
/**********************************************/
#define BMA253_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_POS        (3)
#define BMA253_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_LEN        (1)
#define BMA253_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_MSK        (0x08)
#define BMA253_UNFILT_INTR_SOURCE_SLOW_NO_MOTION_REG        \
BMA253_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF TAP*/
/**********************************************/
#define BMA253_UNFILT_INTR_SOURCE_TAP_POS         (4)
#define BMA253_UNFILT_INTR_SOURCE_TAP_LEN         (1)
#define BMA253_UNFILT_INTR_SOURCE_TAP_MSK         (0x10)
#define BMA253_UNFILT_INTR_SOURCE_TAP_REG         BMA253_INTR_SOURCE_ADDR
/**********************************************/
/**\name  INTERRUPT SOURCE SELECTION OF DATA*/
/**********************************************/
#define BMA253_UNFILT_INTR_SOURCE_DATA_POS        (5)
#define BMA253_UNFILT_INTR_SOURCE_DATA_LEN        (1)
#define BMA253_UNFILT_INTR_SOURCE_DATA_MSK        (0x20)
#define BMA253_UNFILT_INTR_SOURCE_DATA_REG        BMA253_INTR_SOURCE_ADDR
/****************************************************/
/**\name  INTERRUPT PAD ACTIVE LEVEL AND OUTPUT TYPE*/
/****************************************************/
#define BMA253_INTR1_PAD_ACTIVE_LEVEL_POS       (0)
#define BMA253_INTR1_PAD_ACTIVE_LEVEL_LEN       (1)
#define BMA253_INTR1_PAD_ACTIVE_LEVEL_MSK       (0x01)
#define BMA253_INTR1_PAD_ACTIVE_LEVEL_REG       BMA253_INTR_SET_ADDR

#define BMA253_INTR2_PAD_ACTIVE_LEVEL_POS       (2)
#define BMA253_INTR2_PAD_ACTIVE_LEVEL_LEN       (1)
#define BMA253_INTR2_PAD_ACTIVE_LEVEL_MSK       (0x04)
#define BMA253_INTR2_PAD_ACTIVE_LEVEL_REG       BMA253_INTR_SET_ADDR

#define BMA253_INTR1_PAD_OUTPUT_TYPE_POS        (1)
#define BMA253_INTR1_PAD_OUTPUT_TYPE_LEN        (1)
#define BMA253_INTR1_PAD_OUTPUT_TYPE_MSK        (0x02)
#define BMA253_INTR1_PAD_OUTPUT_TYPE_REG        BMA253_INTR_SET_ADDR

#define BMA253_INTR2_PAD_OUTPUT_TYPE_POS        (3)
#define BMA253_INTR2_PAD_OUTPUT_TYPE_LEN        (1)
#define BMA253_INTR2_PAD_OUTPUT_TYPE_MSK        (0x08)
#define BMA253_INTR2_PAD_OUTPUT_TYPE_REG        BMA253_INTR_SET_ADDR
/****************************************************/
/**\name   LATCH INTERRUPT */
/****************************************************/
#define BMA253_LATCH_INTR_POS                (0)
#define BMA253_LATCH_INTR_LEN                (4)
#define BMA253_LATCH_INTR_MSK                (0x0F)
#define BMA253_LATCH_INTR_REG                BMA253_INTR_CTRL_ADDR
/****************************************************/
/**\name   RESET LATCH INTERRUPT */
/****************************************************/
#define BMA253_RESET_INTR_POS           (7)
#define BMA253_RESET_INTR_LEN           (1)
#define BMA253_RESET_INTR_MSK           (0x80)
#define BMA253_RESET_INTR_REG           BMA253_INTR_CTRL_ADDR
/****************************************************/
/**\name   LOW_G HYSTERESIS */
/****************************************************/
#define BMA253_LOW_G_HYST_POS                   (0)
#define BMA253_LOW_G_HYST_LEN                   (2)
#define BMA253_LOW_G_HYST_MSK                   (0x03)
#define BMA253_LOW_G_HYST_REG                   BMA253_LOW_HIGH_HYST_ADDR
/****************************************************/
/**\name   LOW_G MODE */
/****************************************************/
#define BMA253_LOW_G_INTR_MODE_POS               (2)
#define BMA253_LOW_G_INTR_MODE_LEN               (1)
#define BMA253_LOW_G_INTR_MODE_MSK               (0x04)
#define BMA253_LOW_G_INTR_MODE_REG               BMA253_LOW_HIGH_HYST_ADDR

/****************************************************/
/**\name   HIGH_G HYSTERESIS */
/****************************************************/
#define BMA253_HIGH_G_HYST_POS                  (6)
#define BMA253_HIGH_G_HYST_LEN                  (2)
#define BMA253_HIGH_G_HYST_MSK                  (0xC0)
#define BMA253_HIGH_G_HYST_REG                  BMA253_LOW_HIGH_HYST_ADDR
/****************************************************/
/**\name   SLOPE DURATION */
/****************************************************/
#define BMA253_SLOPE_DURN_POS                    (0)
#define BMA253_SLOPE_DURN_LEN                    (2)
#define BMA253_SLOPE_DURN_MSK                    (0x03)
#define BMA253_SLOPE_DURN_REG                    BMA253_SLOPE_DURN_ADDR
/****************************************************/
/**\name   SLOW NO MOTION DURATION */
/****************************************************/
#define BMA253_SLOW_NO_MOTION_DURN_POS                    (2)
#define BMA253_SLOW_NO_MOTION_DURN_LEN                    (6)
#define BMA253_SLOW_NO_MOTION_DURN_MSK                    (0xFC)
#define BMA253_SLOW_NO_MOTION_DURN_REG                    BMA253_SLOPE_DURN_ADDR

/****************************************************/
/**\name   TAP DURATION */
/****************************************************/
#define BMA253_TAP_DURN_POS                    (0)
#define BMA253_TAP_DURN_LEN                    (3)
#define BMA253_TAP_DURN_MSK                    (0x07)
#define BMA253_TAP_DURN_REG                    BMA253_TAP_PARAM_ADDR

/****************************************************/
/**\name   TAP SHOCK DURATION */
/****************************************************/
#define BMA253_TAP_SHOCK_DURN_POS             (6)
#define BMA253_TAP_SHOCK_DURN_LEN             (1)
#define BMA253_TAP_SHOCK_DURN_MSK             (0x40)
#define BMA253_TAP_SHOCK_DURN_REG             BMA253_TAP_PARAM_ADDR

/* This advance tap interrupt only uses for the chip id 0xFB */
#define BMA253_ADV_TAP_INTR_POS                (5)
#define BMA253_ADV_TAP_INTR_LEN                (1)
#define BMA253_ADV_TAP_INTR_MSK                (0x20)
#define BMA253_ADV_TAP_INTR_REG                BMA253_TAP_PARAM_ADDR
/****************************************************/
/**\name   TAP QUIET DURATION */
/****************************************************/
#define BMA253_TAP_QUIET_DURN_POS             (7)
#define BMA253_TAP_QUIET_DURN_LEN             (1)
#define BMA253_TAP_QUIET_DURN_MSK             (0x80)
#define BMA253_TAP_QUIET_DURN_REG             BMA253_TAP_PARAM_ADDR
/****************************************************/
/**\name   TAP THRESHOLD */
/****************************************************/
#define BMA253_TAP_THRES_POS                  (0)
#define BMA253_TAP_THRES_LEN                  (5)
#define BMA253_TAP_THRES_MSK                  (0x1F)
#define BMA253_TAP_THRES_REG                  BMA253_TAP_THRES_ADDR
/****************************************************/
/**\name   TAP SAMPLES */
/****************************************************/
#define BMA253_TAP_SAMPLES_POS                (6)
#define BMA253_TAP_SAMPLES_LEN                (2)
#define BMA253_TAP_SAMPLES_MSK                (0xC0)
#define BMA253_TAP_SAMPLES_REG                BMA253_TAP_THRES_ADDR
/****************************************************/
/**\name  ORIENT MODE */
/****************************************************/
#define BMA253_ORIENT_MODE_POS                  (0)
#define BMA253_ORIENT_MODE_LEN                  (2)
#define BMA253_ORIENT_MODE_MSK                  (0x03)
#define BMA253_ORIENT_MODE_REG                  BMA253_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT BLOCKING */
/****************************************************/
#define BMA253_ORIENT_BLOCK_POS                 (2)
#define BMA253_ORIENT_BLOCK_LEN                 (2)
#define BMA253_ORIENT_BLOCK_MSK                 (0x0C)
#define BMA253_ORIENT_BLOCK_REG                 BMA253_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT HYSTERESIS */
/****************************************************/
#define BMA253_ORIENT_HYST_POS                  (4)
#define BMA253_ORIENT_HYST_LEN                  (3)
#define BMA253_ORIENT_HYST_MSK                  (0x70)
#define BMA253_ORIENT_HYST_REG                  BMA253_ORIENT_PARAM_ADDR
/****************************************************/
/**\name   ORIENT AXIS  */
/****************************************************/
#define BMA253_ORIENT_UD_ENABLE_POS                  (6)
#define BMA253_ORIENT_UD_ENABLE_LEN                  (1)
#define BMA253_ORIENT_UD_ENABLE_MSK                  (0x40)
#define BMA253_ORIENT_UD_ENABLE_REG                  BMA253_THETA_BLOCK_ADDR

/****************************************************/
/**\name   THETA BLOCKING */
/****************************************************/
#define BMA253_THETA_BLOCK_POS                  (0)
#define BMA253_THETA_BLOCK_LEN                  (6)
#define BMA253_THETA_BLOCK_MSK                  (0x3F)
#define BMA253_THETA_BLOCK_REG                  BMA253_THETA_BLOCK_ADDR
/****************************************************/
/**\name   THETA FLAT */
/****************************************************/
#define BMA253_THETA_FLAT_POS                  (0)
#define BMA253_THETA_FLAT_LEN                  (6)
#define BMA253_THETA_FLAT_MSK                  (0x3F)
#define BMA253_THETA_FLAT_REG                  BMA253_THETA_FLAT_ADDR
/****************************************************/
/**\name   THETA HOLD TIME */
/****************************************************/
#define BMA253_FLAT_HOLD_TIME_POS              (4)
#define BMA253_FLAT_HOLD_TIME_LEN              (2)
#define BMA253_FLAT_HOLD_TIME_MSK              (0x30)
#define BMA253_FLAT_HOLD_TIME_REG              BMA253_FLAT_HOLD_TIME_ADDR
/****************************************************/
/**\name   FLAT HYSTERESIS */
/****************************************************/
#define BMA253_FLAT_HYST_POS                   (0)
#define BMA253_FLAT_HYST_LEN                   (3)
#define BMA253_FLAT_HYST_MSK                   (0x07)
#define BMA253_FLAT_HYST_REG                   BMA253_FLAT_HOLD_TIME_ADDR
/****************************************************/
/**\name   FIFO WATER MARK LEVEL TRIGGER RETAIN  */
/****************************************************/
#define BMA253_FIFO_WML_TRIG_RETAIN_POS                   (0)
#define BMA253_FIFO_WML_TRIG_RETAIN_LEN                   (6)
#define BMA253_FIFO_WML_TRIG_RETAIN_MSK                   (0x3F)
#define BMA253_FIFO_WML_TRIG_RETAIN_REG                   BMA253_FIFO_WML_TRIG
/****************************************************/
/**\name   ACTIVATE SELF TEST  */
/****************************************************/
#define BMA253_ENABLE_SELFTEST_POS                (0)
#define BMA253_ENABLE_SELFTEST_LEN                (2)
#define BMA253_ENABLE_SELFTEST_MSK                (0x03)
#define BMA253_ENABLE_SELFTEST_REG                BMA253_SELFTEST_ADDR
/****************************************************/
/**\name   SELF TEST -- NEGATIVE   */
/****************************************************/
#define BMA253_NEG_SELFTEST_POS               (2)
#define BMA253_NEG_SELFTEST_LEN               (1)
#define BMA253_NEG_SELFTEST_MSK               (0x04)
#define BMA253_NEG_SELFTEST_REG               BMA253_SELFTEST_ADDR
/****************************************************/
/**\name   EEPROM CONTROL   */
/****************************************************/
#define BMA253_UNLOCK_EE_PROG_MODE_POS     (0)
#define BMA253_UNLOCK_EE_PROG_MODE_LEN     (1)
#define BMA253_UNLOCK_EE_PROG_MODE_MSK     (0x01)
#define BMA253_UNLOCK_EE_PROG_MODE_REG     BMA253_EEPROM_CTRL_ADDR
/**********************************************************************/
/**\name  SETTING THIS BIT STARTS WRITING SETTING REGISTERS TO EEPROM */
/*********************************************************************/
#define BMA253_START_EE_PROG_TRIG_POS      (1)
#define BMA253_START_EE_PROG_TRIG_LEN      (1)
#define BMA253_START_EE_PROG_TRIG_MSK      (0x02)
#define BMA253_START_EE_PROG_TRIG_REG      BMA253_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   STATUS OF WRITING TO EEPROM   */
/****************************************************/
#define BMA253_EE_PROG_READY_POS          (2)
#define BMA253_EE_PROG_READY_LEN          (1)
#define BMA253_EE_PROG_READY_MSK          (0x04)
#define BMA253_EE_PROG_READY_REG          BMA253_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   UPDATE IMAGE REGISTERS WRITING TO EEPROM   */
/****************************************************/
#define BMA253_UPDATE_IMAGE_POS                (3)
#define BMA253_UPDATE_IMAGE_LEN                (1)
#define BMA253_UPDATE_IMAGE_MSK                (0x08)
#define BMA253_UPDATE_IMAGE_REG                BMA253_EEPROM_CTRL_ADDR

#define BMA253_EE_REMAIN_POS                (4)
#define BMA253_EE_REMAIN_LEN                (4)
#define BMA253_EE_REMAIN_MSK                (0xF0)
#define BMA253_EE_REMAIN_REG                BMA253_EEPROM_CTRL_ADDR
/****************************************************/
/**\name   SPI INTERFACE MODE SELECTION   */
/***************************************************/
#define BMA253_ENABLE_SPI_MODE_3_POS              (0)
#define BMA253_ENABLE_SPI_MODE_3_LEN              (1)
#define BMA253_ENABLE_SPI_MODE_3_MSK              (0x01)
#define BMA253_ENABLE_SPI_MODE_3_REG              BMA253_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   I2C WATCHDOG PERIOD SELECTION   */
/***************************************************/
#define BMA253_I2C_WDT_PERIOD_POS        (1)
#define BMA253_I2C_WDT_PERIOD_LEN        (1)
#define BMA253_I2C_WDT_PERIOD_MSK        (0x02)
#define BMA253_I2C_WDT_PERIOD_REG        BMA253_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   I2C WATCHDOG ENABLE   */
/***************************************************/
#define BMA253_ENABLE_I2C_WDT_POS            (2)
#define BMA253_ENABLE_I2C_WDT_LEN            (1)
#define BMA253_ENABLE_I2C_WDT_MSK            (0x04)
#define BMA253_ENABLE_I2C_WDT_REG            BMA253_SERIAL_CTRL_ADDR
/****************************************************/
/**\name   SPI INTERFACE MODE SELECTIONE            */
/***************************************************/
#define BMA253_UNLOCK_EE_WRITE_TRIM_POS        (4)
#define BMA253_UNLOCK_EE_WRITE_TRIM_LEN        (4)
#define BMA253_UNLOCK_EE_WRITE_TRIM_MSK        (0xF0)
#define BMA253_UNLOCK_EE_WRITE_TRIM_REG        BMA253_CTRL_UNLOCK_REG
/******************************************************************/
/**\name   OFFSET  COMPENSATION/SLOW COMPENSATION FOR X,Y,Z AXIS */
/*****************************************************************/
#define BMA253_ENABLE_SLOW_COMP_X_POS              (0)
#define BMA253_ENABLE_SLOW_COMP_X_LEN              (1)
#define BMA253_ENABLE_SLOW_COMP_X_MSK              (0x01)
#define BMA253_ENABLE_SLOW_COMP_X_REG              BMA253_OFFSET_CTRL_ADDR

#define BMA253_ENABLE_SLOW_COMP_Y_POS              (1)
#define BMA253_ENABLE_SLOW_COMP_Y_LEN              (1)
#define BMA253_ENABLE_SLOW_COMP_Y_MSK              (0x02)
#define BMA253_ENABLE_SLOW_COMP_Y_REG              BMA253_OFFSET_CTRL_ADDR

#define BMA253_ENABLE_SLOW_COMP_Z_POS              (2)
#define BMA253_ENABLE_SLOW_COMP_Z_LEN              (1)
#define BMA253_ENABLE_SLOW_COMP_Z_MSK              (0x04)
#define BMA253_ENABLE_SLOW_COMP_Z_REG              BMA253_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   FAST COMPENSATION READY FLAG            */
/***************************************************/
#define BMA253_FAST_CAL_RDY_STAT_POS             (4)
#define BMA253_FAST_CAL_RDY_STAT_LEN             (1)
#define BMA253_FAST_CAL_RDY_STAT_MSK             (0x10)
#define BMA253_FAST_CAL_RDY_STAT_REG             BMA253_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   FAST COMPENSATION FOR X,Y,Z AXIS         */
/***************************************************/
#define BMA253_CAL_TRIGGER_POS                (5)
#define BMA253_CAL_TRIGGER_LEN                (2)
#define BMA253_CAL_TRIGGER_MSK                (0x60)
#define BMA253_CAL_TRIGGER_REG                BMA253_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   RESET OFFSET REGISTERS         */
/***************************************************/
#define BMA253_RST_OFFSET_POS           (7)
#define BMA253_RST_OFFSET_LEN           (1)
#define BMA253_RST_OFFSET_MSK           (0x80)
#define BMA253_RST_OFFSET_REG           BMA253_OFFSET_CTRL_ADDR
/****************************************************/
/**\name   SLOW COMPENSATION  CUTOFF        */
/***************************************************/
#define BMA253_COMP_CUTOFF_POS                 (0)
#define BMA253_COMP_CUTOFF_LEN                 (1)
#define BMA253_COMP_CUTOFF_MSK                 (0x01)
#define BMA253_COMP_CUTOFF_REG                 BMA253_OFFSET_PARAMS_ADDR
/****************************************************/
/**\name    COMPENSATION TARGET       */
/***************************************************/
#define BMA253_COMP_TARGET_OFFSET_X_POS        (1)
#define BMA253_COMP_TARGET_OFFSET_X_LEN        (2)
#define BMA253_COMP_TARGET_OFFSET_X_MSK        (0x06)
#define BMA253_COMP_TARGET_OFFSET_X_REG        BMA253_OFFSET_PARAMS_ADDR

#define BMA253_COMP_TARGET_OFFSET_Y_POS        (3)
#define BMA253_COMP_TARGET_OFFSET_Y_LEN        (2)
#define BMA253_COMP_TARGET_OFFSET_Y_MSK        (0x18)
#define BMA253_COMP_TARGET_OFFSET_Y_REG        BMA253_OFFSET_PARAMS_ADDR

#define BMA253_COMP_TARGET_OFFSET_Z_POS        (5)
#define BMA253_COMP_TARGET_OFFSET_Z_LEN        (2)
#define BMA253_COMP_TARGET_OFFSET_Z_MSK        (0x60)
#define BMA253_COMP_TARGET_OFFSET_Z_REG        BMA253_OFFSET_PARAMS_ADDR
/****************************************************/
/**\name    FIFO DATA SELECT       */
/***************************************************/
#define BMA253_FIFO_DATA_SELECT_POS                 (0)
#define BMA253_FIFO_DATA_SELECT_LEN                 (2)
#define BMA253_FIFO_DATA_SELECT_MSK                 (0x03)
#define BMA253_FIFO_DATA_SELECT_REG                 BMA253_FIFO_MODE_ADDR
/****************************************************/
/**\name   FIFO MODE      */
/***************************************************/
#define BMA253_FIFO_MODE_POS                 (6)
#define BMA253_FIFO_MODE_LEN                 (2)
#define BMA253_FIFO_MODE_MSK                 (0xC0)
#define BMA253_FIFO_MODE_REG                 BMA253_FIFO_MODE_ADDR

/****************************************************/
/**\name  BITSLICE FUNCTIONS      */
/***************************************************/
#define BMA253_GET_BITSLICE(regvar, bitname)\
((regvar & bitname##_MSK) >> bitname##_POS)


#define BMA253_SET_BITSLICE(regvar, bitname, val)\
((regvar & ~bitname##_MSK) | ((val<<bitname##_POS)&bitname##_MSK))

/****************************************************/
/**\name   CONSTANTS      */
/***************************************************/
/****************************************************/
/**\name  RESOLUTION SELECTION      */
/***************************************************/
/* Definitions used for accel resolution bit shifting*/
#define BMA253_14_BIT_SHIFT		(0xFC)
/**< It refers 14bit accel resolution*/
#define BMA253_10_BIT_SHIFT		(0xC0)
/**< It refers 10bit accel resolution*/
#define BMA253_12_BIT_SHIFT		(0xF0)
/**< It refers 12bit accel resolution*/
#define BANDWIDTH_DEFINE		(0xFB)
/**< Chip id set for accel bandwidth define*/

/****************************************************/
/**\name  ENABLE DISABLE SELECTION     */
/***************************************************/
#define INTR_ENABLE	(0X01)
/**< Enable selection for bit */
#define INTR_DISABLE	(0x00)
/**< Disable selection for bit */

/****************************************************/
/**\name  OUTPUT TYPE SELECT     */
/***************************************************/
#define OPEN_DRAIN	(0x01)
/**< It refers open drain selection*/
#define PUSS_PULL	(0x01)
/**< It refers push pull selection*/

/****************************************************/
/**\name  LEVEL SELECT     */
/***************************************************/
#define	ACTIVE_LOW	(0x00)
/**< It refers active low selection*/
#define	ACTIVE_HIGH	(0x01)
/**< It refers active high selection*/

/****************************************************/
/**\name  STATUS SELECT     */
/***************************************************/
#define BMA253_STAT1                             (0)
/**< It refers Status interrupt1 */
#define BMA253_STAT2                             (1)
/**< It refers Status interrupt2 */
#define BMA253_STAT3                             (2)
/**< It refers Status interrupt3  */
#define BMA253_STAT4                             (3)
/**< It refers Status interrupt4  */
#define BMA253_STAT5                             (4)
/**< It refers Status interrupt5  */

/****************************************************/
/**\name  RANGE AND BANDWIDTH SELECT     */
/***************************************************/
#define BMA253_RANGE_2G                 (3)
/**< sets range to +/- 2G mode */
#define BMA253_RANGE_4G                 (5)
/**< sets range to +/- 4G mode */
#define BMA253_RANGE_8G                 (8)
/**< sets range to +/- 8G mode */
#define BMA253_RANGE_16G                (12)
/**< sets range to +/- 16G mode */


#define BMA253_BW_7_81HZ        (0x08)
 /**< sets bandwidth to LowPass 7.81HZ  */
#define BMA253_BW_15_63HZ       (0x09)
/**< sets bandwidth to LowPass 15.63HZ  */
#define BMA253_BW_31_25HZ       (0x0A)
/**< sets bandwidth to LowPass 31.25HZ  */
#define BMA253_BW_62_50HZ       (0x0B)
 /**< sets bandwidth to LowPass 62.50HZ  */
#define BMA253_BW_125HZ         (0x0C)
 /**< sets bandwidth to LowPass 125HZ  */
#define BMA253_BW_250HZ         (0x0D)
/**< sets bandwidth to LowPass 250HZ  */
#define BMA253_BW_500HZ         (0x0E)
/**< sets bandwidth to LowPass 500HZ  */
#define BMA253_BW_1000HZ        (0x0F)
 /**< sets bandwidth to LowPass 1000HZ  */

/******************************************/
/**\name  SLEEP DURATION SELECT     */
/******************************************/
#define BMA253_SLEEP_DURN_0_5MS        (0x05)
/* sets sleep duration to 0.5 ms  */
#define BMA253_SLEEP_DURN_1MS          (0x06)
/* sets sleep duration to 1 ms */
#define BMA253_SLEEP_DURN_2MS          (0x07)
/* sets sleep duration to 2 ms */
#define BMA253_SLEEP_DURN_4MS          (0x08)
/* sets sleep duration to 4 ms */
#define BMA253_SLEEP_DURN_6MS          (0x09)
/* sets sleep duration to 6 ms*/
#define BMA253_SLEEP_DURN_10MS         (0x0A)
/* sets sleep duration to 10 ms */
#define BMA253_SLEEP_DURN_25MS         (0x0B)
/* sets sleep duration to 25 ms */
#define BMA253_SLEEP_DURN_50MS         (0x0C)
/* sets sleep duration to 50 ms */
#define BMA253_SLEEP_DURN_100MS        (0x0D)
/* sets sleep duration to 100 ms */
#define BMA253_SLEEP_DURN_500MS        (0x0E)
/* sets sleep duration to 500 ms */
#define BMA253_SLEEP_DURN_1S           (0x0F)
/* sets sleep duration to 1 s */

/******************************************/
/**\name  LATCH DURATION     */
/******************************************/
#define BMA253_LATCH_DURN_NON_LATCH    (0x00)
/* sets LATCH duration to NON LATCH  */
#define BMA253_LATCH_DURN_250MS        (0x01)
/* sets LATCH duration to 250 ms */
#define BMA253_LATCH_DURN_500MS        (0x02)
/* sets LATCH duration to 500 ms */
#define BMA253_LATCH_DURN_1S           (0x03)
 /* sets LATCH duration to 1 s */
#define BMA253_LATCH_DURN_2S           (0x04)
 /* sets LATCH duration to 2 s*/
#define BMA253_LATCH_DURN_4S           (0x05)
 /* sets LATCH duration to 4 s */
#define BMA253_LATCH_DURN_8S           (0x06)
 /* sets LATCH duration to 8 s */
#define BMA253_LATCH_DURN_LATCH        (0x07)
 /* sets LATCH duration to LATCH */
#define BMA253_LATCH_DURN_NON_LATCH1   (0x08)
 /* sets LATCH duration to NON LATCH1 */
#define BMA253_LATCH_DURN_250US        (0x09)
 /* sets LATCH duration to 250 Us */
#define BMA253_LATCH_DURN_500US        (0x0A)
 /* sets LATCH duration to 500 Us */
#define BMA253_LATCH_DURN_1MS          (0x0B)
 /* sets LATCH duration to 1 Ms */
#define BMA253_LATCH_DURN_12_5MS       (0x0C)
/* sets LATCH duration to 12.5 Ms */
#define BMA253_LATCH_DURN_25MS         (0x0D)
/* sets LATCH duration to 25 Ms */
#define BMA253_LATCH_DURN_50MS         (0x0E)
 /* sets LATCH duration to 50 Ms */
#define BMA253_LATCH_DURN_LATCH1       (0x0F)
/* sets LATCH duration to LATCH*/

/******************************************/
/**\name  MODE SETTINGS     */
/******************************************/
#define BMA253_MODE_NORMAL             (0)
#define BMA253_MODE_LOWPOWER1          (1)
#define BMA253_MODE_SUSPEND            (2)
#define BMA253_MODE_DEEP_SUSPEND       (3)
#define BMA253_MODE_LOWPOWER2          (4)
#define BMA253_MODE_STANDBY            (5)

/******************************************/
/**\name  AXIS SELECTION     */
/******************************************/
#define BMA253_X_AXIS           (0)
/**< It refers BMA253 X-axis */
#define BMA253_Y_AXIS           (1)
/**< It refers BMA253 Y-axis */
#define BMA253_Z_AXIS           (2)
/**< It refers BMA253 Z-axis */

/******************************************/
/**\name  INTERRUPT TYPE SELECTION     */
/******************************************/
#define BMA253_LOW_G_INTR       (0)
/**< enable/disable low-g interrupt*/
#define BMA253_HIGH_G_X_INTR    (1)
/**< enable/disable high_g X interrupt*/
#define BMA253_HIGH_G_Y_INTR    (2)
/**< enable/disable high_g Y interrupt*/
#define BMA253_HIGH_G_Z_INTR    (3)
/**< enable/disable high_g Z interrupt*/
#define BMA253_DATA_ENABLE      (4)
/**< enable/disable data interrupt*/
#define BMA253_SLOPE_X_INTR     (5)
/**< enable/disable slope X interrupt*/
#define BMA253_SLOPE_Y_INTR     (6)
/**< enable/disable slope X interrupt*/
#define BMA253_SLOPE_Z_INTR     (7)
/**< enable/disable slope X interrupt*/
#define BMA253_SINGLE_TAP_INTR  (8)
/**< enable/disable single tap interrupt*/
#define BMA253_DOUBLE_TAP_INTR  (9)
/**< enable/disable double tap interrupt*/
#define BMA253_ORIENT_INTR      (10)
/**< enable/disable orient interrupt*/
#define BMA253_FLAT_INTR        (11)
/**< enable/disable flat interrupt*/
#define BMA253_FIFO_FULL_INTR   (12)
/**< enable/disable fifo full interrupt*/
#define BMA253_FIFO_WM_INTR     (13)
/**< enable/disable fifo water mark interrupt*/

/******************************************/
/**\name  INTERRUPTS PADS     */
/******************************************/
#define BMA253_INTR1_LOW_G             (0)
/**< disable low-g interrupt*/
#define BMA253_INTR2_LOW_G             (1)
/**< enable low-g interrupt*/
#define BMA253_INTR1_HIGH_G            (0)
/**< disable high-g interrupt*/
#define BMA253_INTR2_HIGH_G            (1)
/**< enable high-g interrupt*/
#define BMA253_INTR1_SLOPE             (0)
/**< disable slope interrupt*/
#define BMA253_INTR2_SLOPE             (1)
/**< enable slope interrupt*/
#define BMA253_INTR1_SLOW_NO_MOTION    (0)
/**< disable slow no motion interrupt*/
#define BMA253_INTR2_SLOW_NO_MOTION    (1)
/**< enable slow no motion  interrupt*/
#define BMA253_INTR1_DOUBLE_TAP        (0)
/**< disable double tap  interrupt*/
#define BMA253_INTR2_DOUBLE_TAP        (1)
/**< enable double tap  interrupt*/
#define BMA253_INTR1_SINGLE_TAP        (0)
/**< disable single tap  interrupt*/
#define BMA253_INTR2_SINGLE_TAP        (1)
/**< enable single tap  interrupt*/
#define BMA253_INTR1_ORIENT            (0)
/**< disable orient  interrupt*/
#define BMA253_INTR2_ORIENT            (1)
/**< enable orient  interrupt*/
#define BMA253_INTR1_FLAT              (0)
/**< disable flat  interrupt*/
#define BMA253_INTR2_FLAT              (1)
/**< enable flat  interrupt*/
#define BMA253_INTR1_NEWDATA           (0)
/**< disable data  interrupt*/
#define BMA253_INTR2_NEWDATA           (1)
/**< enable data interrupt*/
#define BMA253_INTR1_FIFO_WM           (0)
/**< disable fifo watermark  interrupt*/
#define BMA253_INTR2_FIFO_WM           (1)
/**< enable fifo watermark  interrupt*/
#define BMA253_INTR1_FIFO_FULL         (0)
/**< disable fifo full  interrupt*/
#define BMA253_INTR2_FIFO_FULL         (1)
/**< enable fifo full  interrupt*/

/******************************************/
/**\name  SOURCE REGISTER     */
/******************************************/
#define BMA253_SOURCE_LOW_G            (0)
#define BMA253_SOURCE_HIGH_G           (1)
#define BMA253_SOURCE_SLOPE            (2)
#define BMA253_SOURCE_SLOW_NO_MOTION   (3)
#define BMA253_SOURCE_TAP              (4)
#define BMA253_SOURCE_DATA             (5)

#define BMA253_INTR1_OUTPUT      (0)
#define BMA253_INTR2_OUTPUT      (1)
#define BMA253_INTR1_LEVEL       (0)
#define BMA253_INTR2_LEVEL       (1)

/******************************************/
/**\name  DURATION     */
/******************************************/
#define BMA253_LOW_DURN                (0)
#define BMA253_HIGH_DURN               (1)
#define BMA253_SLOPE_DURN              (2)
#define BMA253_SLOW_NO_MOTION_DURN     (3)

/******************************************/
/**\name  THRESHOLD     */
/******************************************/
#define BMA253_LOW_THRES                (0)
#define BMA253_HIGH_THRES               (1)
#define BMA253_SLOPE_THRES              (2)
#define BMA253_SLOW_NO_MOTION_THRES     (3)


#define BMA253_LOW_G_HYST                (0)
#define BMA253_HIGH_G_HYST               (1)

#define BMA253_ORIENT_THETA             (0)
#define BMA253_FLAT_THETA               (1)

#define BMA253_I2C_SELECT               (0)
#define BMA253_I2C_ENABLE               (1)
/******************************************/
/**\name  COMPENSATION     */
/******************************************/
#define BMA253_SLOW_COMP_X              (0)
#define BMA253_SLOW_COMP_Y              (1)
#define BMA253_SLOW_COMP_Z              (2)
/******************************************/
/**\name  OFFSET TRIGGER     */
/******************************************/
#define BMA253_CUT_OFF                  (0)
#define BMA253_OFFSET_TRIGGER_X         (1)
#define BMA253_OFFSET_TRIGGER_Y         (2)
#define BMA253_OFFSET_TRIGGER_Z         (3)
/******************************************/
/**\name  GP REGISTERS     */
/******************************************/
#define BMA253_GP0                      (0)
#define BMA253_GP1                      (1)
/******************************************/
/**\name  SLO NO MOTION REGISTER      */
/******************************************/
#define BMA253_SLOW_NO_MOTION_ENABLE_X          (0)
#define BMA253_SLOW_NO_MOTION_ENABLE_Y          (1)
#define BMA253_SLOW_NO_MOTION_ENABLE_Z          (2)
#define BMA253_SLOW_NO_MOTION_ENABLE_SELECT     (3)
/******************************************/
/**\name  WAKE UP      */
/******************************************/
#define BMA253_WAKE_UP_DURN_20MS         (0)
#define BMA253_WAKE_UP_DURN_80MS         (1)
#define BMA253_WAKE_UP_DURN_320MS        (2)
#define BMA253_WAKE_UP_DURN_2560MS       (3)


/* LG/HG thresholds are in LSB and depend on RANGE setting */
/* no range check on threshold calculation */

#define BMA253_SELFTEST0_ON            (1)
#define BMA253_SELFTEST1_ON            (2)

#define BMA253_EE_W_OFF                 (0)
#define BMA253_EE_W_ON                  (1)
/******************************************/
/**\name  RESOLUTION SETTINGS      */
/******************************************/
#define BMA253_RESOLUTION_12_BIT        (0)
#define BMA253_RESOLUTION_10_BIT        (1)
#define BMA253_RESOLUTION_14_BIT        (3)

/******************************************/
/**\name  CHIP ID SELECTION      */
/******************************************/
#define BMA253           (0x16)
#define BMA280           (0x17)
#define BMA222E          (0x18)
#define BMA250E          (0x19)
/******************************************/
/**\name  LOW-G MODE SELECTION    */
/******************************************/
#define LOW_G_SINGLE_AXIS_MODE		(0x00)
#define LOW_G_SUMMING_MODE		(0x01)
/******************************************/
/**\name TAP DURATION DEFINITION    */
/******************************************/
#define TAP_DURN_50_MS			(0x00)
#define TAP_DURN_100_MS			(0x01)
#define TAP_DURN_150_MS			(0x02)
#define TAP_DURN_200_MS			(0x03)
#define TAP_DURN_250_MS			(0x04)
#define TAP_DURN_375_MS			(0x05)
#define TAP_DURN_500_MS			(0x06)
#define TAP_DURN_700_MS			(0x07)
/******************************************/
/**\name TAP SHOCK DEFINITION    */
/******************************************/
#define TAP_SHOCK_50_MS		(0x00)
#define TAP_SHOCK_75_MS		(0x01)
/******************************************/
/**\name TAP QUIET DEFINITION    */
/******************************************/
#define	TAP_QUIET_30_MS		(0x00)
#define	TAP_QUIET_20_MS		(0x01)
/****************************************************/
/**\name	ARRAY SIZE DEFINITIONS      */
/***************************************************/
#define BMA253_ACCEL_DATA_SIZE			(2)
#define BMA253_ACCEL_XYZ_DATA_SIZE		(6)
#define BMA253_ACCEL_XYZ_TEMP_DATA_SIZE		(7)
/****************************************************/
/**\name	ARRAY PARAMETERS      */
/***************************************************/

#define BMA253_SENSOR_DATA_ACCEL_LSB	(0)
#define BMA253_SENSOR_DATA_ACCEL_MSB	(1)

#define BMA253_SENSOR_DATA_XYZ_X_LSB	(0)
#define BMA253_SENSOR_DATA_XYZ_X_MSB	(1)
#define BMA253_SENSOR_DATA_XYZ_Y_LSB	(2)
#define BMA253_SENSOR_DATA_XYZ_Y_MSB	(3)
#define BMA253_SENSOR_DATA_XYZ_Z_LSB	(4)
#define BMA253_SENSOR_DATA_XYZ_Z_MSB	(5)
#define BMA253_SENSOR_DATA_TEMP		(6)

#define BMA253_RESOLUTION_12_MASK		(0xF0)
#define BMA253_RESOLUTION_10_MASK		(0xC0)
#define BMA253_RESOLUTION_14_MASK		(0xFC)

#define	BMA253_POWER_MODE_HEX_E_ZERO_MASK	(0xE0)
#define	BMA253_POWER_MODE_HEX_4_ZERO_MASK	(0x40)
#define	BMA253_POWER_MODE_HEX_ZERO_ZERO_MASK	(0x00)
#define	BMA253_POWER_MODE_HEX_ZERO_ONE_MASK	(0x01)
#define	BMA253_POWER_MODE_HEX_ZERO_TWO_MASK	(0x02)
#define	BMA253_POWER_MODE_HEX_ZERO_FOUR_MASK	(0x04)
#define	BMA253_POWER_MODE_HEX_ZERO_SIX_MASK	(0x06)

/** Macro to convert floating point
low-g-thresholds in G to 8-bit register values.<br>
  * Example: BMA253_LOW_TH_IN_G( 0.3, 2.0) generates
  * the register value for 0.3G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA253_LOW_THRES_IN_G(gthres, range)  ((256 * gthres) / range)

/** Macro to convert floating point high-g-thresholds
    in G to 8-bit register values.<br>
  * Example: BMA253_HIGH_TH_IN_G( 1.4, 2.0)
  * generates the register value for 1.4G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA253_HIGH_THRES_IN_G(gthres, range)   ((256 * gthres) / range)

/** Macro to convert floating point low-g-hysteresis
in G to 8-bit register values.<br>
  * Example: BMA253_LOW_HY_IN_G( 0.2, 2.0)
  *generates the register value for 0.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA253_LOW_HYST_IN_G(ghyst, range)   ((32 * ghyst) / range)

/** Macro to convert floating point high-g-hysteresis
   in G to 8-bit register values.<br>
  * Example: BMA253_HIGH_HY_IN_G( 0.2, 2.0) generates
  *the register value for 0.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */
#define BMA253_HIGH_HYST_IN_G(ghyst, range)    ((32 * ghyst) / range)


/** Macro to convert floating point G-thresholds
    to 8-bit register values<br>
  * Example: BMA253_SLOPE_TH_IN_G( 1.2, 2.0)
  * generates the register value for 1.2G threshold in 2G mode.
  * \brief convert g-values to 8-bit value
 */

#define BMA253_SLOPE_THRES_IN_G(gthres, range)    ((128 * gthres) / range)
#endif