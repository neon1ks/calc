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
	
	std::string strIn   = {"    (a + b)"};
	std::string strOut;
	bool errorStatus = {false};
	bool actual;
	bool expected;
	unsigned int i = {0};
	unsigned int out = {0};
	
	out = parse_brackets(strIn, strOut, errorStatus, i);
	
	actual = !strOut.compare("a + b");
	expected = true;
    ASSERT_EQ(expected, actual);
    
    expected = false;
    ASSERT_EQ(expected, errorStatus);
    
    ASSERT_EQ((unsigned int)10, out);
    
}

TEST(test003, test)
{
	
	std::string strIn = {"  d  (a + b)"};
	std::string strOut;
	bool errorStatus = {false};
	bool expected;
	unsigned int i = {0};
	unsigned int out = {0};
		
	out = parse_brackets(strIn, strOut, errorStatus, i);
	
	expected = true;
    ASSERT_EQ(expected, errorStatus);
    
    ASSERT_EQ((unsigned int)2, out);
    
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}

