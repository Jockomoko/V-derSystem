#include <iostream>
#ifndef SENSOR_H
#define SENSOR_H


class sensor
{
private:
    float temperature = 0;
    float windSpeed = 0;
    float humidity = 0;
public:
    // Getters
    float getTemp();
    float getWSpeed();
    float getHumidity();
    // Setter
    void setTemp(float temp);
    void setWSpeed(float wSpeed);
    void setHumidity(float humid);
};

#endif // SENSOR_H