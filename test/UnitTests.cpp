#include "libs.h"
#include "gtest/gtest.h"

TEST(test001, test)
{
    bool actual;
    bool expected;

    actual = check_brackets("a + b * (a + b)");
    expected = true;
    ASSERT_EQ(expected, actual);

    actual = check_brackets("sin(x) + cos(y)");
    expected = true;
    ASSERT_EQ(expected, actual);

    actual = check_brackets("(a + b) * (a - b * (a - b))");
    expected = true;
    ASSERT_EQ(expected, actual);

    actual = check_brackets("a + b * (a + b))");
    expected = false;
    ASSERT_EQ(expected, actual);

    actual = check_brackets("a + b * ((a + b)");
    expected = false;
    ASSERT_EQ(expected, actual);
}

TEST(test002, test)
{
    bool actual;
    bool expected;
    std::string str;

    str = "a + b - c * d / e ^ f";
    actual = (check_symbols(str) == str.size());
    expected = true;
    ASSERT_EQ(expected, actual);

    str = "sin(0.5) + cos(0,5)";
    actual = (check_symbols(str) == str.size());
    expected = true;
    ASSERT_EQ(expected, actual);

    str = "(a_b * c_d)";
    actual = (check_symbols(str) == str.size());
    expected = true;
    ASSERT_EQ(expected, actual);

    str = "a + b & (a + b))";
    actual = (check_symbols(str) == str.size());
    expected = false;
    ASSERT_EQ(expected, actual);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
