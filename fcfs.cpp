#include <iostream>
#include <vector>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
};

void FCFS(std::vector<Process>& processes) {
    int currentTime = 0;

    for (size_t i = 0; i < processes.size(); ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].completionTime = currentTime + processes[i].burstTime;
        currentTime = processes[i].completionTime;
    }
}

int main() {
    std::vector<Process> processes = {
        {1, 0, 5, 0},
        {2, 1, 3, 0},
        {3, 2, 8, 0},
        {4, 3, 6, 0},
        {5, 4, 7, 0}
    };

    std::cout << "Original Input Processes:" << std::endl;
    std::cout << "Process ID\tArrival Time\tBurst Time" << std::endl;
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.arrivalTime << "\t\t"
                  << process.burstTime << std::endl;
    }
    std::cout << std::endl;

    FCFS(processes);

    std::cout << "Completion Times After FCFS Scheduling:" << std::endl;
    std::cout << "Process ID\tCompletion Time" << std::endl;
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.completionTime << std::endl;
    }

    return 0;
}

