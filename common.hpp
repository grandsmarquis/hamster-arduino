
#ifndef __H_COMMON__
#define	__H_COMMON__

#include "main.hpp"
#include "storage.hpp"
#include "wifi.hpp"
#include "light.hpp"

#define API_PUT API_URL "/products/"


namespace Common {

  bool joinAccessPoint(Storage *storage, Wifi *wifi, WifiCredentials *wifiinfos);
  bool doAvailableRequest(Storage *storage, Wifi *wifi, WifiCredentials *wifiinfos);
  bool readAnswer(Storage *storage, Wifi *wifi);
  bool doRequest(Storage *storage, Wifi *wifi, String type, String request);
  bool TryToJoinAccessPoint(Storage *storage, Wifi *wifi, Light *light);
}

#endif
