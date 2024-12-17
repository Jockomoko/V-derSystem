#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <cstdlib>
#include <atomic>
#include "sensor.h"

std::atomic<bool> keepRunning(true);

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
    std::cout << "Generated Temperature: " << temp << "°C" <<std::endl;
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
    std::cout << "Generated Humidity: " << humidity << "%" <<std::endl;
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
    std::cout <<"Generated Wind Speed: " << windSpeed << " m/s" <<std::endl;
}

void generateData(std::vector<sensor> &sensors)
{
    sensor s1;
    while(keepRunning)
    {
        clear_screen();
        std::cout <<"Gathering data...\n";
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

void printStatitics(std::vector<sensor> &sensors)
{
    while(keepRunning)
    {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::vector<float> averages = calcAverages(sensors);


    //std::cout << "\nAVERAGES\n"
    std::cout <<"Average Temp: " << averages[0] << std::endl
        << "Average WindSpeed: " << averages[1] << std::endl
        << "Average Humidity: " << averages[2] << std::endl;

    std::vector<float> minValues = calcMinValues(sensors);

    //std::cout << "\nMIN VALUES\n"
    std::cout << "Min Temp: " << minValues[0] <<" C" << std::endl
        << "Min WindSpeed: " << minValues[1] <<" m/ s" << std::endl
        << "Min Humidity: " << minValues[2] <<" %" << std::endl;


    std::vector<float> maxValues = calcMaxValues(sensors);

    //std::cout << "\nMAX VALUES\n"
    std::cout << "Max Temp: " << maxValues[0] <<" C" << std::endl
        << "Max WindSpeed: " << maxValues[1] <<" m/ s" << std::endl
        << "Max Humidity: " << maxValues[2] <<" %" << std::endl;
        //std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
int main()
{
    std::vector<sensor> sensors;
    std::thread generatingData(generateData, std::ref(sensors));
    std::thread printStats(printStatitics, std::ref(sensors));
    std::this_thread::sleep_for(std::chrono::seconds(10));
    keepRunning = false;

    generatingData.join();
    printStats.join();
    
    
    // Create threads for data generation
    /*for(int i = 0; i < 3; i++)
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
    

    std::cout << "Final Sensor Data:" <<std::endl;
    sensor lastSensor = sensors.back();
    
    std::cout <<  "Temperature: " << lastSensor.getTemp() << "°C" <<std::endl;
    std::cout <<  "Humidity: " << lastSensor.getHumidity() << "%" <<std::endl;
    std::cout <<  "Wind Speed: " << lastSensor.getWSpeed() << " m/s" <<std::endl;

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