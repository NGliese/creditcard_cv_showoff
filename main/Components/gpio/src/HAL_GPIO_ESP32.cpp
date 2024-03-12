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
 *  \file       HAL_GPIO_ESP32.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2023
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/HAL_GPIO_ESP32.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "HAL_GPIO_ESP32";
#endif

HAL_GPIO_ESP32::~HAL_GPIO_ESP32() {}

bool HAL_GPIO_ESP32::setDirection(const HAL_BASE<gpio_num_t>::io_def_t& dir) {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "setDirection");
#endif
#ifdef __ESP32__
  // set the direction
  if (!gpio_set_direction(getPin(),
                          dir == HAL_BASE<gpio_num_t>::io_def_t::OUTPUT
                              ? GPIO_MODE_OUTPUT
                              : GPIO_MODE_INPUT) == ESP_OK) {
    return false;
  }
  // set pulldown if dir is input
  if (dir == HAL_BASE<gpio_num_t>::io_def_t::INPUT) {
    if (!gpio_set_pull_mode(getPin(), GPIO_PULLDOWN_ONLY) == ESP_OK) {
      return false;
    }
  }
#endif
  return true;
}

bool HAL_GPIO_ESP32::setValue(const HAL_BASE<gpio_num_t>::io_val_t& val) {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "setValue");
#endif
#ifdef __ESP32__
  if (gpio_set_level(getPin(), val == HAL_BASE<gpio_num_t>::io_val_t::HIGH
                                   ? true
                                   : false) == ESP_OK) {
    return true;
  }

#endif
  return false;
}

HAL_BASE<gpio_num_t>::io_val_t HAL_GPIO_ESP32::getValue() const {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "getValue");
#endif
#ifdef __ESP32__
  return gpio_get_level(getPin()) == 1 ? HAL_BASE<gpio_num_t>::io_val_t::HIGH
                                       : HAL_BASE<gpio_num_t>::io_val_t::LOW;
#endif
  return HAL_BASE<gpio_num_t>::io_val_t::LOW;
}

bool HAL_GPIO_ESP32::installInterruptDriver(
    void (*callbackfunction)(void*),
    const HAL_BASE<gpio_num_t>::io_intr_t& intr) {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "installInterruptDriver");
#endif

#ifdef __ESP32__
  switch (intr) {
    case HAL_BASE<gpio_num_t>::io_intr_t::ANY_EDGE:
      gpio_set_intr_type(getPin(), GPIO_INTR_ANYEDGE);
      break;
    case HAL_BASE<gpio_num_t>::io_intr_t::FALLING_EDGE:
      gpio_set_intr_type(getPin(), GPIO_INTR_NEGEDGE);
      break;
    case HAL_BASE<gpio_num_t>::io_intr_t::RISING_EDGE:
      gpio_set_intr_type(getPin(), GPIO_INTR_POSEDGE);
      break;
    default:
      return false;
  }

  // install gpio isr service
  gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);  // Todo
  // hook isr handler for specific gpio pin
  gpio_isr_handler_add(getPin(), callbackfunction, NULL);
#endif

  return true;
}

bool HAL_GPIO_ESP32::enableInterrupt() {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "enableInterrupt");
#endif
#ifdef __ESP32__
  return gpio_intr_enable(getPin()) == ESP_OK
             ? true
             : false;  // Enable the pin for interrupts
#endif
  return false;
}

bool HAL_GPIO_ESP32::disableInterrupt() {
#ifdef DEBUG
  ESP_LOGI(LOG_TAG, "disableInterrupt");
#endif
#ifdef __ESP32__
  return gpio_intr_disable(getPin()) == ESP_OK
             ? true
             : false;  // disable the pin for interrupts
#endif
  return false;
}
