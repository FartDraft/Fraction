#include "_utility.hh"

// Fraction
TEST(CmpFraction, Equal0) {
    Fraction a;
    Fraction b;

    ASSERT_EQ(cmp(a, b), 0);
}

TEST(CmpFraction, EqualFractionReduce) {
    Fraction a(3, 11, 5);
    Fraction b(5, 1, 5);

    ASSERT_EQ(cmp(a, b), 0);
}

TEST(CmpFraction, Less) {
    Fraction a(2.71);
    Fraction b(3.14);

    ASSERT_EQ(cmp(a, b), -1);
}

TEST(CmpFraction, Greater) {
    Fraction a("3.14");
    Fraction b("2.71");

    ASSERT_EQ(cmp(a, b), 1);
}

TEST(CmpFraction, WithMinus) {
    Fraction a("-5 119/130");
    Fraction b("0 1/2");

    ASSERT_EQ(cmp(a, b), -1);
}

// Double
TEST(CmpDouble, Zero) {
    Fraction a(0.1);

    ASSERT_EQ(cmp(a, 0), 1);
}

TEST(CmpDouble, Equal) {
    Fraction a("2/100");

    ASSERT_EQ(cmp(a, 0.02), 0);
}

// String
TEST(CmpString, Equal) {
    Fraction a(-1.7);

    ASSERT_EQ(cmp(a, "-17/10"), 0);
}
