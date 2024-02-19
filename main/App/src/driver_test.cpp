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
 *  \file       driver_test.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/driver_test.hpp"

#include "../../Components/Timeservice/include/Timeservice.hpp"
#include "../../Components/uart/include/uart_hal.hpp"
#include "../../Components/CO2Sensor/include/s8lp_sensor.hpp"
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "driver_test";
#endif

driver_test::driver_test()
{

}

driver_test::~driver_test()
{

}

bool driver_test::run_uart_write()
{
#ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> driver_test::run >> ");
#endif

    // Executable code:
    uart_hal uart;
    uart.initialize();
    uart.open();
    while(1)
    {
        std::cout << "Uart test: ... " << std::endl;
        // initialize
        uint8_t data[] = {0xde, 0xad, 0xbe, 0xef};
        // write
        uart.write(data, sizeof(data));
        // sleep for 1 sec
        Timeservice::wait_sec(1);
    }
    uart.close();

}

bool driver_test::run_uart_write_read()
{
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> driver_test::run >> ");
#endif

    // Executable code:
    uart_hal uart;
    uart.initialize();
    uart.open();
    while(1)
    {
        std::cout << "Uart test: ... " << std::endl;
        // initialize
        uint8_t data[] = {0xde, 0xad, 0xbe, 0xef};
        // write
        uart.write(data, sizeof(data));
        // read
        uint8_t data_read[4];
        uart.read(data_read, sizeof(data_read));
        // print
        std::cout << "data read: " << std::endl;
        for (size_t i = 0; i < sizeof(data_read); i++)
        {
            std::cout << "data_read[" << i << "]: " << std::hex << (int)data_read[i] << std::endl;
        }
        

        // sleep for 1 sec
        Timeservice::wait_sec(1);
    }
    uart.close();

}
constexpr uint8_t ANY_ADDRESS = 0xFE;
constexpr uint8_t READ_INPUT_REGISTER = 0x04;
constexpr uint8_t INPUT_REGISTER1_ADDRESS_HIGH = 0x00;
constexpr uint8_t INPUT_REGISTER1_ADDRESS_LOW = 0x00;
constexpr uint8_t INPUT_REGISTER3_ADDRESS_HIGH = 0x00;
constexpr uint8_t INPUT_REGISTER3_ADDRESS_LOW = 0x03;
constexpr uint8_t READ_LENGTH_HIGH = 0x00;
constexpr uint8_t READ_LENGTH_LOW = 0x01;
constexpr uint8_t CRC_CONST_STATUS_HIGH = 0x25;
constexpr uint8_t CRC_CONST_STATUS_LOW = 0xC5;
constexpr uint8_t CRC_CONST_CO2_LEVEL_HIGH = 0xD5;
constexpr uint8_t CRC_CONST_CO2_LEVEL_LOW = 0xC5;
constexpr uint8_t EXPECTED_SIZE = (7);
constexpr uint8_t ERROR_STATUS_REGISTER = (4);

bool driver_test::run_uart_write_read_s8lp()
{

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> driver_test::run >> ");
#endif

    // Executable code:
    uart_hal uart;
    uart.initialize();
     uart.open();
    while(1)
    {
       
        std::cout << "Uart test: ... " << std::endl;
        // initialize
        uint8_t write_array[8] = {ANY_ADDRESS,
		   READ_INPUT_REGISTER,
		   INPUT_REGISTER3_ADDRESS_HIGH,
		   INPUT_REGISTER3_ADDRESS_LOW,
		   READ_LENGTH_HIGH,
		   READ_LENGTH_LOW,
		   CRC_CONST_CO2_LEVEL_HIGH,
		   CRC_CONST_CO2_LEVEL_LOW};
        // write
        uart.write(write_array, sizeof(write_array));
        // read
        uint8_t data_read[EXPECTED_SIZE];
        uart.read(data_read, sizeof(data_read));
        // print
        std::cout << "data read: " << std::endl;
        for (size_t i = 0; i < sizeof(data_read); i++)
        {
            std::cout << "data_read[" << i << "]: " << std::hex << (int)data_read[i] << std::endl;
        }
        
       
        // sleep for 1 sec
        Timeservice::wait_sec(1);
    }
 uart.close();

}

bool driver_test::run_s8lp_sensor()
{
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> driver_test::run_s8lp_sensor >> ");
#endif

    s8lp_sensor s8lp;
    s8lp.initialize();

    while(1)
    {
        std::cout << "S8LP test: ... " << std::endl;

        uint16_t co2_level = 0;
        s8lp.measure(co2_level);
        // print co2 level in decimal
        std::cout << "co2_level: " << std::dec << co2_level << std::endl;
        // sleep for 1 sec
        Timeservice::wait_sec(1);

    }

}