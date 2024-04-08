#ifndef main_Components_GPIO_include_HAL_MOCK_hpp
#define main_Components_GPIO_include_HAL_MOCK_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  HAL_MOCK.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, HAL_MOCK.hpp, is designed as:
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

/*----------------- DEFAULT INCLUDE
 * -------------------------------------------*/

/*-----------------------------------------------------------------------------*/

#include <iostream>

#include "HAL_BASE.hpp"
/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

class HAL_MOCK final : public HAL_BASE<int> {
 public:
  HAL_MOCK(const int& pin) : HAL_BASE<int>(pin) {
    std::cout << "HAL_MOCK: " << pin << std::endl;
  }
  HAL_MOCK(const HAL_MOCK& other) = delete;  // delete copy constructor
  ~HAL_MOCK(void);
  bool setDirection(const HAL_BASE<int>::io_def_t& dir) override;
  bool setValue(const HAL_BASE<int>::io_val_t& val) override;
  HAL_BASE<int>::io_val_t getValue() const override;
  bool installInterruptDriver(void (*callbackfunction)(void*),
                              const HAL_BASE<int>::io_intr_t& intr) override;
  bool enableInterrupt() override;
  bool disableInterrupt() override;

  // ment to be public for testing
  bool m_isInterruptEnabled_called = false;
  bool m_isInterruptInstalled_called = false;
  bool m_isDirectionSet_called = false;
  bool m_isValueSet_called = false;
};

#endif /*main_Components_GPIO_include_HAL_MOCK_hpp*/