/*!  \file     platform_defines.h
*    \brief    Defines specific to our platform: SERCOMs, GPIOs...
*    Created:  10/11/2017
*    Author:   Mathieu Stephan
*/
#ifndef PLATFORM_DEFINES_H_
#define PLATFORM_DEFINES_H_

#include <asf.h>
#include "defines.h"

/**************** FIRMWARE DEFINES ****************/
#define FW_MAJOR    0
#define FW_MINOR    3

/* Changelog:
- v0.2: platform info message, flash aux mcu message, reindex bundle message
- v0.3: many things.... sleep problems solved
*/

/**************** SETUP DEFINES ****************/
/*  This project should be built differently
 *  depending on the Mooltipass version.
 *  Simply define one of these:
 *
 *  PLAT_V1_SETUP
 *  => only 2 boards were made, one shipped to Miguel, one to Mathieu. No silkscreen marking
 *
 *  PLAT_V2_SETUP
 *  => board with the new LT1613 stepup, "beta v2 (new DC/DC)" silkscreen. SMC_POW_nEN pin change.
 *
 *  PLAT_V3_SETUP
 *  => MiniBLE v2 breakout, 13/06/2018
 * - MAIN_MCU_WAKE removed (AUX_Tx used for wakeup)
 * - FORCE_RESET_AUX removed (little added benefits)
 * - NO_COMMS added (see github pages)
 */
 #define PLAT_V3_SETUP 
 
 /* Features depending on the defined platform */
 #if defined(PLAT_V1_SETUP)
     #define OLED_PRINTF_ENABLED
     #define DEBUG_USB_COMMANDS_ENABLED
     #define DEBUG_MENU_ENABLED
     #define NO_SECURITY_BIT_CHECK
     #define DEBUG_USB_PRINTF_ENABLED
     #define DEVELOPER_FEATURES_ENABLED     
     #define DBFLASH_CHIP_8M
#elif defined(PLAT_V2_SETUP)
     #define OLED_PRINTF_ENABLED
     #define DEBUG_USB_COMMANDS_ENABLED
     #define DEBUG_MENU_ENABLED
     #define NO_SECURITY_BIT_CHECK
     #define DEBUG_USB_PRINTF_ENABLED
     #define DEVELOPER_FEATURES_ENABLED
     #define DBFLASH_CHIP_8M
#elif defined(PLAT_V3_SETUP)
     #define OLED_PRINTF_ENABLED
     #define DEBUG_USB_COMMANDS_ENABLED
     #define DEBUG_MENU_ENABLED
     #define NO_SECURITY_BIT_CHECK
     #define DEBUG_USB_PRINTF_ENABLED
     #define DEVELOPER_FEATURES_ENABLED
     #define DBFLASH_CHIP_8M
#endif

/* Developer features */
#ifdef DEVELOPER_FEATURES_ENABLED
    #define DEV_SKIP_INTRO_ANIM
    #define SPECIAL_DEVELOPER_CARD_FEATURE
#endif

/* Enums */
typedef enum {PIN_GROUP_0 = 0, PIN_GROUP_1 = 1} pin_group_te;
typedef uint32_t PIN_MASK_T;
typedef uint32_t PIN_ID_T;

/* Structs */
typedef struct
{
    Sercom* sercom_pt;
    pin_group_te cs_pin_group;
    PIN_MASK_T cs_pin_mask;
} spi_flash_descriptor_t;

/*********************************************/
/*  Bootloader and memory related defines    */
/*********************************************/
#ifdef FEATURE_NVM_RWWEE
    #define RWWEE_MEMORY ((volatile uint16_t *)NVMCTRL_RWW_EEPROM_ADDR)
#endif
/* Simply an array point to our internal memory */
#define NVM_MEMORY ((volatile uint16_t *)FLASH_ADDR)
/* Our firmware start address */
#define APP_START_ADDR (0x2000)
/* Internal storage slot for settings storage */
#define SETTINGS_STORAGE_SLOT               0
#define FIRST_CPZ_LUT_ENTRY_STORAGE_SLOT    4

/**********************/
/* Device limitations */
/**********************/
#define MAX_NUMBER_OF_USERS     112

/********************/
/* Settings defines */
/********************/
#define FIRMWARE_UPGRADE_FLAG   0x5478ABAA

/********************/
/* Voltage cutout   */
/********************/
#define BATTERY_ADC_OUT_CUTOUT      (1140*273/110)
#define BATTERY_ADC_OVER_VOLTAGE    (1600*273/110)

/********************/
/* Display defines  */
/********************/
#define GUI_DISPLAY_WIDTH           256

