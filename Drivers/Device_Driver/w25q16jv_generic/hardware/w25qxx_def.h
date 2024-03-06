#ifndef __W25QXX_DEF_H
#define __W25QXX_DEF_H

/**
 * @brief w25qxx type enumeration definition
 */
typedef enum
{
    W25Q80  = 0XEF13U,        /**< w25q80 */
    W25Q16  = 0XEF14U,        /**< w25q16 */
    W25Q32  = 0XEF15U,        /**< w25q32 */
    W25Q64  = 0XEF16U,        /**< w25q64 */
    W25Q128 = 0XEF17U,        /**< w25q128 */
    W25Q256 = 0XEF18U,        /**< w25q256 */
} w25qxx_type_t;

/**
 * @brief w25qxx interface enumeration definition
 */
typedef enum
{
    W25QXX_INTERFACE_SPI  = 0x00,        /**< spi interface */
    W25QXX_INTERFACE_QSPI = 0x01,        /**< dspi qspi interface */
} w25qxx_interface_t;

/**
 * @brief w25qxx bool enumeration definition
 */
typedef enum
{
    W25QXX_BOOL_FALSE = 0x00,        /**< false */
    W25QXX_BOOL_TRUE  = 0x01,        /**< true */
} w25qxx_bool_t;

/**
 * @brief w25qxx address mode enumeration definition
 */
typedef enum
{
    W25QXX_ADDRESS_MODE_3_BYTE = 0x00,        /**< 3 byte mode */
    W25QXX_ADDRESS_MODE_4_BYTE = 0x01,        /**< 4 byte mode */
} w25qxx_address_mode_t;

/**
 * @}
 */

/**
 * @addtogroup w25qxx_advance_driver
 * @{
 */

/**
 * @brief w25qxx qspi read dummy enumeration definition
 */
typedef enum
{
    W25QXX_QSPI_READ_DUMMY_2_33MHZ = 0x00,        /**< qspi read dummy 2 max 33 MHz */
    W25QXX_QSPI_READ_DUMMY_4_55MHZ = 0x01,        /**< qspi read dummy 4 max 55 MHz */
    W25QXX_QSPI_READ_DUMMY_6_80MHZ = 0x02,        /**< qspi read dummy 6 max 80 MHz */
    W25QXX_QSPI_READ_DUMMY_8_80MHZ = 0x03,        /**< qspi read dummy 8 max 80 MHz */
} w25qxx_qspi_read_dummy_t;

/**
 * @brief w25qxx qspi read wrap length enumeration definition
 */
typedef enum
{
    W25QXX_QSPI_READ_WRAP_LENGTH_8_BYTE  = 0x00,        /**< read wrap length 8 byte */
    W25QXX_QSPI_READ_WRAP_LENGTH_16_BYTE = 0x01,        /**< read wrap length 16 byte */
    W25QXX_QSPI_READ_WRAP_LENGTH_32_BYTE = 0x02,        /**< read wrap length 32 byte */
    W25QXX_QSPI_READ_WRAP_LENGTH_64_BYTE = 0x03,        /**< read wrap length 64 byte */
} w25qxx_qspi_read_wrap_length_t;


/**
 * @brief w25qxx security register enumeration definition
 */
typedef enum
{
    W25QXX_SECURITY_REGISTER_1 = 0x1000,        /**< security register 1 */
    W25QXX_SECURITY_REGISTER_2 = 0x2000,        /**< security register 2 */
    W25QXX_SECURITY_REGISTER_3 = 0x3000,        /**< security register 3 */
} w25qxx_security_register_t;

/**
 * @brief w25qxx burst wrap enumeration definition
 */
typedef enum
{
    W25QXX_BURST_WRAP_NONE    = 0x10,        /**< no burst wrap */
    W25QXX_BURST_WRAP_8_BYTE  = 0x00,        /**< 8 byte burst wrap */
    W25QXX_BURST_WRAP_16_BYTE = 0x20,        /**< 16 byte burst wrap */
    W25QXX_BURST_WRAP_32_BYTE = 0x40,        /**< 32 byte burst wrap */
    W25QXX_BURST_WRAP_64_BYTE = 0x60,        /**< 64 byte burst wrap */
} w25qxx_burst_wrap_t;

/**
 * @brief w25qxx status 1 enumeration definition
 */
