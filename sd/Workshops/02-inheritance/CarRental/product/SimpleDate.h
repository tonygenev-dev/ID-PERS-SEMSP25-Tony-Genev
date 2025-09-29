#pragma once

#include <string>
#include <time.h>

using namespace std;

class SimpleDate {
public:
    // Constructor
    SimpleDate(int day, int month, int year);

    // Getters
    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;

    // Returns the number of days between this date and another
    int DaysDifference(const SimpleDate& other) const;

    // String representation in DD-MM-YYYY
    string ToString() const;

private:
    int day;
    int month;
    int year;

    // Helper: convert to time_t
    time_t ToTimeT() const;
};
