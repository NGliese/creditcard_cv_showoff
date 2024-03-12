#ifndef Components_Boards_ESP32_BOARDS_include_esp32_servo_board_v1_0_hpp
#define Components_Boards_ESP32_BOARDS_include_esp32_servo_board_v1_0_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  esp32_servo_board_v1_0.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, esp32_servo_board_v1_0.hpp, is designed as:
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

/*-----------------------------------------------------------------------------*/

#include <iostream>
#ifdef __ESP32__
#include <driver/gpio.h>
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

namespace esp32_servo_board_v1_0 {
#ifdef __ESP32__
constexpr ADC_PIN ADC_SENSOR_1 = ADC1_CHANNEL_5;  // might change to adc_pin
constexpr ADC_PIN ADC_SENSOR_2 = ADC1_CHANNEL_4;  // might change to adc_pin
constexpr ADC_PIN ADC_SENSOR_3 = ADC1_CHANNEL_6;  // might change to adc_pin
constexpr GPIO_PIN PWM_1 = GPIO_NUM_27;
constexpr GPIO_PIN PWM_2 = GPIO_NUM_26;
constexpr GPIO_PIN PWM_3 = GPIO_NUM_25;
#else
typedef int GPIO_PIN;
typedef int ADC_PIN;
constexpr ADC_PIN ADC_SENSOR_1 = 5;
constexpr ADC_PIN ADC_SENSOR_2 = 4;
constexpr ADC_PIN ADC_SENSOR_3 = 6;
constexpr GPIO_PIN PWM_1 = 27;
constexpr GPIO_PIN PWM_2 = 26;
constexpr GPIO_PIN PWM_3 = 25;
#endif
}  // namespace esp32_servo_board_v1_0

#endif /*Components_Boards_ESP32_BOARDS_include_esp32_servo_board_v1_0_hpp*/