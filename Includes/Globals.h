#ifndef GLOBALS_H
#define GLOBALS_H

#include <atomic>
#include <mutex>

extern std::atomic<bool> keepRunning;
extern std::atomic<bool> newDataAvailable;
extern std::mutex sensor_mutex;
extern std::mutex cout_mutex;

#endif // GLOBALS_H