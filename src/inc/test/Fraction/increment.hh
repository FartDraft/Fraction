#include "_utility.hh"

TEST(Increment, Plus) {
    Fraction a(0.7);

    ASSERT_EQ(++a == 1.7, true);
}

TEST(Increment, Minus) {
    Fraction a(-0.7);
    a++;

    ASSERT_EQ(a == 0.3, true);
}

TEST(Decrement, Plus) {
    Fraction a(-0.3);

    ASSERT_EQ(--a == -1.3, true);
}

TEST(Decrement, Minus) {
    Fraction a(0.3);
    a--;

    ASSERT_EQ(a == -0.7, true);
}
