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
 *  \file       wifi_test.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2023
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/wifi_test.hpp"
#include "../../Components/wifi/include/WiFi_SAL_esp32.hpp"
#include "../../Components/Timeservice/include/Timeservice.hpp"
#include "../../Components/http/include/esp32_http_sal.hpp"
#include "../../Components/wifi/include/WiFi_SoftAP_esp32.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "wifi_test";
#endif

wifi_test::wifi_test()
{

}

wifi_test::~wifi_test()
{

}

bool wifi_test::run()
{
    // create the wifi object
    auto wifi = WiFi_SAL_esp32("Drone01", "14Louise");
    // connect to the wifi
    wifi.connect();
    auto SERVER = "192.168.0.189";
    auto PORT = 1880;
    auto HTTP_GET = "/esp32_simple_get_test";
    auto HTTP_POST = "/esp32_simple_post_test";
    auto http = esp32_http_sal(SERVER,PORT);
    while(1)
    {
        std::cout << "wifi status: ... " << std::endl;
        // send a get request
        std::string output;
        http.get(HTTP_GET, output);
        std::cout << "output: " << output << std::endl;
        http.post(HTTP_POST, esp32_http_sal::content_type::TEXT,"hello world");
        // sleep for 1 sec
        Timeservice::wait_sec(1);
    }
    // disconnect from the wifi
    wifi.disconnect();
  
    return true;
}

bool wifi_test::run_access_point()
{
    
    // create the wifi object
    auto wifi = WiFi_SoftAP_esp32("manufacturing_IQ", "open_solutions_143");
    // connect to the wifi
    wifi.connect();
    while (1)
    {
        std::cout << "wifi status: ... " << std::endl;
        // sleep for 1 sec
        Timeservice::wait_sec(1);
    }
    // disconnect from the wifi
    wifi.disconnect();

    return true;
    
}