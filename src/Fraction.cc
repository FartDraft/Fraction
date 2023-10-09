#include "inc/Fraction.hh"

unsigned long long
Fraction::gcd(unsigned long long a, unsigned long long b) const {
    if (a == 0llU) {
        return b;
    }
    if (b == 0llU) {
        return a;
    }
    return a < b ? gcd(a, b % a) : gcd(b, a % b);
}

Fraction::Fraction(unsigned long long number, unsigned long long numerator, unsigned long long denominator, bool sign) {
    if (denominator == 0llU) {
        std::cerr << "Denominator may not be 0!" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->sign = sign;
    if (numerator > denominator) {
        number += numerator / denominator;
        numerator %= denominator;
    }
    this->number = number;
    unsigned long long gcd_ = gcd(numerator, denominator);
    this->numerator = numerator / gcd_;
    this->denominator = denominator / gcd_;
}

Fraction::Fraction(const Fraction& fraction) {
    this->number = fraction.number;
    this->numerator = fraction.numerator;
    this->denominator = fraction.denominator;
    this->sign = fraction.sign;
}

// Fraction::Fraction(double fraction, unsigned long long precision) {
//     if (precision == 0) {
//         std::cerr << "Precision may not be 0!" << std::endl;
//         exit(EXIT_FAILURE);
//     }
//     if (fraction < 0) {
//         this->sign = true;
//     }
//     this->number = static_cast<int>(fraction);
//     unsigned long long numerator = (fraction - this->number) * precision;
//     unsigned long long gcd_ = gcd(numerator, precision);
//     this->numerator = numerator / gcd_;
//     this->denominator = precision / gcd_;
// }

unsigned long long
Fraction::get_number() const {
    return this->number;
}

unsigned long long
Fraction::get_numerator() const {
    return this->numerator;
}

unsigned long long
Fraction::get_denominator() const {
    return this->denominator;
}

bool
Fraction::get_sign() const {
    return this->sign;
}
