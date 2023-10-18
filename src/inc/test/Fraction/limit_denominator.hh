#include "_utility.hh"

TEST(LimitDenominator, LimitEquals0) {
    ASSERT_DEATH(
        {
            Fraction fraction("7/77");
            fraction.limit_denominator(0);
        },
        "limit of denominator should be at least 1!");
}

TEST(LimitDenominator, Default) {
    Fraction b("245850922/78256779");

    ASSERT_EQ(b.limit_denominator() == b, true);
}

TEST(LimitDenominator, Simple) {
    Fraction b("3/7");

    ASSERT_EQ(b.limit_denominator(6) == Fraction("2/5"), true);
}

TEST(LimitDenominator, Pi7) {
    Fraction b("245850922/78256779");

    ASSERT_EQ(b.limit_denominator(7) == Fraction("22/7"), true);
}

TEST(LimitDenominator, Pi106) {
    Fraction b("245850922/78256779");

    ASSERT_EQ(b.limit_denominator(106) == Fraction("333/106"), true);
}

TEST(LimitDenominator, Pi113) {
    Fraction b("-245850922/78256779");

    ASSERT_EQ(b.limit_denominator(130) == Fraction("-355/113"), true);
}
