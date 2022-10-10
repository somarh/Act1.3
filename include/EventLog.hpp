/**
 * @file EventLog.hpp
 * @author Adrian Hernandez (a01747038@tec.mx)
 * @brief EventLog class declaration
 * @version 0.1
 * @date 2022-09-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>
#include <vector>

#include "Event.hpp"

class EventLog {
    private:
        std::vector<Event> events;
    
        // radix sort like events 
        void sortEvents(int, int, int);

        // get index position of event with given date
        int getEventIndex(Event) const;


    public:
        EventLog() = default;

        void loadEvents(std::string);
        std::vector<Event> getEventsByRange(std::string, std::string) const; 

        // for registering 
        void saveEvents(std::string);
        
        // for vizualization
        void displayEvents() const;
};
