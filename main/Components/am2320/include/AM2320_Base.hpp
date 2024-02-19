#ifndef Components_Sensor_AM2320_include_AM2320_Base_hpp
#define Components_Sensor_AM2320_include_AM2320_Base_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  AM2320_Base.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, AM2320_Base.hpp, is designed as:
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
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/

#include "../../Timeservice/include/Timeservice.hpp"

#include "../../i2c/include/i2c.hpp"
#include "../../i2c/include/i2c_esp32.hpp"
#include "../../utils/include/utils.h"
/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class AM2320_Base
{
#ifdef __UNITTEST__
	friend class friend_AM2320_Base;
#endif
  public:
	AM2320_Base(const i2c_conf_t& conf, const uint8_t& slaveaddress);
	virtual ~AM2320_Base();
	/**
	 * @brief Get the Measurement object
	 * execution function to handle the i2c communication, convertion to SI
	 * and to return the actual value.
	 * @attention If return is 0 it means an error has occured
	 * @return uint16_t
	 */
	uint16_t getMeasurement();

  protected:
	i2c<i2c_esp32> m_i2c;
	const uint8_t m_address;

	const uint8_t FUNCTION_CODE_TEMPERATURE = 0x02;
	const uint8_t FUNCTION_CODE_HUMIDITY = 0x00;

	/**
	 * @brief Get the Raw object
	 * get the raw i2c value
	 * @return uint16_t
	 */
	virtual uint16_t getRaw() = 0;
	/**
	 * @brief Get the Sensor Value object
	 * get the i2c result from the given function code
	 *
	 * @return uint16_t
	 */
	uint16_t getSensorValue(const uint8_t& register_address);

  private:
	/**
	 * @brief wake up the sensor
	 *
	 * @return true
	 * @return false
	 */
	bool wakeUp();
};
/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_AM2320_Base
{
  public:
	explicit friend_AM2320_Base(AM2320_Base* AM2320_Base) : m_sensor{AM2320_Base} {};
	~friend_AM2320_Base(){};

  private:
	AM2320_Base* m_sensor;
};
#endif
#endif /*Components_Sensor_AM2320_include_AM2320_Base_hpp*/