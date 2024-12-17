#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <cstdlib>
#include "sensor.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear"); // macOS and Linux
#endif
}

std::vector<float> calcAverages (std::vector<sensor> input); 
std::vector<float> calcMinValues (std::vector<sensor> input);
std::vector<float> calcMaxValues (std::vector<sensor> input);

// Mutex for thread safety
std::mutex sensor_mutex;
void generateTemp(sensor &newSen)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(5, 35);
    float temp = dis(gen);
    // Protect access to the sensor object
    std::lock_guard<std::mutex> lock(sensor_mutex);
    newSen.setTemp(temp);
    std::cout << "Generated Temperature: " << temp << "°C\n";
}
void generateHuminity(sensor &newSen)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(30, 100);
    float humidity = dis(gen);
    // Protect access to the sensor object
    std::lock_guard<std::mutex> lock(sensor_mutex);
    newSen.setHumidity(humidity);
    std::cout << "Generated Humidity: " << humidity << "%\n";
}
void generateWindSpeed(sensor &newSen)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    float windSpeed = dis(gen);
    // Protect access to the sensor object
    std::lock_guard<std::mutex> lock(sensor_mutex);
    newSen.setWSpeed(windSpeed);
    std::cout << "Generated Wind Speed: " << windSpeed << " m/s\n";
}
int main()
{
    std::vector<sensor> sensors;

    
    
    // Create threads for data generation
    for(int i = 0; i < 3; i++)
    {
        sensor s1;
        std::cout << "Gathering data...\n";
    std::thread tempThread(generateTemp, std::ref(s1));
    std::thread humidThread(generateHuminity, std::ref(s1));
    std::thread windThread(generateWindSpeed, std::ref(s1));
     tempThread.join();
    humidThread.join();
    windThread.join();
    sensors.push_back(s1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    // Wait for all threads to finish
    //tempThread.join();
    //humidThread.join();
    //windThread.join();
    // Print final sensor values

    //system("cls");

    std::vector<float> averages = calcAverages(sensors);


    std::cout << "\nAVERAGES\n"
        << "Temp: " << averages[0] << std::endl
        << "Speed: " << averages[1] << std::endl
        << "Humidity: " << averages[2] << std::endl;

    std::vector<float> minValues = calcMinValues(sensors);

    std::cout << "\nMIN VALUES\n"
        << "Temp: " << minValues[0] <<" C" << std::endl
        << "Speed: " << minValues[1] <<" m/ s"<< std::endl
        << "Humidity: " << minValues[2] <<" %" << std::endl;


    std::vector<float> maxValues = calcMaxValues(sensors);

    std::cout << "\nMAX VALUES\n"
        << "Temp: " << maxValues[0] <<" C" << std::endl
        << "Speed: " << maxValues[1] <<" m/ s"<< std::endl
        << "Humidity: " << maxValues[2] <<" %" << std::endl;


    //std::cout << "\nFinal Sensor Data:\n";

    /*for(auto &s : sensors)
    {
        clear_screen();
        std::cout << "Temperature: " << s.getTemp() << "°C\n";
        std::cout << "Humidity: " << s.getHumidity() << "%\n";
        std::cout << "Wind Speed: " << s.getWSpeed() << " m/s\n";
        std::cout << "-------------------\n";
    };*/
    

    std::cout << "\nFinal Sensor Data:\n";
    sensor lastSensor = sensors.back();
    
    std::cout << "Temperature: " << lastSensor.getTemp() << "°C\n";
    std::cout << "Humidity: " << lastSensor.getHumidity() << "%\n";
    std::cout << "Wind Speed: " << lastSensor.getWSpeed() << " m/s\n";

    std::cin.get();

    return 0; 
}

std::vector<float> calcAverages (std::vector<sensor> input) {
    // takes a vector of sensors as input
    std::vector<float> returnVector;

    // averages each type of value in each sensor
    float a = 0;
    for (int i = 0; i < input.size(); i++) {
        a += input[i].getTemp();
    };
    returnVector.push_back(a / input.size());
    a = 0;

    for (int i = 0; i < input.size(); i++) {
        a += input[i].getWSpeed();
    };
    returnVector.push_back(a / input.size());
    a = 0;

    for (int i = 0; i < input.size(); i++) {
        a += input[i].getHumidity();
    };
    returnVector.push_back(a / input.size());
    a = 0;

    // returns a vector<float> with the average values
    return returnVector;
};

std::vector<float> calcMinValues (std::vector<sensor> input) {
    // takes a vector of sensors as input
    std::vector<float> returnVector;

    // averages each type of value in each sensor
    float minValue = std::numeric_limits<float>::max();
    for(int i = 0; i < input.size(); i++) {
        if(input[i].getTemp() < minValue) {
            minValue = input[i].getTemp();
        }
    }
    returnVector.push_back(minValue);
   
    minValue = std::numeric_limits<float>::max();
    for(int i = 0; i < input.size(); i++) {
        if(input[i].getWSpeed() < minValue) {
            minValue = input[i].getWSpeed();
        }
    }
    returnVector.push_back(minValue);

    minValue =std::numeric_limits<float>::max();
    for(int i = 0; i < input.size(); i++) {
        if(input[i].getHumidity() < minValue) {
            minValue = input[i].getHumidity();
        }
    }
    returnVector.push_back(minValue);

    // returns a vector<float> with the average values
    return returnVector;
};

std::vector<float> calcMaxValues (std::vector<sensor> input) {
    // takes a vector of sensors as input
    std::vector<float> returnVector;

    // averages each type of value in each sensor
    float maxValue = std::numeric_limits<float>::min();
    for(int i = 0; i < input.size(); i++) {
        if(input[i].getTemp() > maxValue) {
            maxValue = input[i].getTemp();
        }
    }
    returnVector.push_back(maxValue);
   
    maxValue = std::numeric_limits<float>::min();
    for(int i = 0; i < input.size(); i++) {
        if(input[i].getWSpeed() > maxValue) {
            maxValue = input[i].getWSpeed();
        }
    }
    returnVector.push_back(maxValue);

    maxValue = std::numeric_limits<float>::min();
    
    for(int i = 0; i < input.size(); i++) {
        if(input[i].getHumidity() > maxValue) {
            maxValue = input[i].getHumidity();
        }
    }
    returnVector.push_back(maxValue);

    // returns a vector<float> with the average values
    return returnVector;
};