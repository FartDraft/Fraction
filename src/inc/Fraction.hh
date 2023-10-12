#pragma once
#define PCRE2_CODE_UNIT_WIDTH 8
#include <cmath>
#include <iostream>
#include <numeric>
#include <pcre2.h>
#include <string>

namespace fraction {

class Fraction {
  public:
    // Constructors
    explicit Fraction();
    explicit Fraction(const Fraction& fraction);
    explicit Fraction(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
                      bool sign = false);
    explicit Fraction(double fraction, double err = 1e-10);
    explicit Fraction(const std::string& fraction);

    // Setters
    const Fraction& zero();
    const Fraction& copy(const Fraction& fraction);
    const Fraction& assign(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
                           bool sign = false);
    const Fraction& from_double(double fraction, double err = 1e-10);
    const Fraction& from_string(const std::string& fraction);

    // to_double
    // to_string

    // Comparison Fraction
    friend constexpr int cmp(const Fraction& a, const Fraction& b);

    friend constexpr bool
    operator==(const Fraction& lhs, const Fraction& rhs) {
        return cmp(lhs, rhs) == 0;
    }

    friend constexpr bool
    operator!=(const Fraction& lhs, const Fraction& rhs) {
        return cmp(lhs, rhs) != 0;
    }

    friend constexpr bool
    operator<(const Fraction& lhs, const Fraction& rhs) {
        return cmp(lhs, rhs) < 0;
    }

    friend constexpr bool
    operator>(const Fraction& lhs, const Fraction& rhs) {
        return cmp(lhs, rhs) > 0;
    }

    friend constexpr bool
    operator<=(const Fraction& lhs, const Fraction& rhs) {
        return cmp(lhs, rhs) <= 0;
    }

    friend constexpr bool
    operator>=(const Fraction& lhs, const Fraction& rhs) {
        return cmp(lhs, rhs) >= 0;
    }

    // Comparison Integer
    template <typename I>
    friend constexpr int cmp(const Fraction& a, const I& b);
    template <typename I>
    friend constexpr int cmp(const I& b, const Fraction& a);

    template <typename I>
    friend constexpr bool
    operator==(const Fraction& lhs, const I& rhs) {
        return cmp(lhs, rhs) == 0;
    }

    template <typename I>
    friend constexpr bool
    operator==(const I& rhs, const Fraction& lhs) {
        return cmp(lhs, rhs) == 0;
    }

    template <typename I>
    friend constexpr bool
    operator!=(const Fraction& lhs, const I& rhs) {
        return cmp(lhs, rhs) != 0;
    }

    template <typename I>
    friend constexpr bool
    operator!=(const I& rhs, const Fraction& lhs) {
        return cmp(lhs, rhs) != 0;
    }

    template <typename I>
    friend constexpr bool
    operator<(const Fraction& lhs, const I& rhs) {
        return cmp(lhs, rhs) < 0;
    }

    template <typename I>
    friend constexpr bool
    operator<(const I& rhs, const Fraction& lhs) {
        return cmp(lhs, rhs) < 0;
    }

    template <typename I>
    friend constexpr bool
    operator>(const Fraction& lhs, const I& rhs) {
        return cmp(lhs, rhs) > 0;
    }

    template <typename I>
    friend constexpr bool
    operator>(const I& rhs, const Fraction& lhs) {
        return cmp(lhs, rhs) > 0;
    }

    template <typename I>
    friend constexpr bool
    operator<=(const Fraction& lhs, const I& rhs) {
        return cmp(lhs, rhs) <= 0;
    }

    template <typename I>
    friend constexpr bool
    operator<=(const I& rhs, const Fraction& lhs) {
        return cmp(lhs, rhs) <= 0;
    }

    template <typename I>
    friend constexpr bool
    operator>=(const Fraction& lhs, const I& rhs) {
        return cmp(lhs, rhs) >= 0;
    }

    template <typename I>
    friend constexpr bool
    operator>=(const I& rhs, const Fraction& lhs) {
        return cmp(lhs, rhs) >= 0;
    }

    // Getters
    unsigned long long number() const;
    unsigned long long numerator() const;
    unsigned long long denominator() const;
    bool sign() const;

  private:
    unsigned long long _number, _numerator, _denominator;
    bool _sign;
};

constexpr int
cmp(const Fraction& a, const Fraction& b) {
    if (a._sign and not b._sign) {
        return -1;
    }
    if (not a._sign and b._sign) {
        return 1;
    }
    if (a._number < b._number) {
        return -1;
    }
    if (a._number > b._number) {
        return 1;
    }
    unsigned long long denominator = std::lcm(a._denominator, b._denominator);
    unsigned long long a_numerator = a._numerator * (denominator / a._denominator);
    unsigned long long b_numerator = b._numerator * (denominator / b._denominator);
    if (a_numerator < b_numerator) {
        return -1;
    }
    if (a_numerator > b_numerator) {
        return 1;
    }
    return 0;
}

template <typename I>
constexpr int
cmp(const Fraction& a, const I& b) {
    if (a._sign and b > 0) {
        return -1;
    }
    if (not a._sign and b < 0) {
        return 1;
    }
    unsigned long long a_int = a._number;
    unsigned long long b_int = b;
    if (a_int < b_int) {
        return -1;
    }
    if (a_int > b_int) {
        return 1;
    }
    if (a._numerator != 0) {
        return 1;
    }
    return 0;
}

template <typename I>
constexpr int
cmp(const I& b, const Fraction& a) {
    return cmp(a, b);
}

} // namespace fraction
