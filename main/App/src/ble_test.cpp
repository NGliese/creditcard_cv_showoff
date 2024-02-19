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
 *  \file       ble_test.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/ble_test.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "ble_test";
#endif

ble_test::ble_test()
{

}

ble_test::~ble_test()
{

}

bool ble_test::run_test(void)
{
    #ifdef DEBUG
    ESP_LOGI(LOG_TAG, "Running test");
    #endif

    ble_server_esp32 ble;
    ble.setup_gap_default("test_device_name");

    while (1)
    {

        std::cout << "Hello World from ble test!\n";
        Timeservice::wait_sec(5);
    }
}