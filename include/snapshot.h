#ifndef SNAPSHOT_H
#define SNAPSHOT_H

class Snapshot {
public:
    static void compare(
        double oldCPU, double oldRAM, double oldDisk,
        double newCPU, double newRAM, double newDisk
    );
};

#endif