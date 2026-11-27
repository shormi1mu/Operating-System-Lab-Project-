#include "snapshot.h"
#include <iostream>

void Snapshot::compare(
    double oldCPU, double oldRAM, double oldDisk,
    double newCPU, double newRAM, double newDisk
) {
    double cpuChange = newCPU - oldCPU;
    double ramChange = newRAM - oldRAM;
    double diskChange = newDisk - oldDisk;

    std::cout << "\n--- Snapshot Comparison ---\n";

    std::cout << "CPU change: " << cpuChange << " percentage points\n";
    std::cout << "RAM change: " << ramChange << " percentage points\n";
    std::cout << "Disk change: " << diskChange << " percentage points\n";

    if (cpuChange >= ramChange && cpuChange >= diskChange)
        std::cout << "Most changed resource: CPU\n";
    else if (ramChange >= diskChange)
        std::cout << "Most changed resource: RAM\n";
    else
        std::cout << "Most changed resource: Disk\n";
}