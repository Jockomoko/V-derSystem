#ifndef GENERATINGDATA_H
#define GENERATINGDATA_H
#include <vector>
#include <mutex>
#include <atomic>
#include "Sensor.h"
#include "Globals.h"

class GeneratingData{
    public:
    static void generateTemp(sensor &newSen);
    static void generateHuminity(sensor &newSen);
    static void generateWindSpeed(sensor &newSen);
    static void generateData(std::vector<sensor> &sensors);
    static std::vector<float> calcAverages(std::vector<sensor> input);
    static std::vector<float> calcMinValues(std::vector<sensor> input);
    static std::vector<float> calcMaxValues(std::vector<sensor> input);
    static std::vector<std::vector<float>> generateStatistics(std::vector<sensor> &sensors);
};
#endif // GENERATINGDATA_H
