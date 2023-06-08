/*
 *
 * HIGH SPEED LOW LEVEL DISPLAY FUNCTIONS USING DIRECT TRANSFER MODE
 *
*/

#ifndef _TFTSPI_H_
#define _TFTSPI_H_

#include "tftspi.h"
#include "../spidriver/spi_master_lobo.h"
#include "sdkconfig.h"
#include "stmpe610.h"

#define TOUCH_TYPE_NONE		0
#define TOUCH_TYPE_XPT2046	1
#define TOUCH_TYPE_STMPE610	2

#define TP_CALX_XPT2046		7472920
#define TP_CALY_XPT2046		122224794

#define TP_CALX_STMPE610	21368532
#define TP_CALY_STMPE610	11800144

// === Screen orientation constants ===
#define PORTRAIT	0
#define LANDSCAPE	1
#define PORTRAIT_FLIP	2
#define LANDSCAPE_FLIP	3

#define DISP_TYPE_ILI9488	1

// Configuration for other boards, set the correct values for the display used
//----------------------------------------------------------------------------
#define DISP_COLOR_BITS_24	0x66
//#define DISP_COLOR_BITS_16	0x55  // Do not use!

// #############################################
// ### Set to 1 for some displays,           ###
//     for example the one on ESP-WROWER-KIT ###
// #############################################
#define TFT_INVERT_ROTATION 0
#define TFT_INVERT_ROTATION1 0

// ################################################
// ### SET TO 0X00 FOR DISPLAYS WITH RGB MATRIX ###
// ### SET TO 0X08 FOR DISPLAYS WITH BGR MATRIX ###
// ### For ESP-WROWER-KIT set to 0x00           ###
// ################################################
#define TFT_RGB_BGR 0x08

// ##############################################################
// ### Define ESP32 SPI pins to which the display is attached ###
// ##############################################################

// The pins configured here are the native spi pins for HSPI interface
// Any other valid pin combination can be used
#define PIN_NUM_MISO 19		// SPI MISO
#define PIN_NUM_MOSI 23		// SPI MOSI
#define PIN_NUM_CLK  18		// SPI CLOCK pin
#define PIN_NUM_CS   5		// Display CS pin
#define PIN_NUM_DC   26		// Display command/data pin

// --------------------------------------------------------------
// ** Set Reset and Backlight pins to 0 if not used !
// ** If you want to use them, set them to some valid GPIO number
#define PIN_NUM_RST  4  	// GPIO used for RESET control
// --------------------------------------------------------------

// #######################################################
// Set this to 1 if you want to use touch screen functions
// #######################################################
#define USE_TOUCH	TOUCH_TYPE_NONE
// #######################################################

// #######################################################################
// Default display width (smaller dimension) and height (larger dimension)
// #######################################################################
#define DEFAULT_TFT_DISPLAY_WIDTH  320
#define DEFAULT_TFT_DISPLAY_HEIGHT 480
// #######################################################################
#define DEFAULT_GAMMA_CURVE 0
#define DEFAULT_SPI_CLOCK   26000000
#define DEFAULT_DISP_TYPE   DISP_TYPE_ILI9488
//----------------------------------------------------------------------------

// ##############################################################
// #### Global variables                                     ####
// ##############################################################

// ==== Converts colors to grayscale if 1 =======================
extern uint8_t gray_scale;

// ==== Spi clock for reading data from display memory in Hz ====
extern uint32_t max_rdclock;

// ==== Display dimensions in pixels ============================
extern int _width;
extern int _height;

// ==== Display type, DISP_TYPE_ILI9488 or DISP_TYPE_ILI9341 ====
extern uint8_t tft_disp_type;

// ==== Spi device handles for display and touch screen =========
extern spi_lobo_device_handle_t disp_spi;
extern spi_lobo_device_handle_t ts_spi;

// ##############################################################

