#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

struct MemoryBlock {
    int blockSize;
    bool allocated;

    MemoryBlock(int size) : blockSize(size), allocated(false) {}
};

void printMemory(const std::vector<MemoryBlock>& memory) {
    std::cout << "Memory Blocks:" << std::endl;
    std::cout << "Block ID\tBlock Size\tAllocated" << std::endl;
    for (size_t i = 0; i < memory.size(); ++i) {
        std::cout << i + 1 << "\t\t" << memory[i].blockSize << "\t\t" << (memory[i].allocated ? "Yes" : "No") << std::endl;
    }
    std::cout << std::endl;
}

// First Fit Memory Allocation Algorithm
void firstFit(std::vector<MemoryBlock>& memory, int processSize) {
    for (size_t i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].blockSize >= processSize) {
            memory[i].allocated = true;
            std::cout << "First Fit: Process of size " << processSize << " allocated in block of size " << memory[i].blockSize << std::endl;
            return;
        }
    }
    std::cout << "First Fit: Unable to allocate process of size " << processSize << std::endl;
}

// Best Fit Memory Allocation Algorithm
void bestFit(std::vector<MemoryBlock>& memory, int processSize) {
    int bestFitIndex = -1;
    int minBlockSize = INT_MAX;

    for (size_t i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].blockSize >= processSize && memory[i].blockSize < minBlockSize) {
            bestFitIndex = i;
            minBlockSize = memory[i].blockSize;
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = true;
        std::cout << "Best Fit: Process of size " << processSize << " allocated in block of size " << memory[bestFitIndex].blockSize << std::endl;
    } else {
        std::cout << "Best Fit: Unable to allocate process of size " << processSize << std::endl;
    }
}

// Worst Fit Memory Allocation Algorithm
void worstFit(std::vector<MemoryBlock>& memory, int processSize) {
    int worstFitIndex = -1;
    int maxBlockSize = INT_MIN;

    for (size_t i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].blockSize >= processSize && memory[i].blockSize > maxBlockSize) {
            worstFitIndex = i;
            maxBlockSize = memory[i].blockSize;
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = true;
        std::cout << "Worst Fit: Process of size " << processSize << " allocated in block of size " << memory[worstFitIndex].blockSize << std::endl;
    } else {
        std::cout << "Worst Fit: Unable to allocate process of size " << processSize << std::endl;
    }
}

int main() {
    std::vector<MemoryBlock> memory = {
        MemoryBlock(100),
        MemoryBlock(500),
        MemoryBlock(200),
        MemoryBlock(300),
        MemoryBlock(600)
    };

    printMemory(memory);

    int processSize = 350;

    firstFit(memory, processSize);
    bestFit(memory, processSize);
    worstFit(memory, processSize);

    // Display final allocation in tabular form
    std::cout << "\nFinal Memory Allocation:" << std::endl;
    std::cout << std::left << std::setw(15) << "Block ID" << std::setw(15) << "Block Size" << std::setw(15) << "Allocated" << std::endl;
    for (size_t i = 0; i < memory.size(); ++i) {
        std::cout << std::setw(15) << i + 1 << std::setw(15) << memory[i].blockSize << std::setw(15) << (memory[i].allocated ? "Yes" : "No") << std::endl;
    }

    return 0;
}

