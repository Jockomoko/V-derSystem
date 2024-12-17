#include "sensor.h"
// Calc
float sensor::calcMinValue()
{
    return temperature;
}
float sensor::calcMaxValue()
{
    return temperature;
}
float sensor::calcAverageValue()
{
    return temperature;
}

float sensor::getTemp()
{
    return temperature; // Return as float
}
float sensor::getWSpeed()
{
    return windSpeed; // Return as float
}
float sensor::getHumidity()
{
    return humidity; // Return as float
}

void sensor::setTemp(float temp)
{
    temperature = temp; // Accept as float
}
void sensor::setWSpeed(float wSpeed)
{
    windSpeed = wSpeed; // Accept as float
}
void sensor::setHumidity(float humid)
{
    humidity = humid; // Accept as float
}