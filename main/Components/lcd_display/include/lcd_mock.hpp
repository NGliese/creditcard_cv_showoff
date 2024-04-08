#ifndef main_Components_lcd_display_include_lcd_mock_hpp
#define main_Components_lcd_display_include_lcd_mock_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  lcd_mock.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, lcd_mock.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE
 * -------------------------------------------*/

#include "hal_base.hpp"

/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

class lcd_mock final : public hal_base {
 public:
  lcd_mock(void);
  virtual ~lcd_mock(void);
  bool init() override;
  bool deinit() override;
  bool clear() override;
  bool write(const uint8_t* data, const size_t size) override;
  bool setCursor(int x, int y) override;
  bool test_display(const uint8_t cmd) override;

  // its ment to be public for testing
  bool m_init_called = false;
  bool m_clear_called = false;
  bool m_write_called = false;
  bool m_setCursor_called = false;
  int m_x = 0;
  int m_y = 0;
  const uint8_t* m_data = nullptr;
};

#endif /*main_Components_lcd_display_include_lcd_mock_hpp*/