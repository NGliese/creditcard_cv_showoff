#ifndef Components_Boards_ESP32_BOARDS_include_esp32_env_v1_0_hpp
#define Components_Boards_ESP32_BOARDS_include_esp32_env_v1_0_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  esp32_env_v1_0.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, esp32_env_v1_0.hpp, is designed as:
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
#ifdef __ESP32__
#include <driver/adc.h>
#include <driver/gpio.h>
#endif
namespace esp32_env_v1_0 {
#ifdef __ESP32__
constexpr gpio_num_t I2C_SDA = GPIO_NUM_22;
constexpr gpio_num_t I2C_SCLK = GPIO_NUM_23;
#else
typedef int gpio_num_t;
constexpr gpio_num_t I2C_SDA = 22;
constexpr gpio_num_t I2C_SCLK = 23;
#endif
}  // namespace esp32_env_v1_0

#endif /*Components_Boards_ESP32_BOARDS_include_esp32_env_v1_0_hpp*/