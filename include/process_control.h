#ifndef PROCESS_CONTROL_H
#define PROCESS_CONTROL_H

class ProcessControl {
public:
    static void sendSignal(int pid, int signalNumber);
};

#endif