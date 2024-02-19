#ifndef main_Components_bluetooth_include_ble_server_esp32_hpp
#define main_Components_bluetooth_include_ble_server_esp32_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  ble_server_esp32.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, ble_server_esp32.hpp, is designed as:
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

#include "ble_gap_esp32.hpp"

#include <esp_system.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <esp_bt.h>

#include <esp_gap_ble_api.h>
#include <esp_gatts_api.h>
#include <esp_bt_defs.h>
#include <esp_bt_main.h>
#include <esp_gatt_common_api.h>


/*----------------- DEFAULT INCLUDE -------------------------------------------*/

/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


class ble_server_esp32 {

      public:
      ble_server_esp32(void);
      virtual ~ble_server_esp32(void);
      bool setup_gap_default(const std::string &device_name);

      private:
      ble_gap_esp32 m_gap;
      };

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#endif /*main_Components_bluetooth_include_ble_server_esp32_hpp*/