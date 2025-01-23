#include <iostream>
#ifndef SENSOR_H
#define SENSOR_H

/**
 * @brief
 * @
 * @param temperature int
 * @param windSpeed
 * @param humidity
 */
class sensor
{
private:
    float temperature = 0;
    float windSpeed = 0;
    float humidity = 0;

public:
    // Getters
    /**
     * @brief Get temperature
     *
     * @return temperature as float
     */
    float getTemp();
    /**
     * @brief Get windspeed
     *
     * @return windspeed as float
     */
    float getWSpeed();
    /**
     * @brief Get Humidity
     *
     * @return humidity as float
     */
    float getHumidity();
    // Setter
    /**
     * @brief Sätter temperaturen
     *
     * @param temp
     */
    void setTemp(float temp);
    /**
     * @brief Sätter vindhastigheten
     *
     * @param wSpeed
     */
    void setWSpeed(float wSpeed);
    /**
     * @brief Sätter the Humidity
     *
     * @param humid
     */
    void setHumidity(float humid);
};

#endif // SENSOR_H