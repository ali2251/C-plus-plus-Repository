#ifndef MAXIMUM_GATES_H
#define MAXIMUM_GATES_H

#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;


// TODO: Your answer for question 2 goes here

int maximumGates(vector<int> const  &arrives, vector<int> const &departs) {

    vector<int> localDeparts = departs;

    int num = 0;
    int min = *std::min_element(localDeparts.begin(), localDeparts.end());

    int index = 1;

    std::sort(localDeparts.begin(),localDeparts.end());

    for(int i = 0; i< arrives.size(); ++i) {

       if(arrives[i] < min) {
           num++;
       } else {

           min = localDeparts[index];
           index++;

       }

    }

    return num;

}




// Do not write any code below this line


#endif
