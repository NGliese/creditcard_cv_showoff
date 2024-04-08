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
 *  \file       Timeservice.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2023
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Timeservice.hpp"

#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#ifdef __ESP32__
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#else
#include <thread>
#endif
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "Timeservice";
#endif

void Timeservice::wait_ns(uint64_t ns) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": wait_ns" << std::endl;
#endif
#ifdef __ESP32__
  // see if ns is less than 1 ms
  if (ns < 1000000) {
    // we dont have a freertos tick less than 1 ms, therefor we use usleep
    usleep(ns / 1000);
    return;
  } else {
    // convert to ms and call wait_ms
    Timeservice::wait_ms(ns / 1000000);
  }
#else
  std::this_thread::sleep_for(std::chrono::nanoseconds(ns));
#endif
}

void Timeservice::wait_us(uint64_t us) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": wait_us" << std::endl;
#endif

#ifdef __ESP32__
  // see if us is less than 1 ms
  if (us < 1000) {
    // we dont have a freertos tick less than 1 ms, therefor we use usleep
    usleep(us);
    return;
  } else {
    // convert to ms and call wait_ms
    Timeservice::wait_ms(us / 1000);
  }
#else
  std::this_thread::sleep_for(std::chrono::microseconds(us));
#endif
}

void Timeservice::wait_ms(uint64_t ms) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": wait_ms" << std::endl;
#endif

#ifdef __ESP32__
  vTaskDelay(ms / portTICK_PERIOD_MS);
#else
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
#endif
}

void Timeservice::wait_sec(uint64_t s) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": wait_sec" << std::endl;
#endif

#ifdef __ESP32__
  // convert to ms and call wait_ms
  Timeservice::wait_ms(s * 1000);
#else
  std::this_thread::sleep_for(std::chrono::seconds(s));
#endif
}

void Timeservice::wait_min(uint64_t m) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": wait_min" << std::endl;
#endif

#ifdef __ESP32__
  // convert to ms and call wait_ms
  Timeservice::wait_ms(m * 60 * 1000);
#else
  std::this_thread::sleep_for(std::chrono::minutes(m));
#endif
}

void Timeservice::wait_hour(uint64_t h) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": wait_hour" << std::endl;
#endif

#ifdef __ESP32__
  vTaskDelay(h * 60 * 60 * 1000 / portTICK_PERIOD_MS);
#else
  std::this_thread::sleep_for(std::chrono::hours(h));
#endif
}

uint64_t Timeservice::get_millis() {
#ifdef DEBUG
  std::cout << LOG_TAG << ": get_millis" << std::endl;
#endif

#ifdef __ESP32__
  return (uint64_t)(esp_timer_get_time() / 1000);
#else
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
#endif
}