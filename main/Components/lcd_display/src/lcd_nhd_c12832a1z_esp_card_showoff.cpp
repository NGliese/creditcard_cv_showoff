/***********************************************************************************************+
 *  \brief      BRIEF TEXT
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       lcd_nhd_c12832a1z_esp_card_showoff.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/lcd_nhd_c12832a1z_esp_card_showoff.hpp"
#include "../include/lcd_data.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "lcd_nhd_c12832a1z_esp_card_showoff";
#endif

/*
    COMMANDS FOR THE DISPLAY
*/
#define CMD_DISPLAY_OFF 0xAE
#define CMD_DISPLAY_ON 0xAF
#define CMD_SET_DISP_START_LINE 0x40
#define CMD_SET_PAGE 0xB0
#define CMD_SET_COLUMN_UPPER 0x10
#define CMD_SET_COLUMN_LOWER 0x00
#define CMD_SET_ADC_NORMAL 0xA0
#define CMD_SET_ADC_REVERSE 0xA1
#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7
#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON 0xA5
#define CMD_SET_BIAS_9 0xA2
#define CMD_SET_BIAS_7 0xA3
#define CMD_RMW 0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET 0xE2
#define CMD_SET_COM_NORMAL 0xC0
#define CMD_SET_COM_REVERSE 0xC8
#define CMD_SET_POWER_CONTROL 0x2F
#define CMD_SET_RESISTOR_RATIO 0x21
#define CMD_SET_VOLUME_FIRST 0x81
#define CMD_SET_VOLUME_SECOND 0x20
#define CMD_SET_STATIC_OFF 0xAC
#define CMD_SET_STATIC_ON 0xAD
#define CMD_SET_STATIC_REG 0x0
#define CMD_SET_BOOSTER_FIRST 0xF8
#define CMD_SET_BOOSTER_234 0
#define CMD_SET_BOOSTER_5 1
#define CMD_SET_BOOSTER_6 3
#define CMD_NOP 0xE3
#define CMD_TEST 0xF0

lcd_nhd_c12832a1z_esp_card_showoff::lcd_nhd_c12832a1z_esp_card_showoff(
    const HAL_GPIO_ESP32::pin& rst_pin, 
    const HAL_GPIO_ESP32::pin& cmd_pin)
    : m_rst_pin{rst_pin},
      m_cmd_pin{cmd_pin}, m_spi{IO_SCL_PIN, IO_SDA_PIN, -1, CS_PIN, 10* 1000*1000} {



      }

lcd_nhd_c12832a1z_esp_card_showoff::~lcd_nhd_c12832a1z_esp_card_showoff() {}

bool lcd_nhd_c12832a1z_esp_card_showoff::init() {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "init called");
#endif
  // set all pins to output
  m_rst_pin.setToOutput();
  m_cmd_pin.setToOutput();
  // set rst and cs to low
  m_rst_pin.setLow();
  m_cmd_pin.setLow();
  m_spi.open();
  // wait 100 ms

  Timeservice::wait_ms(100);
  m_rst_pin.setHigh();
  // wait 100 ms
  Timeservice::wait_ms(100);

/*
  // initialize the display
  send_command(CMD_DISPLAY_OFF);  // display off
  Timeservice::wait_ms(100);

  send_command(CMD_SET_DISP_START_LINE);  // set display start line
  Timeservice::wait_ms(100);

  send_command(CMD_SET_PAGE);  // set page
  Timeservice::wait_ms(100);

  send_command(CMD_SET_ADC_NORMAL);  // set adc normal
  Timeservice::wait_ms(100);

  send_command(CMD_SET_DISP_NORMAL);  // set display normal
  Timeservice::wait_ms(100);

  send_command(CMD_SET_COM_NORMAL);  // set com normal
  Timeservice::wait_ms(100);

  send_command(CMD_SET_BIAS_9);  // set bias 9
  Timeservice::wait_ms(100);

  send_command(CMD_SET_POWER_CONTROL);  // set power control
  Timeservice::wait_ms(100);

  send_command(CMD_DISPLAY_ON);  // display on
  Timeservice::wait_ms(100);
*/

