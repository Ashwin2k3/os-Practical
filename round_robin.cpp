#include <iostream>
#include <vector>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    Process(int id, int at, int bt) : processID(id), arrivalTime(at), burstTime(bt), remainingTime(bt), 
                                      completionTime(0), turnaroundTime(0), waitingTime(0) {}
};

void roundRobinScheduling(std::vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].remainingTime > 0) {
                int executeTime = std::min(processes[i].remainingTime, timeQuantum);
                processes[i].remainingTime -= executeTime;
                currentTime += executeTime;

                if (processes[i].remainingTime == 0) {
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    ++completedProcesses;
                }
            }
        }
    }
}

int main() {
    std::vector<Process> processes = {
        {1, 0, 5},
        {2, 1, 3},
        {3, 2, 8},
        {4, 3, 6},
        {5, 4, 7}
    };

    int timeQuantum = 3; // Set the time quantum

    std::cout << "Initial Input Processes:" << std::endl;
    std::cout << "Process ID\tArrival Time\tBurst Time\n";
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.arrivalTime << "\t\t"
                  << process.burstTime << std::endl;
    }
    std::cout << std::endl;

    roundRobinScheduling(processes, timeQuantum);

    std::cout << "Final Process Metrics:" << std::endl;
    std::cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.arrivalTime << "\t\t"
                  << process.burstTime << "\t\t"
                  << process.completionTime << "\t\t"
                  << process.turnaroundTime << "\t\t"
                  << process.waitingTime << std::endl;
    }

    return 0;
}

