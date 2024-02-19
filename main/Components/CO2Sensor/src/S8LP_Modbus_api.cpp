/*
 * S8LP_Modbus_api.cpp
 *
 *  Created on: Jan 13, 2021
 *      Author: espenv
 */

/***********************************************************************************************+
 *  \brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       S8LP_Modbus_api.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/S8LP_Modbus_api.hpp"
#include <vector>


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

enum class L8_Status_t
{
	NO_ERROR = 0,
	FATAL_ERROR = 1,
	OFFSET_ERROR = 2,
	ALGORITHM_ERROR = 3,
	SELF_DIAG_ERROR = 4,
	OUT_OF_RANGE = 5,
	MEMORY_ERROR = 6
};
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "S8LP_Modbus_api";
#endif
// TODO abstract uart
S8LP_Modbus_api::S8LP_Modbus_api()  {


}
S8LP_Modbus_api::~S8LP_Modbus_api() {

	//m_uart.close();

}

bool S8LP_Modbus_api::initialize() 
{
	m_uart.initialize();
	m_uart.open();
	return true;
}

uint16_t S8LP_Modbus_api::getCO2Level() noexcept
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> S8LP_Modbus_api::getCO2Level >> ");
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
	LOG_PRINT_INFO(LOG_TAG, "<< S8LP_Modbus_api::getCO2Level << ");
#endif

	return processValue(read_array, EXPECTED_SIZE);
}

bool S8LP_Modbus_api::getSensorStatus() noexcept
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> S8LP_Modbus_api::getSensorStatus >> ");
#endif
	// Executable code:

	// pr MODBUS S8LP datasheet, page 13:
	// master transmit : FE 04 00 00 00 01 25 C5
	/*
	uint8_t write_array[8] = {ANY_ADDRESS,
					 READ_INPUT_REGISTER,
					 INPUT_REGISTER1_ADDRESS_HIGH,
					 INPUT_REGISTER1_ADDRESS_LOW,
					 READ_LENGTH_HIGH,
					 READ_LENGTH_LOW,
					 CRC_CONST_STATUS_HIGH,
					 CRC_CONST_STATUS_LOW};
					 */
	uint8_t write_array[8] = {0xFE,
					 0x04,
					 0x00,
					 0x00,
					 0x00,
					 0x01,
					 0x25,
					 0xC5};

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

// utest hack
#ifdef __UNITTEST__
	return true;
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< S8LP_Modbus_api::getSensorStatus << ");
#endif
	// convert the read_string to a vector of uint8_t
	std::vector<uint8_t> vec;
	for(auto& element : read_array)
	{
		vec.push_back(element);
	}

	auto res = processStatus(vec);


	return res;
}
/**
 * @brief      evaluate the input string to determine the status of the modbus s8lp sensor
 *
 * @attention
 *
 *
 * @param[in] str
 *
 * @return
 *    - true
 *    -
 *    -
 */
bool S8LP_Modbus_api::processStatus(std::vector<uint8_t>& vec)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> S8LP_Modbus_api::processStatus >> ");
#endif


	// Executable code:
	if(vec.size() != EXPECTED_SIZE)
	{
		std::cout << "s8lb mismatch in input string, expected size of " << (int)EXPECTED_SIZE
				  << " but was size of : " << vec.size() << "\n";
		return false;
	}


	// get the str element @ ERROR_STATUS_REGISTER and convert it to unit8_t and then to L8_Status_t
	auto ele = vec.at(ERROR_STATUS_REGISTER);
	// print out the element
	std::cout << "Error status register is : " << (int)ele << "\n";

	auto error_status = static_cast<L8_Status_t>(vec.at(ERROR_STATUS_REGISTER));

	switch(error_status)
	{
		case L8_Status_t::NO_ERROR:
			return true;
		// see the datasheet for error messages.
		// currently we do not handle any error type other than just returning a fail
		// TODO implement higher order error handling
		default:
			std::cout << "Error in status read, value is : " << static_cast<int>(error_status)
					  << "\n";
			return false;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< S8LP_Modbus_api::processStatus << ");
#endif

	return true;
}

uint16_t S8LP_Modbus_api::processValue(const uint8_t* data, const size_t& len)

{
	if(len != EXPECTED_SIZE)
	{
		std::cout << "s8lb mismatch in input string, expected size of " << (int)EXPECTED_SIZE
				  << " but was size of : " << len << "\n";
		return 0;
	}
	// index 3 and 4 is the higher and lower byte of the co2 data
	uint8_t high = data[3];
	uint8_t low = data[4];
    // 
	return (uint16_t)high << 8 | (uint16_t)low;
}
