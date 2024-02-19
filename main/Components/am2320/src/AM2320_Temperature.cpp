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
 *  \file       AM2320_Temperature.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2022
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/AM2320_Temperature.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "AM2320_Temperature";
#endif

uint16_t AM2320_Temperature::getRaw()
{
#ifdef DEBUG
	std::cout << " >> AM2320_Temperature::getRaw >> \n";
#endif
	// do magic
	auto val = getSensorValue(FUNCTION_CODE_TEMPERATURE);
#ifdef DEBUG
	std::cout << " << AM2320_Temperature::getRaw << \n";
#endif

	return val;
}
