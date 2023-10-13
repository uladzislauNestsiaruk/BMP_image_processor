#include "rational.h"

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {
}  // NOLINT

Rational::Rational(int numer, int denom) {
    int divisor = std::gcd(numer, denom);
    numer_ = numer / divisor;
    denom_ = denom / divisor;
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
    numer_ = numer;
    denom_ = denom;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int new_numer = lhs.numer_ * rhs.denom_ + lhs.denom_ * rhs.numer_;
    int new_denom = lhs.denom_ * rhs.denom_;
    int divisor = std::__gcd(abs(new_denom), new_numer);
    lhs.Set(lhs.numer_ / divisor, lhs.denom_ / divisor);
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int new_numer = lhs.numer_ * rhs.numer_;
    int new_denom = lhs.denom_ * rhs.denom_;
    int divisor = std::__gcd(abs(new_denom), new_numer);
    lhs.Set(lhs.numer_ / divisor, lhs.denom_ / divisor);
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
    Rational temporary(rhs.GetDenominator(), rhs.GetNumerator());
    if (temporary.GetDenominator() < 0) {
        temporary.SetNumerator(-temporary.GetNumerator());
        temporary.SetDenominator(-temporary.GetDenominator());
    }
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
    Rational temporary(rhs.GetDenominator(), rhs.GetNumerator());
    if (temporary.GetDenominator() < 0) {
        temporary.SetNumerator(-temporary.GetNumerator());
        temporary.SetDenominator(-temporary.GetDenominator());
    }
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