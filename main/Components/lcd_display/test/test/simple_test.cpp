/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */

#include <gtest/gtest.h>

#include <iostream>

// Include the header for the code you want to test
//#include "my_code.h"
#include "../../include/lcd_interface.hpp"
#include "../../include/lcd_mock.hpp"

// overwrite the lcd interface for access to the mock
template <typename HAL = lcd_mock>
class lcd_interface_mock : public lcd_interface<HAL> {
 public:
  HAL& get_hal() { return this->m_hal; }
};

// Write test cases
TEST(MyCodeTests, test_init) {
  // Arrange
  lcd_interface_mock<lcd_mock> lcd;
  // Assert
  ASSERT_TRUE(lcd.get_hal().m_init_called);
}

TEST(MyCodeTests, test_clear) {
  // Arrange
  lcd_interface_mock<lcd_mock> lcd;
  // init the lcd
  ASSERT_TRUE(lcd.clear());
  // Assert
  ASSERT_TRUE(lcd.get_hal().m_clear_called);
}

TEST(MyCodeTests, test_write) {
  // Arrange
  lcd_interface_mock<lcd_mock> lcd;
  // init the lcd
  ASSERT_TRUE(lcd.write("Hello, World!", 13));
  // Assert
  ASSERT_TRUE(lcd.get_hal().m_write_called);
}

TEST(MyCodeTests, test_write_data) {
  // Arrange
  lcd_interface_mock<lcd_mock> lcd;
  // init the lcd
  ASSERT_TRUE(lcd.write("Hello, World!", 13));
  // Assert
  ASSERT_STREQ(lcd.get_hal().m_data, "Hello, World!");
}

TEST(MyCodeTests, test_setCursor) {
  // Arrange
  lcd_interface_mock<lcd_mock> lcd;
  // init the lcd
  ASSERT_TRUE(lcd.setCursor(0, 1));
  // Assert
  ASSERT_TRUE(lcd.get_hal().m_setCursor_called);
}

TEST(MyCodeTests, test_setCursor_x) {
  // Arrange
  lcd_interface_mock<lcd_mock> lcd;
  // init the lcd

  ASSERT_TRUE(lcd.setCursor(0, 1));
  // Assert
  ASSERT_EQ(lcd.get_hal().m_x, 0);
}

TEST(MyCodeTests, test_setCursor_y) {
  // Arrange
  lcd_interface_mock<lcd_mock> lcd;
  // init the lcd
  ASSERT_TRUE(lcd.setCursor(0, 1));
  // Assert
  ASSERT_EQ(lcd.get_hal().m_y, 1);
}
