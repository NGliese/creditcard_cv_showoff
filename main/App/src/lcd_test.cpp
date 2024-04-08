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
 *  \file       lcd_test.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/lcd_test.hpp"

#include <driver/gpio.h>

#include <GPIO_API.hpp>
#include <HAL_GPIO_ESP32.hpp>
#include <Timeservice.hpp>
#include <lcd_interface.hpp>
#include <lcd_nhd_c12832a1z_esp_card_showoff.hpp>
#include <spi_esp32.hpp>
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "lcd_test";
#endif

lcd_test::lcd_test() {}

lcd_test::~lcd_test() {}

void lcd_test::test_io() {
  std::cout << " testing IO" << std::endl;
  GPIO_API<HAL_GPIO_ESP32> m_rst_pin{GPIO_NUM_26};
  GPIO_API<HAL_GPIO_ESP32> m_cs_pin{GPIO_NUM_27};
  GPIO_API<HAL_GPIO_ESP32> m_cmd_pin{GPIO_NUM_25};

  GPIO_API<HAL_GPIO_ESP32> m_sda_pin{GPIO_NUM_22};
  GPIO_API<HAL_GPIO_ESP32> m_scl_pin{GPIO_NUM_23};

  Timeservice::wait_ms(2000);

  auto res = m_cmd_pin.setToOutput();
  std::cout << "m_cmd_pin.setToOutput() = " << res << std::endl;
  res = m_rst_pin.setToOutput();
  std::cout << "m_cmd_pin.setToOutput() = " << res << std::endl;
  res = m_cs_pin.setToOutput();
  std::cout << "m_cmd_pin.setToOutput() = " << res << std::endl;
  res = m_sda_pin.setToOutput();
  std::cout << "m_cmd_pin.setToOutput() = " << res << std::endl;
  res = m_scl_pin.setToOutput();
  std::cout << "m_cmd_pin.setToOutput() = " << res << std::endl;

  Timeservice::wait_ms(2000);

  // toogle the pins 10 times with 2 sec delay
  for (int i = 0; i < 10; i++) {
    std::cout << "toogle the pins high" << std::endl;
    res = m_rst_pin.setHigh();
    std::cout << "m_rst_pin.setHigh() = " << res << std::endl;
    res = m_cs_pin.setHigh();
    std::cout << "m_cs_pin.setHigh() = " << res << std::endl;

    res = m_cmd_pin.setHigh();
    std::cout << "m_cmd_pin.setHigh() = " << res << std::endl;
    res = m_sda_pin.setHigh();
    std::cout << "m_sda_pin.setHigh() = " << res << std::endl;
    res = m_scl_pin.setHigh();
    std::cout << "m_scl_pin.setHigh() = " << res << std::endl;
    Timeservice::wait_ms(2000);
    res = m_rst_pin.setLow();
    std::cout << "m_rst_pin.setLow() = " << res << std::endl;
    res = m_cs_pin.setLow();
    std::cout << "m_cs_pin.setLow() = " << res << std::endl;
    res = m_cmd_pin.setLow();
    std::cout << "m_cmd_pin.setLow() = " << res << std::endl;
    res = m_sda_pin.setLow();
    std::cout << "m_sda_pin.setLow() = " << res << std::endl;
    res = m_scl_pin.setLow();
    std::cout << "m_scl_pin.setLow() = " << res << std::endl;
    Timeservice::wait_ms(2000);

    //
  }
}


void lcd_test::run() {
#ifdef DEBUG
  std::cout << LOG_TAG << ": run" << std::endl;
#endif
  // create the lcd
  lcd_interface<lcd_nhd_c12832a1z_esp_card_showoff> lcd;
  std::string data = "Hello, World!";
  lcd.clear();
  Timeservice::wait_ms(1000);
  //for(int i = 0; i < 10; i++)
  //{
  //lcd.write(FMRadio, sizeof(FMRadio));
  lcd.test_display(0);
  std::cout << "lcd_test::run: wait 1 sec" << std::endl;
  //}


  Timeservice::wait_ms(10000);
 // lcd.clear();

  //lcd.clear();
}

void lcd_test::test_spi() {
  std::cout << " testing SPI" << std::endl;
  // create spi
  /*
  
  GPIO_API<HAL_GPIO_ESP32> m_rst_pin{GPIO_NUM_26};
  GPIO_API<HAL_GPIO_ESP32> m_cs_pin{GPIO_NUM_27};
  GPIO_API<HAL_GPIO_ESP32> m_cmd_pin{GPIO_NUM_25};

  GPIO_API<HAL_GPIO_ESP32> m_sda_pin{GPIO_NUM_22};
  GPIO_API<HAL_GPIO_ESP32> m_scl_pin{GPIO_NUM_23};
  */

  spi_esp32 spi{GPIO_NUM_23, GPIO_NUM_22, -1, GPIO_NUM_27,  10000};
   spi.open();
  for(int i = 0; i < 10; i++)
  {
    
    std::string data = "Hello, World!";
    spi.write((uint8_t*)data.c_str(),data.size() );
   
    // wait 2 sec
    Timeservice::wait_ms(2000);
  }
 spi.close();
  // end spi
  std::cout << " testing SPI done" << std::endl;
}