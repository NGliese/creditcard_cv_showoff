# Set the minimum required version of CMake and explicitly set the behavior.
# It is recommended to use CMake 3.17+ due to certain beneficial changes, but this script requires at least 3.14.
cmake_minimum_required(VERSION 3.18.4)

# Define the project and its properties.
project(ComponentModule
    VERSION 1.0
    DESCRIPTION "A CMake script to handle the modules in the Component folder for unit testing."
    LANGUAGES C CXX
)

# GoogleTest requires at least C++14.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: Include additional build options defined in a separate file.
# include(cmake/BuildOptions.cmake)

# Option to enable coverage reporting.
option(ENABLE_COVERAGE "Enable coverage reporting" ON)

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Check if this project is built as the main project and not as a dependency.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(WARNING "Building with testing enabled.")
    #set(BUILD_TESTING ON)

    # Include CMake's testing module.
    include(CTest)

    # If testing is enabled, disable optimizations for more accurate test coverage.
    add_compile_options("-O0")

    # Define a custom target for running tests and generating coverage reports.
    add_custom_target(simple_test
    DEPENDS ${CUSTOM_TEST_FILES} # Assuming this is a typo: COSTUM_TEST_FILES
    COMMAND ctest --output-on-failure
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage
    COMMAND lcov --capture --directory . --output-file ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/coverage.info
    COMMAND lcov --remove ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/coverage.info '/usr/*' --output-file ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/filtered.info 
    COMMAND lcov --remove ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/filtered.info '*/_deps/googletest-src/*' --output-file ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/filtered.info # remove the coverage of the googletest
    COMMAND genhtml ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/filtered.info --output-directory ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/html
)

    # Additional custom command to open coverage report in browser (uncomment if needed).
    # add_custom_command(
    #     TARGET simple_test POST_BUILD
    #     COMMAND ${CMAKE_COMMAND} -E echo "Opening coverage report in browser..."
    #     COMMAND ${CMAKE_COMMAND} -E env "BROWSER=firefox" xdg-open ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/html/index.html || open ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/html/index.html || start ${CMAKE_CURRENT_LIST_DIR}/build/reports/coverage/html/index.html
    # )

    # Add compile definitions for unit test mode.
    add_compile_definitions(__UNITTEST__=1)

    # Fetch and make available GoogleTest.
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings.
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Custom global variables for source, include, and test files.
set(CUSTOM_SRC_FILES "" CACHE STRING "Available build sources" FORCE)
set(CUSTOM_INC_FILES "" CACHE STRING "Available build includes" FORCE)
set(CUSTOM_TEST_FILES "" CACHE STRING "Available build tests" FORCE)

# Create a static library for the ComponentModule.
add_library(ComponentModule STATIC)

# Add subdirectories containing additional CMakeLists.txt.
add_subdirectory(Timeservice)
add_subdirectory(button)
add_subdirectory(gpio)
add_subdirectory(lcd_display)

# Configure the library with source and include files.
target_sources(ComponentModule PRIVATE ${CUSTOM_SRC_FILES})
target_include_directories(ComponentModule PRIVATE ${CUSTOM_INC_FILES})
