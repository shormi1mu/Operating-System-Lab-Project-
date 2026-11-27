#include "load_monitor.h"
#include <fstream>

void LoadMonitor::getLoad(
    double& one,
    double& five,
    double& fifteen
) {
    std::ifstream file("/proc/loadavg");

    if (!(file >> one >> five >> fifteen)) {
        one = five = fifteen = 0.0;
    }
}