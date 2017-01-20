#ifndef HOW_MANY_WAYS_TO_MAKE_H
#define HOW_MANY_WAYS_TO_MAKE_H

#include<vector>
using std::vector;


// TODO: Your answer for question 1a goes here

const int calculate(int const &moneytoMake, vector<int> const &available, int const &index);

const int howManyWaysToMake(int const &money, vector<int> const &available)  {

    return calculate(money,available,0);

}


const int calculate(int const &moneytoMake, vector<int> const &available, int const &index)  {
    if (moneytoMake < 0) {
        return 0;
    }
    if (moneytoMake == 0) {
        return 1;
    }
    if (index == available.size() && moneytoMake > 0) {
        return 0;
    }
    return calculate(moneytoMake - available[index], available, index) + calculate(moneytoMake, available, index + 1);
}


// Do not write any code below this line

#endif