/*************************/
/* Functionality defines */
/*************************/
/* specify that the flash is alone on the spi bus */
#define FLASH_ALONE_ON_SPI_BUS
/* Use DMA transfers to read from external flash */
#define FLASH_DMA_FETCHES
/* Use DMA transfers to send data to OLED screen */
#define OLED_DMA_TRANSFER
/* Use a frame buffer on the platform */
#define OLED_INTERNAL_FRAME_BUFFER
/* allow printf for the screen */
//#define OLED_PRINTF_ENABLED
/* Allow debug USB commands */
//#define DEBUG_USB_COMMANDS_ENABLED
/* Allow debug menu */
//#define DEBUG_MENU_ENABLED
/* No security bit check */
//#define NO_SECURITY_BIT_CHECK
/* Debug printf through USB */
//#define DEBUG_USB_PRINTF_ENABLED

/* GCLK ID defines */
#define GCLK_ID_48M             GCLK_CLKCTRL_GEN_GCLK0_Val
#define GCLK_ID_32K             GCLK_CLKCTRL_GEN_GCLK3_Val

/* ADC defines */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define VBAT_ADC_PIN_MUXPOS     ADC_INPUTCTRL_MUXPOS_PIN1_Val
#elif defined(PLAT_V3_SETUP)
    #define VBAT_ADC_PIN_MUXPOS     ADC_INPUTCTRL_MUXPOS_PIN0_Val
#endif

/* SERCOM defines */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SMARTCARD_GCLK_SERCOM_ID    GCLK_CLKCTRL_ID_SERCOM5_CORE_Val
    #define SMARTCARD_MOSI_SCK_PADS     MOSI_P0_SCK_P3_SS_P1
    #define SMARTCARD_MISO_PAD          MISO_PAD1
    #define SMARTCARD_APB_SERCOM_BIT    SERCOM5_
    #define SMARTCARD_SERCOM            SERCOM5
    #define DATAFLASH_GCLK_SERCOM_ID    GCLK_CLKCTRL_ID_SERCOM2_CORE_Val
    #define DATAFLASH_MOSI_SCK_PADS     MOSI_P0_SCK_P1_SS_P2
    #define DATAFLASH_MISO_PAD          MISO_PAD2
    #define DATAFLASH_APB_SERCOM_BIT    SERCOM2_
    #define DATAFLASH_SERCOM            SERCOM2
    #define DBFLASH_GCLK_SERCOM_ID      GCLK_CLKCTRL_ID_SERCOM3_CORE_Val
    #define DBFLASH_MOSI_SCK_PADS       MOSI_P0_SCK_P1_SS_P2
    #define DBFLASH_MISO_PAD            MISO_PAD3
    #define DBFLASH_APB_SERCOM_BIT      SERCOM3_
    #define DBFLASH_SERCOM              SERCOM3
    #define AUXMCU_GCLK_SERCOM_ID       GCLK_CLKCTRL_ID_SERCOM4_CORE_Val
    #define AUXMCU_APB_SERCOM_BIT       SERCOM4_
    #define AUXMCU_SERCOM               SERCOM4
    #define AUXMCU_RX_TXPO              1
    #define AUXMCU_TX_PAD               3
    #define OLED_GCLK_SERCOM_ID         GCLK_CLKCTRL_ID_SERCOM0_CORE_Val
    #define OLED_MOSI_SCK_PADS          MOSI_P0_SCK_P1_SS_P2
    #define OLED_MISO_PAD               MISO_PAD3
    #define OLED_APB_SERCOM_BIT         SERCOM0_
    #define OLED_SERCOM                 SERCOM0
    #define ACC_GCLK_SERCOM_ID          GCLK_CLKCTRL_ID_SERCOM1_CORE_Val
    #define ACC_MOSI_SCK_PADS           MOSI_P0_SCK_P3_SS_P1
    #define ACC_MISO_PAD                MISO_PAD1
    #define ACC_APB_SERCOM_BIT          SERCOM1_
    #define ACC_SERCOM                  SERCOM1
