#ifndef main_Components_wifi_include_WiFi_SoftAP_esp32_hpp
#define main_Components_wifi_include_WiFi_SoftAP_esp32_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  WiFi_SoftAP_esp32.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, WiFi_SoftAP_esp32.hpp, is designed as:
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

#include "WiFiBase.hpp"
#include "../../Timeservice/include/Timeservice.hpp"
/*----------------- DEFAULT INCLUDE -------------------------------------------*/

/*-----------------------------------------------------------------------------*/

#include <iostream>
#include <cstring>

#ifdef __ESP32__
#include "esp_wifi.h"
#include "esp_netif.h"

#include "nvs_flash.h"


#include "esp_mac.h"
#include "esp_netif_net_stack.h"
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/
#ifndef __ESP32__
#define esp_netif_t int
#define esp_event_base_t int
#endif
/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


class WiFi_SoftAP_esp32 : public WiFiBase{

      public:
      WiFi_SoftAP_esp32(const std::string& ssid, const std::string& pwd);
      virtual ~WiFi_SoftAP_esp32(void);
        bool connect(void) override;
        bool disconnect(void) override; 
      private:
       esp_netif_t *wifi_init_softap(void);

	    static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id,
							  void* event_data);

       // variables
        esp_netif_t *m_esp_netif_ap;
      };

#endif /*main_Components_wifi_include_WiFi_SoftAP_esp32_hpp*/