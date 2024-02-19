/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */

#include <iostream>

#include "CppUTest/TestHarness.h"

#include "../../include/Timeservice.hpp"
#include <sys/time.h>

TEST_GROUP(TIME_GRP){void setup(){

} void teardown(){
	// Uninit stuff

}};


// test init
TEST(TIME_GRP, wait_sec)
{
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
	CHECK_TRUE(time_taken > 0.9);
	CHECK_TRUE(time_taken < 1.1);
	
}