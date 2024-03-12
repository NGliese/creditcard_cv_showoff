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

#include <Timeservice.hpp>
#include <lcd_interface.hpp>
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "lcd_test";
#endif

lcd_test::lcd_test() {}

lcd_test::~lcd_test() {}

void lcd_test::run() {
#ifdef DEBUG
  std::cout << LOG_TAG << ": run" << std::endl;
#endif
  // create the lcd
  lcd_interface lcd;
  lcd.init();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);
  lcd.clear();
  lcd.write("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.write("Hello, World!");
  std::cout << "Wrote :: Hello, World!" << std::endl;
  Timeservice::wait_ms(2000);

  lcd.clear();
}