// lets follow the guide from the data sheet

  send_command(CMD_SET_ADC_NORMAL); // ADC select
  send_command(CMD_DISPLAY_OFF); // Display OFF
  send_command(CMD_SET_COM_REVERSE); // COM direction scan
  send_command(CMD_SET_BIAS_9); // LCD bias set
  send_command(CMD_SET_POWER_CONTROL); // Power Control set
  send_command(CMD_SET_RESISTOR_RATIO); // Resistor Ratio Set
  send_command(CMD_SET_VOLUME_FIRST); // Electronic Volume Command (set contrast) Double Btye: 1 of 2
  send_command(CMD_SET_VOLUME_SECOND); // Electronic Volume value (contrast value) Double Byte: 2 of 2
  // costum commands
  //send_command(CMD_SET_DISP_REVERSE); // Display reverse
  send_command(CMD_DISPLAY_ON); // Display ON
  
  // we are now initialized
  is_init = true;

  return true;
}

bool lcd_nhd_c12832a1z_esp_card_showoff::deinit() {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "deinit called");
#endif
  m_spi.close();
  return true;
}

bool lcd_nhd_c12832a1z_esp_card_showoff::clear() {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "clear called");
#endif

   unsigned char page = CMD_SET_PAGE; // page address
  send_command(CMD_DISPLAY_OFF); // Display OFF
  send_command(CMD_SET_DISP_START_LINE); // Display start address + 0x40
  uint8_t lcd_string[1] = {0x00}; // 2 bytes of data
  for (unsigned int i = 0; i < 4; i++)
  {                   // 32pixel display / 8 pixels per page = 4 pages
    send_command(page); // send page address
    send_command(CMD_SET_COLUMN_UPPER); // column address upper 4 bits + 0x10
    send_command(CMD_SET_COLUMN_LOWER); // column address lower 4 bits + 0x00
    for (unsigned int j = 0; j < 128; j++)
    {                          // 128 columns wide
      write(lcd_string,1); // send picture data
     // lcd_string[0] = ~lcd_string[0]; // invert data
    }
    page++; // after 128 columns, go to next page
  }
  send_command(CMD_DISPLAY_ON);
  return true;

  return true;
}

bool lcd_nhd_c12832a1z_esp_card_showoff::write(const uint8_t* data,
                                               const size_t size) {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "write called");
#endif

  // set cmd pin to high
  m_cmd_pin.setHigh();

  Timeservice::wait_us(10);
  // copy data
  
  m_spi.write(data, size);

  return true;
}

bool lcd_nhd_c12832a1z_esp_card_showoff::setCursor(int x, int y) {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "setCursor called");
#endif

  return true;
}

bool lcd_nhd_c12832a1z_esp_card_showoff::send_command(const uint8_t data) {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "send_command called");
#endif
  // set cmd pin to low
  m_cmd_pin.setLow();
  Timeservice::wait_us(10);
  // copy data
  uint8_t data_copy = data;
  m_spi.write(&data_copy, 1);

  // set cmd pin to high
  m_cmd_pin.setHigh();

  return true;
}

bool lcd_nhd_c12832a1z_esp_card_showoff::test_display(const uint8_t cmd) {

  // see if the icon is already displayed
  if (local_icon_id == cmd)
  {
    return true;
  }
  // set the icon id
  local_icon_id = cmd;
   unsigned char page = CMD_SET_PAGE; // page address
  send_command(CMD_DISPLAY_OFF); // Display OFF
  send_command(CMD_SET_DISP_START_LINE); // Display start address + 0x40
  lcd_data data;
  uint8_t* lcd_string = data.get_icon(cmd); 
  for (unsigned int i = 0; i < 4; i++)
  {                   // 32pixel display / 8 pixels per page = 4 pages
    send_command(page); // send page address
    send_command(CMD_SET_COLUMN_UPPER); // column address upper 4 bits + 0x10
    send_command(CMD_SET_COLUMN_LOWER); // column address lower 4 bits + 0x00
    for (unsigned int j = 0; j < 128; j++)
    {                          // 128 columns wide
      write(lcd_string,1); // send picture data
      lcd_string++; // move to next data
    }
    page++; // after 128 columns, go to next page
  }
  send_command(CMD_DISPLAY_ON); // Display ON

  return true;

}

/***********************************************************************************************+
 *  End of file
 ***********************************************************************************************/