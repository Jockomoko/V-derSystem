
#include <iostream>
#include <thread>
#include <random>
#include "../Includes/GeneratingData.h"

void GeneratingData::generateTemp(sensor &newSen)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(5.0, 35.0);
    float temp = dis(gen);
    std::lock_guard<std::mutex> lock(sensor_mutex);
    newSen.setTemp(temp);
    newDataAvailable = true;
}

void GeneratingData::generateHuminity(sensor &newSen)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(30, 100);
    float humidity = dis(gen);
    std::lock_guard<std::mutex> lock(sensor_mutex);
    newSen.setHumidity(humidity);
    newDataAvailable = true;
}
void GeneratingData::generateWindSpeed(sensor &newSen)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    float windSpeed = dis(gen);
    std::lock_guard<std::mutex> lock(sensor_mutex);
    newSen.setWSpeed(windSpeed);
    newDataAvailable = true;
}

// Function that calls the generateFunctions and saves the result in a vector.
void GeneratingData::generateData(std::vector<sensor> &sensors)
{
    sensor s1;
    while (keepRunning)
    {
        generateTemp(s1);
        generateHuminity(s1);
        generateWindSpeed(s1);
        {
            std::lock_guard<std::mutex> lock(sensor_mutex);
            sensors.push_back(s1);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// Function that calculates the average of the values in the sensors vector.
std::vector<float> GeneratingData::calcAverages(std::vector<sensor> input)
{
    // takes a vector of sensors as sensors
    std::vector<float> returnVector;

    // averages each type of value in each sensor
    float a = 0;
    for (int i = 0; i < input.size(); i++)
    {
        a += input[i].getTemp();
    };
    returnVector.push_back(a / input.size());
    a = 0;

    for (int i = 0; i < input.size(); i++)
    {
        a += input[i].getWSpeed();
    };
    returnVector.push_back(a / input.size());
    a = 0;

    for (int i = 0; i < input.size(); i++)
    {
        a += input[i].getHumidity();
    };
    returnVector.push_back(a / input.size());
    a = 0;

    // returns a vector<float> with the average values
    return returnVector;
};

// Function that calculates the minimum values of the temp, speed and humidity in the sensors vector.
std::vector<float> GeneratingData::calcMinValues(std::vector<sensor> input)
{
    std::vector<float> returnVector;
    /*Uses numeric_limits to set the minimum value to the maximum possible
    value and then compares it to the values in the sensors vector.*/
    float minValue = std::numeric_limits<float>::max();
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].getTemp() < minValue)
        {
            minValue = input[i].getTemp();
        }
    }
    returnVector.push_back(minValue);

    minValue = std::numeric_limits<float>::max();
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].getWSpeed() < minValue)
        {
            minValue = input[i].getWSpeed();
        }
    }
    returnVector.push_back(minValue);

    minValue = std::numeric_limits<float>::max();
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].getHumidity() < minValue)
        {
            minValue = input[i].getHumidity();
        }
    }
    returnVector.push_back(minValue);
    return returnVector;
}

// Function that calculates the maximum values of the temp, speed and humidity in the sensors vector.
std::vector<float> GeneratingData::calcMaxValues(std::vector<sensor> input)
{
    std::vector<float> returnVector;

    /*Uses numeric_limits to set the maximum value to the minimum possible
    value and then compares it to the values in the sensors vector.*/
    float maxValue = std::numeric_limits<float>::min();
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].getTemp() > maxValue)
        {
            maxValue = input[i].getTemp();
        }
    }
    returnVector.push_back(maxValue);

    maxValue = std::numeric_limits<float>::min();
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].getWSpeed() > maxValue)
        {
            maxValue = input[i].getWSpeed();
        }
    }
    returnVector.push_back(maxValue);

    maxValue = std::numeric_limits<float>::min();
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].getHumidity() > maxValue)
        {
            maxValue = input[i].getHumidity();
        }
    }
    returnVector.push_back(maxValue);

    return returnVector;
}

/*Function that uses the calculation functions to generate statitics from the gathered data.
Only executes if there is new data available.*/
std::vector<std::vector<float>> GeneratingData::generateStatistics(std::vector<sensor> &sensors)
{
    std::vector<std::vector<float>> statitics;
    if (newDataAvailable)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::vector<float> averages = GeneratingData::calcAverages(sensors);
        statitics.push_back(averages);
        std::vector<float> minValues = GeneratingData::calcMinValues(sensors);
        statitics.push_back(minValues);
        std::vector<float> maxValues = GeneratingData::calcMaxValues(sensors);
        statitics.push_back(maxValues);
        newDataAvailable = false;
    }
    return statitics;
}