#include "inc/Fraction.hh"

Fraction::ull_t
Fraction::gcd(ull_t a, ull_t b) const {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    return a < b ? gcd(a, b % a) : gcd(b, a % b);
}

Fraction::Fraction(ull_t number, ull_t numerator, ull_t denominator, bool sign) {
    if (denominator == 0) {
        std::cerr << "Denominator may not be 0!" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->sign = sign;
    if (numerator > denominator) {
        number += numerator / denominator;
        numerator %= denominator;
    }
    this->number = number;
    ull_t gcd_ = gcd(numerator, denominator);
    this->numerator = numerator / gcd_;
    this->denominator = denominator / gcd_;
}

Fraction::Fraction(const Fraction& fraction) {
    this->number = fraction.number;
    this->numerator = fraction.numerator;
    this->denominator = fraction.denominator;
    this->sign = fraction.sign;
}

Fraction::ull_t
Fraction::get_number() const {
    return this->number;
}

Fraction::ull_t
Fraction::get_numerator() const {
    return this->numerator;
}

Fraction::ull_t
Fraction::get_denominator() const {
    return this->denominator;
}

bool
Fraction::get_sign() const {
    return this->sign;
}