#elif defined(PLAT_V3_SETUP)
    #define SMARTCARD_GCLK_SERCOM_ID    GCLK_CLKCTRL_ID_SERCOM2_CORE_Val
    #define SMARTCARD_MOSI_SCK_PADS     MOSI_P3_SCK_P1_SS_P2
    #define SMARTCARD_MISO_PAD          MISO_PAD2
    #define SMARTCARD_APB_SERCOM_BIT    SERCOM2_
    #define SMARTCARD_SERCOM            SERCOM2
    #define DATAFLASH_GCLK_SERCOM_ID    GCLK_CLKCTRL_ID_SERCOM3_CORE_Val
    #define DATAFLASH_MOSI_SCK_PADS     MOSI_P2_SCK_P3_SS_P1
    #define DATAFLASH_MISO_PAD          MISO_PAD0
    #define DATAFLASH_APB_SERCOM_BIT    SERCOM3_
    #define DATAFLASH_SERCOM            SERCOM3
    #define DBFLASH_GCLK_SERCOM_ID      GCLK_CLKCTRL_ID_SERCOM1_CORE_Val
    #define DBFLASH_MOSI_SCK_PADS       MOSI_P3_SCK_P1_SS_P2
    #define DBFLASH_MISO_PAD            MISO_PAD2
    #define DBFLASH_APB_SERCOM_BIT      SERCOM1_
    #define DBFLASH_SERCOM              SERCOM1
    #define AUXMCU_GCLK_SERCOM_ID       GCLK_CLKCTRL_ID_SERCOM5_CORE_Val
    #define AUXMCU_APB_SERCOM_BIT       SERCOM5_
    #define AUXMCU_SERCOM               SERCOM5
    #define AUXMCU_RX_TXPO              1
    #define AUXMCU_TX_PAD               3
    #define OLED_GCLK_SERCOM_ID         GCLK_CLKCTRL_ID_SERCOM4_CORE_Val
    #define OLED_MOSI_SCK_PADS          MOSI_P2_SCK_P3_SS_P1
    #define OLED_MISO_PAD               MISO_PAD0
    #define OLED_APB_SERCOM_BIT         SERCOM4_
    #define OLED_SERCOM                 SERCOM4
    #define ACC_GCLK_SERCOM_ID          GCLK_CLKCTRL_ID_SERCOM0_CORE_Val
    #define ACC_MOSI_SCK_PADS           MOSI_P0_SCK_P3_SS_P1
    #define ACC_MISO_PAD                MISO_PAD1
    #define ACC_APB_SERCOM_BIT          SERCOM0_
    #define ACC_SERCOM                  SERCOM0
#endif

/* DMA channel descriptors */
#define DMA_DESCID_RX_COMMS         0
#define DMA_DESCID_RX_FS            1
#define DMA_DESCID_TX_FS            2
#define DMA_DESCID_TX_ACC           3
#define DMA_DESCID_TX_OLED          4
#define DMA_DESCID_RX_ACC           5
#define DMA_DESCID_TX_COMMS         6

/* External interrupts numbers */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define ACC_EXTINT_NUM              4
    #define ACC_EIC_SENSE_REG           SENSE4
    #define WHEEL_CLICK_EXTINT_NUM      8
    #define WHEEL_CLICK_EIC_SENSE_REG   SENSE0
    #define WHEEL_TICKA_EXTINT_NUM      0
    #define WHEEL_TICKA_EIC_SENSE_REG   SENSE0
    #define WHEEL_TICKB_EXTINT_NUM      1
    #define WHEEL_TICKB_EIC_SENSE_REG   SENSE1
#elif defined(PLAT_V3_SETUP)
    #define ACC_EXTINT_NUM              9
    #define ACC_EIC_SENSE_REG           SENSE1
    #define WHEEL_CLICK_EXTINT_NUM      8
    #define WHEEL_CLICK_EIC_SENSE_REG   SENSE0
    #define WHEEL_TICKA_EXTINT_NUM      15
    #define WHEEL_TICKA_EIC_SENSE_REG   SENSE7
    #define WHEEL_TICKB_EXTINT_NUM      2
    #define WHEEL_TICKB_EIC_SENSE_REG   SENSE2
#endif

/* User event channels mapping */
#define ACC_EV_GEN_CHANNEL          0
#define ACC_EV_GEN_SEL              (0x0C + ACC_EXTINT_NUM)

/* SERCOM trigger for flash data transfers */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DATAFLASH_DMA_SERCOM_RXTRIG     0x05
    #define DATAFLASH_DMA_SERCOM_TXTRIG     0x06
    #define DBFLASH_DMA_SERCOM_RXTRIG       0x07
    #define DBFLASH_DMA_SERCOM_TXTRIG       0x08
    #define ACC_DMA_SERCOM_RXTRIG           0x03
    #define ACC_DMA_SERCOM_TXTRIG           0x04
    #define AUX_MCU_SERCOM_RXTRIG           0x09
    #define AUX_MCU_SERCOM_TXTRIG           0x0A
