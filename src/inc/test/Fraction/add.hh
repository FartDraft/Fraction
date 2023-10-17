#include "_utility.hh"

TEST(PlusFraction, PosPos) {
    Fraction a(0, 1, 2);
    Fraction b(1, 1, 2);

    ASSERT_EQ(a + b == 2, true);
}

TEST(PlusFraction, NegNeg) {
    Fraction a(0, 1, 2, true);
    Fraction b(1, 1, 2, true);

    ASSERT_EQ(a + b == -2, true);
}

TEST(PlusFraction, EqEq) {
    Fraction a(0, 1, 2, true);
    Fraction b(0, 1, 2);

    ASSERT_EQ(a + b == 0, true);
}

TEST(PlusFraction, EqGreat) {
    Fraction a(0, 1, 2);
    Fraction b(0, 1, 5, true);

    ASSERT_EQ(a + b == 0.3, true);
}

TEST(PlusFraction, EqLess) {
    Fraction a(0, 1, 5);
    Fraction b(0, 1, 2, true);

    ASSERT_EQ(a + b == -0.3, true);
}

TEST(PlusFraction, GreatEq) {
    Fraction a(1, 1, 2);
    Fraction b(0, 1, 2, true);

    ASSERT_EQ(a + b == 1, true);
}

TEST(PlusFraction, GreatGreat) {
    Fraction a(2, 1, 2);
    Fraction b(1, 1, 5, true);

    ASSERT_EQ(a + b == 1.3, true);
}

TEST(PlusFraction, GreatLess) {
    Fraction a(2, 1, 5);
    Fraction b(1, 1, 2, true);

    ASSERT_EQ(a + b == 0.7, true);
}

TEST(PlusFraction, LessEq) {
    Fraction a(0, 1, 2);
    Fraction b(1, 1, 2, true);

    ASSERT_EQ(a + b == -1, true);
}

TEST(PlusFraction, LessLess) {
    Fraction a(1, 1, 5);
    Fraction b(2, 1, 2, true);

    ASSERT_EQ(a + b == -1.3, true);
}

TEST(PlusFraction, LessGreat) {
    Fraction a(0, 1, 2);
    Fraction b(1, 1, 4, true);

    ASSERT_EQ(a + b == -0.75, true);
}

TEST(MinusFraction, PosPos) {
    Fraction a;
    Fraction b;

    ASSERT_EQ(a - b == 0, true);
}

TEST(MinusFraction, NegNeg) {
    Fraction a(0, 1, 5, true);
    Fraction b(1, 1, 4, true);

    ASSERT_EQ(a - b == 1.05, true);
}

TEST(MinusFraction, PosNeg) {
    Fraction a(0, 1, 2);
    Fraction b(1, 1, 4, true);

    ASSERT_EQ(a - b == 1.75, true);
}

TEST(MinusFraction, NegPos) {
    Fraction a(0, 1, 5, true);
    Fraction b(1, 1, 4);

    ASSERT_EQ(a - b == -1.45, true);
}
