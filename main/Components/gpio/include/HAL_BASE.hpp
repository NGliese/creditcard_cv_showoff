
/*
 This is the hal base class, which is the base class for all the HALs.
*/

#ifndef MAIN_COMPONENTS_GPIO_INCLUDE_HAL_BASE_HPP_
#define MAIN_COMPONENTS_GPIO_INCLUDE_HAL_BASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  HAL_BASE.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, HAL_BASE.hpp, is designed as:
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

/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/
template <typename pin_type_t = int>
class HAL_BASE {
 public:
  typedef pin_type_t pin;

  typedef enum { INPUT = 0, OUTPUT = 1 } io_def_t;
  typedef enum { LOW = 0, HIGH = 1 } io_val_t;
  typedef enum { FALLING_EDGE = 0, RISING_EDGE, ANY_EDGE } io_intr_t;
  HAL_BASE(const pin_type_t& pin) : m_pin{pin} {};
  ~HAL_BASE(){};

  virtual bool setDirection(const HAL_BASE::io_def_t& dir) { return false; };
  virtual bool setValue(const HAL_BASE::io_val_t& val) { return false; };
  virtual HAL_BASE::io_val_t getValue() const {
    return HAL_BASE::io_val_t::LOW;
  };
  virtual bool installInterruptDriver(void (*callbackfunction)(void*),
                                      const HAL_BASE::io_intr_t& intr) {
    return false;
  };
  virtual bool enableInterrupt() { return false; };
  virtual bool disableInterrupt() { return false; };
  const pin_type_t& getPin() const { return m_pin; };

 private:
  pin_type_t m_pin;
};

#endif