#elif defined(PLAT_V3_SETUP)
    #define DATAFLASH_DMA_SERCOM_RXTRIG     0x07
    #define DATAFLASH_DMA_SERCOM_TXTRIG     0x08
    #define DBFLASH_DMA_SERCOM_RXTRIG       0x03
    #define DBFLASH_DMA_SERCOM_TXTRIG       0x04
    #define ACC_DMA_SERCOM_RXTRIG           0x01
    #define ACC_DMA_SERCOM_TXTRIG           0x02
    #define AUX_MCU_SERCOM_RXTRIG           0x0B
    #define AUX_MCU_SERCOM_TXTRIG           0x0C
#endif

/* SERCOM trigger for OLED data transfers */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define OLED_DMA_SERCOM_TX_TRIG         0x02
#elif defined(PLAT_V3_SETUP)
    #define OLED_DMA_SERCOM_TX_TRIG         0x0A
#endif

/* Speed defines */
#define CPU_SPEED_HF                48000000UL
#define CPU_SPEED_MF                8000000UL
/* SMARTCARD SPI SCK =  48M / (2*(119+1)) = 200kHz (Supposed Max is 300kHz) */
//#define SMARTCARD_BAUD_DIVIDER      119
#define SMARTCARD_BAUD_DIVIDER      239
/* OLED SPI SCK = 48M / 2*(5+1)) = 4MHz (Max from datasheet) */
/* Note: Has successfully been tested at 24MHz, but without speed improvements */
#define OLED_BAUD_DIVIDER           5
/* ACC SPI SCK = 48M / 2*(2+1)) = 8MHz (Max is 10MHz) */
#define ACC_BAUD_DIVIDER            2
/* DATA & DB FLASH SPI SCK = 48M / 2*(1+1)) = 12MHz (24MHz may not work on some boards when querying JEDEC ID) */
#define DATAFLASH_BAUD_DIVIDER      1
#define DBFLASH_BAUD_DIVIDER        1

/* PORT defines */
/* WHEEL ENCODER */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define WHEEL_A_GROUP           PIN_GROUP_0
    #define WHEEL_A_PINID           0
#elif defined(PLAT_V3_SETUP)
    #define WHEEL_A_GROUP           PIN_GROUP_0
    #define WHEEL_A_PINID           27
#endif
#define WHEEL_A_MASK            (1UL << WHEEL_A_PINID)
#if (WHEEL_A_PINID % 2) == 1
    #define WHEEL_A_PMUXREGID   PMUXO
#else
    #define WHEEL_A_PMUXREGID   PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define WHEEL_B_GROUP           PIN_GROUP_0
    #define WHEEL_B_PINID           1
#elif defined(PLAT_V3_SETUP)
    #define WHEEL_B_GROUP           PIN_GROUP_1
    #define WHEEL_B_PINID           2
#endif
#define WHEEL_B_MASK            (1UL << WHEEL_B_PINID)
#if (WHEEL_B_PINID % 2) == 1
    #define WHEEL_B_PMUXREGID   PMUXO
#else
    #define WHEEL_B_PMUXREGID   PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define WHEEL_SW_GROUP          PIN_GROUP_0
    #define WHEEL_SW_PINID          28
#elif defined(PLAT_V3_SETUP)
    #define WHEEL_SW_GROUP          PIN_GROUP_0
    #define WHEEL_SW_PINID          28
#endif
#define WHEEL_SW_MASK           (1UL << WHEEL_SW_PINID)
#if (WHEEL_SW_PINID % 2) == 1
    #define WHEEL_SW_PMUXREGID  PMUXO
#else
    #define WHEEL_SW_PMUXREGID  PMUXE
#endif

/* POWER & BLE SYSTEM */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SWDET_EN_GROUP          PIN_GROUP_0
    #define SWDET_EN_PINID          2
#elif defined(PLAT_V3_SETUP)
    #define SWDET_EN_GROUP          PIN_GROUP_0
    #define SWDET_EN_PINID          15
#endif
#define SWDET_EN_MASK           (1UL << SWDET_EN_PINID)

#if defined(PLAT_V1_SETUP)
    #define SMC_POW_NEN_GROUP   PIN_GROUP_0
    #define SMC_POW_NEN_PINID   3
    #define SMC_POW_NEN_MASK    (1UL << SMC_POW_NEN_PINID)
#elif defined(PLAT_V2_SETUP)
    #define SMC_POW_NEN_GROUP   PIN_GROUP_0
    #define SMC_POW_NEN_PINID   30
    #define SMC_POW_NEN_MASK    (1UL << SMC_POW_NEN_PINID)
#elif defined(PLAT_V3_SETUP)
    #define SMC_POW_NEN_GROUP   PIN_GROUP_0
    #define SMC_POW_NEN_PINID   25
    #define SMC_POW_NEN_MASK    (1UL << SMC_POW_NEN_PINID)
#endif

