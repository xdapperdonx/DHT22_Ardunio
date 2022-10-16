#include <DHT.h>

#define dataPin 2
#define DHTTYPE DHT22

DHT dht(dataPin, DHTTYPE);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}

//convert to Fahernheit
float toFahrenheit(float celcius)
{
  float temp = (celcius * 1.8) + 32;

  return temp;
}

//find minimium temperature
float checkMin(float prevTemp, float temp)
{
  if(temp < prevTemp)
    return temp;
  else
    return prevTemp;
}

//finds max temperature
float checkMax(float prevTemp, float temp)
{
  if(temp > prevTemp)
    return temp;
  else
    return prevTemp;
}

//used to display to serial monitor
void print(float minTemp, float maxTemp, float currTemp, float humid)
{
  Serial.print("Min. Temperature = ");
  Serial.print(toFahrenheit(minTemp));
  Serial.print(" F ");

  Serial.print("Max. Temperature = ");
  Serial.print(toFahrenheit(maxTemp));
  Serial.print(" F ");

  Serial.print(" Temperature = ");
  Serial.print(toFahrenheit(currTemp));
  Serial.print(" F ");

  Serial.print(" Humidity = ");
  Serial.print(humid);
  Serial.println(" % ");

  delay(500);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  float currTemp = dht.readTemperature();
  float humid = dht.readHumidity();

  static float prevTemp = currTemp;
  float minTemp = checkMin(prevTemp, currTemp);
  float maxTemp = checkMax(prevTemp, currTemp);

  print(minTemp, maxTemp, currTemp, humid);
}
