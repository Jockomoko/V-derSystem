#ifndef GENERATINGDATA_H
#define GENERATINGDATA_H
#include <vector>
#include <mutex>
#include <atomic>
#include "Sensor.h"
#include "Globals.h"

class GeneratingData
{
public:
    /**
     * @brief Genererar slumpmässig temperatur mellan 5.0 - 35.0
     *
     * Calling on function setTemp from class sensor to set the temperature
     * @param newSen skickar in en sensor för att lagra temperaturen
     */
    static void generateTemp(sensor &newSen);
    /**
     * @brief Generate a random humidity between 30 - 100
     * @param newSen
     */
    static void generateHuminity(sensor &newSen);

    static void generateWindSpeed(sensor &newSen);
    static void generateData(std::vector<sensor> &sensors);
    static std::vector<float> calcAverages(std::vector<sensor> input);
    static std::vector<float> calcMinValues(std::vector<sensor> input);
    static std::vector<float> calcMaxValues(std::vector<sensor> input);
    static std::vector<std::vector<float>> generateStatistics(std::vector<sensor> &sensors);
};
#endif // GENERATINGDATA_H