#if defined(PLAT_V2_SETUP)
    #define VOLED_VIN_GROUP     PIN_GROUP_0
    #define VOLED_VIN_PINID     3
    #define VOLED_VIN_MASK      (1UL << VOLED_VIN_PINID)
    #define VOLED_VIN_PMUX_ID   PORT_PMUX_PMUXE_B_Val
    #if (VOLED_VIN_PINID % 2) == 1
        #define VOLED_VIN_PMUXREGID PMUXO
    #else
        #define VOLED_VIN_PMUXREGID PMUXE
    #endif
#elif defined(PLAT_V3_SETUP)
    #define VOLED_VIN_GROUP     PIN_GROUP_0
    #define VOLED_VIN_PINID     2
    #define VOLED_VIN_MASK      (1UL << VOLED_VIN_PINID)
    #define VOLED_VIN_PMUX_ID   PORT_PMUX_PMUXE_B_Val
    #if (VOLED_VIN_PINID % 2) == 1
        #define VOLED_VIN_PMUXREGID PMUXO
    #else
        #define VOLED_VIN_PMUXREGID PMUXE
    #endif
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define BLE_EN_GROUP            PIN_GROUP_0
    #define BLE_EN_PINID            13
#elif defined(PLAT_V3_SETUP)
    #define BLE_EN_GROUP            PIN_GROUP_1
    #define BLE_EN_PINID            3
#endif
#define BLE_EN_MASK             (1UL << BLE_EN_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define USB_3V3_GROUP           PIN_GROUP_0
    #define USB_3V3_PINID           27
#elif defined(PLAT_V3_SETUP)
    #define USB_3V3_GROUP           PIN_GROUP_0
    #define USB_3V3_PINID           1
#endif
#define USB_3V3_MASK            (1UL << USB_3V3_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define VOLED_1V2_EN_GROUP      PIN_GROUP_1
    #define VOLED_1V2_EN_PINID      22
#elif defined(PLAT_V3_SETUP)
    #define VOLED_1V2_EN_GROUP      PIN_GROUP_0
    #define VOLED_1V2_EN_PINID      8
#endif
#define VOLED_1V2_EN_MASK       (1UL << VOLED_1V2_EN_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define VOLED_3V3_EN_GROUP      PIN_GROUP_1
    #define VOLED_3V3_EN_PINID      23
#elif defined(PLAT_V3_SETUP)
    #define VOLED_3V3_EN_GROUP      PIN_GROUP_0
    #define VOLED_3V3_EN_PINID      0
#endif
#define VOLED_3V3_EN_MASK       (1UL << VOLED_3V3_EN_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define MCU_AUX_RST_EN_GROUP    PIN_GROUP_0
    #define MCU_AUX_RST_EN_PINID    15
    #define MCU_AUX_RST_EN_MASK     (1UL << MCU_AUX_RST_EN_PINID)
#endif

/* OLED */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define OLED_MOSI_GROUP         PIN_GROUP_0
    #define OLED_MOSI_PINID         4
#elif defined(PLAT_V3_SETUP)
    #define OLED_MOSI_GROUP         PIN_GROUP_1
    #define OLED_MOSI_PINID         10
#endif
#define OLED_MOSI_MASK          (1UL << OLED_MOSI_PINID)
#define OLED_MOSI_PMUX_ID       PORT_PMUX_PMUXE_D_Val
#if (OLED_MOSI_PINID % 2) == 1
    #define OLED_MOSI_PMUXREGID PMUXO
#else
    #define OLED_MOSI_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define OLED_SCK_GROUP          PIN_GROUP_0
    #define OLED_SCK_PINID          5
#elif defined(PLAT_V3_SETUP)
    #define OLED_SCK_GROUP          PIN_GROUP_1
    #define OLED_SCK_PINID          11
#endif
#define OLED_SCK_MASK           (1UL << OLED_SCK_PINID)
#define OLED_SCK_PMUX_ID        PORT_PMUX_PMUXO_D_Val
#if (OLED_SCK_PINID % 2) == 1
    #define OLED_SCK_PMUXREGID  PMUXO
#else
    #define OLED_SCK_PMUXREGID  PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define OLED_nCS_GROUP          PIN_GROUP_1
    #define OLED_nCS_PINID          9
#elif defined(PLAT_V3_SETUP)
    #define OLED_nCS_GROUP          PIN_GROUP_0
    #define OLED_nCS_PINID          14
#endif
#define OLED_nCS_MASK           (1UL << OLED_nCS_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define OLED_CD_GROUP           PIN_GROUP_0
    #define OLED_CD_PINID           6
#elif defined(PLAT_V3_SETUP)
    #define OLED_CD_GROUP           PIN_GROUP_0
    #define OLED_CD_PINID           12
