
#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]


cmake_minimum_required(VERSION 3.14)

project(ComponentModule
	VERSION 1.0
	DESCRIPTION "A CMakeScript to handle the modules in the Component folder. - This is only for unit testing"
	LANGUAGES C CXX)



# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include(cmake/BuildOptions.cmake)


# only use testing if we're not somebody's subproject!
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
message(WARNING "We are build with testing")
# CMake's test module
include(CTest)

# if we are testing, lets remove optimiziation
add_compile_options("-O0")

add_custom_target(simple_test
DEPENDS  ${COSTUM_TEST_FILES} # does this mean, that every test has been compiled?    
COMMAND ctest --output-on-failure --output-junit ${CMAKE_CURRENT_LIST_DIR}/build/reports/junit/test-results.xml
)

# in order to specify that the library should be running in unit test mode, we need to add the
# follwoing definitions:
# @attention this should probably be handled in a better way, now that we do not use a .hpp file to switch from one domain to another
# ToDo fix it
add_compile_definitions(	
	__UNITTEST__=1
 )


####################################################################################

###########################################################################################
#							Install CppUtest											  #	
###########################################################################################



include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# then use : target_link_libraries(run_tests PRIVATE CppUTest CppUTestExt)

####################################################################################

endif()


####################################################################################
set(COSTUM_SRC_FILES "" CACHE STRING "avaliable build src" FORCE)
set(COSTUM_INC_FILES "" CACHE STRING "avaliable build inc" FORCE)
set(COSTUM_TEST_FILES "" CACHE STRING "avaliable build tests" FORCE)

#Create a static library
add_library(ComponentModule STATIC)


################################################
## add the source folder to the cmake list:
#add_subdirectory(Timeservice)
#add_subdirectory(i2c)
#add_subdirectory(wifi)
#add_subdirectory(http)
#add_subdirectory(adc)
#add_subdirectory(am2320)
#add_subdirectory(utils)
#add_subdirectory(CO2Sensor)
#add_subdirectory(uart)
#add_subdirectory(bluetooth)
add_subdirectory(button)




################################################

target_sources(ComponentModule PRIVATE ${COSTUM_SRC_FILES} )

target_include_directories(ComponentModule PRIVATE  ${COSTUM_INC_FILES} )

####################################################################################

