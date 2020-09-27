#include <string>

class Date {
 public:
    int our_year, our_month, our_day;
    Date(int year, int month, int day) {
        our_year = year;
        our_month = month;
        our_day = day;
    }
    bool IsLeap() const {
        if ((our_year % 4 == 0 && our_year % 100 != 0) || our_year % 400 == 0) {
            return true;
        } else {
            return false;
        }
    }
    std::string ToString() const {
        std::string date = "";
        if (our_day < 10) {
            date = "0" + std::to_string(our_day) + ".";
        } else {
            date = std::to_string(our_day) + ".";
        }
        if (our_month > 0 && our_month < 10) {
            date += "0" + std::to_string(our_month) + ".";
        } else {
            date += std::to_string(our_month) + ".";
        }
        int size = std::to_string(our_year).length();
        if (size != 4) {
            for (int i = 0; i < 4 - size; i++) {
                date += "0";
            }
            return date + std::to_string(our_year);
        } else {
            return date + std::to_string(our_year);
        }
    }
    Date DaysLater(int days) const {
        int all_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int day = our_day, month = our_month, year = our_year;
        if (!IsLeap()) {
            if (days <= all_month[month - 1] - day) {
                Date new_date(year, month, day + days);
                return new_date;
            }
        } else if (IsLeap()) {
            all_month[1] = 29;
            if (days <= all_month[month - 1] - day) {
                Date new_date(year, month, day + days);
                return new_date;
            }
        }
        while (days != 0) {
            if (!((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
                all_month[1] = 28;
                if (all_month[month - 1] - day <= days) {
                    int end = all_month[month - 1] - day + 1;
                    days -= end;
                    day = 1;
                    if (month == 12) {
                        month = 1;
                        year += 1;
                    } else {
                        month += 1;
                    }
                } else {
                    day += days;
                    days = 0;
                }
            } else {
                all_month[1] = 29;
                if (all_month[month - 1] - day <= days) {
                    int end = all_month[month - 1] - day + 1;
                    days -= end;
                    day = 1;
                    if (month == 12) {
                        month = 1;
                        year += 1;
                    } else {
                        month += 1;
                    }
                } else {
                    day += days;
                    days = 0;
                }
            }
        }
        Date new_date(year, month, day);
        return new_date;
    }
    int DaysLeft(const Date& date) const {
        int all_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int day = date.our_day, month = date.our_month, year = date.our_year;
        if (day == our_day && month == our_month && year == our_year) {
            return 0;
        }
        int first_days = 0;
        int second_days = 0;
        if ((our_year % 4 == 0 && our_year % 100 != 0) || our_year % 400 == 0) {
            all_month[1] = 29;
        }
        if (our_month == 1) {
            first_days = our_day;
        } else {
            for (int i = 0; i < our_month - 1; i++) {
                first_days += all_month[i];
            }
            first_days += our_day;
        }
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            all_month[1] = 29;
        } else {
            all_month[1] = 28;
        }
        if (month == 1) {
            second_days = day;
        } else {
            for (int i = 0; i < month - 1; i++) {
                second_days += all_month[i];
            }
            second_days += day;
        }
        if (year == our_year) {
            return (second_days - first_days);
        } else {
            int all_years = 0;
            for (int i = our_year; i < year; i++) {
                if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
                    all_years += 366;
                } else {
                    all_years += 365;
                }
            }
            return (all_years - first_days + second_days);
        }
    }
};