typedef enum
{
    W25QXX_STATUS1_STATUS_REGISTER_PROTECT_0             = (1 << 7),        /**< status register protect 0 */
    W25QXX_STATUS1_SECTOR_PROTECT_OR_TOP_BOTTOM_PROTECT  = (1 << 6),        /**< sector protect bit or top / bottom protect bit */
    W25QXX_STATUS1_TOP_BOTTOM_PROTECT_OR_BLOCK_PROTECT_3 = (1 << 5),        /**< top / bottom protect bit or block 3 protect bit */
    W25QXX_STATUS1_BLOCK_PROTECT_2                       = (1 << 4),        /**< block 2 protect bit */
    W25QXX_STATUS1_BLOCK_PROTECT_1                       = (1 << 3),        /**< block 1 protect bit */
    W25QXX_STATUS1_BLOCK_PROTECT_0                       = (1 << 2),        /**< block 0 protect bit */
    W25QXX_STATUS1_WRITE_ENABLE_LATCH                    = (1 << 1),        /**< write enable latch */
    W25QXX_STATUS1_ERASE_WRITE_PROGRESS                  = (1 << 0),        /**< erase / write in progress */
} w25qxx_status1_t;

/**
 * @brief w25qxx status 2 enumeration definition
 */
typedef enum
{
    W25QXX_STATUS2_SUSPEND_STATUS                = (1 << 7),        /**< suspend status */
    W25QXX_STATUS2_COMPLEMENT_PROTECT            = (1 << 6),        /**< complement protect */
    W25QXX_STATUS2_SECURITY_REGISTER_3_LOCK_BITS = (1 << 5),        /**< security register 3 lock bits */
    W25QXX_STATUS2_SECURITY_REGISTER_2_LOCK_BITS = (1 << 4),        /**< security register 2 lock bits */
    W25QXX_STATUS2_SECURITY_REGISTER_1_LOCK_BITS = (1 << 3),        /**< security register 1 lock bits */
    W25QXX_STATUS2_QUAD_ENABLE                   = (1 << 1),        /**< quad enable */
    W25QXX_STATUS2_STATUS_REGISTER_PROTECT_1     = (1 << 0),        /**< status register protect 1 */
} w25qxx_status2_t;

/**
 * @brief w25qxx status 3 enumeration definition
 */
typedef enum
{
    W25QXX_STATUS3_HOLD_RESET_FUNCTION                   = (1 << 7),        /**< HOLD or RESET function */
    W25QXX_STATUS3_OUTPUT_DRIVER_STRENGTH_100_PERCENTAGE = (0 << 5),        /**< output driver strength 100% */
    W25QXX_STATUS3_OUTPUT_DRIVER_STRENGTH_75_PERCENTAGE  = (1 << 5),        /**< output driver strength 75% */
    W25QXX_STATUS3_OUTPUT_DRIVER_STRENGTH_50_PERCENTAGE  = (2 << 5),        /**< output driver strength 50% */
    W25QXX_STATUS3_OUTPUT_DRIVER_STRENGTH_25_PERCENTAGE  = (3 << 5),        /**< output driver strength 25% */
    W25QXX_STATUS3_WRITE_PROTECT_SELECTION               = (1 << 2),        /**< write protect selection */
    W25QXX_STATUS3_POWER_UP_ADDRESS_MODE                 = (1 << 1),        /**< power up address mode */
    W25QXX_STATUS3_CURRENT_ADDRESS_MODE                  = (1 << 0),        /**< current address mode */
} w25qxx_status3_t;

#define W25QXX_PAGE_SIZE                256
#define W25QXX_PAGES_PER_SECTOR         16
#define W25QXX_SECTORS_PER_BLOCK        16
#define W25QXX_BLOCKS_PER_CHIP          32

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Winbond W25QXX"        /**< chip name */
#define MANUFACTURER_NAME         "Winbond"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                    /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                    /**< chip max supply voltage */
#define MAX_CURRENT               25.0f                   /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                  /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                   /**< chip max operating temperature */
#define DRIVER_VERSION            1000                    /**< driver version */

/**
 * @brief chip command definition
 */
