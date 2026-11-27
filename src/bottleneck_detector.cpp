#include "bottleneck_detector.h"
#include <algorithm>
#include <iostream>
#include <string>

BottleneckDetector::BottleneckDetector(
    double cpu, double ram, double disk, int samples
)
    : cpuThreshold(cpu),
      ramThreshold(ram),
      diskThreshold(disk),
      cpuCount(0),
      ramCount(0),
      diskCount(0),
      requiredSamples(std::max(1, samples)) {}

void BottleneckDetector::check(
    double cpuUsage, double ramUsage, double diskUsage
) {
    cpuCount = cpuUsage >= cpuThreshold ? cpuCount + 1 : 0;
    ramCount = ramUsage >= ramThreshold ? ramCount + 1 : 0;
    diskCount = diskUsage >= diskThreshold ? diskCount + 1 : 0;

    if (cpuCount == requiredSamples)
        std::cout << "[BOTTLENECK] CPU: " << cpuUsage << "%\n";

    if (ramCount == requiredSamples)
        std::cout << "[BOTTLENECK] RAM: " << ramUsage << "%\n";

    if (diskCount == requiredSamples)
        std::cout << "[BOTTLENECK] Disk: " << diskUsage << "%\n";
}