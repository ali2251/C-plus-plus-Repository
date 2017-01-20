#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:

template<typename T>
class TreeNode {

public:
	T data;
	unique_ptr<TreeNode<T>> leftChild;
	unique_ptr<TreeNode<T>> rightChild;
	TreeNode<T>* parent;

	TreeNode<T>*  left = nullptr;
	TreeNode<T>*  right = nullptr;

	


	TreeNode(T dataIn) 
	:data(dataIn), parent(nullptr) {

	}

	void setLeftChild(TreeNode<T>* child) {
		//delete leftChild.release();
		leftChild.reset(child);
		leftChild.get()->parent = this;


	}

	void setRightChild(TreeNode<T>* child) {
		//delete rightChild.release();
		rightChild.reset(child);
		child->parent = this;
		//rightChild.get()->parent = this;

	}

	
	

	void write(ostream & stream)   {


		if(leftChild) {

			left = leftChild.get();
			if(left) {
				left->write(stream);
			}
		}

		stream << " " << data << " ";

		if(rightChild) {

			right = rightChild.get();
			if(right) {
				right->write(stream);
			}
			
		}
		
		
	}


	int maxDepth() {

		
		int leftDepth = 1;
		int rightDepth  = 1;


		TreeNode<T>*  localLeftChild  =  leftChild.get();

		TreeNode<T>*  localRightChild  =  rightChild.get();


		if(leftChild) {

			leftDepth = localLeftChild->maxDepth();
			++leftDepth;

		}



		if(localRightChild) {

			rightDepth = localRightChild->maxDepth();

			++rightDepth;
		}

		

		if(rightDepth > leftDepth) {

			return rightDepth;
			
		}  else {


			return leftDepth;
		}




	}
		

};


template<typename T>
class TreeNodeIterator {


public:
	TreeNode<T>* current;

	TreeNodeIterator(TreeNode<T>* currentIn) 
	:current(currentIn){

	}


	 T & operator*() const {

        return current->data;
    }

    bool operator==( const TreeNodeIterator<T> & n) const {

    	return current==n.current;

    	//if(current == n.current) {return true; } else { return false;}
    }
    bool operator!=( const TreeNodeIterator<T> & n) const {
    	
    	return (current!=n.current);

    	//if(current != n.current) {return true; } else { return false;}
    }


     void operator++() {

       TreeNode<T>* temp = nullptr;

	//nullptr cannot be incremented
    
    if (!current)  { return; }
   
/* checking if there is a right child (using algorithm that walk for right then run for left)   */ 
 	else if (current->rightChild) {

 		//cout << "here" << endl;

      current = current->rightChild.get();
     
      while (current->leftChild) {
        current = current->leftChild.get();
      	 }

     } else {
       
       /* All left branches have been visited 
			Have to go up for the parent, as long as current is the right child of it

        */

       temp = current->parent;
       while (temp && current == temp->rightChild.get()) {
 
 	           current = temp;
    	       temp = temp->parent;
 
         }
       current = temp;

    	}


	}


};






// do not edit below this line

#endif
