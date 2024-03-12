#ifndef main_Components_lcd_display_include_hal_base_hpp
#define main_Components_lcd_display_include_hal_base_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  hal_base.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, hal_base.hpp, is designed as:
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

/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

class hal_base {
 public:
  hal_base(void) : is_init{false} {};
  virtual ~hal_base(void){};
  virtual bool init() = 0;
  virtual bool deinit() =0;
  virtual bool clear() =0;
  virtual bool write(const char* data) = 0;
  virtual bool setCursor(int x, int y) = 0;
  bool is_initialized() const { return is_init; };

 protected:
  bool is_init;
};

#endif /*main_Components_lcd_display_include_hal_base_hpp*/