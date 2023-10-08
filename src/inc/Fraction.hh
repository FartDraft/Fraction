#pragma once
#include <iostream>
#include <string>

class Fraction {
  public:
    typedef unsigned long long ull_t;
    typedef long double ld_t;

    explicit Fraction(ull_t number = 0, ull_t numerator = 0, ull_t denominator = 1, bool sign = false);
    explicit Fraction(const Fraction& fraction);
    // explicit Fraction(ld_t fraction);
    // explicit Fraction(std::string fraction);

    ull_t get_number() const;
    ull_t get_numerator() const;
    ull_t get_denominator() const;
    bool get_sign() const;

  private:
    ull_t number, numerator, denominator;
    bool sign;

    ull_t gcd(ull_t a, ull_t b) const;
};
