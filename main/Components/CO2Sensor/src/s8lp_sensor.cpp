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
 *  \file       s8lp_sensor.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/s8lp_sensor.hpp"

uart_hal m_uart;

// MODBUS DEFINES
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

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "s8lp_sensor";
#endif

s8lp_sensor::s8lp_sensor()
{

}

s8lp_sensor::~s8lp_sensor()
{

    m_uart.close();
}

bool s8lp_sensor::measure(uint16_t& co2_level)
{

#ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> s8lp_sensor::measure >> ");
#endif
    // read status
    /*
    if(!read_status())
    {
        std::cout << "s8lb read status failed\n";
        return false;
    }
    Timeservice::wait_ms(100);
    */
    // read co2 level
    if(!read_co2_level(co2_level))
    {
        std::cout << "s8lb read co2 level failed\n";
        return false;
    }

#ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< s8lp_sensor::measure << ");
#endif
    return true;

}

bool s8lp_sensor::initialize(void)
{
    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, ">> s8lp_sensor::initialize >> ");
    #endif

    // Executable code:
    m_uart.initialize();
    m_uart.open();
    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, "<< s8lp_sensor::initialize << ");
    #endif

    return true;
}

bool s8lp_sensor::read_co2_level(uint16_t& co2_level)
{
    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, ">> s8lp_sensor::read_co2_level >> ");
    #endif

    // Executable code:
	// pr MODBUS S8LP datasheet, page 13:
	// master transmit : FE 04 00 03 00 01 D5 C5
	
	// str = {ANY_ADDRESS,READ_INPUT_REGISTER,0x00,0x00,0x00,0x01,0x25,0xC5};
	uint8_t write_array[8] = {ANY_ADDRESS,
		   READ_INPUT_REGISTER,
		   INPUT_REGISTER3_ADDRESS_HIGH,
		   INPUT_REGISTER3_ADDRESS_LOW,
		   READ_LENGTH_HIGH,
		   READ_LENGTH_LOW,
		   CRC_CONST_CO2_LEVEL_HIGH,
		   CRC_CONST_CO2_LEVEL_LOW};

	m_uart.write(write_array,sizeof(write_array));
	

	uint8_t read_array[EXPECTED_SIZE] = {0};
	m_uart.read(read_array, EXPECTED_SIZE);

	// for each element in the str print out the hex
	std::cout << "recieved data: ";
	for(auto& element : read_array)
	{
		std::cout << std::hex << static_cast<int>(element)  << " ";
	}
	std::cout << "\n";

    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, "<< s8lp_sensor::read_co2_level << ");
    #endif
    // if the size is not as expected, then return false
    if(sizeof(read_array) != EXPECTED_SIZE)
    {
        std::cout << "s8lb mismatch in input string, expected size of " << (int)EXPECTED_SIZE
                  << " but was size of : " << sizeof(read_array) << "\n";
        return false;
    }

    // index 3 and 4 is the higher and lower byte of the co2 data
	uint8_t high = read_array[3];
	uint8_t low = read_array[4];

    co2_level = (high << 8) | low;
    // if co2 level is 0, then the sensor is not ready
    if(co2_level == 0)
    {
        std::cout << "s8lb co2 level is 0, sensor is not ready\n";
        return false;
    }

    return true;

}

bool s8lp_sensor::read_status()
{
    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, ">> s8lp_sensor::read_status >> ");
    #endif

    // Executable code:
    	// pr MODBUS S8LP datasheet, page 13:
	// master transmit : FE 04 00 00 00 01 25 C5
	
	uint8_t write_array[8] = {ANY_ADDRESS,
					 READ_INPUT_REGISTER,
					 INPUT_REGISTER1_ADDRESS_HIGH,
					 INPUT_REGISTER1_ADDRESS_LOW,
					 READ_LENGTH_HIGH,
					 READ_LENGTH_LOW,
					 CRC_CONST_STATUS_HIGH,
					 CRC_CONST_STATUS_LOW};
    m_uart.write(write_array,sizeof(write_array));

	uint8_t read_array[EXPECTED_SIZE] = {0};
	m_uart.read(read_array, EXPECTED_SIZE);

    std::cout << "recieved data: ";
	for(auto& element : read_array)
	{
		std::cout << std::hex << static_cast<int>(element)  << " ";
	}
	std::cout << "\n";
    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, "<< s8lp_sensor::read_status << ");
    #endif

    return process_status(read_array, sizeof(read_array));

}

bool s8lp_sensor::process_status(uint8_t* data,const size_t size)
{
    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, ">> s8lp_sensor::process_status >> ");
    #endif

    // Executable code:
	if(size != EXPECTED_SIZE)
	{
		std::cout << "s8lb mismatch in input string, expected size of " << (int)EXPECTED_SIZE
				  << " but was size of : " << size << "\n";
		return false;
	}

    // check if the error bit is set
    if(data[ERROR_STATUS_REGISTER] != 0)
    {
        std::cout << "s8lb error bit is set, error code: " << (int)data[ERROR_STATUS_REGISTER] << "\n";
        return false;
    }

    #ifdef DEBUG
        LOG_PRINT_INFO(LOG_TAG, "<< s8lp_sensor::process_status << ");
    #endif

    return true;

}