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
 *  \file       ble_gap_esp32.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/ble_gap_esp32.hpp"

#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "ble_gap_esp32";
#endif

static esp_ble_adv_params_t adv_params = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    //.peer_addr            =
    //.peer_addr_type       =
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

// advertising parameters
constexpr uint8_t m_adv_config_flag = 1;
constexpr uint8_t m_scan_rsp_config_flag = 2;
static uint8_t adv_config_done = 0;


ble_gap_esp32::ble_gap_esp32()
{

}

ble_gap_esp32::~ble_gap_esp32()
{

}

bool ble_gap_esp32::setup_gap_default(const std::string &device_name)
{
    #ifdef DEBUG
    ESP_LOGI(LOG_TAG, "Setting up gap with default parameters");
    #endif
    // set device name
    if(!set_device_name(device_name))
    {
        #ifdef DEBUG
        ESP_LOGE(LOG_TAG, "Failed to set device name");
        #endif
        return false;
    }

    // register callback
    auto ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret){
        #ifdef DEBUG
        ESP_LOGE(LOG_TAG, "gap register error, error code = %x", ret);
        #endif
        return false;
    }
    
    return true;
}

bool ble_gap_esp32::set_device_name(const std::string &device_name)
{
    #ifdef DEBUG
    ESP_LOGI(LOG_TAG, "Setting device name");
    #endif
    // set device name

    esp_err_t err = esp_ble_gap_set_device_name(device_name.c_str());
    if(err != ESP_OK)
    {
        #ifdef DEBUG
        ESP_LOGE(LOG_TAG, "Failed to set device name");
        #endif
        return false;
    }
    // save device name
    m_device_name = device_name;
    return true;
}

const std::string ble_gap_esp32::get_device_name(void)
{
    #ifdef DEBUG
    ESP_LOGI(LOG_TAG, "Getting device name");
    #endif
    // get device name

    return m_device_name;
}

 void ble_gap_esp32::gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param){
    

    
    switch (event) {

    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~m_adv_config_flag);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
        adv_config_done &= (~m_scan_rsp_config_flag);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&adv_params);
        }
        break;

    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {            
            ESP_LOGE(LOG_TAG, "Advertising start failed\n");            
        }
        break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(LOG_TAG, "Advertising stop failed\n");
        } else {
            ESP_LOGI(LOG_TAG, "Stop adv successfully\n");
        }
        break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
         ESP_LOGI(LOG_TAG, "update connection params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
        break;
    default:
        break;
    }
 }