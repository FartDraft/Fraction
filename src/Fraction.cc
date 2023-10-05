#include "inc/Fraction.hh"

Fraction::ull_t
Fraction::gcd(ull_t a, ull_t b) {
    if (b == 0) {
        return a;
    }
    return a < b ? gcd(a, b % a) : gcd(b, a % b);
}

Fraction::Fraction(ull_t number, ull_t numerator, ull_t denominator, bool minus) {
    if (denominator == 0) {
        std::cerr << "Denominator may not be 0." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (numerator == 0) {
        // Fix?
        Fraction(number, minus);
    } else {
        this->minus = minus;
        this->number = number;
        if (numerator > denominator) {
            this->number += numerator / denominator;
            numerator %= denominator;
        }
        ull_t gcd_ = gcd(numerator, denominator);
        this->numerator = numerator / gcd_;
        this->denominator = denominator / gcd_;
    }
}

Fraction::Fraction(ld_t fraction) {
    if (fraction < 0) {
        this->minus = true;
    }
    this->number = static_cast<int>(fraction);
    ull_t numerator = (fraction - this->number) * this->precision;
    ull_t gcd_ = gcd(numerator, this->precision);
    this->numerator = numerator / gcd_;
    this->denominator = this->precision / gcd_;
}

std::ostream&
operator<<(std::ostream& os, const Fraction& fraction) {
    if (fraction.numerator == 0) {
        os << '0';
    } else {
        if (fraction.minus) {
            os << '-';
        }
        if (fraction.number != 0) {
            os << fraction.number << ' ';
        }
        os << fraction.numerator << '/' << fraction.denominator;
    }
    return os;
}

std::istream&
operator>>(std::istream& is, Fraction& fraction) {
    // TODO: In string and then Fraction(string)
    is >> fraction.number >> fraction.numerator >> fraction.denominator;
    return is;
}
