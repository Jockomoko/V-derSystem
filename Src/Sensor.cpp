#include "../Includes/Sensor.h"
// Getters

float sensor::getTemp()
{
    return temperature;
}

float sensor::getWSpeed()
{
    return windSpeed;
}

float sensor::getHumidity()
{
    return humidity;
}

// Setter

void sensor::setTemp(float temp)
{
    temperature = temp;
}

void sensor::setWSpeed(float wSpeed)
{
    windSpeed = wSpeed;
}

void sensor::setHumidity(float humid)
{
    humidity = humid;
}