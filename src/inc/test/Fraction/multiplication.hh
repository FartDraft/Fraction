#include "_utility.hh"

TEST(MulFraction, Zero) {
    Fraction a(0);
    Fraction b(1, 1, 2);

    ASSERT_EQ(a * b == 0, true);
}

TEST(MulFraction, PosPos) {
    Fraction a(0.5);
    Fraction b(1);

    ASSERT_EQ(a * b == 0.5, true);
}

TEST(MulFraction, NegNeg) {
    Fraction a(-0.1);
    Fraction b(-0.1);

    ASSERT_EQ(a * b == 0.01, true);
}

TEST(MulFraction, PosNeg) {
    Fraction a(0.5);
    Fraction b(-2);

    ASSERT_EQ(a * b == -1, true);
}

TEST(MulFraction, NegPos) {
    Fraction a(0, 1, 7, true);
    Fraction b(49);

    ASSERT_EQ(a * b == -7, true);
}

TEST(DivFraction, Zero) {
    ASSERT_DEATH(
        {
            Fraction a(0, 1, 7, true);
            Fraction b(0);
            a / b;
        },
        "division by 0!");
}

TEST(DivFraction, _) {
    Fraction a(-1);
    Fraction b(0, 1, 7);

    ASSERT_EQ(a / b == -7, true);
}
