#include "treenode.h"
#include "tree.h"

#include <algorithm>
#include <iostream>
#include <sstream> 
#include <vector>

using std::cout;
using std::endl;
using std::ostringstream;
using std::vector;

int main() {

		BinarySearchTree<int> tree;
        
        vector<int> putIn{5,1,2,6};


        cout << "hello" << endl;
        
        for (const int & e : putIn) {
            tree.insert(e);        
        }
             

        std::sort(putIn.begin(), putIn.end());



        vector<int> was;


         
        
        for (auto & e : tree) { 
           was.push_back(e);  

         } 


         cout << was.size();

          for (int & e : was) {
                cout << " " << e;
            }

            cout << endl;





}