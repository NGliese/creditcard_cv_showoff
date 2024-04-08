#ifndef main_Components_spi_include_spi_esp32_hpp
#define main_Components_spi_include_spi_esp32_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  spi_esp32.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, spi_esp32.hpp, is designed as:
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
#include <cstring>
#ifdef __ESP32__
#include <driver/spi_master.h>
#else 
typedef int  spi_device_handle_t;
typedef int spi_device_interface_config_t;
typedef int spi_bus_config_t;
#endif

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


class spi_esp32 {

      public:
      spi_esp32(const int& sclk, const int& mosi, const int& miso, const int& cs , const uint32_t& clock_speed_hz);
      virtual ~spi_esp32(void);
      bool open();
      bool close();
      bool write(const uint8_t* data, size_t len);
        bool read(uint8_t* data, size_t len);

        private:
        spi_device_handle_t m_spi;
        spi_device_interface_config_t m_devcfg;
        spi_bus_config_t m_buscfg;
        bool is_open;
      };

#endif /*main_Components_spi_include_spi_esp32_hpp*/