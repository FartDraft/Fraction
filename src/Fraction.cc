#include "inc/Fraction.hh"

using namespace fraction;

Fraction::Fraction() { this->zero(); }

Fraction::Fraction(const Fraction& fraction) { this->copy(fraction); }

Fraction::Fraction(unsigned long long number, unsigned long long numerator, unsigned long long denominator, bool sign) {
    this->assign(number, numerator, denominator, sign);
}

Fraction::Fraction(double fraction, double err) { this->from_double(fraction, err); }

Fraction::Fraction(const std::string& fraction) { this->from_string(fraction); }

const Fraction&
Fraction::zero() {
    this->_sign = false;
    this->_number = 0llU;
    this->_numerator = 0llU;
    this->_denominator = 1llU;

    return *this;
}

const Fraction&
Fraction::copy(const Fraction& fraction) {
    this->_number = fraction._number;
    this->_numerator = fraction._numerator;
    this->_denominator = fraction._denominator;
    this->_sign = fraction._sign;

    return *this;
}

const Fraction&
Fraction::assign(unsigned long long number, unsigned long long numerator, unsigned long long denominator, bool sign) {
    if (denominator == 0llU) {
        std::cerr << __PRETTY_FUNCTION__ << " : denominator may not be 0!" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->_sign = sign;
    if (numerator > denominator) {
        number += numerator / denominator;
        numerator %= denominator;
    }
    this->_number = number;
    unsigned long long gcd_ = std::gcd(numerator, denominator);
    this->_numerator = numerator / gcd_;
    this->_denominator = denominator / gcd_;

    return *this;
}

const Fraction&
Fraction::from_double(double fraction, double err) {
    unsigned long long numerator, denominator;
    double sign = fraction < 0 ? -1.0 : 1.0, g = std::abs(fraction);
    unsigned long long s, a = 0, b = 1, c = 1, d = 0;
    unsigned int iter = 0;
    do {
        s = std::floor(g);
        numerator = a + s * c;
        denominator = b + s * d;
        a = c;
        b = d;
        c = numerator;
        d = denominator;
        g = 1.0 / (g - s);
        if (err > std::abs(sign * numerator / denominator - fraction)) {
            this->assign(0, numerator, denominator, fraction < 0);
            return *this;
        }
    } while (iter++ < 1e6);

    std::cerr << __PRETTY_FUNCTION__ << " : failed to find a fraction for " << fraction << std::endl;
    exit(EXIT_FAILURE);
}

const Fraction&
Fraction::from_string(const std::string& fraction) {
    // Default values
    unsigned long long number = 0llU, numerator = 0llU, denominator = 1llU;
    bool sign = false;
    PCRE2_SPTR subject = (PCRE2_SPTR)fraction.c_str();

    int error_code;
    PCRE2_SIZE error_offset;
    const char regex_str[] = "([+-])?(?:(?:(\\d+) (\\d+)\\/(\\d+))|(?:(\\d+)\\/(\\d+))|(\\d+)|(\\d*\\.\\d*))";
    PCRE2_SPTR pattern = (PCRE2_SPTR)regex_str;
    pcre2_code* regex = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_ANCHORED | PCRE2_ENDANCHORED, &error_code,
                                      &error_offset, NULL);
    if (regex == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(error_code, buffer, sizeof(buffer));
        fprintf(stderr, "PCRE2 compilation failed at offset %d: %s\n", (int)error_offset, buffer);
        exit(EXIT_FAILURE);
    }

    pcre2_match_data* match_data = pcre2_match_data_create_from_pattern(regex, NULL);
    int group_count = pcre2_match(regex, subject, PCRE2_ZERO_TERMINATED, 0, PCRE2_NOTEMPTY, match_data, NULL);
    PCRE2_UCHAR* result;
    PCRE2_SIZE result_len;
    double real = -1.0;
    switch (group_count) {
        // number numerator/denominator
        case 5:
            pcre2_substring_get_bynumber(match_data, 2, &result, &result_len);
            number = std::stoull(std::string(result, result + result_len));
            pcre2_substring_free(result);

            pcre2_substring_get_bynumber(match_data, 3, &result, &result_len);
            numerator = std::stoull(std::string(result, result + result_len));
            pcre2_substring_free(result);

            pcre2_substring_get_bynumber(match_data, 4, &result, &result_len);
            denominator = std::stoull(std::string(result, result + result_len));
            pcre2_substring_free(result);
            break;
        // numerator/denominator
        case 7:
            pcre2_substring_get_bynumber(match_data, 5, &result, &result_len);
            numerator = std::stoull(std::string(result, result + result_len));
            pcre2_substring_free(result);

            pcre2_substring_get_bynumber(match_data, 6, &result, &result_len);
            denominator = std::stoull(std::string(result, result + result_len));
            pcre2_substring_free(result);
            break;
        // number
        case 8:
            pcre2_substring_get_bynumber(match_data, 7, &result, &result_len);
            number = std::stoull(std::string(result, result + result_len));
            pcre2_substring_free(result);
            break;
        // real
        case 9:
            pcre2_substring_get_bynumber(match_data, 8, &result, &result_len);
            if (result_len == 1) { // Dot only
                goto match_error;
            }
            real = std::stod(std::string(result, result + result_len));
            pcre2_substring_free(result);
            break;
        default:
        match_error:
            std::cerr << __PRETTY_FUNCTION__ << " : string: " << fraction << std::endl;
            std::cerr << "Does not match pattern: r" << '"' << regex_str << '"' << std::endl;
            exit(EXIT_FAILURE);
            break;
    }
    // sign
    if (pcre2_substring_get_bynumber(match_data, 1, &result, &result_len) != PCRE2_ERROR_UNSET) {
        sign = ('-' == result[0]);
        pcre2_substring_free(result);
    }

    if (real == -1.0) {
        this->assign(number, numerator, denominator, sign);
    } else {
        this->from_double(real);
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(regex);
    return *this;
}

unsigned long long
Fraction::number() const {
    return this->_number;
}

unsigned long long
Fraction::numerator() const {
    return this->_numerator;
}

unsigned long long
Fraction::denominator() const {
    return this->_denominator;
}

bool
Fraction::sign() const {
    return this->_sign;
}
