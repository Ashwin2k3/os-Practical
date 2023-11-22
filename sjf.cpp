#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    bool executed;

    Process(int id, int at, int bt) : processID(id), arrivalTime(at), burstTime(bt), completionTime(0),
                                       turnaroundTime(0), waitingTime(0), responseTime(-1), executed(false) {}
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

void SJF(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;
    std::vector<bool> completed(processes.size(), false);

    while (completedProcesses < processes.size()) {
        int shortestJobIndex = -1;
        int shortestJobTime = INT_MAX;

        for (size_t i = 0; i < processes.size(); ++i) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < shortestJobTime) {
                shortestJobIndex = i;
                shortestJobTime = processes[i].burstTime;
            }
        }

        if (shortestJobIndex != -1) {
            completed[shortestJobIndex] = true;
            processes[shortestJobIndex].completionTime = currentTime + processes[shortestJobIndex].burstTime;
            processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].completionTime - processes[shortestJobIndex].arrivalTime;
            processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].turnaroundTime - processes[shortestJobIndex].burstTime;
            
            if (!processes[shortestJobIndex].executed) {
                processes[shortestJobIndex].responseTime = currentTime - processes[shortestJobIndex].arrivalTime;
                processes[shortestJobIndex].executed = true;
            }

            currentTime = processes[shortestJobIndex].completionTime;
            ++completedProcesses;
        } else {
            ++currentTime;
        }
    }
}

int main() {
    std::vector<Process> processes = {
        {1, 0, 6},
        {2, 1, 3},
        {3, 2, 8},
        {4, 3, 7},
        {5, 4, 4}
    };

    std::cout << "Initial Input Processes:" << std::endl;
    std::cout << "Process ID\tArrival Time\tBurst Time\n";
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.arrivalTime << "\t\t"
                  << process.burstTime << std::endl;
    }
    std::cout << std::endl;

    SJF(processes);

    std::cout << "Final Process Metrics:" << std::endl;
    std::cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n";
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.arrivalTime << "\t\t"
                  << process.burstTime << "\t\t"
                  << process.completionTime << "\t\t"
                  << process.turnaroundTime << "\t\t"
                  << process.waitingTime << "\t\t"
                  << process.responseTime << std::endl;
    }

    return 0;
}