#endif
#define OLED_CD_MASK            (1UL << OLED_CD_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define OLED_nRESET_GROUP       PIN_GROUP_0
    #define OLED_nRESET_PINID       7
#elif defined(PLAT_V3_SETUP)
    #define OLED_nRESET_GROUP       PIN_GROUP_0
    #define OLED_nRESET_PINID       13
#endif
#define OLED_nRESET_MASK        (1UL << OLED_nRESET_PINID)

/* DATAFLASH FLASH */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DATAFLASH_MOSI_GROUP         PIN_GROUP_0
    #define DATAFLASH_MOSI_PINID         8
#elif defined(PLAT_V3_SETUP)
    #define DATAFLASH_MOSI_GROUP         PIN_GROUP_0
    #define DATAFLASH_MOSI_PINID         20
#endif
#define DATAFLASH_MOSI_MASK          (1UL << DATAFLASH_MOSI_PINID)
#define DATAFLASH_MOSI_PMUX_ID       PORT_PMUX_PMUXE_D_Val
#if (DATAFLASH_MOSI_PINID % 2) == 1
    #define DATAFLASH_MOSI_PMUXREGID PMUXO
#else
    #define DATAFLASH_MOSI_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DATAFLASH_MISO_GROUP         PIN_GROUP_0
    #define DATAFLASH_MISO_PINID         10
    #define DATAFLASH_MISO_PMUX_ID       PORT_PMUX_PMUXE_D_Val
#elif defined(PLAT_V3_SETUP)
    #define DATAFLASH_MISO_GROUP         PIN_GROUP_0
    #define DATAFLASH_MISO_PINID         22
    #define DATAFLASH_MISO_PMUX_ID       PORT_PMUX_PMUXE_C_Val
#endif
#define DATAFLASH_MISO_MASK          (1UL << DATAFLASH_MISO_PINID)
#if (DATAFLASH_MISO_PINID % 2) == 1
    #define DATAFLASH_MISO_PMUXREGID PMUXO
#else
    #define DATAFLASH_MISO_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DATAFLASH_SCK_GROUP          PIN_GROUP_0
    #define DATAFLASH_SCK_PINID          9
#elif defined(PLAT_V3_SETUP)
    #define DATAFLASH_SCK_GROUP          PIN_GROUP_0
    #define DATAFLASH_SCK_PINID          21
#endif
#define DATAFLASH_SCK_MASK           (1UL << DATAFLASH_SCK_PINID)
#define DATAFLASH_SCK_PMUX_ID        PORT_PMUX_PMUXO_D_Val
#if (DATAFLASH_SCK_PINID % 2) == 1
    #define DATAFLASH_SCK_PMUXREGID  PMUXO
#else
    #define DATAFLASH_SCK_PMUXREGID  PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DATAFLASH_nCS_GROUP          PIN_GROUP_0
    #define DATAFLASH_nCS_PINID          11
#elif defined(PLAT_V3_SETUP)
    #define DATAFLASH_nCS_GROUP          PIN_GROUP_0
    #define DATAFLASH_nCS_PINID          23
#endif
#define DATAFLASH_nCS_MASK           (1UL << DATAFLASH_nCS_PINID)

/* DBFLASH FLASH */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DBFLASH_MOSI_GROUP         PIN_GROUP_0
    #define DBFLASH_MOSI_PINID         22
#elif defined(PLAT_V3_SETUP)
    #define DBFLASH_MOSI_GROUP         PIN_GROUP_0
    #define DBFLASH_MOSI_PINID         19
#endif
#define DBFLASH_MOSI_MASK          (1UL << DBFLASH_MOSI_PINID)
#define DBFLASH_MOSI_PMUX_ID       PORT_PMUX_PMUXE_C_Val
#if (DBFLASH_MOSI_PINID % 2) == 1
    #define DBFLASH_MOSI_PMUXREGID PMUXO
#else
    #define DBFLASH_MOSI_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DBFLASH_MISO_GROUP         PIN_GROUP_0
    #define DBFLASH_MISO_PINID         25
#elif defined(PLAT_V3_SETUP)
    #define DBFLASH_MISO_GROUP         PIN_GROUP_0
    #define DBFLASH_MISO_PINID         18
#endif
#define DBFLASH_MISO_MASK          (1UL << DBFLASH_MISO_PINID)
#define DBFLASH_MISO_PMUX_ID       PORT_PMUX_PMUXE_C_Val
#if (DBFLASH_MISO_PINID % 2) == 1
    #define DBFLASH_MISO_PMUXREGID PMUXO