#define W25QXX_COMMAND_WRITE_ENABLE                      0x06        /**< write enable */
#define W25QXX_COMMAND_VOLATILE_SR_WRITE_ENABLE          0x50        /**< sr write enable */
#define W25QXX_COMMAND_WRITE_DISABLE                     0x04        /**< write disable */
#define W25QXX_COMMAND_READ_STATUS_REG1                  0x05        /**< read status register-1 */
#define W25QXX_COMMAND_READ_STATUS_REG2                  0x35        /**< read status register-2 */
#define W25QXX_COMMAND_READ_STATUS_REG3                  0x15        /**< read status register-3 */
#define W25QXX_COMMAND_WRITE_STATUS_REG1                 0x01        /**< write status register-1 */
#define W25QXX_COMMAND_WRITE_STATUS_REG2                 0x31        /**< write status register-2 */
#define W25QXX_COMMAND_WRITE_STATUS_REG3                 0x11        /**< write status register-3 */
#define W25QXX_COMMAND_CHIP_ERASE                        0xC7        /**< chip erase */
#define W25QXX_COMMAND_ERASE_PROGRAM_SUSPEND             0x75        /**< erase suspend */
#define W25QXX_COMMAND_ERASE_PROGRAM_RESUME              0x7A        /**< erase resume */
#define W25QXX_COMMAND_POWER_DOWN                        0xB9        /**< power down */
#define W25QXX_COMMAND_RELEASE_POWER_DOWN                0xAB        /**< release power down */
#define W25QXX_COMMAND_READ_MANUFACTURER                 0x90        /**< manufacturer */
#define W25QXX_COMMAND_JEDEC_ID                          0x9F        /**< jedec id */
#define W25QXX_COMMAND_GLOBAL_BLOCK_SECTOR_LOCK          0x7E        /**< global block lock */
#define W25QXX_COMMAND_GLOBAL_BLOCK_SECTOR_UNLOCK        0x98        /**< global block unlock */
#define W25QXX_COMMAND_ENTER_QSPI_MODE                   0x38        /**< enter spi mode */
#define W25QXX_COMMAND_ENABLE_RESET                      0x66        /**< enable reset */
#define W25QXX_COMMAND_RESET_DEVICE                      0x99        /**< reset device */
#define W25QXX_COMMAND_READ_UNIQUE_ID                    0x4B        /**< read unique id */
#define W25QXX_COMMAND_PAGE_PROGRAM                      0x02        /**< page program */
#define W25QXX_COMMAND_QUAD_PAGE_PROGRAM                 0x32        /**< quad page program */
#define W25QXX_COMMAND_SECTOR_ERASE_4K                   0x20        /**< sector erase */
#define W25QXX_COMMAND_BLOCK_ERASE_32K                   0x52        /**< block erase */
#define W25QXX_COMMAND_BLOCK_ERASE_64K                   0xD8        /**< block erase */
#define W25QXX_COMMAND_READ_DATA                         0x03        /**< read data */
#define W25QXX_COMMAND_FAST_READ                         0x0B        /**< fast read */
#define W25QXX_COMMAND_FAST_READ_DUAL_OUTPUT             0x3B        /**< fast read dual output */
#define W25QXX_COMMAND_FAST_READ_QUAD_OUTPUT             0x6B        /**< fast read quad output */
#define W25QXX_COMMAND_READ_SFDP_REGISTER                0x5A        /**< read SFDP register */
#define W25QXX_COMMAND_ERASE_SECURITY_REGISTER           0x44        /**< erase security register */
#define W25QXX_COMMAND_PROGRAM_SECURITY_REGISTER         0x42        /**< program security register */
#define W25QXX_COMMAND_READ_SECURITY_REGISTER            0x48        /**< read security register */
#define W25QXX_COMMAND_INDIVIDUAL_BLOCK_LOCK             0x36        /**< individual block lock */
#define W25QXX_COMMAND_INDIVIDUAL_BLOCK_UNLOCK           0x39        /**< individual block unlock */
#define W25QXX_COMMAND_READ_BLOCK_LOCK                   0x3D        /**< read block lock */
#define W25QXX_COMMAND_FAST_READ_DUAL_IO                 0xBB        /**< fast read dual I/O */
#define W25QXX_COMMAND_DEVICE_ID_DUAL_IO                 0x92        /**< device id dual I/O */
#define W25QXX_COMMAND_SET_BURST_WITH_WRAP               0x77        /**< set burst with wrap */
#define W25QXX_COMMAND_FAST_READ_QUAD_IO                 0xEB        /**< fast read quad I/O */
#define W25QXX_COMMAND_WORD_READ_QUAD_IO                 0xE7        /**< word read quad I/O */
#define W25QXX_COMMAND_OCTAL_WORD_READ_QUAD_IO           0xE3        /**< octal word read quad I/O */
#define W25QXX_COMMAND_DEVICE_ID_QUAD_IO                 0x94        /**< device id quad I/O */

#endif