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

void button_test::run()
{
    std::cout << "This is the button test" << std::endl;
    std::cout << "Press the button to see the result" << std::endl;

    // Set the GPIO pin as input

    while(1)
    {
        // Read the GPIO pin
        // If the button is pressed, print "Button pressed"
        // If the button is not pressed, print "Button not pressed"
        std::cout << "waiting 5 sec" << std::endl;
        Timeservice::wait_sec(5);
    }
}