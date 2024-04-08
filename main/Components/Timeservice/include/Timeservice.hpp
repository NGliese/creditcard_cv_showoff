#ifndef main_Components_Timeservice_include_Timeservice_hpp
#define main_Components_Timeservice_include_Timeservice_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Timeservice.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Timeservice.hpp, is designed as:
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

class Timeservice {
#ifdef __UNITTEST__
  friend class friend_Timeservice;
#endif
 public:
  static void wait_ns(uint64_t ns);  // this is a blocking function
  static void wait_us(uint64_t us);  // this is a blocking function
  // none of the following wait functions must be blocking
  static void wait_ms(uint64_t ms);
  static void wait_sec(uint64_t s);
  static void wait_min(uint64_t m);
  static void wait_hour(uint64_t h);
  static uint64_t get_millis();
};
#endif

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Timeservice {
 public:
  explicit friend_Timeservice(Timeservice* Timeservice)
      : m_sensor{Timeservice} {};
  ~friend_Timeservice(){};

 private:
  Timeservice* m_sensor;
};
#endif /*main_Components_Timeservice_include_Timeservice_hpp*/