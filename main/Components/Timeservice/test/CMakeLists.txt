#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]
cmake_minimum_required(VERSION 3.18.4)

add_executable(${LIBNAME}_tests )

set(CUSTOM_TEST_FILES ${CUSTOM_TEST_FILES} "${LIBNAME}_tests;" CACHE STRING "avaliable build tests" FORCE)


target_include_directories( ${LIBNAME}_tests PRIVATE mock test )
target_link_libraries( ${LIBNAME}_tests PRIVATE  GTest::gtest_main  ComponentModule ${CUSTOM_LIBRARIES})

# Create the test inside the test folder and rename it to "tests" for vscode to easily detect it 
set_target_properties ( ${LIBNAME}_tests  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${LIBNAME}_tests PROPERTIES OUTPUT_NAME "tests")
###############################################################
#															  #
# 					USER CHANGE START						  #
#															  #
#	In the following the user needs to specify the test files #
#	in the "target_sources(  )" command.					  #
#	example of syntax: 										  #
#       target_sources( tests PRIVATE test_main.cpp #
#       test/time_test.cpp  # <- test file					  #
#       )													  #
#															  #
###############################################################
target_sources( ${LIBNAME}_tests PRIVATE test_main.cpp
test/time_test.cpp
)
###############################################################
#															  #
#					USER CHANGE END							  #
#															  #
###############################################################

add_test(NAME ${LIBNAME}.Test
	COMMAND ${LIBNAME}_tests
)





