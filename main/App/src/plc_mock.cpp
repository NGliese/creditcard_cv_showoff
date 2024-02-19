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
 *  \file       plc_mock.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2023
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/plc_mock.hpp"


#include "../../Components/Timeservice/include/Timeservice.hpp"
#include "../../Components/GPIO/include/HAL_GPIO_ESP32.hpp"
#include "../../Components/GPIO/include/GPIO_API.hpp"

#include "sdkconfig.h"
#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_log.h>

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "plc_mock";
#endif

plc_mock::plc_mock()
{

}

plc_mock::~plc_mock()
{

}

bool plc_mock::run()
{
    
GPIO_API<HAL_GPIO_ESP32> ready_signal(gpio_num_t::GPIO_NUM_5);
GPIO_API<HAL_GPIO_ESP32> trigger_signal(gpio_num_t::GPIO_NUM_17);
GPIO_API<HAL_GPIO_ESP32> ok_signal(gpio_num_t::GPIO_NUM_16);
GPIO_API<HAL_GPIO_ESP32> bad_signal(gpio_num_t::GPIO_NUM_12);

// set the direction
ready_signal.setToInput();
trigger_signal.setToOutput();
ok_signal.setToInput();
bad_signal.setToInput();
// define states
enum class state_t
{
  READY,
  TRIGGER,
  OK,
  BAD
};

// define the state
state_t state = state_t::READY;


while (1)
{
  Timeservice::wait_ms(100);

  switch (state)
  {
  case state_t::READY:
    Timeservice::wait_sec(3);
    std::cout << "State: READY ... waiting for camera" << std::endl;
    if (ready_signal.isHigh())
    {     
      state = state_t::TRIGGER;
      trigger_signal.setHigh();
    }
    break;
  case state_t::TRIGGER:
  std::cout << "State: TRIGGER ... waiting for ok or bad signal" << std::endl;
    if (ok_signal.isHigh())
    {
      state = state_t::OK;
      trigger_signal.setLow();
    }
    else if (bad_signal.isHigh())
    {
      state = state_t::BAD;
      trigger_signal.setLow();
    }
    break;
  case state_t::OK:

      std::cout << "OK SIGNAL RECIEVED" << std::endl;
      state = state_t::READY;
    break;
  case state_t::BAD:
      std::cout << "BAD SIGNAL RECIEVED" << std::endl;
      state = state_t::READY;
      break;
}



}
    
        return true;
}