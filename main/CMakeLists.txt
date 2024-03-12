
###############################################################################################################
#							INSTALL Library
###############################################################################################################





###############################################################################################################
set(INSTALL_PATH "${CMAKE_CURRENT_LIST_DIR}/")


###############################################################################################################
#                               Basic ESP32 setup
###############################################################################################################

idf_component_register(SRC_DIRS "."
             INCLUDE_DIRS ""   
             SRC_DIRS "./App/src"
             INCLUDE_DIRS "./App/include"
             SRC_DIRS "./Components/Timeservice/src"
             INCLUDE_DIRS "./Components/Timeservice/include"
             SRC_DIRS "./Components/gpio/src"
             INCLUDE_DIRS "./Components/gpio/include" 
             INCLUDE_DIRS "./Components/boards/esp32_boards/include"
             SRC_DIRS "./Components/button/src"
             INCLUDE_DIRS "./Components/button/include"
                SRC_DIRS "./Components/lcd_display/src"
                INCLUDE_DIRS "./Components/lcd_display/include"
             )



###############################################################################################################
#						ADDON FOR ESP32 SPECIFIC SiP DEFINITIONS
###############################################################################################################
            
target_compile_definitions(${COMPONENT_LIB} PRIVATE
__ESP32__=1
)
