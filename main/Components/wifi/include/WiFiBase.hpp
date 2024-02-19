#ifndef Components_Connector_WiFi_v2_include_WiFiBase_hpp
#define Components_Connector_WiFi_v2_include_WiFiBase_hpp
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  WiFiBase.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 	      :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, WiFiBase.hpp, is designed as:
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
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/


#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class WiFiBase 
{
  public:
	WiFiBase(const std::string& ssid, const std::string& pwd) : m_ssid{ssid}, m_pwd{pwd} {};
	virtual ~WiFiBase(){};

	virtual bool connect() = 0;
	virtual bool disconnect() = 0;

  protected:
	const std::string m_ssid;
	const std::string m_pwd;

  private:
	WiFiBase(WiFiBase const& src) = delete;
	WiFiBase& operator=(WiFiBase const& rhs) = delete;
};

#endif /*Components_Connector_WiFi_v2_include_WiFiBase_hpp*/