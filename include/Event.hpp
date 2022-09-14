#pragma once

#include <string>

class Event {
    private:
        std::string message;
        std::string date;

    public:
        Event() = default;
        Event(std::string, std::string);

        std::string getMessage() const;
        std::string getDate() const;

        void setMessage(std::string);
        void setDate(std::string);

        double getNumDate() const;

        void loadData(std::string);

        std::string str() const;
};