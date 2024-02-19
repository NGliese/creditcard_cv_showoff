
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
             SRC_DIRS "./Components/GPIO/src"
             INCLUDE_DIRS "./Components/GPIO/include"
             SRC_DIRS "./Components/i2c/src"
            INCLUDE_DIRS "./Components/i2c/include"
            SRC_DIRS "./Components/wifi/src"
            INCLUDE_DIRS "./Components/wifi/include"
            SRC_DIRS "./Components/http/src"
            INCLUDE_DIRS "./Components/http/include" 
            INCLUDE_DIRS "./Components/boards/esp32_boards/include"
            SRC_DIRS "./Components/uart/src"
            INCLUDE_DIRS "./Components/uart/include"
            SRC_DIRS "./Components/bluetooth/src"
            INCLUDE_DIRS "./Components/bluetooth/include"
            # include bluetooth api
            INCLUDE_DIRS "/home/gliese/esp-idf/components/bt/include/esp32/include"            
            INCLUDE_DIRS "/home/gliese/esp-idf/components/bt/host/bluedroid/api/include/api"
            INCLUDE_DIRS "/home/gliese/esp-idf/components/bt/host/bluedroid/common/include/common/"
             )



###############################################################################################################
#						ADDON FOR ESP32 SPECIFIC SiP DEFINITIONS
###############################################################################################################
            
target_compile_definitions(${COMPONENT_LIB} PRIVATE
__ESP32__=1
)
