#include "SimpleDate.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

SimpleDate::SimpleDate(int day, int month, int year)
    : day(day), month(month), year(year)
{
    // Basic validation
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1) {
        throw invalid_argument("Invalid date");
    }
    // Further validation can be added (e.g., check for leap years, days in month)
}

int SimpleDate::GetDay() const {
    return day;
}

int SimpleDate::GetMonth() const {
    return month;
}

int SimpleDate::GetYear() const {
    return year;
}

time_t SimpleDate::ToTimeT() const {
    tm tm = {};
    tm.tm_mday = day;
    tm.tm_mon = month - 1; // tm_mon is 0-based
    tm.tm_year = year - 1900; // tm_year is years since 1900
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1; // Not considering daylight saving
    return mktime(&tm);
}

int SimpleDate::DaysDifference(const SimpleDate& other) const {
    time_t t1 = this->ToTimeT();
    time_t t2 = other.ToTimeT();
    double diff = difftime(t2, t1);
    return static_cast<int>(diff / (60 * 60 * 24));
}

string SimpleDate::ToString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << day << "-"
        << setw(2) << setfill('0') << month << "-"
        << year;
    return oss.str();
}
