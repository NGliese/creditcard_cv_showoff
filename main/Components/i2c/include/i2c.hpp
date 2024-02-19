#ifndef _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_HPP_
#define _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  i2c.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-02-22
 |
 |  @brief  	   :  This class, i2c.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  @version       : 1.0
 |
 |  @bug  		   :   no known bugs
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/


#include <array>
#include <iostream>

#include "i2c_common.hpp"
/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
template<typename i2c_class>
class i2c
{
#ifdef __UNITTEST__
	friend class friend_i2c;
#endif
  public:
	/**
	 * @brief Get the Instance object
	 * 	TODO Make sure that users can re-install with new config file
	 * 		 Currently we can pnly install it once
	 * @param conf
	 * @return i2c&
	 */
	static i2c& getInstance(const i2c_conf_t& conf)
	{
		static i2c ref_to_i2c{conf};
		return ref_to_i2c;
	}
	~i2c(){};
	bool writeByte(const uint8_t& slave_address, const uint8_t& byte)
	{
		return m_hal.writeByte(slave_address, byte);
	}

	template<size_t N>
	bool writeMultiBytes(const uint8_t& slave_address, const std::array<uint8_t, N>& array)
	{
		return m_hal.writeMultiBytes(slave_address, array.data(), array.size());
	}

	template<size_t N>
	bool readMultiBytes(const uint8_t& slave_address, std::array<uint8_t, N>& array)
	{
		return m_hal.readMultiBytes(slave_address, array.data(), array.size());
	}
	template<size_t N>
	bool readMultiBytes(const uint8_t& slave_address, const uint8_t& function_code,
								 const uint8_t& register_address, std::array<uint8_t, N>& array)
	{
		return m_hal.readMultiBytes(slave_address, array.data(), array.size());
	}

	bool writeWord(const uint8_t& slave_address, const uint16_t& word)
	{
		auto arr = word2bytes(word);
		return writeMultiBytes<2>(slave_address, arr);
	}
	uint8_t readByte(const uint8_t& slave_address)
	{
		return m_hal.readByte(slave_address);
	};
	uint16_t readWord(const uint8_t& slave_address)
	{
		std::array<uint8_t, 2> arr;
		readMultiBytes<2>(slave_address, arr);
		return bytes2word(arr);
	}

	uint16_t readWord(const uint8_t& slave_address, const uint8_t& function_code,
					  const uint8_t& register_address)
	{
		std::array<uint8_t, 2> arr;
		readMultiBytes<2>(slave_address, function_code, register_address, arr);
		return bytes2word(arr);
	}
	/**
	 * @brief Scan
	 * 		Scan the whole range and print out if any device is
	 * 		attached to the i2c channel
	 *
	 */
	void scan()
	{
		printf("Data Pin: %d, Clock Pin: %d\n", m_conf.pin_sda, m_conf.pin_sclk);
		printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
		printf("00:         ");
		for(uint8_t i = 0; i < 0x78; i++)
		{
			if(i % 16 == 0)
			{
				printf("\n%.2x:", i);
			}
			if(slavePresent(i))
			{
				printf(" %.2x", i);
			}
			else
			{
				printf(" --");
			}
		}
		printf("\n");
	};
	bool slavePresent(const uint8_t& slave_address)
	{
		return m_hal.slavePresent(slave_address);
	};

  private:
	i2c(const i2c_conf_t& conf) : m_conf{conf}, m_hal{conf} {};

	std::array<uint8_t, 2> word2bytes(const uint16_t& data)
	{
		return {static_cast<uint8_t>(data >> 8 & 0xff), static_cast<uint8_t>(data & 0xff)};
	}

	uint16_t bytes2word(const std::array<uint8_t, 2>& arr)
	{
		return static_cast<uint16_t>((arr[0] * 256) + arr[1]);
	}

	i2c_conf_t m_conf;
	i2c_class m_hal;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
#include "../test/mock/i2c_mock.hpp"
class friend_i2c
{
  public:
	explicit friend_i2c(i2c<i2c_mock>* sensor) : m_sensor{sensor} {};
	~friend_i2c(){};
	auto& getHAL()
	{
		return m_sensor->m_hal;
	}
	auto word2bytes(uint16_t data)
	{
		return m_sensor->word2bytes(data);
	}
	auto bytes2word(const std::array<uint8_t, 2>& arr)
	{
		return m_sensor->bytes2word(arr);
	}

  private:
	i2c<i2c_mock>* m_sensor;
};
#endif

#endif //_COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_HPP_