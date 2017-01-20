#ifndef YOUR_TEST_FOR_HOW_MANY_WAYS_TO_MAKE_H
#define YOUR_TEST_FOR_HOW_MANY_WAYS_TO_MAKE_H

#include "HowManyWaysToMake.h"


int testHowManyWaysToMake() {
    // TODO: your test case for question 1b goes inside this function, instead of the next line of code:

    const int result = howManyWaysToMake(5,{1,2,3});

    if(result == 5) {
        return 0;
    }



    return 1;
    
}


// Do not write any code below this line

#endif
