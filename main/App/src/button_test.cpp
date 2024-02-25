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
 *  \file       button_test.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/button_test.hpp"
#include <HAL_GPIO_ESP32.hpp>
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "button_test";
#endif

button_test::button_test()
{

}

button_test::~button_test()
{

}

static bool button_pressed = false;

void button_test::cb_button_pressed(void *orb)
{
    button_pressed = true;
}

void button_test::run()
{
    std::cout << "This is the button test" << std::endl;
    std::cout << "Press the button to see the result" << std::endl;
    // Create a button object
    Button<HAL_GPIO_ESP32> m_button(gpio_num_t::GPIO_NUM_21);
    // Install the interrupt
    m_button.installInterrupt(HAL_GPIO_ESP32::io_intr_t::FALLING_EDGE, &button_test::cb_button_pressed);
    while(1)
    {
        
 
        if(button_pressed)
        {
            m_button.disableInterrupt();
            button_pressed = false;
            std::cout << "Button pressed" << std::endl;    
            m_button.enableInterrupt();        
        }
        Timeservice::wait_ms(50);
    }
}