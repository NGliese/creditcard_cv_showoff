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
 *  \file       moist_sensor.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2023
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/moist_sensor.hpp"
#include "../../Components/adc/include/ADC_API_ESP32.hpp"
#include "../../Components/Timeservice/include/Timeservice.hpp"
#include "../../Components/wifi/include/WiFi_SAL_esp32.hpp"
#include "../../Components/http/include/esp32_http_sal.hpp"
#include "../../Components/boards/esp32_boards/include/esp32_i2c_adc_battery_v1_0.hpp"
#include "esp_sleep.h"


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "moist_sensor";
#endif

moist_sensor::moist_sensor()
{

}

moist_sensor::~moist_sensor()
{

}


static void deep_sleep_task(void *args)
{
    // create the wifi object
    auto wifi = WiFi_SAL_esp32("Drone01", "14Louise");
    // connect to the wifi
    wifi.connect();
    auto SERVER = "192.168.0.189";
    auto PORT = 1880;
    auto HTTP_POST = "/esp32_tree_moist_value";
    auto http = esp32_http_sal(SERVER,PORT);
    // create the adc object
    ADC_API_ESP32::config conf{"adc_test",64,esp32_i2c_adc_battery_v1_0::ADC_SENSOR};
    ADC_API_ESP32 adc{conf};
    // measure the value
    auto value = adc.measureValue();
    // print the value
    std::cout << "value: " << value << std::endl;
    // send the value to the server
    http.post(HTTP_POST, esp32_http_sal::content_type::TEXT,std::to_string(value));
    // wait 1 sec
    //Timeservice::wait_sec(1);
    // instead of wait 1 sec, i want the esp32 to go to sleep for 5 min
    // and then wake up and measure again
    // i need to use the esp32 deep sleep mode
    // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html

    wifi.disconnect();
    // enter deep sleep
    esp_deep_sleep_start();
}



bool moist_sensor::run()
{
    auto sleep_min = 15;
    esp_sleep_enable_timer_wakeup(sleep_min * 60 * 1000000);   
    xTaskCreate(deep_sleep_task, "deep_sleep_task", 4096, NULL, 6, NULL);
    return true;
}