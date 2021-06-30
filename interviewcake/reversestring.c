#include <assert.h>
#include <stdio.h>

// Interview Cake C Unit Test Framework, based on CuTest
#include "Cake/UnitTest.h"

// my solution

#if 0
void reverse(char *str)
{
    // reverse input string in place
    size_t stringSize, loopCount;

    // identify the size of the string
    for(loopCount = 0; str[loopCount] != '/0', loopCount++) {}

    stringSize = loopCount;

    for(loopCount = 0; loopCount <= stringSize/2 , loopCount++) {
        char tempChar = str[loopCount];
        str[loopCount] = str[stringSize - loopCount];
        str[stringSize - loopCount] = tempChar;
    }

}

#else
// based on the solution
void reverse(char *str){
    size_t leftindex, rightindex = 0, length = strlen(str);
    char temp;

    if(length == 0)
        return;
    
    rightindex = length - 1;
    while (leftindex < rightindex)
    {
        /* code */
        // swap
        temp = str[leftindex];
        str[leftindex] = str[rightindex];
        str[rightindex] = temp;

        leftindex++;
        rightindex--;
    }
    
}

#endif
















// tests

void emptyStringTest(Test *tc)
{
    const char *expected = "";
    char actual[] = "";
    reverse(actual);
    AssertStrEquals(tc, expected, actual);
}

void singleCharacterStringTest(Test *tc)
{
    const char *expected = "A";
    char actual[] = "A";
    reverse(actual);
    AssertStrEquals(tc, expected, actual);
}

void longerStringTest(Test *tc)
{
    const char *expected = "EDCBA";
    char actual[] = "ABCDE";
    reverse(actual);
    AssertStrEquals(tc, expected, actual);
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, emptyStringTest);
    SUITE_ADD_TEST(tests, singleCharacterStringTest);
    SUITE_ADD_TEST(tests, longerStringTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}