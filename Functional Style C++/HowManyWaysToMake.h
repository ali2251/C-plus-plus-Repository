#ifndef HOW_MANY_WAYS_TO_MAKE_H
#define HOW_MANY_WAYS_TO_MAKE_H

// TODO: Your code goes here
template<class it>
int howManyWaysToMake(it begin, it end, int money) {

	if (money < 0) {
        return 0;
    }
    if (money == 0) {
        return 1;
    }
    if(begin == end) {
    	return 0;
    }

    return howManyWaysToMake(begin, end ,money - *begin) + howManyWaysToMake(++begin,end,money);



}


/*
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
} */


// Do not write any code below this line

#endif
