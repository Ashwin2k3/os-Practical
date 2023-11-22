#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    bool executed;

    Process(int id, int at, int bt, int prio) : processID(id), arrivalTime(at), burstTime(bt), priority(prio), 
                                               completionTime(0), turnaroundTime(0), waitingTime(0), 
                                               responseTime(-1), executed(false) {}
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool comparePriority(const Process& a, const Process& b) {
    return a.priority < b.priority;
}

void priorityScheduling(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;
    std::vector<bool> completed(processes.size(), false);

    while (completedProcesses < processes.size()) {
        std::sort(processes.begin(), processes.end(), comparePriority);

        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        for (size_t i = 0; i < processes.size(); ++i) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime && processes[i].priority < highestPriority) {
                highestPriorityIndex = i;
                highestPriority = processes[i].priority;
            }
        }

        if (highestPriorityIndex != -1) {
            completed[highestPriorityIndex] = true;
            processes[highestPriorityIndex].completionTime = currentTime + processes[highestPriorityIndex].burstTime;
            processes[highestPriorityIndex].turnaroundTime = processes[highestPriorityIndex].completionTime - processes[highestPriorityIndex].arrivalTime;
            processes[highestPriorityIndex].waitingTime = processes[highestPriorityIndex].turnaroundTime - processes[highestPriorityIndex].burstTime;
            
            if (!processes[highestPriorityIndex].executed) {
                processes[highestPriorityIndex].responseTime = currentTime - processes[highestPriorityIndex].arrivalTime;
                processes[highestPriorityIndex].executed = true;
            }

            currentTime = processes[highestPriorityIndex].completionTime;
            ++completedProcesses;
        } else {
            ++currentTime;
        }
    }
}

int main() {
    std::vector<Process> processes = {
        {1, 0, 6, 3},
        {2, 1, 3, 1},
        {3, 2, 8, 2},
        {4, 3, 7, 4},
        {5, 4, 4, 5}
    };

    std::cout << "Initial Input Processes:" << std::endl;
    std::cout << "Process ID\tArrival Time\tBurst Time\tPriority\n";
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.arrivalTime << "\t\t"
                  << process.burstTime << "\t\t"
                  << process.priority << std::endl;
    }
    std::cout << std::endl;

    priorityScheduling(processes);

    std::cout << "Final Process Metrics:" << std::endl;
    std::cout << "Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n";
    for (const auto& process : processes) {
        std::cout << process.processID << "\t\t"
                  << process.arrivalTime << "\t\t"
                  << process.burstTime << "\t\t"
                  << process.priority << "\t\t"
                  << process.completionTime << "\t\t"
                  << process.turnaroundTime << "\t\t"
                  << process.waitingTime << "\t\t"
                  << process.responseTime << std::endl;
    }

    return 0;
}

