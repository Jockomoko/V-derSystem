#include <iostream>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
#include "Includes/Sensor.h"
#include "Includes/GeneratingData.h"
#include "Includes/DataPrinting.h"
#include "Includes/Globals.h"


std::atomic<bool> keepRunning(true);
std::atomic<bool> newDataAvailable(false);
std::mutex sensor_mutex;
std::mutex cout_mutex;


int main()
{
    std::vector<sensor> sensors;
    DataPrinting::printStaticText();
    std::thread generatingData(GeneratingData::generateData, std::ref(sensors));
    std::thread generatingStatistics(GeneratingData::generateStatistics, std::ref(sensors));
    std::thread displayStatitics(DataPrinting::printStatitics, std::ref(sensors));
    std::thread displayLatestData(DataPrinting::displayData, std::ref(sensors));
    std::thread waitForkeyPress(DataPrinting::waitForPress);

    generatingData.join();
    generatingStatistics.join();
    displayStatitics.join();
    displayLatestData.join();
    waitForkeyPress.join();
   
    DataPrinting::goodbyeMessage();
    std::cin.get();

    return 0;
}
