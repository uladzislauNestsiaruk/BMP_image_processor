#include "rational.h"

Rational::Rational(): numer_(0), denom_(1) {}

Rational::Rational(int value):numer_(value), denom_(1) {} // NOLINT

Rational::Rational(int numer, int denom): numer_(numer), denom_(denom){}

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
    int divisor = std::__gcd(new_denom, new_numer);
    lhs.Set(lhs.numer_ / divisor, lhs.denom_ / divisor);
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int new_numer = lhs.numer_ * rhs.numer_;
    int new_denom = lhs.denom_ * rhs.denom_;
    int divisor = std::__gcd(new_denom, new_numer);
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

}
