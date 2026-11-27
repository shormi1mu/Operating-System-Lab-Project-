#ifndef BOTTLENECK_DETECTOR_H
#define BOTTLENECK_DETECTOR_H

class BottleneckDetector {
private:
    double cpuThreshold;
    double ramThreshold;
    double diskThreshold;

    int cpuCount;
    int ramCount;
    int diskCount;

    int requiredSamples;

public:
    BottleneckDetector(
        double cpu = 80.0,
        double ram = 85.0,
        double disk = 90.0,
        int samples = 3
    );

    void check(
        double cpuUsage,
        double ramUsage,
        double diskUsage
    );
};

#endif