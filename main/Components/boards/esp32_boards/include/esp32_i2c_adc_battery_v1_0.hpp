#ifndef _COMPONENTS_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADC_BATTERY_V1_0_HPP_
#define _COMPONENTS_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADC_BATTERY_V1_0_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  esp32_i2c_adc_battery_v1_0.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-27
 |
 |  @brief  	   :  This class, esp32_i2c_adc_battery_v1_0.hpp, is designed
 as:
 |
 |
 |
 |
 |
 |
 |
 |  @version       : 1.0
 |
 |  @bug  		   :   no known bugs
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes |
 +------------------------------------------------------------------------------*/

#include <iostream>

#ifdef __ESP32__
#include <driver/adc.h>
#include <driver/gpio.h>
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

namespace esp32_i2c_adc_battery_v1_0 {
#ifdef __ESP32__
constexpr gpio_num_t I2C_SDA = GPIO_NUM_13;
constexpr gpio_num_t I2C_SCLK = GPIO_NUM_14;
constexpr adc1_channel_t ADC_BATTERY =
    ADC1_CHANNEL_5;  // might change to adc_pin
constexpr adc1_channel_t ADC_SENSOR =
    ADC1_CHANNEL_6;  // might change to adc_pin
constexpr gpio_num_t ON_OFF_SENSOR = GPIO_NUM_27;
#else
typedef int gpio_num_t;
typedef int ADC_PIN;
constexpr gpio_num_t I2C_SDA = 13;
constexpr gpio_num_t I2C_SCLK = 14;
constexpr adc1_channel_t ADC_BATTERY = 33;
constexpr adc1_channel_t ADC_SENSOR = 34;
constexpr gpio_num_t ON_OFF_SENSOR = 27;
#endif
}  // namespace esp32_i2c_adc_battery_v1_0

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class |
 +------------------------------------------------------------------------------*/

#endif  //_COMPONENTS_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADC_BATTERY_V1_0_HPP_