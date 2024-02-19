#ifndef _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_ESP32_HPP_
#define _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_ESP32_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  i2c_esp32.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-04-07
 |
 |  @brief  	   :  This class, i2c_esp32.hpp, is designed as:
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



#include "i2c_common.hpp"
#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/
#ifdef __ESP32__
#include <driver/gpio.h>
#include <driver/i2c.h>
#endif

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class i2c_esp32
{
#ifdef __UNITTEST__
	friend class friend_i2c_esp32;
#endif
  public:
	i2c_esp32(const i2c_conf_t& conf);
	~i2c_esp32();
	bool slavePresent(uint8_t address);

	bool writeByte(const uint8_t& slave_address, const uint8_t& byte);
	bool writeMultiBytes(const uint8_t& slave_address, const uint8_t* data,
								  const size_t& length);
	uint8_t readByte(const uint8_t& slave_address);

	bool readMultiBytes(const uint8_t& slave_address, uint8_t* data, const size_t& length);
	bool readMultiBytes(const uint8_t& slave_address, const uint8_t& function_code,
								 const uint8_t& register_address, uint8_t* data,
								 const size_t& length);

  private:
	bool initialize_transaction();
	bool insert_start_bit();

	bool insert_write_byte(const uint8_t& slave_address, const uint8_t& byte);
	bool insert_write_bytes(const uint8_t& slave_address, const uint8_t* bytes,
									 const size_t& length);

	bool insert_read_byte(const uint8_t& slave_address, uint8_t* byte);
	bool insert_read_bytes(const uint8_t& slave_address, uint8_t* bytes,
									const size_t& length);

	bool insert_stop_bit();
	bool execute_transaction();

#ifdef __ESP32__
	i2c_cmd_handle_t m_cmd = nullptr;
	const i2c_port_t m_portNum = I2C_NUM_0;
#endif
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_i2c_esp32
{
  public:
	explicit friend_i2c_esp32(i2c_esp32* sensor) : m_sensor{sensor} {};
	~friend_i2c_esp32();

  private:
	i2c_esp32* m_sensor;
};
#endif

#endif //_COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_ESP32_HPP_
