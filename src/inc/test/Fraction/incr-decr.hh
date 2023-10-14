#include "_utility.hh"

TEST(Increment, Plus) {
    Fraction a;
    ++a;
    Fraction b(1);

    ASSERT_EQ(a == b, true);
}

TEST(Increment, Minus) {
    Fraction a(-1);
    Fraction b = a++;

    ASSERT_EQ(a == ++b, true);
}

TEST(Decrement, Plus) {
    Fraction a;
    --a;
    Fraction b(-1);

    ASSERT_EQ(a == b, true);
}

TEST(Decrement, Minus) {
    Fraction a(1);
    Fraction b = a--;

    ASSERT_EQ(a == --b, true);
}
