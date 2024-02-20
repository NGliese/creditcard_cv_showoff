#ifndef main_Components_GPIO_include_HAL_GPIO_ESP32_hpp
#define main_Components_GPIO_include_HAL_GPIO_ESP32_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  HAL_GPIO_ESP32.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, HAL_GPIO_ESP32.hpp, is designed as:
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
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/

/*-----------------------------------------------------------------------------*/

#include <iostream>

#include "HAL_BASE.hpp"
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/
#ifdef __ESP32__
#include <driver/gpio.h>
#else
typedef int gpio_num_t;
#endif
/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


class HAL_GPIO_ESP32 final : public HAL_BASE<gpio_num_t>{

    public:
        HAL_GPIO_ESP32(const gpio_num_t& pin) : HAL_BASE<gpio_num_t>(pin) {
            std::cout << "HAL_GPIO_ESP32: " << pin << std::endl;
        };
        HAL_GPIO_ESP32(const HAL_GPIO_ESP32& other) = delete; // delete copy constructor
        virtual ~HAL_GPIO_ESP32(void);      
        bool setDirection(const HAL_BASE<gpio_num_t>::io_def_t& dir)  override;
        bool setValue(const HAL_BASE<gpio_num_t>::io_val_t& val) override;
        HAL_BASE<gpio_num_t>::io_val_t getValue() const  override;
        bool installInterruptDriver(void (*callbackfunction)(void*),
                                            const HAL_BASE<gpio_num_t>::io_intr_t& intr) override;
        bool enableInterrupt() override;
        bool disableInterrupt() override;
      };

#endif /*main_Components_GPIO_include_HAL_GPIO_ESP32_hpp*/