#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

class CPUMonitor {
private:
    unsigned long long previousTotal = 0;
    unsigned long long previousIdle = 0;
    bool firstSample = true;

public:
    double getUsage();
};

#endif