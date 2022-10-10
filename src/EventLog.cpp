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
#include <cmath>

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

int EventLog::getEventIndex(Event event) const {
    // gets the index of the event with the closest date to date
    
    // date = { month, day, hour, min, sec }
    // num value searched for comparison

    int lower = 0;    
    int upper = events.size();
    int middle = (lower + upper) / 2;

    while (lower <= upper) {
        middle = (lower + upper) / 2;
        if (events[middle].getNumDate() == event.getNumDate()) {
            return middle;
        }
        if (events[middle].getNumDate() < event.getNumDate()) {
            lower = middle + 1;
        } else {
            upper = middle - 1;
        }
    } 
    return middle;
}


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

void EventLog::saveEvents(std::string filePath) {
    std::ofstream mfile(filePath);

    for (Event event: events) {
        mfile << event.str() << "\n";
    }
    mfile.close();
}

std::vector<Event> EventLog::getEventsByRange(std::string startDate, 
                                              std::string endDate) const {
    // return 
    std::vector<Event> selectedEvents;
    Event startEvent("dummy message", startDate);
    Event endEvent("dummy message", endDate);
    
    int start = getEventIndex(startEvent);

    while (events[start].getNumDate() >= startEvent.getNumDate() && 
           events[start].getNumDate() <= endEvent.getNumDate()) {
        selectedEvents.push_back(events[start]);
        start++;
    }
    return selectedEvents;
}

void EventLog::displayEvents() const {
    for (Event event: events) {
        std::cout << event.str() << std::endl;
    }
}