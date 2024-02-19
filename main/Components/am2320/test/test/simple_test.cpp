/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */

#include "../../include/AM2320_Base.hpp"
#include "../../include/AM2320_Temperature.hpp"

#include "../../include/AM2320_Humidity.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"

class AM2320_MOCK : public AM2320_Base
{
  public:
	AM2320_MOCK() : AM2320_Base({5000, 21, 22}, 0x5c){};
	~AM2320_MOCK(){};

  private:
	uint16_t getRaw() override
	{
		return 10;
	}
};

TEST_GROUP(AM2320_GRP)
{
	AM2320_Temperature m_temp_sensor{{5000, 21, 22}};
	friend_AM2320_Temperature m_temp_friend{&m_temp_sensor};

	AM2320_Humidity m_hum_sensor{{5000, 21, 22}};
	friend_AM2320_Humidity m_hum_friend{&m_hum_sensor};
	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(AM2320_GRP, init)
{
	AM2320_MOCK m_sensor;
	CHECK(true);
}

// test init
TEST(AM2320_GRP, getMeasurement)
{
	AM2320_MOCK m_sensor;
	LONGS_EQUAL(10, m_sensor.getMeasurement());
}

// test init
TEST(AM2320_GRP, init_temp)
{
	AM2320_Temperature m_sensor{{5000, 21, 22}};
	friend_AM2320_Temperature m_friend{&m_sensor};
	CHECK(true);
}
