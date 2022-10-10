/**
 * @file Event.cpp
 * @author Adrian Hernandez (a01747038@tec.mx)
 * @brief Event class implementation
 * @version 0.1
 * @date 2022-09-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once 

#include <Event.hpp>

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <map>

void Event::constructMap() {
    monthsToNums["Jan"] = 1; 
    monthsToNums["Feb"] = 2;
    monthsToNums["Mar"] = 3;
    monthsToNums["Apr"] = 4;
    monthsToNums["May"] = 5;
    monthsToNums["Jun"] = 6;
    monthsToNums["Jul"] = 7;
    monthsToNums["Aug"] = 8;
    monthsToNums["Sep"] = 9;
    monthsToNums["Oct"] = 10;
    monthsToNums["Nov"] = 11;
    monthsToNums["Dec"] = 12;
}


void Event::updateNumIp(){
  std::stringstream ipStream;
  ipStream << ip;


  std::string ip_1;
  std::string ip_2;
  std::string ip_3;
  std::string ip_4;

  std::getline(ipStream, ip_1, '.');
  std::getline(ipStream, ip_2, '.');
  std::getline(ipStream, ip_3, '.');
  std::getline(ipStream, ip_4, ':');

  int value_ip1 = std::stoi(ip_1);
  int value_ip2 = std::stoi(ip_2);
  int value_ip3 = std::stoi(ip_3);
  int value_ip4 = std::stoi(ip_4);

  arrDate = {value_ip4, value_ip3, value_ip2, value_ip1};
  
    numIp = 0;
    
    numIp += value_ip4 * std::pow(1000, 3);
    numIp += value_ip3 * std::pow(1000, 2);
    numIp += value_ip2 * 1000;
    numIp += value_ip1;
  

}

/* No sé si este funcione 

void Event::updateNumIp() {
  std::stringstream ipStream;
  ipStream << ip;

  std::string ip_value;
  numIp = 0;
  int counter = 13;
  
  while(getc(ipStream)!= ':'){
    
    counter--;
    
    if(getc(ipStream) == '.'){
      getc(ipStream);
    }
    
    ip_value = getc(ipStream);
    int ip_nvalue = std::stoi(ip_value);
    
    numIp += ip_nvalue * std::pow(12, counter);
    
  }
  */
  
  }
void Event::updateNumDate() {
    std::stringstream dateStream;
    dateStream << date;

    // update arrDate

    std::string month;
    std::string day;
    std::string time;

    std::getline(dateStream, month, ' ');
    std::getline(dateStream, day, ' ');
    std::getline(dateStream, time, ' ');
        
    int nMonth = monthsToNums[month];
    int nDay = std::stoi(day);

    // pase time 
    std::stringstream timeStream;
    timeStream << time;

    std::string hour;
    std::string min;
    std::string sec;

    getline(timeStream, hour, ':');
    getline(timeStream, min, ':');
    getline(timeStream, sec, ':');

    int nHour = std::stoi(hour);
    int nMin = std::stoi(min);
    int nSec = std::stoi(sec);

    arrDate = {nMonth, nDay, nHour, nMin, nSec};
    
    // update numDate
    numDate = 0;
    
    numDate += nMonth * std::pow(60, 4);
    numDate += nDay * std::pow(60, 3);
    numDate += nHour * std::pow(60, 2);
    numDate += nMin * 60;
    numDate += nSec;
}

Event::Event() {
     constructMap();
}

Event::Event(std::string _message, std::string _ip, std::string _date) {
    constructMap();
    
    message = _message;
    ip = _ip;
    date = _date;
    updateNumDate();
    updateNumIp();
}

std::string Event::getMessage() const {
    return message;
}

std::string Event::getIp() const {
    return ip;
}

std::string Event::getDate() const {
    return date;
}

void Event::setMessage(std::string _message) {
    message = _message;
}

void Event::setIp(std::string _ip) {
    ip = _ip;
    updateNumIp();
  
}

void Event::setDate(std::string _date) {
    date = _date;
    updateNumDate();
}

int Event::getNumDate() const {
    return numDate;
}

int Event::getNumIp() const {
    return numIp;
}


std::vector<int> Event::getArrDate() const {
    return arrDate;
}

void Event::loadData(std::string data) {
    std::stringstream dataStream;
    dataStream << data;

    std::stringstream dateStream;
    std::stringstream ipStream;
    std::stringstream messageStream;
    

    std::string temp;
    
    // add date data
    for (int i=0; i<3; i++) {
        std::getline(dataStream, temp, ' ');
        dateStream << temp << " ";
    }

    // add the ip data
    for (int i=0; i<1; i++) {
        
      while (std::getline(dataStream, temp, ':')) {
        ipStream << temp << ' '; 
    
          }
    
      }

   // add the rest of the message
    while (std::getline(ipStream, temp, ' ')) {
       messageStream << temp << " "; 
    }

    date = dateStream.str();
    ip = ipStream.str();
    message = messageStream.str();

    updateNumDate();
    updateNumIp();
}

std::string Event::str() const {
    std::stringstream msg;
    msg << date << " " << ip << " " << message; 
    return msg.str();
}