#else
    #define DBFLASH_MISO_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DBFLASH_SCK_GROUP          PIN_GROUP_0
    #define DBFLASH_SCK_PINID          23
#elif defined(PLAT_V3_SETUP)
    #define DBFLASH_SCK_GROUP          PIN_GROUP_0
    #define DBFLASH_SCK_PINID          17
#endif
#define DBFLASH_SCK_MASK           (1UL << DBFLASH_SCK_PINID)
#define DBFLASH_SCK_PMUX_ID        PORT_PMUX_PMUXO_C_Val
#if (DBFLASH_SCK_PINID % 2) == 1
    #define DBFLASH_SCK_PMUXREGID  PMUXO
#else
    #define DBFLASH_SCK_PMUXREGID  PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define DBFLASH_nCS_GROUP          PIN_GROUP_0
    #define DBFLASH_nCS_PINID          24
#elif defined(PLAT_V3_SETUP)
    #define DBFLASH_nCS_GROUP          PIN_GROUP_0
    #define DBFLASH_nCS_PINID          16
#endif
#define DBFLASH_nCS_MASK           (1UL << DBFLASH_nCS_PINID)

/* ACCELEROMETER */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define ACC_MOSI_GROUP         PIN_GROUP_0
    #define ACC_MOSI_PINID         16
    #define ACC_MOSI_PMUX_ID       PORT_PMUX_PMUXE_C_Val
#elif defined(PLAT_V3_SETUP)
    #define ACC_MOSI_GROUP         PIN_GROUP_0
    #define ACC_MOSI_PINID         4
    #define ACC_MOSI_PMUX_ID       PORT_PMUX_PMUXE_D_Val
#endif
#define ACC_MOSI_MASK          (1UL << ACC_MOSI_PINID)
#if (ACC_MOSI_PINID % 2) == 1
    #define ACC_MOSI_PMUXREGID PMUXO
#else
    #define ACC_MOSI_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define ACC_MISO_GROUP         PIN_GROUP_0
    #define ACC_MISO_PINID         17
    #define ACC_MISO_PMUX_ID       PORT_PMUX_PMUXE_C_Val
#elif defined(PLAT_V3_SETUP)
    #define ACC_MISO_GROUP         PIN_GROUP_0
    #define ACC_MISO_PINID         5
    #define ACC_MISO_PMUX_ID       PORT_PMUX_PMUXE_D_Val
#endif
#define ACC_MISO_MASK          (1UL << ACC_MISO_PINID)
#if (ACC_MISO_PINID % 2) == 1
    #define ACC_MISO_PMUXREGID PMUXO
#else
    #define ACC_MISO_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define ACC_SCK_GROUP          PIN_GROUP_0
    #define ACC_SCK_PINID          19
    #define ACC_SCK_PMUX_ID        PORT_PMUX_PMUXO_C_Val
#elif defined(PLAT_V3_SETUP)
    #define ACC_SCK_GROUP          PIN_GROUP_0
    #define ACC_SCK_PINID          7
    #define ACC_SCK_PMUX_ID        PORT_PMUX_PMUXO_D_Val
#endif
#define ACC_SCK_MASK           (1UL << ACC_SCK_PINID)
#if (ACC_SCK_PINID % 2) == 1
    #define ACC_SCK_PMUXREGID  PMUXO
#else
    #define ACC_SCK_PMUXREGID  PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define ACC_nCS_GROUP          PIN_GROUP_0
    #define ACC_nCS_PINID          18
#elif defined(PLAT_V3_SETUP)
    #define ACC_nCS_GROUP          PIN_GROUP_0
    #define ACC_nCS_PINID          6
#endif
#define ACC_nCS_MASK           (1UL << ACC_nCS_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define ACC_INT_GROUP          PIN_GROUP_0
    #define ACC_INT_PINID          20
#elif defined(PLAT_V3_SETUP)
    #define ACC_INT_GROUP          PIN_GROUP_1
    #define ACC_INT_PINID          9
#endif
#define ACC_INT_MASK           (1UL << ACC_INT_PINID)
#if (ACC_INT_PINID % 2) == 1
    #define ACC_INT_PMUXREGID  PMUXO
#else
    #define ACC_INT_PMUXREGID  PMUXE
#endif

/* SMARTCARD */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SMC_MOSI_GROUP         PIN_GROUP_1
    #define SMC_MOSI_PINID         2
#elif defined(PLAT_V3_SETUP)
    #define SMC_MOSI_GROUP         PIN_GROUP_0
    #define SMC_MOSI_PINID         11
