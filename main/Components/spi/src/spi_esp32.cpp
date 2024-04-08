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
 *  \file       spi_esp32.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/spi_esp32.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "spi_esp32";
#endif

spi_esp32::spi_esp32(const int& sclk, const int& mosi, const int& miso, const int& cs , const uint32_t& clock_speed_hz)
{

#ifdef __ESP32__
    // initialize the spi bus
    m_spi = nullptr;
    m_devcfg = {};
    m_buscfg = {};
  // initialize the busconfig
    m_buscfg.miso_io_num = miso;
    m_buscfg.mosi_io_num = mosi;
    m_buscfg.sclk_io_num = sclk;
    m_buscfg.quadwp_io_num = -1;
    m_buscfg.quadhd_io_num = -1;
    m_buscfg.max_transfer_sz = 0;

    // initialize the device config
    m_devcfg.command_bits = 0;
    m_devcfg.address_bits = 0;
    m_devcfg.dummy_bits = 0;
    m_devcfg.mode = 0;
    m_devcfg.duty_cycle_pos = 0;
    m_devcfg.cs_ena_pretrans = 0;
    m_devcfg.cs_ena_posttrans = 0;
    m_devcfg.clock_speed_hz = clock_speed_hz; // 10MHz
    m_devcfg.spics_io_num = cs;
    m_devcfg.queue_size = 7;
#endif

}

spi_esp32::~spi_esp32()
{
    // if the spi is open, close it
    if(is_open)
    {
        close();
    }

}


bool spi_esp32::open()
{
    #ifdef __ESP32__
    esp_err_t ret;
    //Initialize the SPI bus
    std::cout << "initializing the buss ... \n";
    ret = spi_bus_initialize(SPI2_HOST, &m_buscfg, 1);
    ESP_ERROR_CHECK(ret);
    std::cout << "adding the device ... \n";

    // attach the spi device
    ret = spi_bus_add_device(SPI2_HOST, &m_devcfg, &m_spi);
    ESP_ERROR_CHECK(ret);

    std::cout << " spi init complete ...! \n";
    #endif
    is_open = true;
    return true;
}

bool spi_esp32::close()
{
    #ifdef __ESP32__
    esp_err_t ret;
    ret = spi_bus_remove_device(m_spi);
    ESP_ERROR_CHECK(ret);

    ret = spi_bus_free(SPI2_HOST);
    ESP_ERROR_CHECK(ret);
    #endif
    is_open = false;
    return true;
}

bool spi_esp32::write(const uint8_t* data, size_t len)
{
    #ifdef __ESP32__
        esp_err_t ret;
        spi_transaction_t t;
        if (len == 0) {
        return true;    //no need to send anything
        }
        std::memset(&t, 0, sizeof(t));       //Zero out the transaction
        t.length = len * 8;             //Len is in bytes, transaction length is in bits.
        t.tx_buffer = data;             //Data
        t.user = (void*)1;              //D/C needs to be set to 1
        ret = spi_device_polling_transmit(m_spi, &t); //Transmit!
        ESP_ERROR_CHECK(ret);
    #endif
    return true;

}