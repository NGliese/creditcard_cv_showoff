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
 *  \file       co2sensor_test.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/co2sensor_test.hpp"
#include "../../Components/Timeservice/include/Timeservice.hpp"

#include "../../Components/CO2Sensor/include/s8lp_sensor.hpp"

#include "../../Components/am2320/include/AM2320_Humidity.hpp"
#include "../../Components/am2320/include/AM2320_Temperature.hpp"

#include "../../Components/boards/esp32_boards/include/esp32_env_v1_0.hpp"


#include "../../Components/wifi/include/WiFi_SAL_esp32.hpp"
#include "../../Components/http/include/esp32_http_sal.hpp"
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "co2sensor_test";
#endif

co2sensor_test::co2sensor_test()
{

}

co2sensor_test::~co2sensor_test()
{

}

bool co2sensor_test::run()
{
#ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> co2sensor_test::run >> ");
#endif
    
    // Executable code:
    s8lp_sensor s8lp;
    s8lp.initialize();
    i2c_conf_t conf{ 100000, esp32_env_v1_0::I2C_SDA, esp32_env_v1_0::I2C_SCLK };
    AM2320_Temperature temp = AM2320_Temperature(conf);
    AM2320_Humidity hum = AM2320_Humidity(conf);
    // setup wifi
        // create the wifi object
    //auto wifi = WiFi_SAL_esp32("Drone01", "14Louise");
    auto wifi = WiFi_SAL_esp32("manufacturing_IQ", "open_solutions_143");

    // connect to the wifi
    wifi.connect();
    auto SERVER = "192.168.0.10";
    auto PORT = 1880;
    auto HTTP_POST_HUM = "/esp32_humidity_value";
    auto HTTP_POST_TEMP = "/esp32_temperature_value";
    auto HTTP_POST_CO2 = "/esp32_co2_value";

    auto http = esp32_http_sal(SERVER,PORT);
        // run
        while(1)
        {
            // read
            std::cout << "S8LP test: ... " << std::endl;

            uint16_t co2_level = 0;
            uint16_t temp_level = 0;
            uint16_t hum_level = 0;
            s8lp.measure(co2_level);
            temp_level = temp.getMeasurement();
            hum_level = hum.getMeasurement();
            // print co2 level in decimal
            std::cout << "co2_level: " << std::dec << co2_level << std::endl;
            std::cout << "Temperature: " << temp_level/10 << " C\n";
            std::cout << "Humidity: " << hum_level/10 << " %\n";

            // upload to cloud
            http.post(HTTP_POST_HUM, esp32_http_sal::content_type::TEXT,std::to_string(hum_level/10));
            http.post(HTTP_POST_TEMP, esp32_http_sal::content_type::TEXT,std::to_string(temp_level/10));
            http.post(HTTP_POST_CO2, esp32_http_sal::content_type::TEXT,std::to_string(co2_level));

            // sleep for 1 sec
            Timeservice::wait_sec(10);
        }
        return true;
}