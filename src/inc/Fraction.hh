#pragma once
#define PCRE2_CODE_UNIT_WIDTH 8
#include <iostream>
#include <numeric>
#include <pcre2.h>
#include <string>

class Fraction {
  public:
    Fraction();
    explicit Fraction(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
                      bool sign = false);
    explicit Fraction(const Fraction& fraction);
    explicit Fraction(std::string fraction);

    unsigned long long get_number() const;
    unsigned long long get_numerator() const;
    unsigned long long get_denominator() const;
    bool get_sign() const;

  private:
    unsigned long long number, numerator, denominator;
    bool sign;
};
