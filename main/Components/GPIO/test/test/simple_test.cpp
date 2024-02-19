/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */


#include <iostream>

#include <gtest/gtest.h>

#include "../../include/GPIO_API.hpp"
#include "../../include/HAL_MOCK.hpp"

// Include the header for the code you want to test
//#include "my_code.h"

// Write test cases
TEST(MyCodeTests, TestFunction1) {
    // Arrange
    // ...
    GPIO_API<HAL_MOCK> gpio(1);
    // Act
    // Call the function you want to test

    // Assert
    ASSERT_TRUE(gpio.setToOutput());
}

// Define more test cases as needed