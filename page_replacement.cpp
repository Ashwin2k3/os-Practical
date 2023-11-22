#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>

// LRU (Least Recently Used) Page Replacement Algorithm
int lruPageReplacement(std::vector<int>& pages, int capacity) {
    int pageFaults = 0;
    std::unordered_map<int, int> pageMap;
    std::vector<int> pageQueue;

    for (int page : pages) {
        if (pageMap.find(page) != pageMap.end()) {
            auto it = std::find(pageQueue.begin(), pageQueue.end(), page);
            pageQueue.erase(it);
        } else {
            ++pageFaults;
            if (pageQueue.size() == capacity) {
                int leastUsed = pageQueue.front();
                pageQueue.erase(pageQueue.begin());
                pageMap.erase(leastUsed);
            }
        }

        pageQueue.push_back(page);
        pageMap[page] = 1;
    }

    return pageFaults;
}

// FIFO (First-In-First-Out) Page Replacement Algorithm
int fifoPageReplacement(std::vector<int>& pages, int capacity) {
    int pageFaults = 0;
    std::queue<int> pageQueue;
    std::unordered_map<int, int> pageMap;

    for (int page : pages) {
        if (pageMap.find(page) != pageMap.end()) {
            continue;
        } else {
            ++pageFaults;
            if (pageQueue.size() == capacity) {
                int frontPage = pageQueue.front();
                pageQueue.pop();
                pageMap.erase(frontPage);
            }
        }

        pageQueue.push(page);
        pageMap[page] = 1;
    }

    return pageFaults;
}

// Optimal Page Replacement Algorithm
int optimalPageReplacement(std::vector<int>& pages, int capacity) {
    int pageFaults = 0;
    std::unordered_map<int, int> pageMap;

    for (size_t i = 0; i < pages.size(); ++i) {
        if (pageMap.find(pages[i]) != pageMap.end()) {
            continue;
        } else {
            ++pageFaults;
            if (pageMap.size() == capacity) {
                int farthestPage = -1;
                int farthestIndex = std::numeric_limits<int>::max();

                for (const auto& entry : pageMap) {
                    int nextPage = entry.first;
                    size_t j = i + 1;
                    while (j < pages.size() && pages[j] != nextPage) {
                        ++j;
                    }

                    if (j == pages.size()) {
                        farthestPage = nextPage;
                        break;
                    } else if (j > farthestIndex) {
                        farthestIndex = j;
                        farthestPage = nextPage;
                    }
                }

                pageMap.erase(farthestPage);
            }
        }

        pageMap[pages[i]] = i;
    }

    return pageFaults;
}

int main() {
    std::vector<int> pages = {2, 3, 1, 4, 2, 5, 3, 4, 5, 2};
    int capacity = 3;

    std::cout << "pages = {2, 3, 1, 4, 2, 5, 3, 4, 5, 2} \n";
    std::cout << "Page Replacement using LRU: " << lruPageReplacement(pages, capacity) << " page faults\n";
    std::cout << "Page Replacement using FIFO: " << fifoPageReplacement(pages, capacity) << " page faults\n";
    std::cout << "Page Replacement using Optimal: " << optimalPageReplacement(pages, capacity) << " page faults\n";

    return 0;
}

