#include "_utility.hh"

// Bool
TEST(CastBool, Zero) {
    Fraction a(0);

    ASSERT_EQ(bool(a), false);
}

TEST(CastBool, FractionOnly) {
    Fraction a(0, 1, 10);

    ASSERT_EQ(bool(a), true);
}

TEST(CastBool, Operator) {
    Fraction a(3);
    Fraction b(0);

    ASSERT_EQ(a and not b, true);
}

// Double
TEST(CastDouble, _) {
    Fraction a(-3.15);

    ASSERT_EQ(double(a), -3.15);
}

// String
TEST(CastString, _) {
    Fraction a("-3 3/15");

    ASSERT_EQ(std::string(a), "-3 1/5");
}
