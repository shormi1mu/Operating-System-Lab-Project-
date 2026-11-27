#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H

#include <string>
#include <vector>

struct ProcessInfo {
    int pid;
    std::string name;
    char state;
    long memoryKB;
};

class ProcessMonitor {
public:
    std::vector<ProcessInfo> getProcesses();
    void displayTopMemory(int count = 5);
};

#endif