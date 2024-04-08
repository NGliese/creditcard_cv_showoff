/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */

#include <gtest/gtest.h>

#include <iostream>

#include "../../include/GPIO_API.hpp"
#include "../../include/HAL_MOCK.hpp"

// override gpio_api to access hal
template <typename HAL>
class GPIO_API_MOCK : public GPIO_API<HAL> {
 public:
  GPIO_API_MOCK(const typename HAL::pin& pin) : GPIO_API<HAL>(pin) {}
  HAL& getHal() { return this->m_hal; }
};

// Include the header for the code you want to test
//#include "my_code.h"

// Write test cases
TEST(MyCodeTests, test_to_output) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_TRUE(gpio.setToOutput());
  ASSERT_TRUE(gpio.getHal().m_isDirectionSet_called);
}

TEST(MyCodeTests, test_to_input) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_TRUE(gpio.setToInput());
  ASSERT_TRUE(gpio.getHal().m_isDirectionSet_called);
}

TEST(MyCodeTests, test_toggle) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  gpio.toggle();
  ASSERT_TRUE(gpio.getHal().m_isValueSet_called);
  gpio.toggle();
  ASSERT_TRUE(gpio.getHal().m_isValueSet_called);
}

TEST(MyCodeTests, test_get_value) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_EQ(gpio.getHal().getValue(), HAL_MOCK::io_val_t::LOW);
}

TEST(MyCodeTests, test_set_high) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_TRUE(gpio.setHigh());
  ASSERT_TRUE(gpio.getHal().m_isValueSet_called);
}

TEST(MyCodeTests, test_set_low) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_TRUE(gpio.setLow());
  ASSERT_TRUE(gpio.getHal().m_isValueSet_called);
}

TEST(MyCodeTests, install_interrupt) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_TRUE(gpio.getHal().installInterruptDriver(
      nullptr, HAL_MOCK::io_intr_t::RISING_EDGE));
  ASSERT_TRUE(gpio.getHal().m_isInterruptInstalled_called);
}

TEST(MyCodeTests, enable_interrupt) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_TRUE(gpio.enableInterrupt());
  ASSERT_TRUE(gpio.getHal().m_isInterruptEnabled_called);
}

TEST(MyCodeTests, disable_interrupt) {
  // Arrange
  // ...
  GPIO_API_MOCK<HAL_MOCK> gpio(1);
  // Act
  // Call the function you want to test
  // Assert
  ASSERT_TRUE(gpio.disableInterrupt());
  ASSERT_FALSE(gpio.getHal().m_isInterruptEnabled_called);
}
