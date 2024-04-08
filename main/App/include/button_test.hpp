#ifndef main_App_include_button_test_hpp
#define main_App_include_button_test_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  button_test.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, button_test.hpp, is designed as:
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

#include <Button.hpp>
#include <Timeservice.hpp>

/*----------------- DEFAULT INCLUDE
 * -------------------------------------------*/

/*-----------------------------------------------------------------------------*/

#include <iostream>

#include <lcd_nhd_c12832a1z_esp_card_showoff.hpp>

#include <lcd_interface.hpp>
/*------------------------------------------------------------------------------+
 |                               Typedef |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class |
 +------------------------------------------------------------------------------*/

class button_test {
 public:
  button_test(void);
  virtual ~button_test(void);
  void run(void);
  void run_controlled_lcd(void);

  static void cb_sw1_button_pressed(void* obj);
  static void cb_sw2_button_pressed(void* obj);
};

#endif /*main_App_include_button_test_hpp*/