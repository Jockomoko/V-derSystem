#include <iostream>
class sensor
{
private:
    int temperature = 0;
    int windSpeed = 0;
    int humidity = 0;
public:
    // Calc
    int calcMinValue();
    int calcMaxValue();
    int calcAverageValue();
    // Getters
    int getTemp();
    int getWSpeed();
    int getHumidity();
    // Setter
    void setTemp(int temp);
    void setWSpeed(int wSpeed);
    void setHumidity(int humid);
};