
#ifndef __H_SETUP__
#define	__H_SETUP__

#include "main.hpp"
#include "storage.hpp"
#include "wifi.hpp"

#define SETUP_DELIM_CHAR ':'

namespace Setup {

  bool	  initAccessPoint(Storage *storage, Wifi *wifi);
  bool    sendSerialNumber(Storage *storage, Wifi *wifi);
  bool    receiveConnectionInformations(Storage *storage, Wifi *wifi);

}

#endif
