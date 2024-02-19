#ifndef _COMPONENTS_PROTOCOLS_I2C_TEST_MOCK_I2C_MOCK_HPP_
#define _COMPONENTS_PROTOCOLS_I2C_TEST_MOCK_I2C_MOCK_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  i2c_mock.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-04-07
 |
 |  @brief  	   :  This class, i2c_mock.hpp, is designed as:
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


#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

#include "../../include/i2c_common.hpp"
#include <vector>
#include <array>
/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class i2c_mock
{
#ifdef __UNITTEST__
	friend class friend_i2c_mock;
#endif
  public:
	i2c_mock(const i2c_conf_t& conf){};
	~i2c_mock(){};
	bool slavePresent(uint8_t address)
	{
		hasBeenCalledAmount_slavePresent++;
		return true;
	};

	bool writeByte(const uint8_t& slave_address, const uint8_t& byte)
	{
		hasBeenCalledAmount_writeByte++;
		return true;
	};
	bool writeMultiBytes(const uint8_t& slave_address, const uint8_t* data,
								  const size_t& length)
	{
		for(size_t i = 0; i < length; ++i)
		{
			data_array.push_back(*(data + i));
		}
		return true;
	}
	bool writeWord(const uint8_t& slave_address, const uint16_t& word)
	{
		hasBeenCalledAmount_writeWord++;

		return true;
	};
	uint8_t readByte(const uint8_t& slave_address)
	{
		hasBeenCalledAmount_readByte++;
		return 0xfa;
	}
	bool readMultiBytes(const uint8_t& slave_address, uint8_t* data, const size_t& length)
	{
		std::cout << "length is <" << (int)length << "> \n";
		for(size_t i = 0; i < length; ++i)
		{
			*(data + i) = read_array[i];
		}
		return true;
	}
	uint16_t readWord(const uint8_t& slave_address)
	{
		hasBeenCalledAmount_readWord++;
		return 0xfafa;
	}
	void reset()
	{
		hasBeenCalledAmount_slavePresent = 0;
		hasBeenCalledAmount_writeByte = 0;
		hasBeenCalledAmount_writeWord = 0;
		hasBeenCalledAmount_readByte = 0;
		hasBeenCalledAmount_readWord = 0;
		data_array.clear();
	}

	int hasBeenCalledAmount_slavePresent = 0;
	int hasBeenCalledAmount_writeByte = 0;
	int hasBeenCalledAmount_writeWord = 0;
	int hasBeenCalledAmount_readByte = 0;
	int hasBeenCalledAmount_readWord = 0;
	std::vector<uint8_t> data_array;
	std::array<uint8_t, 5> read_array{1, 2, 3, 4, 5};

  private:
	bool initialize_transaction()
	{
		return true;
	};
	bool execute_transaction()
	{
		return true;
	};
	bool insert_start_bit()
	{
		return true;
	};
	bool insert_stop_bit()
	{
		return true;
	};
};

#endif //_COMPONENTS_PROTOCOLS_I2C_TEST_MOCK_I2C_MOCK_HPP_