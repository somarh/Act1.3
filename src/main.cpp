#include <iostream>
#include <vector>

#include "Event.cpp"
#include "EventLog.cpp"

void printVector(std::vector<int> arr) {
    for (int item: arr) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    EventLog el;
    // global path
    el.loadEvents("/mnt/c/Users/adrhe/AloritmosYEstrucutrasTec/Act1.3/src/bitacora.txt");
    el.displayEvents();
}