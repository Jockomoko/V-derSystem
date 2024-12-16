#include "sensor.h"
// Calc
int sensor::calcMinValue()
{
    return temperature;
}
int sensor::calcMaxValue()
{
    return temperature;
}
int sensor::calcAverageValue()
{
    return temperature;
}
// Getters
int sensor::getTemp()
{
    return temperature;
}
int sensor::getWSpeed()
{
    return windSpeed;
}
int sensor::getHumidity()
{
    return humidity;
}
// Setters
void sensor::setTemp(int temp)
{
    temperature = temp;
}
void sensor::setWSpeed(int wSpeed)
{
    windSpeed = wSpeed;
}
void sensor::setHumidity(int humid)
{
    humidity = humid;
}