// 24-bit color type structure
typedef struct __attribute__((__packed__)) {
//typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t ;

// ==== Display commands constants ====
#define TFT_INVOFF     0x20
#define TFT_INVONN     0x21
#define TFT_DISPOFF    0x28
#define TFT_DISPON     0x29
#define TFT_MADCTL	   0x36
#define TFT_PTLAR 	   0x30
#define TFT_ENTRYM 	   0xB7

#define TFT_CMD_NOP			0x00
#define TFT_CMD_SWRESET		0x01
#define TFT_CMD_RDDID		0x04
#define TFT_CMD_RDDST		0x09

#define TFT_CMD_SLPIN		0x10
#define TFT_CMD_SLPOUT		0x11
#define TFT_CMD_PTLON		0x12
#define TFT_CMD_NORON		0x13

#define TFT_CMD_RDMODE		0x0A
#define TFT_CMD_RDMADCTL	0x0B
#define TFT_CMD_RDPIXFMT	0x0C
#define TFT_CMD_RDIMGFMT	0x0D
#define TFT_CMD_RDSELFDIAG  0x0F

#define TFT_CMD_GAMMASET	0x26

#define TFT_CMD_FRMCTR1		0xB1
#define TFT_CMD_FRMCTR2		0xB2
#define TFT_CMD_FRMCTR3		0xB3
#define TFT_CMD_INVCTR		0xB4
#define TFT_CMD_DFUNCTR		0xB6

#define TFT_CMD_PWCTR1		0xC0
#define TFT_CMD_PWCTR2		0xC1
#define TFT_CMD_PWCTR3		0xC2
#define TFT_CMD_PWCTR4		0xC3
#define TFT_CMD_PWCTR5		0xC4
#define TFT_CMD_VMCTR1		0xC5
#define TFT_CMD_VMCTR2		0xC7

#define TFT_CMD_RDID1		0xDA
#define TFT_CMD_RDID2		0xDB
#define TFT_CMD_RDID3		0xDC
#define TFT_CMD_RDID4		0xDD

#define TFT_CMD_GMCTRP1		0xE0
#define TFT_CMD_GMCTRN1		0xE1

#define TFT_CMD_POWERA		0xCB
#define TFT_CMD_POWERB		0xCF
#define TFT_CMD_POWER_SEQ	0xED
#define TFT_CMD_DTCA		0xE8
#define TFT_CMD_DTCB		0xEA
#define TFT_CMD_PRC			0xF7
#define TFT_CMD_3GAMMA_EN	0xF2

#define ST_CMD_VCOMS       0xBB
#define ST_CMD_FRCTRL2      0xC6
#define ST_CMD_PWCTR1		0xD0

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_PWCTR6  0xFC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_MH  0x04

#define TFT_CASET		0x2A
#define TFT_PASET		0x2B
#define TFT_RAMWR		0x2C
#define TFT_RAMRD		0x2E
#define TFT_CMD_PIXFMT	0x3A

#define TFT_CMD_DELAY	0x80

// Initialization sequence for ILI9488
// ====================================
static const uint8_t ILI9488_init[] = {
#if PIN_NUM_RST
        17,                   					        // 17 commands in list
#else
        18,                   					        // 18 commands in list
        TFT_CMD_SWRESET, TFT_CMD_DELAY,					//  1: Software reset, no args, w/delay
        200,												//     200 ms delay
#endif
        0xE0, 15, 0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F,
        0xE1, 15,	0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F,
        0xC0, 2,   //Power Control 1
        0x17,    //Vreg1out
        0x15,    //Verg2out

        0xC1, 1,   //Power Control 2
        0x41,    //VGH,VGL

        0xC5, 3,   //Power Control 3
        0x00,
        0x12,    //Vcom
        0x80,

#if TFT_INVERT_ROTATION
        TFT_MADCTL, 1, (MADCTL_MV | TFT_RGB_BGR),			// Memory Access Control (orientation), set to portrait
#else
        TFT_MADCTL, 1, (MADCTL_MX | TFT_RGB_BGR),			// Memory Access Control (orientation), set to portrait
#endif

        // *** INTERFACE PIXEL FORMAT: 0x66 -> 18 bit;
        TFT_CMD_PIXFMT, 1, DISP_COLOR_BITS_24,

        0xB0, 1,   // Interface Mode Control
        0x00,    // 0x80: SDO NOT USE; 0x00 USE SDO

        0xB1, 1,   //Frame rate
        0xA0,    //60Hz

        0xB4, 1,   //Display Inversion Control
        0x02,    //2-dot

        0xB6, 2,   //Display Function Control  RGB/MCU Interface Control
        0x02,    //MCU
        0x02,    //Source,Gate scan direction

        0xE9, 1,   // Set Image Function
        0x00,    // Disable 24 bit data

        0x53, 1,   // Write CTRL Display Value
        0x28,    // BCTRL && DD on

        0x51, 1,   // Write Display Brightness Value
        0x7F,    //

        0xF7, 4,   // Adjust Control
        0xA9,
        0x51,
        0x2C,
        0x02,    // D7 stream, loose


        0x11, TFT_CMD_DELAY,  //Exit Sleep
        120,
        0x29, 0,      //Display on

};

// ==== Public functions =========================================================

// == Low level functions; usually not used directly ==
esp_err_t wait_trans_finish(uint8_t free_line);
void disp_spi_transfer_cmd(int8_t cmd);
void disp_spi_transfer_cmd_data(int8_t cmd, uint8_t *data, uint32_t len);
void drawPixel(int16_t x, int16_t y, color_t color, uint8_t sel);
void send_data(int x1, int y1, int x2, int y2, uint32_t len, color_t *buf);
void TFT_pushColorRep(int x1, int y1, int x2, int y2, color_t data, uint32_t len);
int read_data(int x1, int y1, int x2, int y2, int len, uint8_t *buf, uint8_t set_sp);
color_t readPixel(int16_t x, int16_t y);
int touch_get_data(uint8_t type);


// Deactivate display's CS line
//========================
esp_err_t disp_deselect();

// Activate display's CS line and configure SPI interface if necessary
//======================
esp_err_t disp_select();


// Find maximum spi clock for successful read from display RAM
// ** Must be used AFTER the display is initialized **
//======================
uint32_t find_rd_speed();


// Change the screen rotation.
// Input: m new rotation value (0 to 3)
//=================================
void _tft_setRotation(uint8_t rot);

// Initialize all pins used by display driver
// ** MUST be executed before SPI interface initialization
//=================
void TFT_PinsInit();

// Perform display initialization sequence
// Sets orientation to landscape; clears the screen
// * All pins must be configured
// * SPI interface must already be setup
// * 'tft_disp_type', 'COLOR_BITS', '_width', '_height' variables must be set
//======================
void TFT_display_init();

//===================
void stmpe610_Init();

//============================================================
int stmpe610_get_touch(uint16_t *x, uint16_t *y, uint16_t *z);

//========================
uint32_t stmpe610_getID();

// ===============================================================================

#endif