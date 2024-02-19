/*
 * S8LP_Modbus_api.hpp
 *
 *  Created on: Jan 13, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_S8LP_API_INCLUDE_S8LP_MODBUS_API_HPP_
#define MAIN_COMPONENTS_S8LP_API_INCLUDE_S8LP_MODBUS_API_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  S8LP_Modbus_api.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, S8LP_Modbus_api.hpp, is designed as:
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
 |   		 					Datasheet Awareness              		        |
 +------------------------------------------------------------------------------+
 |
 |
 |  Datasheet Awareness 1):
 |  	Link:[ ], Jan 13, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jan 13, 2021
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/


#include "../../uart/include/uart_hal.hpp"
#include <cstdlib>

#include "../../Timeservice/include/Timeservice.hpp"
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class S8LP_Modbus_api
{
#ifdef __UNITTEST__
	friend class friend_S8LP_Modbus_api;
#endif
  public:
	S8LP_Modbus_api();
	~S8LP_Modbus_api() ;
	bool initialize() noexcept;
	uint16_t getCO2Level() noexcept;
	bool getSensorStatus() noexcept;

  private:
	bool processStatus(std::vector<uint8_t>& vec);
	uint16_t processValue(const uint8_t* data, const size_t& len);
	uart_hal m_uart;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_S8LP_Modbus_api
{
  public:
	explicit friend_S8LP_Modbus_api(S8LP_Modbus_api* S8LP_Modbus_api)
		: m_sensor{S8LP_Modbus_api} {};
	bool test_status(const std::string& str)
	{
		return m_sensor->processStatus(str);
	}
	uint16_t test_value(const std::string& str)
	{
		return m_sensor->processValue(str);
	}
	~friend_S8LP_Modbus_api(){};

  private:
	S8LP_Modbus_api* m_sensor;
};
#endif

#endif /* MAIN_COMPONENTS_S8LP_API_INCLUDE_S8LP_MODBUS_API_HPP_ */
