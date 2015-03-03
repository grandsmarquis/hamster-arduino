
#include "main.hpp"
#include "speedmeter/speedmeter.hpp"

SpeedMeter *sensor;

void	setup()
{
  Serial.begin(9600);
  
  sensor = new SpeedMeter(2, 1, 10);

}

void	loop()
{
  sensor->update();
  //  Serial.print("Loop");
}
