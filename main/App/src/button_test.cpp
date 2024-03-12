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
static const char *LOG_TAG = "button_test";
#endif

button_test::button_test() {}

button_test::~button_test() {}

static bool sw1_button_pressed = false;
static int sw1_button_count = 0;

static bool sw2_button_pressed = false;
static int sw2_button_count = 0;
constexpr uint64_t DEBOUNCE_TIME_MS = 250;  // ms
void button_test::cb_sw1_button_pressed(void *orb) {
  static uint64_t last_interrupt_time_sw1 = 0;
  uint64_t interrupt_time_sw1 = Timeservice::get_millis();
  if (interrupt_time_sw1 - last_interrupt_time_sw1 > DEBOUNCE_TIME_MS) {
    sw1_button_pressed = true;
    sw1_button_count++;
    last_interrupt_time_sw1 = interrupt_time_sw1;
  }
}

void button_test::cb_sw2_button_pressed(void *orb) {
  static uint64_t last_interrupt_time_sw2 = 0;
  uint64_t interrupt_time_sw2 = Timeservice::get_millis();
  if (interrupt_time_sw2 - last_interrupt_time_sw2 > DEBOUNCE_TIME_MS) {
    sw2_button_pressed = true;
    sw2_button_count++;
    last_interrupt_time_sw2 = interrupt_time_sw2;
  }
}

void button_test::run() {
  std::cout << "This is the button test" << std::endl;
  std::cout << "Press the button to see the result" << std::endl;
  // Create a button object
  Button<HAL_GPIO_ESP32> m_sw1_button(gpio_num_t::GPIO_NUM_21);
  Button<HAL_GPIO_ESP32> m_sw2_button(gpio_num_t::GPIO_NUM_22);
  // Install the interrupt
  m_sw1_button.installInterrupt(HAL_GPIO_ESP32::io_intr_t::RISING_EDGE,
                                &button_test::cb_sw1_button_pressed);
  m_sw2_button.installInterrupt(HAL_GPIO_ESP32::io_intr_t::RISING_EDGE,
                                &button_test::cb_sw2_button_pressed);
  while (1) {
    if (sw1_button_pressed) {
      m_sw1_button.disableInterrupt();
      sw1_button_pressed = false;
      std::cout << "SW1 Button pressed < " << sw1_button_count << " >"
                << std::endl;
      m_sw1_button.enableInterrupt();
    }

    if (sw2_button_pressed) {
      m_sw2_button.disableInterrupt();
      sw2_button_pressed = false;
      std::cout << "SW2 Button pressed < " << sw2_button_count << " >"
                << std::endl;
      m_sw2_button.enableInterrupt();
    }
    Timeservice::wait_ms(50);
  }
}