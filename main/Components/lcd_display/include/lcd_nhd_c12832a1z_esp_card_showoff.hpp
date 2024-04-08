#ifndef main_Components_lcd_display_include_lcd_nhd_c12832a1z_esp_card_showoff_hpp
#define main_Components_lcd_display_include_lcd_nhd_c12832a1z_esp_card_showoff_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  lcd_nhd_c12832a1z_esp_card_showoff.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, lcd_nhd_c12832a1z_esp_card_showoff.hpp, is
 designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes |
 +------------------------------------------------------------------------------*/
#include <GPIO_API.hpp>
#include <HAL_GPIO_ESP32.hpp>
#include <Timeservice.hpp>
#include <spi_esp32.hpp>

#include "hal_base.hpp"

/*----------------- DEFAULT INCLUDE
 * -------------------------------------------*/

/*-----------------------------------------------------------------------------*/

#include <iostream>
/*
#ifdef __ESP32__
#include <driver/gpio.h>
#define RST_PIN GPIO_NUM_26
#define CMD_PIN GPIO_NUM_25
#else
#define RST_PIN 26
#define CMD_PIN 25
#endif

#define CS_PIN 27
#define IO_SCL_PIN 23
#define IO_SDA_PIN 22
*/
// ORIGINAL BOARD PINS

#ifdef __ESP32__
#include <driver/gpio.h>
#define RST_PIN GPIO_NUM_16
#define CMD_PIN GPIO_NUM_4
#else
#define RST_PIN 26
#define CMD_PIN 25
#endif

#define CS_PIN 17
#define IO_SCL_PIN 13
#define IO_SDA_PIN 14
/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

class lcd_nhd_c12832a1z_esp_card_showoff final : public hal_base {
 public:
  lcd_nhd_c12832a1z_esp_card_showoff(
      const HAL_GPIO_ESP32::pin& rst_pin = RST_PIN,
      const HAL_GPIO_ESP32::pin& cmd_pin = CMD_PIN);
  virtual ~lcd_nhd_c12832a1z_esp_card_showoff(void);
  bool init() override;
  bool deinit() override;
  bool clear() override;
  bool write(const uint8_t* data, const size_t size) override;
  bool setCursor(int x, int y) override;
  bool test_display() override; 
 private:
  bool send_command(const uint8_t data);
  GPIO_API<HAL_GPIO_ESP32> m_rst_pin;
  GPIO_API<HAL_GPIO_ESP32> m_cmd_pin;
  spi_esp32 m_spi;
};

#endif /*main_Components_lcd_display_include_lcd_nhd_c12832a1z_esp_card_showoff_hpp*/