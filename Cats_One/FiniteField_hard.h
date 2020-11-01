#include "num.h"
#include <cstdint>

Num::Num(int value, int modulo) {
    this->modulo = modulo;
    if (modulo == 0) {
        this->value = value;
    } else {
        this->value = value % modulo;
    }
}
Num &Num::operator=(const Num& other) {
    value = other.value;
    return *this;
}
Num Num::operator+(const Num& other) {
    int64_t v = ((int64_t) value + (int64_t) other.value);
    return Num(v % modulo, modulo);
}
Num Num::operator-(const Num& other) {
    int new_value;
    if (value > other.value) {
        new_value = (value - other.value) % modulo;
    } else {
        new_value = (value + modulo - other.value) % modulo;
    }
    return Num(new_value, modulo);
}
Num Num::operator*(const Num& other) {
    int64_t a = ((int64_t) value * (int64_t) other.value);
    return Num(a % modulo, modulo);
}
Num Num::operator+(int num) {
    int64_t new_value = ((int64_t) value + (int64_t) num);
    return Num(new_value % modulo, modulo);
}
Num Num::operator-(int num) {
    int new_value;
    if (value > num) {
        new_value = (value - num) % modulo;
    } else {
        new_value = (value + modulo - num) % modulo;
    }
    return Num(new_value, modulo);
}
Num Num::operator*(int num) {
    int64_t answer = ((int64_t) value * (int64_t) num);
    return Num(answer % modulo, modulo);
}
Num &Num::operator+=(const Num& other) {
    int64_t v = ((int64_t) value + (int64_t) other.value);
    value = v % modulo;
    return *this;
}
Num &Num::operator-=(const Num& other) {
    if (value > other.value) {
        value = (value - other.value) % modulo;
    } else {
        value = (value + modulo - other.value) % modulo;
    }
    return *this;
}
Num &Num::operator*=(const Num& other) {
    int64_t a = ((int64_t) value * (int64_t) other.value);
    value = a % modulo;
    return *this;
}
Num &Num::operator+=(int num) {
    int64_t new_value = ((int64_t) value + (int64_t) num);
    value = new_value % modulo;
    return *this;
}
Num &Num::operator-=(int num) {
    if (value > num) {
        value = (value - num) % modulo;
    } else {
        value = (value + modulo - num) % modulo;
    }
    return *this;
}
Num &Num::operator*=(int num) {
    int64_t answer = ((int64_t) value * (int64_t) num);
    value = answer % modulo;
    return *this;
}
