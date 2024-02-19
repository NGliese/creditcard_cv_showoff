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
 *  \file       HAL_MOCK.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2023
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/HAL_MOCK.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "HAL_MOCK";
#endif


HAL_MOCK::~HAL_MOCK(void)
{

}

bool HAL_MOCK::setDirection(const HAL_BASE<int>::io_def_t& dir)
{
    return false;
}

bool HAL_MOCK::setValue(const HAL_BASE<int>::io_val_t& val)
{
    return true;
}

HAL_BASE<int>::io_val_t HAL_MOCK::getValue() const
{
    return HAL_BASE<int>::io_val_t::LOW;
}

bool HAL_MOCK::installInterruptDriver(void (*callbackfunction)(void*),
                                      const HAL_BASE<int>::io_intr_t& intr)
{
    return true;
}

bool HAL_MOCK::enableInterrupt()
{
    return true;
}

bool HAL_MOCK::disableInterrupt()
{
    return true;
}