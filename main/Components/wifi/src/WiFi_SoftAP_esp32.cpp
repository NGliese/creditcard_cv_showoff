/***********************************************************************************************+
 *  \brief      BRIEF TEXT
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       WiFi_SoftAP_esp32.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/WiFi_SoftAP_esp32.hpp"

//#define DEBUG // default uncommeted


static const char* LOG_TAG = "WiFi_SoftAP_esp32";


WiFi_SoftAP_esp32::WiFi_SoftAP_esp32(const std::string& ssid, const std::string& pwd) : WiFiBase(ssid, pwd)
{
#ifdef __ESP32__
	// Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
#endif
}

WiFi_SoftAP_esp32::~WiFi_SoftAP_esp32()
{

}

void WiFi_SoftAP_esp32::event_handler(void* arg, esp_event_base_t event_base, int32_t event_id,
								   void* event_data)
{
    #ifdef __ESP32__
if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *) event_data;
       // std::cout<< "Log_Tag :" << LOG_TAG << " Station " << event->mac << " joined, AID=" << event->aid << std::endl;

    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *) event_data;
        //std::cout<< "Log_Tag :" << LOG_TAG << " Station " << event->mac << " left, AID=" << event->aid << std::endl;

    } else if (event_base == IP_EVENT && event_id == IP_EVENT_AP_STAIPASSIGNED) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        //std::cout<< "Log_Tag :" << LOG_TAG << " assigned ip:" << event->ip_info.ip << std::endl;
    }
    #endif
}


/* Initialize soft AP */
esp_netif_t * WiFi_SoftAP_esp32::wifi_init_softap(void)
{
    // Initialize the tcp/ip adapter
    esp_netif_t *esp_netif_ap= nullptr;
    #ifdef __ESP32__
     esp_netif_ap = esp_netif_create_default_wifi_ap();

     wifi_config_t wifi_config{};
    // Set the wifi configuration
    
	::memcpy(wifi_config.ap.ssid, m_ssid.data(), m_ssid.size());
	::memcpy(wifi_config.ap.password, m_pwd.data(), m_pwd.size());
    wifi_config.ap.channel = 5;
    wifi_config.ap.max_connection = 10;
    wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
    wifi_config.ap.pmf_cfg.required = false;

    if (strlen(m_pwd.c_str()) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    std::cout << "wifi_init_softap finished. SSID:" << m_ssid.c_str() << " password:" << m_pwd.c_str() << " channel:" << 0 << std::endl;

    #endif
    return esp_netif_ap;
}

bool WiFi_SoftAP_esp32::connect(void)
{
    // Initialize the wifi
    #ifdef __ESP32__
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
     /* Register Event handler */
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                    ESP_EVENT_ANY_ID,
                    &event_handler,
                    NULL,
                    NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                    IP_EVENT_STA_GOT_IP,
                    &event_handler,
                    NULL,
                    NULL));

    /*Initialize WiFi */

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    #endif

    m_esp_netif_ap = wifi_init_softap();
    // check for nullptr
    if(m_esp_netif_ap == nullptr)
    {
        return false;
    }

    // Start the wifi
    #ifdef __ESP32__ 
    ESP_ERROR_CHECK(esp_wifi_start() );
    #endif

       /* Enable napt on the AP netif */
    #ifdef __ESP32__
    if (esp_netif_napt_enable(m_esp_netif_ap) != ESP_OK) {
        std::cout << "NAPT not enabled on the netif: " << m_esp_netif_ap << std::endl;
    }
    #endif
    // Executable code:
    return true;
}

bool WiFi_SoftAP_esp32::disconnect(void)
{
    	// disconnect from the wifi
#ifdef __ESP32__
	ESP_ERROR_CHECK(esp_wifi_stop());
	ESP_ERROR_CHECK(esp_wifi_deinit());
	ESP_ERROR_CHECK(esp_event_loop_delete_default());
#endif
    // Executable code:
    return true;
}