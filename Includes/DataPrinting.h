#include <vector>
#include "Sensor.h"
#include "GeneratingData.h"
#include "Globals.h"

class DataPrinting
{
    public:
    static void printStatitics(std::vector<sensor> &sensors);
    static void displayData(std::vector<sensor> &sensors);
    static void printStaticText();
    static void waitForPress();
    static void goodbyeMessage();

};