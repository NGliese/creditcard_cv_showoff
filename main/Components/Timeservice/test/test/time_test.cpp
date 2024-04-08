/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */

#include <gtest/gtest.h>
#include <sys/time.h>

#include <iostream>

#include "../../include/Timeservice.hpp"

// Include the header for the code you want to test
//#include "my_code.h"

// Write test cases
TEST(MyCodeTests, wait_1_sec) {
  // get start time
  struct timeval start, end;
  gettimeofday(&start, NULL);

  Timeservice::wait_sec(1);

  // get end time
  gettimeofday(&end, NULL);

  // get time difference
  double time_taken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e6;
  time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

  // check if time is within 10% of 1 sec
  ASSERT_TRUE(time_taken > 0.9);
  ASSERT_TRUE(time_taken < 1.1);
}

TEST(MyCodeTests, wait_10_ms) {
  // get start time
  struct timeval start, end;
  gettimeofday(&start, NULL);

  Timeservice::wait_ms(10);

  // get end time
  gettimeofday(&end, NULL);

  // get time difference
  double time_taken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e6;
  time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

  // check if time is within 10% of 1 ms
  std::cout << "time_taken: " << time_taken << std::endl;
  ASSERT_TRUE(time_taken > 0.009);
  ASSERT_TRUE(time_taken < 0.011);
}

TEST(MyCodeTests, get_millis) {
  // get start time
  auto start_time = Timeservice::get_millis();
  // wait 100 ms
  Timeservice::wait_ms(100);
  // get end time
  auto end_time = Timeservice::get_millis();

  // get time difference
  auto time_taken = end_time - start_time;
  // check if time is within 10% of 100 ms
  std::cout << "time_taken: " << time_taken << std::endl;
  ASSERT_TRUE(time_taken > 99);
  ASSERT_TRUE(time_taken < 101);
}
