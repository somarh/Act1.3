#include <iostream>
#include <vector>

#include "Event.cpp"
#include "EventLog.cpp"

int main() {
    EventLog el;
    // global path of "bitacora.txt"
    el.loadEvents("/mnt/c/Users/adrhe/AloritmosYEstrucutrasTec/Act1.3/src/bitacora.txt");
    el.saveEvents("/mnt/c/Users/adrhe/AloritmosYEstrucutrasTec/Act1.3/src/ordenado.txt");
    
    // usuario
    std::string startDate, endDate;

    while (true) {
        std::cout << "To get events by range enter a start date and an end date in\n";
        std::cout << "the following format: (Oct 9 10:32:24) \n \n";

        std::cout << "START DATE: \n";
        std::getline(std::cin, startDate);
        std::cout << "END DATE: \n";
        std::getline(std::cin, endDate);

        std::vector<Event> events = el.getEventsByRange(startDate, endDate);
        std::cout << "DISPLAYING EVENTS IN RANGE \n";

        for (Event event: events) {
            std::cout << event.str() << "\n";
        }
    }
}