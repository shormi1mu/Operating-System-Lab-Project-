#include "report_generator.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <filesystem>

void ReportGenerator::generate() {
    std::ifstream csv("data/resource_history.csv");

    if (!csv.is_open()) {
        std::cout << "CSV file not found!\n";
        return;
    }

    std::string line;
    std::getline(csv, line); // Skip header

    double cpu, ram, disk;
    double cpuSum = 0, ramSum = 0, diskSum = 0;
    double cpuMax = 0, ramMax = 0, diskMax = 0;
    int count = 0;

    while (std::getline(csv, line)) {
        std::stringstream ss(line);
        std::string timestamp;

        if (!std::getline(ss, timestamp, ','))
            continue;

        if (!(ss >> cpu))
            continue;

        ss.ignore(1, ',');

        if (!(ss >> ram))
            continue;

        ss.ignore(1, ',');

        if (!(ss >> disk))
            continue;

        cpuSum += cpu;
        ramSum += ram;
        diskSum += disk;

        if (cpu > cpuMax) cpuMax = cpu;
        if (ram > ramMax) ramMax = ram;
        if (disk > diskMax) diskMax = disk;

        count++;
    }

    csv.close();

    if (count == 0) {
        std::cout << "No history data available.\n";
        return;
    }

    std::filesystem::create_directories("reports");

    std::ofstream report("reports/performance_report.txt");

    if (!report.is_open()) {
        std::cout << "Could not create report.\n";
        return;
    }

    report << "====================================\n";
    report << "     ResourceWatch Performance Report\n";
    report << "====================================\n\n";

    report << std::fixed << std::setprecision(2);

    report << "Total Samples: " << count << "\n\n";

    report << "Average CPU Usage: "
           << cpuSum / count << "%\n";

    report << "Average RAM Usage: "
           << ramSum / count << "%\n";

    report << "Average Disk Usage: "
           << diskSum / count << "%\n\n";

    report << "Peak CPU Usage: "
           << cpuMax << "%\n";

    report << "Peak RAM Usage: "
           << ramMax << "%\n";

    report << "Peak Disk Usage: "
           << diskMax << "%\n\n";

    report << "Bottleneck Summary:\n";

    if (cpuMax >= 80)
        report << "- High CPU usage detected.\n";

    if (ramMax >= 85)
        report << "- High RAM usage detected.\n";

    if (diskMax >= 90)
        report << "- High Disk usage detected.\n";

    report.close();

    std::cout << "Report generated successfully!\n";
    std::cout << "File: reports/performance_report.txt\n";
}