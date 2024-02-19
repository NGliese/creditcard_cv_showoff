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
 *  \file       AM2320_Base.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2022
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/AM2320_Base.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "AM2320_Base";
#endif

AM2320_Base::AM2320_Base(const i2c_conf_t& conf, const uint8_t& slaveaddress)
	: m_i2c{i2c<i2c_esp32>::getInstance(conf)}, m_address{slaveaddress}
{
}

AM2320_Base::~AM2320_Base() {}

bool AM2320_Base::wakeUp()
{
#ifdef DEBUG
	std::cout << " >> AM2320_Base::wakeUp >> \n";
#endif
	// do magic
	constexpr uint8_t MAX_TRIES = 5;
	constexpr uint8_t DELAY_100ms = 100;
	uint8_t count = 0;
	bool res = false;

	do
	{
		res = m_i2c.slavePresent(m_address);
		Timeservice::wait_ms(DELAY_100ms);

	} while(!res and (++count) < MAX_TRIES);

#ifdef DEBUG
	std::cout << " << AM2320_Base::wakeUp << \n";
#endif

	return true;
}

uint16_t AM2320_Base::getMeasurement()
{
#ifdef DEBUG
	std::cout << " >> AM2320_Base::getMeasurement >> \n";
#endif
	if(!wakeUp())
	{
		std::cout << " could not wake up the sensor ... \n";
		return 0;
	}
	auto val = getRaw();

	return val;

#ifdef DEBUG
	std::cout << " << AM2320_Base::getMeasurement << \n";
#endif

	return 0;
}

uint16_t AM2320_Base::getSensorValue(const uint8_t& register_address)
{
#ifdef DEBUG
	std::cout << " >> AM2320_Base::getSensorValue >> \n";
#endif
	// do magic
	m_i2c.writeMultiBytes<3>(m_address, {0x03, register_address, 2});
	Timeservice::wait_ms(10);
	std::array<uint8_t, 5> vec;
	m_i2c.readMultiBytes<5>(m_address, vec);

#ifdef DEBUG
	std::cout << " << AM2320_Base::getSensorValue << \n";
#endif

	return basic_utils::shift8BitTo16(vec.at(2), vec.at(3));
}