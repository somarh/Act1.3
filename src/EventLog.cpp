/**
 * @file EventLog.cpp
 * @author Adrian Hernandez (a01747038@tec.mx)
 * @brief 
 * @version 0.1
 * @date 2022-09-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <iostream>
#include <fstream>
#include <string>   
#include <vector>

#include <EventLog.hpp>

#include "Event.cpp"

// bucket sort events
void EventLog::sortEvents(int start, int end, int level) {
    // level of sorting (month = 0, day = 1, hour = 2, min = 3, sec = 4)
    // there is nothing to be sorted at level 5
    if (level > 4 || level < 0) {
        return;
    }

    // buckets for sorting
    std::vector<Event> buckets[60];
    

    for (int i=start; i<end; i++) {
        Event event = events[i];
        // index for bucket sorting
        int index = event.getArrDate()[level];
        buckets[index].push_back(event);
    }
    
    // same value in this level ranges
    std::vector<std::vector<int>> ranges;

    
    // we take into consideration that we have no more events than what we can fit
    // in the range we are given [start, end)

    for (std::vector<Event> bucket: buckets) {
        int curStart = start; // start of the partition of events in this bucket
        for (Event event: bucket) {
            events[start] = event;
            start++;
        }
        // if partition has length of more than 1 then register the range to sort it
        if (start - curStart > 1) {
            ranges.push_back({curStart, start});
        }
    }

    // increase level and then sort paritions with the same digit at this level
    level++;

    for (std::vector<int> range: ranges) {
        sortEvents(range[0], range[1], level);
    }
}

// void EventLog::getEventIndex(std::string date) const {
//     // gets the index of the event with the closest date to date
// }

void EventLog::loadEvents(std::string filePath) {
    std::ifstream mfile(filePath);

    std::string row;
    Event *event;

    while (std::getline(mfile, row, '\n')) {
        event = new Event();
        event->loadData(row);
        events.push_back(*event);
    }
    mfile.close();

    sortEvents(0, events.size(), 0);
}

// std::vector<Event> EventLog::getEventsByRange(std::string lowerDate, 
//                                               std::string upperDate) const {
    
// }

void EventLog::displayEvents() const {
    for (Event event: events) {
        std::cout << event.str() << std::endl;
    }
}