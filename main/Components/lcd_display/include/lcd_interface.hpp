#ifndef main_Components_lcd_display_include_lcd_interface_hpp
#define main_Components_lcd_display_include_lcd_interface_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  lcd_interface.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, lcd_interface.hpp, is designed as:
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

#include "hal_base.hpp"
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

template <typename HAL = hal_base>
class lcd_interface {
 public:
  lcd_interface(void) {
    // initialize the hal
    std::cout << "lcd_interface::init: init called" << std::endl;
    const auto ret = m_hal.init();
    // if the hal is not initialized, write a warning
    if (!ret) {
      std::cout << "lcd_interface::init: hal init failed" << std::endl;
    }
  };
  virtual ~lcd_interface(void) {
    // deinitialize the hal
    std::cout << "lcd_interface::deinit: deinit called" << std::endl;
    const auto ret = m_hal.deinit();
    // if the hal is not deinitialized, write a warning
    if (!ret) {
      std::cout << "lcd_interface::deinit: hal deinit failed" << std::endl;
    }
  };
  bool clear() {
    // if init is not called, write a warning and return false
    if (!m_hal.is_initialized()) {
      std::cout << "lcd_interface::clear: init not called" << std::endl;
      return false;
    }
    return m_hal.clear();
  };
  bool write(const uint8_t* data, const size_t size) {
    // if init is not called, write a warning and return false
    if (!m_hal.is_initialized()) {
      std::cout << "lcd_interface::write: init not called" << std::endl;
      return false;
    }
    return m_hal.write(data, size);
  };
  bool setCursor(int x, int y) {
    // if init is not called, write a warning and return false
    if (!m_hal.is_initialized()) {
      std::cout << "lcd_interface::setCursor: init not called" << std::endl;
      return false;
    }
    return m_hal.setCursor(x, y);
  };

  bool test_display() {
    // if init is not called, write a warning and return false
    if (!m_hal.is_initialized()) {
      std::cout << "lcd_interface::test_display: init not called" << std::endl;
      return false;
    }
    return m_hal.test_display();
  };

 protected:  // for testing
  HAL m_hal;

 private:
  lcd_interface(const lcd_interface&);             // no copy
  lcd_interface& operator=(const lcd_interface&);  // no assign
};

#endif /*main_Components_lcd_display_include_lcd_interface_hpp*/