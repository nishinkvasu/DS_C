#include <assert.h>
#include <stdio.h>

// Interview Cake C Unit Test Framework, based on CuTest
//#include "Cake/UnitTest.h"

// sample message - message[] = "cake pound steal";
void reverseWords(char *message)
{
    // decode the message by reversing the words
    // identify the length of the message
    size_t stringLength = strlen(message);
    // cake pound steal --  extract steal and place it in front
    printf("%d\n",stringLength);
    char *msgCopy = (char *)malloc((stringLength+1) * sizeof(char));
    // copy message to temporary buffer
    memcpy(msgCopy, message, stringLength);
    
    for(size_t i = 0; i < stringLength; i++)
        printf("%c",msgCopy[i]);

    printf("\n");
    // iterate from back from last index to first space (increment a local count)
    size_t subStringLength = 0,i = stringLength, j = 0;
    char c = ' ';
    do{
        i--;
        // reducing the length first to avoid the null character
        if((msgCopy[i] != c) && (i != 0)){
            subStringLength++;
        }
        else{
            if(i == 0){
                //subStringLength++;
                printf("%c", msgCopy[i]);
            }

            for(j = 0; j<subStringLength; j++){
                printf("%c", msgCopy[i+1+j]);
            }
            printf("\n");
            subStringLength = 0;
        }

    }while(i);
    // when it hits the space start a loop to copy from that point + 1 for the length of count


    free(msgCopy);
}


















// tests

void oneWordTest(/*Test *tc*/)
{
    const char *expected = "get another one";
    char actual[] = "one another get";
    reverseWords(actual);
    //AssertStrEquals(tc, expected, actual);
}

// void twoWordsTest(Test *tc)
// {
//     const char *expected = "cake thief";
//     char actual[] = "thief cake";
//     reverseWords(actual);
//     AssertStrEquals(tc, expected, actual);
// }

// void threeWordsTest(Test *tc)
// {
//     const char *expected = "get another one";
//     char actual[] = "one another get";
//     reverseWords(actual);
//     AssertStrEquals(tc, expected, actual);
// }

// void multipleWordsSameLengthTest(Test *tc)
// {
//     const char *expected = "the cat ate the rat";
//     char actual[] = "rat the ate cat the";
//     reverseWords(actual);
//     AssertStrEquals(tc, expected, actual);
// }

// void multipleWordsDifferentLengthsTest(Test *tc)
// {
//     const char *expected = "chocolate bundt cake is yummy";
//     char actual[] = "yummy is cake bundt chocolate";
//     reverseWords(actual);
//     AssertStrEquals(tc, expected, actual);
// }

// void emptyStringTest(Test *tc)
// {
//     const char *expected = "";
//     char actual[] = "";
//     reverseWords(actual);
//     AssertStrEquals(tc, expected, actual);
// }

int main()
{
    
    // TestSuite *tests = TestSuiteNew();

    // SUITE_ADD_TEST(tests, oneWordTest);
    // SUITE_ADD_TEST(tests, twoWordsTest);
    // SUITE_ADD_TEST(tests, threeWordsTest);
    // SUITE_ADD_TEST(tests, multipleWordsSameLengthTest);
    // SUITE_ADD_TEST(tests, multipleWordsDifferentLengthsTest);
    // SUITE_ADD_TEST(tests, emptyStringTest);

    // TestSuiteRun(tests);
    // TestSuiteDelete(tests);
    oneWordTest();
    return 0;
}