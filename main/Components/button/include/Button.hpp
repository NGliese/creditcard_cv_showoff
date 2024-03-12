#ifndef main_Components_button_include_Button_hpp
#define main_Components_button_include_Button_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Button.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Button.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes |
 +------------------------------------------------------------------------------*/

#include "../../gpio/include/GPIO_API.hpp"

/*----------------- DEFAULT INCLUDE
 * -------------------------------------------*/

/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

template <typename HAL = HAL_BASE<int>>
class Button {
 public:
  Button(const HAL::pin_type_t& pin) : m_gpio(pin) {
    // button is always input
    auto res = m_gpio.setToInput();
    if (res == false) {
      std::cout << "Button: failed to set direction to input" << std::endl;
    }
  };
  ~Button(void){};
  bool isPressed(void) { return m_gpio.isLow(); }
  bool installInterrupt(const typename HAL::io_intr_t& type,
                        void (*callbackfunction)(void*)) {
    return m_gpio.installInterrupt(type, callbackfunction);
  }
  bool enableInterrupt(void) { return m_gpio.enableInterrupt(); }
  bool disableInterrupt(void) { return m_gpio.disableInterrupt(); }

 private:
  GPIO_API<HAL> m_gpio;
};

#endif /*main_Components_button_include_Button_hpp*/