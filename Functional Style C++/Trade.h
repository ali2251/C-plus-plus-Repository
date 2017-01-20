#ifndef TRADE_H
#define TRADE_H

#include <algorithm>
#include <iostream>   //#include <vector>
#include <numeric>

using std::cout;
using std::endl;
using std::pair;

// TODO your code goes here:




template<class it>
int bestProfit(const it &begin, const it &end) {

	int min = 100000;
	int max  = -1;
	if(begin == end) {
		return 0;
	}
	std::pair<int,int> toReturn(0,*begin);


	auto alpha = std::accumulate(begin,end,toReturn,[](const std::pair<int,int> a, const int b){
		
		//first = max profit
		//second = lowest seen

		int first = b - a.second;
		int second = b;

		if(a.second < second) {

			second = a.second;
		}

		if(a.first > first) {
			first = a.first;
		}


		return pair<int,int>(first,second);


	});
	return alpha.first;

}





// Don't write any code below this line

#endif
