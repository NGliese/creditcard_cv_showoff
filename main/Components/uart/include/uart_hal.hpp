/*
 * uart_hal.hpp
 *
 *  Created on: Jan 12, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_DATA_PROTOCOL_INCLUDE_UART_HAL_HPP_
#define MAIN_COMPONENTS_DATA_PROTOCOL_INCLUDE_UART_HAL_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  uart_hal.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 : <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, uart_hal.hpp, is designed as:
 |                  Hal driver for the esp32 uart
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
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/


#include "../../utils/include/utils.h"

#ifdef __ESP32__
#include <driver/uart.h>
#include <esp_err.h>
#endif

#include <iostream>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class uart_hal
{
#ifdef __UNITTEST__
	friend class friend_uart_hal;
#endif
  public:
	uart_hal() = default;
	~uart_hal();
	bool initialize(void);
	bool open(void);
	bool close(void);
	bool write(const uint8_t* data, size_t len) const;
	bool read(uint8_t* data, size_t len);

  private:
#ifdef __ESP32__
	uart_config_t uart_config;
	QueueHandle_t uart_queue;
#endif
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_uart_hal
{
  public:
	explicit friend_uart_hal(uart_hal* uart_hal) : m_sensor{uart_hal} {};

	~friend_uart_hal(){};

  private:
	uart_hal* m_sensor;
};
#endif

#endif /* MAIN_COMPONENTS_DATA_PROTOCOL_INCLUDE_UART_HAL_HPP_ */
