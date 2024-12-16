#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <cstdlib>

void clear_screen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear"); // macOS and Linux
#endif
}

// Include your sensor class definition
#include "sensor.cpp"
#include "sensor.h"

std::vector<float> calcAverages (std::vector<sensor> input); 

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
        std::cout << "Generating data...\n";
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

    
    std::cout << "\nFinal Sensor Data:\n";

    for(auto &s : sensors)
    {
        clear_screen();
        std::cout << "Temperature: " << s.getTemp() << "°C\n";
        std::cout << "Humidity: " << s.getHumidity() << "%\n";
        std::cout << "Wind Speed: " << s.getWSpeed() << " m/s\n";
        std::cout << "-------------------\n";
    };
    

    std::cin.get();
    //std::cout << "\nFinal Sensor Data:\n";
    //std::cout << "Temperature: " << s1.getTemp() << "°C\n";
    //std::cout << "Humidity: " << s1.getHumidity() << "%\n";
    //std::cout << "Wind Speed: " << s1.getWSpeed() << " m/s\n";

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