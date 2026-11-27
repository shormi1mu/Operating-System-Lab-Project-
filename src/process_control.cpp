#include "process_control.h"
#include <iostream>
#include <csignal>
#include <unistd.h>

void ProcessControl::sendSignal(int pid, int signalNumber) {
    if (pid <= 1) {
        std::cout << "Invalid PID.\n";
        return;
    }

    char answer;
    std::cout << "Send signal to PID " << pid
              << "? (y/n): ";
    std::cin >> answer;

    if (answer != 'y' && answer != 'Y')
        return;

    if (kill(pid, signalNumber) == 0)
        std::cout << "Signal sent successfully.\n";
    else
        perror("Signal failed");
}