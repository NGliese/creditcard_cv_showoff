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
 *  \file       lcd_mock.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2024
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/lcd_mock.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "lcd_mock";
#endif

lcd_mock::lcd_mock() {}

lcd_mock::~lcd_mock() {}

bool lcd_mock::init() {
#ifdef DEBUG
  std::cout << LOG_TAG << ": init" << std::endl;
#endif
  m_init_called = true;
  // set the init flag
  is_init = true;
  return true;
}
bool lcd_mock::deinit() {
#ifdef DEBUG
  std::cout << LOG_TAG << ": deinit" << std::endl;
#endif
  is_init = false;
  return true;
}

bool lcd_mock::clear() {
#ifdef DEBUG
  std::cout << LOG_TAG << ": clear" << std::endl;
#endif
  m_clear_called = true;
  return true;
}

bool lcd_mock::write(const uint8_t* data, const size_t size) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": write" << std::endl;
#endif
  m_data = data;
  m_write_called = true;
  return true;
}

bool lcd_mock::setCursor(int x, int y) {
#ifdef DEBUG
  std::cout << LOG_TAG << ": setCursor" << std::endl;
#endif
  m_x = x;
  m_y = y;
  m_setCursor_called = true;
  return true;
}

bool lcd_mock::test_display() {
  return true;
}
