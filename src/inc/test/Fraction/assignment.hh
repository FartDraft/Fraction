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

// Change assignment
TEST(ChangeAssignment, Plus) {
    Fraction a("3 7/20");
    Fraction b("13/20");
    a += b;

    ASSERT_EQ(a == 4, true);
}

TEST(ChangeAssignment, Minus) {
    Fraction a("3 7/20");
    Fraction b("7/20");
    a -= b;

    ASSERT_EQ(a == 3, true);
}

TEST(ChangeAssignment, Mul) {
    Fraction a("7/20");
    Fraction b("20");
    a *= b;

    ASSERT_EQ(a == 7, true);
}

TEST(ChangeAssignment, Div) {
    Fraction a("7/20");
    Fraction b("13/20");
    a /= b;

    ASSERT_EQ(a == Fraction("7/13"), true);
}
