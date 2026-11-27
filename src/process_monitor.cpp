#include "process_monitor.h"

#include <dirent.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

std::vector<ProcessInfo> ProcessMonitor::getProcesses() {
    std::vector<ProcessInfo> processes;

    DIR* directory = opendir("/proc");

    if (!directory)
        return processes;

    struct dirent* entry;

    while ((entry = readdir(directory)) != nullptr) {
        if (!std::isdigit(entry->d_name[0]))
            continue;

        int pid = 0;

        try {
            pid = std::stoi(entry->d_name);
        } catch (...) {
            continue;
        }

        std::string path =
            "/proc/" + std::to_string(pid) + "/status";

        std::ifstream file(path);

        if (!file.is_open())
            continue;

        ProcessInfo process{};
        process.pid = pid;
        process.state = '?';
        process.memoryKB = 0;

        std::string line;

        while (std::getline(file, line)) {
            if (line.rfind("Name:", 0) == 0) {
                process.name = line.substr(6);
            }
            else if (line.rfind("State:", 0) == 0) {
                process.state = line[7];
            }
            else if (line.rfind("VmRSS:", 0) == 0) {
                try {
                    process.memoryKB =
                        std::stol(line.substr(6));
                } catch (...) {
                    process.memoryKB = 0;
                }
            }
        }

        processes.push_back(process);
    }

    closedir(directory);
    return processes;
}

void ProcessMonitor::displayTopMemory(int count) {
    auto processes = getProcesses();

    std::sort(
        processes.begin(),
        processes.end(),
        [](const ProcessInfo& a, const ProcessInfo& b) {
            return a.memoryKB > b.memoryKB;
        }
    );

    std::cout << "\n--- Top Processes by RAM ---\n";
    std::cout << "PID\tNAME\t\tSTATE\tRAM(MB)\n";

    int limit = std::min(count, (int)processes.size());

    for (int i = 0; i < limit; i++) {
        const auto& p = processes[i];

        std::cout << p.pid << "\t"
                  << p.name << "\t"
                  << p.state << "\t"
                  << p.memoryKB / 1024.0
                  << "\n";
    }
}