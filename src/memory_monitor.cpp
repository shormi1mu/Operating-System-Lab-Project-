#include "memory_monitor.h"
#include <fstream>
#include <string>

double MemoryMonitor::getUsage() {
    std::ifstream file("/proc/meminfo");

    std::string key, unit;
    unsigned long long value;
    unsigned long long total = 0;
    unsigned long long available = 0;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:")
            total = value;

        if (key == "MemAvailable:")
            available = value;
    }

    if (total == 0)
        return 0.0;

    return 100.0 * (total - available) / total;
}