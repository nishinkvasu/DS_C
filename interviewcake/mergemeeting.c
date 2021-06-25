#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Interview Cake C Unit Test Framework, based on CuTest
//#include "Cake/UnitTest.h"

typedef struct {
    unsigned int startTime;
    unsigned int endTime;
} Meeting;

size_t mergeRanges(const Meeting *input, size_t inputLength,
                   Meeting *output, size_t maxOutputLength)
{
    // Meeting localCopy[inputLength];
    // memcpy((void *)localCopy, (void *)input, inputLength * sizeof(Meeting));
    memcpy((void *)output, (void *)input, inputLength * sizeof(Meeting));
    // merge meeting ranges
    for(size_t i = 0; i < inputLength; i++){
        for(size_t j = i+1; j < inputLength; j++){
            // printf("startTime = %d\n", input[i].startTime);
            // printf("endTime = %d\n", input[i].endTime);
            
            
            // sort the input array
            if(output[i].startTime > output[j].startTime)
            {
                /// swap
                unsigned int tempVar;
                tempVar = output[i].startTime;
                output[i].startTime = output[j].startTime;
                output[j].startTime = tempVar;
                
                tempVar = output[i].endTime;
                output[i].endTime = output[j].endTime;
                output[j].endTime = tempVar;
            }
        }
    }
    size_t x = 0;
    
    for(size_t i = 0; i < inputLength-x; i++){
        // iterate through the array and see 
        // check if the endtime of i is greater than or equal to (i+1)'s start time
        while((output[i].endTime >= output[i+1].startTime) && (i < (inputLength - x -1))){
            // do the merge
            if(output[i].endTime < output[i+1].endTime)
                output[i].endTime = output[i+1].endTime;
            
            x++;
        
            for(size_t j = i+1; j < inputLength-1; j++){
                output[j].startTime =  output[j+1].startTime;
                output[j].endTime =  output[j+1].endTime;
            }
    // const Meeting meetings[] = { {1, 4}, {2, 5}, {5, 8} };
    // const Meeting expected[] = { {1, 8} };
        }
    }
    
    maxOutputLength = inputLength - x;
    for(size_t i = 0; i < inputLength; i++){
        // printf("startTime = %d\n", output[i].startTime);
        // printf("endTime = %d\n", output[i].endTime);
    }
    

    return maxOutputLength;
}


// tests

#define countof(a) (sizeof(a)/sizeof((a)[0]))

char * meetingToString(const void *arg)
{
    const Meeting *meeting = arg;
    const size_t BUFFER_SIZE = 25;
    char *buffer = malloc(BUFFER_SIZE);

    assert(buffer != NULL);
    snprintf(buffer, BUFFER_SIZE, "(%u, %u)", meeting->startTime, meeting->endTime);
    return buffer;
}

void meetingsOverlapTest(Test *tc)
{
    const Meeting meetings[] = { {1, 3}, {2, 4} };
    const Meeting expected[] = { {1, 4} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

void meetingsTouchTest(Test *tc)
{
    const Meeting meetings[] = { {5, 6}, {6, 8} };
    const Meeting expected[] = { {5, 8} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

void meetingContainsOtherMeetingTest(Test *tc)
{
    const Meeting meetings[] = { {1, 8}, {2, 5} };
    const Meeting expected[] = { {1, 8} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

void meetingsStaySeparateTest(Test *tc)
{
    const Meeting meetings[] = { {1, 3}, {4, 8} };
    const Meeting expected[] = { {1, 3}, {4, 8} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

void multipleMergedMeetingsTest(Test *tc)
{
    const Meeting meetings[] = { {1, 4}, {2, 5}, {5, 8} };
    const Meeting expected[] = { {1, 8} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

void meetingsNotSortedTest(Test *tc)
{
    const Meeting meetings[] = { {5, 8}, {1, 4}, {6, 8} };
    const Meeting expected[] = { {1, 4}, {5, 8} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

void oneLongMeetingContainsSmallerMeetingsTest(Test *tc)
{
    const Meeting meetings[] = { {1, 10}, {2, 5}, {6, 8}, {9, 10}, {10, 12} };
    const Meeting expected[] = { {1, 12} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

void sampleInputTest(Test *tc)
{
    const Meeting meetings[] = { {0, 1}, {3, 5}, {4, 8}, {10, 12}, {9, 10} };
    const Meeting expected[] = { {0, 1}, {3, 8}, {9, 12} };
    Meeting actual[countof(meetings)] = { {0, 0} };

    const size_t actualCount = mergeRanges(meetings, countof(meetings),
                                           actual, countof(actual));
    AssertSizeEquals(tc, countof(expected), actualCount);
    AssertStructArrayEquals(tc, expected, actual, countof(expected),
                            sizeof(Meeting), meetingToString);
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, meetingsOverlapTest);
    SUITE_ADD_TEST(tests, meetingsTouchTest);
    SUITE_ADD_TEST(tests, meetingContainsOtherMeetingTest);
    SUITE_ADD_TEST(tests, meetingsStaySeparateTest);
    SUITE_ADD_TEST(tests, multipleMergedMeetingsTest);
    SUITE_ADD_TEST(tests, meetingsNotSortedTest);
    SUITE_ADD_TEST(tests, oneLongMeetingContainsSmallerMeetingsTest);
    SUITE_ADD_TEST(tests, sampleInputTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}