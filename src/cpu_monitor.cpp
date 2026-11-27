#include "cpu_monitor.h"
#include <fstream>
#include <string>

double CPUMonitor::getUsage() {
    std::ifstream file("/proc/stat");

    if (!file.is_open())
        return 0.0;

    std::string cpu;
    unsigned long long user, nice, system, idle;
    unsigned long long iowait, irq, softirq, steal;

    file >> cpu >> user >> nice >> system >> idle
         >> iowait >> irq >> softirq >> steal;

    unsigned long long total =
        user + nice + system + idle +
        iowait + irq + softirq + steal;

    unsigned long long idleTotal = idle + iowait;

    if (firstSample) {
        previousTotal = total;
        previousIdle = idleTotal;
        firstSample = false;
        return 0.0;
    }

    unsigned long long totalDiff = total - previousTotal;
    unsigned long long idleDiff = idleTotal - previousIdle;

    previousTotal = total;
    previousIdle = idleTotal;

    if (totalDiff == 0)
        return 0.0;

    return 100.0 * (totalDiff - idleDiff) / totalDiff;
}