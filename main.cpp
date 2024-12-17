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
std::mutex cout_mutex;
void generateTemp(sensor &newSen)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(5, 35);
    float temp = dis(gen);
    // Protect access to the sensor object
    std::lock_guard<std::mutex> lock(sensor_mutex);
    newSen.setTemp(temp);
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "\033[7;1\033[KGathered Temperature: " << temp << " C" <<std::endl;
    }
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
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "\033[9;1H\033[KGathered Humidity: " << humidity << " %" <<std::endl;
    }
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
   {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout <<"\033[8;1H\033[KGathered Wind Speed: " << windSpeed << " m/ s" <<std::endl;
   }
}

void generateData(std::vector<sensor> &sensors)
{
    sensor s1;
    while(keepRunning)
    {
        //clear_screen();
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout <<"\033[6;1H\033[KGathering data...\n";
        }
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

    {
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout <<"\033[11;1H\033[KAverage Temp: " << averages[0] <<" C" << std::endl
        << "\033[15;1H\033[KAverage WindSpeed: " << averages[1] <<" m/ s" << std::endl
        << "\033[19;1H\033[KAverage Humidity: " << averages[2] <<" %" << std::endl;
    }
    std::vector<float> minValues = calcMinValues(sensors);

    {
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << "\033[12;1H\033[KMin Temp: " << minValues[0] <<" C" << std::endl
        << "\033[16;1H\033[KMin WindSpeed: " << minValues[1] <<" m/ s" << std::endl
        << "\033[20;1H\033[KMin Humidity: " << minValues[2] <<" %" << std::endl;

    }
    std::vector<float> maxValues = calcMaxValues(sensors);

    {
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << "\033[13;1H\033[KMax Temp: " << maxValues[0] <<" C" << std::endl
        << "\033[17;1H\033[KMax WindSpeed: " << maxValues[1] <<" m/ s" << std::endl
        << "\033[21;1H\033[KMax Humidity: " << maxValues[2] <<" %" << std::endl;
    }
    }
}

void waitForPress()
{
    std::cin.get();
    keepRunning = false;
}
int main()
{
    std::vector<sensor> sensors;
    std::cout <<"Welcome to the Weather Station!\n";
    std::cout <<"Press any key to stop the program\n";
    std::cout <<"This program will gather data every 0.5 seconds\n" 
                 "and print statistics every 5 seconds\n\n";
    std::thread generatingData(generateData, std::ref(sensors));
    std::thread printStats(printStatitics, std::ref(sensors));
    std::thread waitForkeyPress(waitForPress);
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    //keepRunning = false;

    generatingData.join();
    printStats.join();
    waitForkeyPress.join();
    
    
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
    

    std::cout << "\033[23;1H\033[KFinal Sensor Data:" <<std::endl;
    sensor lastSensor = sensors.back();
    
    std::cout <<  "\033[24;1H\033[KTemperature: " << lastSensor.getTemp() << " C" <<std::endl;
    std::cout <<  "\033[25;1H\033[KHumidity: " << lastSensor.getHumidity() << " %" <<std::endl;
    std::cout <<  "\033[26;1H\033[KWind Speed: " << lastSensor.getWSpeed() << " m/ s" <<std::endl;

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