
#ifndef __H_COMMON__
#define	__H_COMMON__

#include "main.hpp"
#include "storage.hpp"
#include "wifi.hpp"

#define API_PORT (80)
#define API_URL "http://hamster-api.herokuapp.com"
#define API_PUT API_URL "/products/"


namespace Common {

  bool joinAccessPoint(Storage *storage, Wifi *wifi);
  bool doAvailableRequest(Storage *storage, Wifi *wifi);
  bool readAnswer(Storage *storage, Wifi *wifi);
  bool doRequest(Storage *storage, Wifi *wifi, String type, String request);
  
}

#endif