#endif
#define SMC_MOSI_MASK          (1UL << SMC_MOSI_PINID)
#define SMC_MOSI_PMUX_ID       PORT_PMUX_PMUXE_D_Val
#if (SMC_MOSI_PINID % 2) == 1
    #define SMC_MOSI_PMUXREGID PMUXO
#else
    #define SMC_MOSI_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SMC_MISO_GROUP         PIN_GROUP_1
    #define SMC_MISO_PINID         3
#elif defined(PLAT_V3_SETUP)
    #define SMC_MISO_GROUP         PIN_GROUP_0
    #define SMC_MISO_PINID         10
#endif
#define SMC_MISO_MASK          (1UL << SMC_MISO_PINID)
#define SMC_MISO_PMUX_ID       PORT_PMUX_PMUXE_D_Val
#if (SMC_MISO_PINID % 2) == 1
    #define SMC_MISO_PMUXREGID PMUXO
#else
    #define SMC_MISO_PMUXREGID PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SMC_SCK_GROUP          PIN_GROUP_0
    #define SMC_SCK_PINID          21
    #define SMC_SCK_PMUX_ID        PORT_PMUX_PMUXO_C_Val
#elif defined(PLAT_V3_SETUP)
    #define SMC_SCK_GROUP          PIN_GROUP_0
    #define SMC_SCK_PINID          9
    #define SMC_SCK_PMUX_ID        PORT_PMUX_PMUXO_D_Val
#endif
#define SMC_SCK_MASK           (1UL << SMC_SCK_PINID)
#if (SMC_SCK_PINID % 2) == 1
    #define SMC_SCK_PMUXREGID  PMUXO
#else
    #define SMC_SCK_PMUXREGID  PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SMC_RST_GROUP          PIN_GROUP_0
    #define SMC_RST_PINID          14
#elif defined(PLAT_V3_SETUP)
    #define SMC_RST_GROUP          PIN_GROUP_0
    #define SMC_RST_PINID          24
#endif
#define SMC_RST_MASK           (1UL << SMC_RST_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SMC_PGM_GROUP          PIN_GROUP_0
    #define SMC_PGM_PINID          31
#elif defined(PLAT_V3_SETUP)
    #define SMC_PGM_GROUP          PIN_GROUP_1
    #define SMC_PGM_PINID          8
#endif
#define SMC_PGM_MASK           (1UL << SMC_PGM_PINID)

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define SMC_DET_GROUP          PIN_GROUP_0
    #define SMC_DET_PINID          12
#elif defined(PLAT_V3_SETUP)
    #define SMC_DET_GROUP          PIN_GROUP_0
    #define SMC_DET_PINID          3
#endif
#define SMC_DET_MASK           (1UL << SMC_DET_PINID)

/* AUX MCU COMMS */
#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define AUX_MCU_TX_GROUP       PIN_GROUP_1
    #define AUX_MCU_TX_PINID       11
#elif defined(PLAT_V3_SETUP)
    #define AUX_MCU_TX_GROUP       PIN_GROUP_1
    #define AUX_MCU_TX_PINID       23
#endif
#define AUX_MCU_TX_MASK        (1UL << AUX_MCU_TX_PINID)
#define AUX_MCU_TX_PMUX_ID     PORT_PMUX_PMUXO_D_Val
#if (AUX_MCU_TX_PINID % 2) == 1
    #define AUX_MCU_TX_PMUXREGID  PMUXO
#else
    #define AUX_MCU_TX_PMUXREGID  PMUXE
#endif

#if defined(PLAT_V1_SETUP) || defined(PLAT_V2_SETUP)
    #define AUX_MCU_RX_GROUP       PIN_GROUP_1
    #define AUX_MCU_RX_PINID       10
#elif defined(PLAT_V3_SETUP)
    #define AUX_MCU_RX_GROUP       PIN_GROUP_1
    #define AUX_MCU_RX_PINID       22
#endif
#define AUX_MCU_RX_MASK        (1UL << AUX_MCU_RX_PINID)
#define AUX_MCU_RX_PMUX_ID     PORT_PMUX_PMUXO_D_Val
#if (AUX_MCU_RX_PINID % 2) == 1
    #define AUX_MCU_RX_PMUXREGID  PMUXO
#else
    #define AUX_MCU_RX_PMUXREGID  PMUXE
#endif

#if defined(PLAT_V3_SETUP)
    #define AUX_MCU_NOCOMMS_GROUP   PIN_GROUP_0
    #define AUX_MCU_NOCOMMS_PINID   30
    #define AUX_MCU_NOCOMMS_MASK    (1UL << AUX_MCU_NOCOMMS_PINID)
#endif

/* Display defines */
#define DEFAULT_FONT_ID         0

#endif /* PLATFORM_DEFINES_H_ */