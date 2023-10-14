#include "_utility.hh"

// Fraction
TEST(AssignmentFraction, _) {
    Fraction a("-3/5");
    Fraction b;
    b = a;

    ASSERT_EQ(a == b, true);
}

// Double
TEST(AssignmentDouble, _) {
    double a = 3.14;
    Fraction b;
    b = a;

    ASSERT_EQ(a == double(b), true);
}

// String
TEST(AssignmentString, _) {
    std::string a = "3 7/50";
    Fraction b;
    b = a;

    ASSERT_EQ(a == std::string(b), true);
}
