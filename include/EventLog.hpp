#pragma once

#include <string>
#include <vector>

#include "Event.hpp"

class EventLog {
    public:
        std::vector<Event> events;
    
        // radix sort like events
        void sortEvents();

        // get index position of event with given date
        int getEventIndex(std::string) const;

    private:
        EventLog() = default;

        void loadEvents(std::string);
        std::vector<Event> getEventsByRange(std::string, std::string) const; 
};
