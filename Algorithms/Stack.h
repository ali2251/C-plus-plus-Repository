#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>


using pep::vector;
using std::string;
using std::istream_iterator;
using std::istringstream;
using std::cout;
using std::endl;
using std::stod;

// TODO: Your code for question 3 goes here
class Stack {

public:
   const bool empty() const {

        return stack.empty();


    }

     double pop() {

        if (empty()) { return 0; }
        int index = stack.size() - 1;
        double temp = stack[index];

        stack.erase(stack.begin() + index);

        return temp;

    }

    void push(const double a) {

        stack.push_back(a);


    }

private:
    vector<double> stack;

};


double evaluate(string s) {

    istringstream stream(s);

    vector<string> tokens{istream_iterator<string>{stream},
                          istream_iterator<string>{}};


    Stack localStack;

    double result = 0;


    for (int i = 0; i < tokens.size(); ++i) {


        if (tokens[i] == "+") {
            double a = localStack.pop();
            double b = localStack.pop();
            localStack.push(a+b);

        } else if (tokens[i] == "-") {

            double a = localStack.pop();
            double b = localStack.pop();
            localStack.push(b-a);

        }
        else if (tokens[i] == "*") {
            double a = localStack.pop();
            double b = localStack.pop();
            localStack.push(a*b);
        }
        else if (tokens[i] == "/") {
            double a = localStack.pop();
            double b = localStack.pop();
            localStack.push(b/a);
        }
        else {
            localStack.push(stod(tokens[i]));
        }


    }


    result = localStack.pop();
    return result;


}



// Do not write anything below this line

#endif
