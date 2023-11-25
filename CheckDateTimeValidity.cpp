#include <iostream>
#include <stdexcept>
#include <array>

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};
using namespace std;

//начало измененного кода

void CheckRange(int value, int min_value, int max_value, const string& error_message) {
    if (value < min_value || value > max_value) {
        throw domain_error(error_message);
    }
}

void CheckDateTimeValidity(const DateTime& dt) {
    CheckRange(dt.year, 1, 9999, "year is out of valid range"s);
    CheckRange(dt.month, 1, 12, "month is out of valid range"s);

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    CheckRange(dt.day, 1, month_lengths[dt.month - 1], "day is out of valid range"s);
    CheckRange(dt.hour, 0, 23, "hour is out of valid range"s);
    CheckRange(dt.minute, 0, 59, "minute is out of valid range"s);
    CheckRange(dt.second, 0, 59, "second is out of valid range"s);
}

//конец измененного кода

int main() {
    try {
        // Пример использования CheckDateTimeValidity
        DateTime dt{2023, 11, 15, 14, 30, 45};
        CheckDateTimeValidity(dt);
        std::cout << "Date and time are valid." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
