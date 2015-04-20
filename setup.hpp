
#ifndef __H_SETUP__
#define	__H_SETUP__

#include "main.hpp"
#include "storage.hpp"
#include "wifi.hpp"
#include "common.hpp"

#define SETUP_DELIM_CHAR ':'
#define SETUP_JOIN_TRIES 5

namespace Setup {

  bool	  initAccessPoint(Storage *storage, Wifi *wifi);
  bool    sendSerialNumber(Storage *storage, Wifi *wifi);
  bool    receiveConnectionInformations(Storage *storage, Wifi *wifi);
  void	  doBinding(Storage *storage, Wifi *wifi);
}

#endif
