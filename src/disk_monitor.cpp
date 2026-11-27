#include "disk_monitor.h"
#include <sys/statvfs.h>

double DiskMonitor::getUsage() {
    struct statvfs info;

    if (statvfs("/", &info) != 0)
        return 0.0;

    unsigned long long total =
        info.f_blocks * info.f_frsize;

    unsigned long long available =
        info.f_bavail * info.f_frsize;

    if (total == 0)
        return 0.0;

    return 100.0 * (total - available) / total;
}