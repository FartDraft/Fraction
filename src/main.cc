#include "inc/Fraction.hh"

int
main() {
    Fraction fraction(1, false);
    std::cout << fraction << std::endl;
    fraction = Fraction(3.1415);
    std::cout << fraction << std::endl;
    fraction = Fraction(7, 55, 13); // 11 3/13
    std::cout << fraction << std::endl;
    std::cin >> fraction;
    std::cout << fraction << std::endl;
}
