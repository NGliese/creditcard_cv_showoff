/*
 * uart_hal.cpp
 *
 *  Created on: Jan 12, 2021
 *      Author: espenv
 */

/***********************************************************************************************+
 *  \brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       uart_hal.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/uart_hal.hpp"

static const int uart_buffer_size = (1024 * 2);
#ifndef __ESP32__
#define UART_NUM_2 (2)
#endif
const int uart_num = UART_NUM_2;
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "uart_hal";
#endif

uart_hal::~uart_hal() {}

bool uart_hal::initialize(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> uart_hal::initialize >> ");
#endif
	// Executable code:

#ifdef __ESP32__
	uart_config.baud_rate = 9600; // default baudrate 115200
	uart_config.data_bits = UART_DATA_8_BITS;
	uart_config.parity = UART_PARITY_DISABLE;
	uart_config.stop_bits = UART_STOP_BITS_1;
	uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
	uart_config.rx_flow_ctrl_thresh = 122;
	// point to NULL here
	uart_queue = NULL;
	// config uart parameters
	ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
	// set UART pins (TX: IO16 (UART2 default) RX: IO17 (UART2 default)), RTS:IO18, CTS: IO19
	ESP_ERROR_CHECK(uart_set_pin(uart_num, 19, 18, 17,
								 UART_PIN_NO_CHANGE)); // @suppress("Invalid arguments") //
													   // @suppress("Symbol is not resolved")
	// flow control
#endif
	std::cout << " uart driver is initialized \n";

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< uart_hal::initialize << ");
#endif

	return true;
}

bool uart_hal::open(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> uart_hal::open >> ");
#endif
	// Executable code:
#ifdef __ESP32__
	// install UART driver
	ESP_ERROR_CHECK(
		uart_driver_install(uart_num, uart_buffer_size , uart_buffer_size , 0, NULL, 0));
#endif
	std::cout << " uart driver is open \n";

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< uart_hal::open << ");
#endif

	return true;
}

bool uart_hal::close(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> uart_hal::close >> ");
#endif
	// Executable code:
#ifdef __ESP32__
	// delete the driver
	ESP_ERROR_CHECK(uart_driver_delete(uart_num));
#endif
	std::cout << " uart driver is closed \n";
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< uart_hal::close << ");
#endif

	return true;
}
bool uart_hal::write(const uint8_t* data, size_t len) const
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> uart_hal::write >> ");
#endif
	// Executable code:
#ifdef __ESP32__
	if(uart_write_bytes(uart_num, data, len) == -1)
	{
		return false;
	}
	// wait for the data to be transmitted
	ESP_ERROR_CHECK(uart_wait_tx_done(uart_num, 1000));
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< uart_hal::write << ");
#endif

	return true;
}


bool uart_hal::read(uint8_t* data, size_t len)
{

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> uart_hal::read >> ");
#endif
// Executable code:
#ifdef __ESP32__
	size_t length = 0;
	// check the buffer size of recieved data
	ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, &length));
	if(!(length > 0))
	{
		return false;
	}
	// read the bytes, wait max 100 tics
	length = uart_read_bytes(uart_num, data, length, 100);
	if(length == -1)
	{
		return false;
	}
	// check if the length is correct
	if(length != len)
	{
		return false;
	}
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< uart_hal::read << ");
#endif

	return true;
}

