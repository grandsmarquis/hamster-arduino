
#include "main.hpp"
#include "speedmeter/speedmeter.hpp"
#include "wifi.hpp"

SpeedMeter *sensor;
Wifi	   *wifi;


void	setup()
{
  Serial.begin(9600);

  wifi = new Wifi(Serial2);

  if (wifi->isAlive())
    Serial.println("[OK] Wifi is alive");
  else
    Serial.println("[FAIL] Wifi is not alive");
  String version = wifi->getVersion();
  Serial.println("Version :: " + version);
  
  
  //  sensor = new SpeedMeter(2, 1, 10);

}

void	loop()
{
  //sensor->update();
  //  Serial.print("Loop");
}
