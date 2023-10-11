#pragma once
#define PCRE2_CODE_UNIT_WIDTH 8
#include <cmath>
#include <iostream>
#include <numeric>
#include <pcre2.h>
#include <string>

class Fraction {
  public:
    explicit Fraction();
    explicit Fraction(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
                      bool sign = false);
    explicit Fraction(const Fraction& fraction);
    explicit Fraction(const std::string& fraction);
    explicit Fraction(double fraction, double err = 1e-10);

    const Fraction& zero();
    const Fraction& assign(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
                           bool sign = false);
    const Fraction& copy(const Fraction& fraction);
    const Fraction& from_string(const std::string& fraction);
    const Fraction& from_double(double fraction, double err = 1e-10);

    unsigned long long number() const;
    unsigned long long numerator() const;
    unsigned long long denominator() const;
    bool sign() const;

  private:
    unsigned long long _number, _numerator, _denominator;
    bool _sign;
};
