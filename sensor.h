//#include <iostream>
#if !defined(SENSOR_H)
#define SENSOR_H


class sensor
{
private:
    float temperature = 0;
    float windSpeed = 0;
    float humidity = 0;
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

#endif // SENSOR_H