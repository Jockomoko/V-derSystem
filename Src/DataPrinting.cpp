#include <iostream>
#include <thread>
#include <iomanip>
#include "../Includes/DataPrinting.h"

/*Function that prints the calculated statitics every 10 seconds. 
Uses ANSI escape codes so that only numbers that are chanching is updated. */
void DataPrinting::printStatitics(std::vector<sensor> &sensors)
{
    while (keepRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::vector<std::vector <float>> statitics = GeneratingData::generateStatistics(sensors);
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "\033[6;1H\033[KTemperature Data:" << std::endl
                      << "\033[8;1H\033[KAverage: " << statitics[0][0] << " C" << std::endl
                      << "\033[12;1H\033[KWind Speed Data:" << std::endl
                      << "\033[14;1H\033[KAverage: " << statitics[0][1] << " m/ s" << std::endl
                      << "\033[18;1H\033[KHumidity Data:" << std::endl
                      << "\033[20;1H\033[KAverage: " << statitics[0][2] << " %" << std::endl
                      << "\033[9;1H\033[KMin: " << statitics[1][0] << " C" << std::endl
                      << "\033[15;1H\033[KMin: " << statitics[1][1] << " m/ s" << std::endl
                      << "\033[21;1H\033[KMin: " << statitics[1][2] << " %" << std::endl
                      << "\033[10;1H\033[KMax: " << statitics[2][0] << " C" << std::endl
                      << "\033[16;1H\033[KMax: " << statitics[2][1] << " m/ s" << std::endl
                      << "\033[22;1H\033[KMax: " << statitics[2][2] << " %" << std::endl;
        }
       
    }
}

/*Function that prints out the latest gathered data every 2 seconds.
Uses ANSI escape codes so that only the numbers that are chanching is updated.*/
void DataPrinting::displayData(std::vector<sensor> &sensors)
{
    while (keepRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        {
            sensor s1 = sensors.back();
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "\033[7;1H\033[KLatest temp: " << s1.getTemp() << " C" << std::endl;
            std::cout << "\033[13;1H\033[KLatest WindSpeed: " << s1.getWSpeed() << " m/ s" << std::endl;
            std::cout << "\033[19;1H\033[KLatest Humidity: " << s1.getHumidity() << " %" << std::endl;
        }
    }
}

void DataPrinting::printStaticText()
{
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << "Welcome to the Weather Station!\n"
              << "Press any key to stop the program. It can take a few seconds before the program stops.\n"
              << "This program will gather data every 0.5 seconds and calculate statistics every 5 seconds.\n"
              << "The program will update the latest gathered data every 2 seconds and the statitics every 10 seconds.\n"
              << "\033[6;1H\033[KTemperature Data:"
              <<std::fixed<<std::setprecision(1)
              <<"\033[7;1H\033[KLatest temp: "
              << "\033[8;1H\033[KAverage: "
              << "\033[9;1H\033[KMin: "
              << "\033[10;1H\033[KMax: "
              << "\033[12;1H\033[KWind Speed Data:"
              <<"\033[13;1H\033[KLatest WindSpeed: "
              << "\033[14;1H\033[KAverage: "
              << "\033[15;1H\033[KMin: "
              << "\033[16;1H\033[KMax: "
              << "\033[18;1H\033[KHumidity Data:"
              << "\033[19;1H\033[KLatest Humidity: "
              << "\033[20;1H\033[KAverage: "
              << "\033[21;1H\033[KMin: "
              << "\033[22;1H\033[KMax: ";
}

//Function that waits for a key press to stop the program.
void DataPrinting::waitForPress()
{
    std::cin.get();
    keepRunning = false;
}

void DataPrinting::goodbyeMessage()
{
    std::cout << "\033[24;1H\033[KPress any key to exit program!";
            
}