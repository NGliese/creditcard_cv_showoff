#ifndef Components_Sensor_AM2320_include_AM2320_Temperature_hpp
#define Components_Sensor_AM2320_include_AM2320_Temperature_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  AM2320_Temperature.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, AM2320_Temperature.hpp, is designed as:
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

#include "AM2320_Base.hpp"
/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class AM2320_Temperature final : public AM2320_Base
{
#ifdef __UNITTEST__
	friend class friend_AM2320_Temperature;
#endif
  public:
	AM2320_Temperature(const i2c_conf_t& conf, const uint8_t& slaveaddress = 0x5C)
		: AM2320_Base(conf, slaveaddress){};
	virtual ~AM2320_Temperature(){};

  private:
	uint16_t getRaw() override;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_AM2320_Temperature
{
  public:
	explicit friend_AM2320_Temperature(AM2320_Temperature* AM2320_Temperature)
		: m_sensor{AM2320_Temperature} {};
	~friend_AM2320_Temperature(){};
	auto getRaw()
	{
		return m_sensor->getRaw();
	}

  private:
	AM2320_Temperature* m_sensor;
};
#endif
#endif /*Components_Sensor_AM2320_include_AM2320_Temperature_hpp*/