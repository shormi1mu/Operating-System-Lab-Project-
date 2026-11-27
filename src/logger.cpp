#include "logger.h"
#include <fstream>
#include <ctime>
#include <filesystem>

void Logger::log(double cpu, double ram, double disk) {
    std::filesystem::create_directories("data");

    bool newFile = !std::filesystem::exists(
        "data/resource_history.csv"
    );

    std::ofstream file(
        "data/resource_history.csv",
        std::ios::app
    );

    if (!file)
        return;

    if (newFile)
        file << "Time,CPU,RAM,Disk\n";

    std::time_t now = std::time(nullptr);

    file << now << ","
         << cpu << ","
         << ram << ","
         << disk << "\n";
}