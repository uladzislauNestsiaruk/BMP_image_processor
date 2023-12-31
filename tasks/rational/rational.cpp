#include "rational.h"

bool FractionReducing(int64_t& numerator, int64_t& denominator) {
    if (denominator == 0) {
        return false;
    }
    int64_t divisor = std::__gcd(llabs(numerator), llabs(denominator));
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

Rational::Rational(int64_t value) : numer_(value), denom_(1) {
}  // NOLINT

Rational::Rational(int64_t numer, int64_t denom) {
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    numer_ = numer;
    denom_ = denom;
}

int64_t Rational::GetDenominator() const {
    if (denom_ == 0) {
        throw RationalDivisionByZero{};
    }
    return denom_;
}

int64_t Rational::GetNumerator() const {
    return numer_;
}

void Rational::SetDenominator(int64_t value) {
    denom_ = value;
    if (!FractionReducing(numer_, denom_)) {
        throw RationalDivisionByZero{};
    }
}

void Rational::SetNumerator(int64_t value) {
    numer_ = value;
    if (!FractionReducing(numer_, denom_)) {
        throw RationalDivisionByZero{};
    }
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t divisor = std::__gcd<int64_t>(llabs(numer), llabs(denom));
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
    int64_t new_numer = lhs.numer_ * rhs.denom_ + lhs.denom_ * rhs.numer_;
    int64_t new_denom = lhs.denom_ * rhs.denom_;
    if (!FractionReducing(new_numer, new_denom)) {
        throw RationalDivisionByZero{};
    }
    lhs.Set(new_numer, new_denom);
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int64_t new_numer = lhs.numer_ * rhs.numer_;
    int64_t new_denom = lhs.denom_ * rhs.denom_;
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
    is >> ratio.numer_;
    if (is.peek() == '/') {
        is.ignore(1);
        if (!(is >> ratio.denom_)) {
            return is;
        }
    }
    if (!FractionReducing(ratio.numer_, ratio.denom_)) {
        throw RationalDivisionByZero{};
    }
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
    int64_t numer = rhs.GetDenominator();
    int64_t denom = rhs.GetNumerator();
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    Rational temporary(numer, denom);
    lhs *= temporary;
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int64_t numer = lhs.GetNumerator() * rhs.GetDenominator() + lhs.GetDenominator() * rhs.GetNumerator();
    int64_t denom = lhs.GetDenominator() * rhs.GetDenominator();
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    Rational result(numer, denom);
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return lhs + (-rhs);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int64_t numer = lhs.GetNumerator() * rhs.GetNumerator();
    int64_t denom = lhs.GetDenominator() * rhs.GetDenominator();
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    Rational result(numer, denom);
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int64_t numer = rhs.GetDenominator();
    int64_t denom = rhs.GetNumerator();
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
    int64_t numer = ratio.GetNumerator();
    int64_t denom = ratio.GetDenominator();
    if (!FractionReducing(numer, denom)) {
        throw RationalDivisionByZero{};
    }
    os << numer;
    if (denom > 1) {
        os << "/" << denom;
    }
    return os;
}