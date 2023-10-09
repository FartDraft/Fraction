#pragma once
#include <iostream>
#include <string>

class Fraction {
  public:
    explicit Fraction(unsigned long long number, unsigned long long numerator, unsigned long long denominator,
                      bool sign = false);
    explicit Fraction(const Fraction& fraction);
    // explicit Fraction(std::string fraction);

    unsigned long long get_number() const;
    unsigned long long get_numerator() const;
    unsigned long long get_denominator() const;
    bool get_sign() const;

  private:
    unsigned long long number, numerator, denominator;
    bool sign;

    /**
     * @brief Computes the greatest common divisor (GCD) of two numbers.
     *
     * @param a The first number.
     * @param b The second number.
     * @return The greatest common divisor of the input numbers.
     */
    unsigned long long gcd(unsigned long long a, unsigned long long b) const;
};
