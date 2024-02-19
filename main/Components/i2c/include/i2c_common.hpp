#ifndef _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_COMMON_HPP_
#define _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_COMMON_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  i2c_common.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-04-07
 |
 |  @brief  	   :  This class, i2c_common.hpp, is designed as:
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
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

#include <stdint.h>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/
#ifdef __ESP32__
#include <driver/gpio.h>
#else
typedef int gpio_num_t;
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

struct i2c_conf_t
{
	uint32_t speed; // 100k Hz default
	gpio_num_t pin_sda; // gpio pin for sda
	gpio_num_t pin_sclk; // pgio pin for clk

	
};

#endif //_COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_COMMON_HPP_