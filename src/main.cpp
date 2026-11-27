#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "disk_monitor.h"
#include "load_monitor.h"
#include "bottleneck_detector.h"
#include "process_monitor.h"
#include "process_control.h"
#include "logger.h"
#include "snapshot.h"
#include "report_generator.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <csignal>

int main() {
    CPUMonitor cpu;
    MemoryMonitor ram;
    DiskMonitor disk;
    LoadMonitor load;
    BottleneckDetector detector;
    ProcessMonitor processes;
    Logger logger;
    ReportGenerator report;

    double cpuUsage = 0;
    double ramUsage = 0;
    double diskUsage = 0;

    std::cout << "================================\n";
    std::cout << "   ResourceWatch System Monitor\n";
    std::cout << "================================\n";

    int choice;

    do {
        std::cout << "\n1. Show System Resources\n";
        std::cout << "2. Show Top 5 RAM Processes\n";
        std::cout << "3. Send Signal to Process\n";
        std::cout << "4. Start Continuous Monitoring\n";
        std::cout << "5. Exit\n";
        std::cout << "6. Generate Performance Report\n";
        std::cout << "Choice: ";

        std::cin >> choice;

        switch (choice) {
        case 1: {
            cpuUsage = cpu.getUsage();
            ramUsage = ram.getUsage();
            diskUsage = disk.getUsage();

            double one, five, fifteen;
            load.getLoad(one, five, fifteen);

            std::cout << std::fixed << std::setprecision(2);

            std::cout << "\nCPU Usage: " << cpuUsage << "%\n";
            std::cout << "RAM Usage: " << ramUsage << "%\n";
            std::cout << "Disk Usage: " << diskUsage << "%\n";

            std::cout << "Load Average: "
                      << one << " "
                      << five << " "
                      << fifteen << "\n";

            detector.check(cpuUsage, ramUsage, diskUsage);
            logger.log(cpuUsage, ramUsage, diskUsage);
            break;
        }

        case 2:
            processes.displayTopMemory(5);
            break;

        case 3: {
            int pid, signalChoice;

            std::cout << "Enter PID: ";
            std::cin >> pid;

            std::cout << "1. Terminate (SIGTERM)\n";
            std::cout << "2. Stop (SIGSTOP)\n";
            std::cout << "3. Continue (SIGCONT)\n";
            std::cout << "Signal choice: ";
            std::cin >> signalChoice;

            if (signalChoice == 1)
                ProcessControl::sendSignal(pid, SIGTERM);
            else if (signalChoice == 2)
                ProcessControl::sendSignal(pid, SIGSTOP);
            else if (signalChoice == 3)
                ProcessControl::sendSignal(pid, SIGCONT);
            else
                std::cout << "Invalid signal choice.\n";

            break;
        }

        case 4: {
            std::cout << "Monitoring started. Press Ctrl+C to stop.\n";

            while (true) {
                cpuUsage = cpu.getUsage();
                ramUsage = ram.getUsage();
                diskUsage = disk.getUsage();

                std::cout << "\nCPU: " << cpuUsage
                          << "% | RAM: " << ramUsage
                          << "% | Disk: " << diskUsage << "%\n";

                detector.check(cpuUsage, ramUsage, diskUsage);
                logger.log(cpuUsage, ramUsage, diskUsage);

                std::this_thread::sleep_for(
                    std::chrono::seconds(2)
                );
            }

            break;
        }

        case 5:
            std::cout << "ResourceWatch closed.\n";
            break;

        case 6:
    report.generate();
    break;

        default:
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}