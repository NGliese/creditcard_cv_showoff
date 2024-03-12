/*
 * GPIO_API.hpp
 *
 *  Created on: Jan 5, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_GPIO_INCLUDE_GPIO_API_HPP_
#define MAIN_COMPONENTS_GPIO_INCLUDE_GPIO_API_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  GPIO_API.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, GPIO_API.hpp, is designed as:
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
 |   		 					Datasheet Awareness
 |
 +------------------------------------------------------------------------------+
 |
 |
 |  Datasheet Awareness 1):
 |  	Link:[ ], Jan 5, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jan 5, 2021
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes |
 +------------------------------------------------------------------------------*/

#include "HAL_BASE.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/
template <typename HAL = HAL_BASE<int>>
class GPIO_API {
 public:
  GPIO_API(const typename HAL::pin& pin) : m_hal{pin} {};
  ~GPIO_API(){};
  /**
   * @brief  toggle the pin
   */
  inline void toggle() { isHigh() == true ? setLow() : setHigh(); }
  /**
   * @brief  set the pin to input
   */
  bool setToInput() {
    // Executable code:
    return m_hal.setDirection(HAL::io_def_t::INPUT);
  };
  /**
   * @brief  set the pin to output
   */
  bool setToOutput() {
    // Executable code:
    return m_hal.setDirection(HAL::io_def_t::OUTPUT);
  };
  /**
   * @brief  set the pin to high
   */
  bool setHigh() { return m_hal.setValue(HAL::io_val_t::HIGH); };
  /**
   * @brief  set the pin to low
   */
  bool setLow() {
    // Executable code:
    return m_hal.setValue(HAL::io_val_t::LOW);
  };
  /**
   * @brief  get the pin value
   */
  bool isHigh() const { return m_hal.getValue() == HAL::io_val_t::HIGH; };
  /**
   * @brief  get the pin value
   */
  bool isLow() const { return m_hal.getValue() == HAL::io_val_t::LOW; };
  /**
   * @brief  install the interrupt
   */
  bool installInterrupt(const typename HAL::io_intr_t& type,
                        void (*callbackfunction)(void*)) {
    return m_hal.installInterruptDriver(callbackfunction, type);
  };
  /**
   * @brief  enable the interrupt
   */
  bool enableInterrupt(void) { return m_hal.enableInterrupt(); };
  /**
   * @brief  disable the interrupt
   */
  bool disableInterrupt(void) { return m_hal.disableInterrupt(); };

 protected:
  HAL m_hal;
};

#endif /* MAIN_COMPONENTS_GPIO_INCLUDE_GPIO_API_HPP_ */
