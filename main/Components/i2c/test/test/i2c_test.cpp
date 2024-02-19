/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
// #include "../../include/esp32Cam.hpp" // example of include
#include <iostream>

#include "../../include/i2c.hpp"
#include "../mock/i2c_mock.hpp"

i2c_conf_t conf{50000, 5, 10};

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"

constexpr uint8_t SLAVE_ID = 0x53;

// clang-format off
TEST_GROUP(I2C_GRP){

	i2c<i2c_mock> m_i2c = i2c<i2c_mock>::getInstance(conf);
	friend_i2c m_friend{&m_i2c};

	void setup(){

	}
	void teardown(){
	// Uninit stuff
	m_friend.getHAL().reset();
	}
};
// clang-format on

// test init
TEST(I2C_GRP, init)
{
	i2c<i2c_mock> n_i2c = i2c<i2c_mock>::getInstance(conf);
	CHECK(true);
}

// test init
TEST(I2C_GRP, scan_all)
{
	m_i2c.scan();
	LONGS_EQUAL(120, m_friend.getHAL().hasBeenCalledAmount_slavePresent);
}
// test init
TEST(I2C_GRP, check_slave)
{
	m_i2c.slavePresent(SLAVE_ID);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_slavePresent);
}

// test init
TEST(I2C_GRP, write_a_byte)
{
	m_i2c.writeByte(SLAVE_ID, 0xff);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_writeByte);
}

// test init
TEST(I2C_GRP, read_a_byte)
{
	m_i2c.readByte(SLAVE_ID);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_readByte);
}

// test init
TEST(I2C_GRP, write_multi_bytes)
{
	std::array<uint8_t, 3> arr{1, 2, 3};
	m_i2c.writeMultiBytes<3>(SLAVE_ID, arr);
	size_t i = 0;
	for(auto& ele : m_friend.getHAL().data_array)
	{
		LONGS_EQUAL(ele, arr[i++]);
	}
}

// test init
TEST(I2C_GRP, array_test)
{
	std::array<uint8_t, 3> arr;
	*(arr.data() + 1) = 5;
	LONGS_EQUAL(5, arr[1]);
}

// test init
TEST(I2C_GRP, read_multi_bytes)
{
	std::array<uint8_t, 5> arr{0, 0, 0, 0, 0};
	m_i2c.readMultiBytes<5>(SLAVE_ID, arr);
	size_t i = 0;
	for(auto& ele : m_friend.getHAL().read_array)
	{
		LONGS_EQUAL(ele, arr[i++]);
	}
}

TEST(I2C_GRP, word2bytes_test)
{
	auto arr = m_friend.word2bytes(0xdead);
	LONGS_EQUAL(0xde, arr[0]);
	LONGS_EQUAL(0xad, arr[1]);
}

TEST(I2C_GRP, bytes2word_test)
{
	auto val = m_friend.bytes2word({0xde, 0xad});
	LONGS_EQUAL(0xdead, val);
}

TEST(I2C_GRP, readword_test)
{
	auto val = m_i2c.readWord(SLAVE_ID);
	LONGS_EQUAL(0x0102, val);
}
// test init
TEST(I2C_GRP, writeword_test)
{
	m_i2c.writeWord(SLAVE_ID, 0xffaa);
	std::array<uint8_t, 2> arr{0xff, 0xaa};
	size_t i = 0;
	for(auto& ele : m_friend.getHAL().data_array)
	{
		LONGS_EQUAL(ele, arr[i++]);
	}
}