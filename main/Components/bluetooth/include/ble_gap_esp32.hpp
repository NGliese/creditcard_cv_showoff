#ifndef main_Components_bluetooth_include_ble_gap_esp32_hpp
#define main_Components_bluetooth_include_ble_gap_esp32_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  ble_gap_esp32.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, ble_gap_esp32.hpp, is designed as:
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


#ifndef __ESP32__
typedef int esp_gap_ble_cb_event_t
typedef int esp_ble_gap_cb_param_t
#endif

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


class ble_gap_esp32 {
      public:
      ble_gap_esp32(void);
      virtual ~ble_gap_esp32(void);
      bool setup_gap_default(const std::string &device_name);
      bool set_device_name(const std::string &device_name);
      const std::string get_device_name(void);
      private:
      static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
      std::string m_device_name;

      };


#endif /*main_Components_bluetooth_include_ble_gap_esp32_hpp*/