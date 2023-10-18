#pragma once

#include <stdexcept>
#include <iostream>
#include <numeric>

class RationalDivisionByZero : public std::runtime_error {
public:
    RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
    }
};

class Rational {
public:
    Rational();

    Rational(int64_t value);  // NOLINT

    Rational(int64_t numer, int64_t denom);

    int64_t GetNumerator() const;

    int64_t GetDenominator() const;

    void SetNumerator(int64_t value);

    void SetDenominator(int64_t value);

    friend Rational& operator+=(Rational& lhs, const Rational& rhs);

    friend Rational& operator*=(Rational& lhs, const Rational& rhs);

    friend Rational& operator++(Rational& ratio);  // faster than += 1

    friend Rational& operator--(Rational& ratio);

    friend std::istream& operator>>(std::istream& is, Rational& ratio);

private:
    void Set(int64_t numer, int64_t denom);

    int64_t numer_;
    int64_t denom_;
};

Rational operator+(const Rational& ratio);

Rational operator-(const Rational& ratio);

Rational& operator-=(Rational& lhs, const Rational& rhs);

Rational& operator/=(Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);

Rational operator-(const Rational& lhs, const Rational& rhs);

Rational operator*(const Rational& lhs, const Rational& rhs);

Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator++(Rational& ratio, int);

Rational operator--(Rational& ratio, int);

bool operator<(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);

bool operator!=(const Rational& lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& os, const Rational& ratio);
