/* pthread/std::thread example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_log.h>

#include <button_test.hpp>
#include <iostream>
#include <lcd_test.hpp>

#include "sdkconfig.h"

extern "C" void app_main(void) {
  std::cout << "Hello, World!" << std::endl;
  std::cout << "This is ESP32 chip with " << CONFIG_IDF_TARGET << " chip"
            << std::endl;

  /*
    RUN THE EXAMPLES BELOW ONE AT A TIME
  */

  // button_test test;
  //  test.run();
  lcd_test lcd;
   lcd.run();
  // lcd.test_io();
  //lcd.test_spi();
  std::cout << "Stopping program" << std::endl;
}
