#include "rational.h"

bool FractionReducing(int& numerator, int& denominator) {
    if (denominator == 0) {
        return false;
    }
    int divisor = std::__gcd(abs(numerator), abs(denominator));
    numerator /= divisor;
    denominator /= divisor;
    if (denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }
    return true;
}

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {
}  // NOLINT

Rational::Rational(int numer, int denom) {
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    numer_ = numer;
    denom_ = denom;
}

int Rational::GetDenominator() const {
    return denom_;
}

int Rational::GetNumerator() const {
    return numer_;
}

void Rational::SetDenominator(int value) {
    denom_ = value;
}

void Rational::SetNumerator(int value) {
    numer_ = value;
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int divisor = std::__gcd(llabs(numer), llabs(denom));
    if (denom < 0) {
        denom *= -1;
        numer *= -1;
    }
    numer /= divisor;
    denom /= divisor;
    numer_ = static_cast<int>(numer);
    denom_ = static_cast<int>(denom);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int new_numer = lhs.numer_ * rhs.denom_ + lhs.denom_ * rhs.numer_;
    int new_denom = lhs.denom_ * rhs.denom_;
    if (!FractionReducing(new_numer, new_denom)) {
        throw RationalDivisionByZero{};
    }
    lhs.Set(new_numer, new_denom);
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int new_numer = lhs.numer_ * rhs.numer_;
    int new_denom = lhs.denom_ * rhs.denom_;
    if (!FractionReducing(new_numer, new_denom)) {
        throw RationalDivisionByZero{};
    }
    lhs.Set(new_numer, new_denom);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    is >> ratio.numer_ >> ratio.denom_;
    return is;
}

Rational operator+(const Rational& ratio) {
    Rational result(ratio.GetNumerator(), ratio.GetDenominator());
    return result;
}

Rational operator-(const Rational& ratio) {
    Rational result(-ratio.GetNumerator(), ratio.GetDenominator());
    return result;
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += -rhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    int numer = rhs.GetDenominator();
    int denom = rhs.GetNumerator();
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    Rational temporary(numer, denom);
    return lhs *= temporary;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs.GetNumerator() * rhs.GetDenominator() + lhs.GetDenominator() * rhs.GetNumerator(),
                    lhs.GetDenominator() * rhs.GetDenominator());
    int divisor = std::__gcd(abs(result.GetNumerator()), result.GetDenominator());
    result.SetNumerator(result.GetNumerator() / divisor);
    result.SetDenominator(result.GetDenominator() / divisor);
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return lhs + (-rhs);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator());
    int divisor = std::__gcd(abs(result.GetDenominator()), result.GetNumerator());
    result.SetNumerator(result.GetNumerator() / divisor);
    result.SetDenominator(result.GetDenominator() / divisor);
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int numer = rhs.GetDenominator();
    int denom = rhs.GetNumerator();
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    Rational temporary(numer, denom);
    return lhs * temporary;
}

Rational operator++(Rational& ratio, int) {
    Rational old_value(ratio.GetNumerator(), ratio.GetDenominator());
    ++ratio;
    return old_value;
}

Rational operator--(Rational& ratio, int) {
    Rational old_value(ratio.GetNumerator(), ratio.GetDenominator());
    --ratio;
    return old_value;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator());
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetDenominator() == rhs.GetDenominator() && lhs.GetNumerator() == rhs.GetNumerator());
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator() << " " << ratio.GetDenominator();
    return os;
}