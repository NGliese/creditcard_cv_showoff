#ifndef main_Components_CO2Sensor_include_s8lp_sensor_hpp
#define main_Components_CO2Sensor_include_s8lp_sensor_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  s8lp_sensor.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, s8lp_sensor.hpp, is designed as:
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

/*-----------------------------------------------------------------------------*/

#include <iostream>
#include "../../Components/Timeservice/include/Timeservice.hpp"
#include "../../Components/uart/include/uart_hal.hpp"
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


class s8lp_sensor {

      public:
      s8lp_sensor(void);
      virtual ~s8lp_sensor(void);

      bool initialize(void);
      bool measure(uint16_t& co2_level);
      private:
      bool read_co2_level(uint16_t& co2_level);
      bool read_status(void);

      bool process_status(uint8_t* data,const size_t size);
      
      
      };

#endif /*main_Components_CO2Sensor_include_s8lp_sensor_hpp*/