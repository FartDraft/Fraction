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
    Fraction() : _number(0llU), _numerator(0llU), _denominator(1llU), _sign(false) {}

    Fraction(const Fraction& fraction)
        : _number(fraction._number), _numerator(fraction._numerator), _denominator(fraction._denominator),
          _sign(fraction._sign) {}

    Fraction(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
             bool sign = false) {
        this->assign(number, numerator, denominator, sign);
    }

    Fraction(double fraction, double err = 1e-10) { this->from_double(fraction, err); }

    // Pattern: r"([+-])?(?:(?:(\d+) (\d+)\/(\d+))|(?:(\d+)\/(\d+))|(\d+)|(\d*\.\d*))"
    Fraction(const std::string& fraction) { this->from_string(fraction); }

    // Setters
    constexpr const Fraction&
    zero() {
        this->_sign = false;
        this->_number = 0llU;
        this->_numerator = 0llU;
        this->_denominator = 1llU;

        return *this;
    }

    constexpr const Fraction&
    copy(const Fraction& fraction) {
        this->_number = fraction._number;
        this->_numerator = fraction._numerator;
        this->_denominator = fraction._denominator;
        this->_sign = fraction._sign;

        return *this;
    }

    const Fraction& assign(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
                           bool sign = false);
    const Fraction& from_double(double fraction, double err = 1e-10);
    // Pattern: r"([+-])?(?:(?:(\d+) (\d+)\/(\d+))|(?:(\d+)\/(\d+))|(\d+)|(\d*\.\d*))"
    const Fraction& from_string(const std::string& fraction);

    // Cast
    constexpr
    operator bool() const {
        return this->_number != 0 or this->_numerator != 0;
    }

    constexpr
    operator double() const {
        return (this->_sign ? -1.0 : 1.0)
               * (static_cast<double>(this->_number)
                  + static_cast<double>(this->_numerator) / static_cast<double>(this->_denominator));
    }

    operator std::string() const {
        // Pattern: r"-?(\d+ \d+/\d+|\d+/\d+|\d+)"
        return (this->_sign ? "-" : "") + std::basic_string(this->_number == 0 and this->_numerator == 0 ? "0" : "")
               + (this->_number == 0 ? "" : std::to_string(this->_number))
               + (this->_number == 0 or this->_numerator == 0 ? "" : " ")
               + (this->_numerator == 0 ? ""
                                        : std::to_string(this->_numerator) + "/" + std::to_string(this->_denominator));
    }

    // Assignment
    Fraction& operator=(const Fraction& other) = default;
    Fraction& operator=(Fraction&& other) = default;

    Fraction&
    operator=(double fraction) {
        this->from_double(fraction);
        return *this;
    }

    Fraction&
    operator=(const std::string& fraction) {
        this->from_string(fraction);
        return *this;
    }

    // Stream
    friend std::ostream&
    operator<<(std::ostream& os, const Fraction& obj) {
        os << std::string(obj);
        return os;
    }

    friend std::istream&
    operator>>(std::istream& is, Fraction& obj) {
        std::string input;
        is >> input;
        obj.from_string(input);
        return is;
    }

    // Increment and decrement
    Fraction&
    operator++() {
        if (this->_sign and --this->_number == 0) {
            this->_sign = false;
        } else {
            ++this->_number;
        }
        return *this;
    }

    Fraction
    operator++(int) {
        Fraction old(*this);
        operator++();
        return old;
    }

    Fraction&
    operator--() {
        if (not this->_sign) {
            if (this->_number == 0) {
                this->_number = 1;
                this->_sign = true;
            } else if (--this->_number == 0) {
                this->_sign = true;
            }
        } else {
            ++this->_number;
        }
        return *this;
    }

    Fraction
    operator--(int) {
        Fraction old(*this);
        operator--();
        return old;
    }

    // Comparison Fraction
    friend constexpr int
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
    friend constexpr int
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
    friend constexpr int
    cmp(const I& b, const Fraction& a) {
        return cmp(a, b);
    }

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
    constexpr unsigned long long
    number() const {
        return this->_number;
    }

    constexpr unsigned long long
    numerator() const {
        return this->_numerator;
    }

    constexpr unsigned long long
    denominator() const {
        return this->_denominator;
    }

    constexpr bool
    sign() const {
        return this->_sign;
    }

  private:
    unsigned long long _number, _numerator, _denominator;
    bool _sign;
};

} // namespace fraction
