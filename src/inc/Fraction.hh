#pragma once
#include <cmath>
#include <iostream>

class Fraction {
  public:
    typedef unsigned long long ull_t;
    typedef long double ld_t;

    bool minus;
    ull_t number, numerator, denominator, precision = 10'000'000'000'000'000'000U;

    Fraction() : minus(false), number(0), numerator(0), denominator(1) {}

    Fraction(ull_t number, bool minus) : minus(minus), number(number), numerator(0), denominator(1) {}

    Fraction(ull_t number, ull_t numerator, ull_t denominator, bool minus = false);
    Fraction(ld_t fraction);

    // assign all =
    // ~Fraction destructor;
    // Fraction get_numerator() const;
    // Need
    // Fraction& operator=(const Fraction&);
    // Fraction& assign(...?);
    // numerator()
    // denominator()
    // ...
    // access

    // TODO: Change Precision

  private:
    // bool minus;
    // ull_t number, numerator, denominator, precision = 10'000'000'000'000'000'000U;
    ull_t gcd(ull_t a, ull_t b);
};

// Unary operators
// Fraction operator+(const Fraction& fraction);
// and more

// Input and output
// TODO: Generate annotation
std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
std::istream& operator>>(std::istream& is, Fraction& fraction);
