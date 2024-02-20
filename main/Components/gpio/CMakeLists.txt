
#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]
cmake_minimum_required(VERSION 3.18.4)
set(LIBNAME gpio)

set(CUSTOM_SRC_FILES ${CUSTOM_SRC_FILES} "${CMAKE_CURRENT_LIST_DIR}/src/HAL_GPIO_ESP32.cpp;" CACHE STRING "avaliable build src" FORCE)
set(CUSTOM_SRC_FILES ${CUSTOM_SRC_FILES} "${CMAKE_CURRENT_LIST_DIR}/src/HAL_MOCK.cpp;" CACHE STRING "avaliable build src" FORCE)

set(CUSTOM_INC_FILES ${CUSTOM_INC_FILES} "${CMAKE_CURRENT_LIST_DIR}/include" CACHE STRING "avaliable build inc" FORCE)


#set(CUSTOM_SRC_FILES_SPECIFIC ${CUSTOM_SRC_FILES_SPECIFIC} "${CMAKE_CURRENT_LIST_DIR}/src/RTC_HAL.cpp;" CACHE STRING "avaliable build-test-specific src" FORCE)
#set(CUSTOM_SRC_FILES_SPECIFIC ${CUSTOM_SRC_FILES_SPECIFIC} "${CMAKE_CURRENT_LIST_DIR}/src/Timeservice.cpp;" CACHE STRING "avaliable build-test-specific src" FORCE)



if(BUILD_TESTING)
MESSAGE(WARNING "Building test for ${LIBNAME}")
## add the source folder to the cmake list:
add_subdirectory(test)
endif()