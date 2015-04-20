
#include "storage.hpp"

Storage::Storage()
{
}

uint8_t	*Storage::getSerial()
{
  return (this->serial);
}

void Storage::read(int address, char *buffer, int len)
{
  int i = 0;

  while (i < len)
    {
      buffer[i] = EEPROM.read(address + i);
      i++;
    }
}

void Storage::write(int address, char *buffer, int len)
{
  int i = 0;

  while (i < len)
    {
      EEPROM.write(address + i, buffer[i]);
      i++;
    }
}

void Storage::getWifi(WifiCredentials *wifi)
{
  this->read(SERIAL_LEN + 1, (char *) wifi, sizeof(wifi));
}

void Storage::setWifi(WifiCredentials *wifi)
{
  this->write(SERIAL_LEN + 1, (char *) wifi, sizeof(wifi));
}

void Storage::getSerial(SerialNumber *sn)
{
}

void Storage::setSerial(SerialNumber *sn)
{
}
