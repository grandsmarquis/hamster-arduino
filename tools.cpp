
#include "tools.hpp"

void Tools::writeSerialNumber(Storage *storage, String serial)
{
  SerialNumber sn;
  serial.toCharArray(sn.serial, SERIAL_LEN);
  storage->setSerial(&sn);
}
