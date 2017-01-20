#ifndef TREE_H
#define TREE_H

#include "treenode.h"
#include <memory>
#include <iostream>
using std::unique_ptr;



// TODO your code goes here:

template<typename T>
class BinarySearchTree {

private:
	unique_ptr<TreeNode<T>> root;

public:

	int count = 0;


	

	void write(ostream& os) const {

		TreeNode<T>* temp = root.get();

		temp->write(os);
	}


	TreeNode<T>* insert(const T dataIn) {


		TreeNode<T>* foundNode = find(dataIn);

		if(foundNode) { return foundNode; }


		


		if(!root) {

		//	num1 =  new TreeNode<T>(dataIn);

			TreeNode<T>* trial = new TreeNode<T>(dataIn);
		
			root.reset(trial);

			++count;

			return trial;


		} else { 


	    TreeNode<T>* compareNode = root.get();


	    TreeNode<T>* parent = nullptr;

	    while(compareNode)

	    {
	    	   parent = compareNode;
	         
	         if(dataIn < compareNode->data) {

	         	compareNode = compareNode->leftChild.get();

	         }	 else {

	         	compareNode = compareNode->rightChild.get();
	         }

	    }

	   // TreeNode<T>* localParent = parent;

	    if(dataIn < parent->data) {

	    	TreeNode<T>* returnTo =  new TreeNode<T>(dataIn);
	      
	         parent->setLeftChild( returnTo );

	         ++count;

	         if(parent->parent) {

	         	if(parent->parent->rightChild.get() == parent) {

	         		//right and left rotation

	         		TreeNode<T>* lastelem = parent->leftChild.release();
	         		
	         		TreeNode<T>* subParent = parent->parent->rightChild.release();
	         		//subParent->parent = nullptr;

	         		parent->parent->setRightChild(lastelem);

	         		lastelem->setRightChild(subParent);

	         		//TreeNode<T>* subRoot = root.release();

	         		//root.reset(subParent);


	         		TreeNode<T>*  newParent = root.get()->rightChild.release();
	         		TreeNode<T>* oldRoot = root.release();
	         		TreeNode<T>* last  = parent->rightChild.release();

	         		newParent->parent = nullptr;
	        // 		last->parent = nullptr;

	         		root.reset(newParent);

	         		newParent->setLeftChild(oldRoot);
	         //		newParent->setRightChild(last);


	     	


	         	}


		         if(balanceFactor(parent->parent) == 2) {

		         	//right rotation


			        if(count == 3) {

		         		TreeNode<T>*  newParent = root.get()->leftChild.release();
		         		TreeNode<T>* oldRoot = root.release();
		         		TreeNode<T>* last  = parent->leftChild.release();

		         		newParent->parent = nullptr;
		         		last->parent = nullptr;

		         		root.reset(newParent);

		         		root.get()->setLeftChild(last);
		         		root.get()->setRightChild(oldRoot); 


		         	} else if(count > 3)  {


		         		if(balanceFactor(parent->parent) == 2) {

				         	TreeNode<T>* newParent = parent->parent->leftChild.release();

			         		TreeNode<T>* grand = parent->parent->parent->leftChild.release();

			         		TreeNode<T>* last = parent->leftChild.release();

			         	
			         		parent->parent->parent->setLeftChild(newParent);

			         		newParent->setLeftChild(last);

			         		newParent->setRightChild(grand); 


		         		}

			         }
		         }
	        }

	         return returnTo;


	    } else {

	    	TreeNode<T>* toReturn =  new TreeNode<T>(dataIn);

	    	if( parent->data < dataIn) {

	         parent->setRightChild( toReturn );

	         ++count;


	         if(parent->parent) {


	         	if(parent->parent->leftChild.get() == parent) {

	         		

	         		//left rotation then right rotation


		         		TreeNode<T>* subParent = parent->parent->leftChild.release();
		         		TreeNode<T>* lastItem = parent->rightChild.release();

						parent->parent->setLeftChild(lastItem);
		         		lastItem->setLeftChild(subParent);

		         		subParent->rightChild.reset(nullptr);

		         		TreeNode<T>*  newParent = root.get()->leftChild.release();
		         		TreeNode<T>* oldRoot = root.release();
		         		TreeNode<T>* last  = parent->leftChild.release();

		         		newParent->parent = nullptr;
		         //		last->parent = nullptr;

		         		root.reset(newParent);

		         	//	root.get()->setLeftChild(last);
		         		root.get()->setRightChild(oldRoot); 

		         		//root.get()->setRightChild(oldRoot);


	         	
	         	}

	         

	         if( balanceFactor(parent->parent) == -2) {


	         	if(count == 3) {
	         		TreeNode<T>*  newParent = root.get()->rightChild.release();
	         		TreeNode<T>* oldRoot = root.release();
	         		TreeNode<T>* last  = parent->rightChild.release();

	         		newParent->parent = nullptr;
	         		last->parent = nullptr;

	         		root.reset(newParent);

	         		newParent->setLeftChild(oldRoot);
	         		newParent->setRightChild(last); 

	         	} else if(count > 3)  {

	         		TreeNode<T>* newParent = parent->parent->rightChild.release();


	         		TreeNode<T>* grand = parent->parent->parent->rightChild.release();

	         		TreeNode<T>* last = parent->rightChild.release();

	         	
	         		parent->parent->parent->setRightChild(newParent);

	         		newParent->setLeftChild(grand);

	         		newParent->setRightChild(last); 

		         		}
	         		}

	         		return toReturn;  
 				}

		}
	  }
	}

	return foundNode;
}

	TreeNode<T>* find(const T dataIn) const {


		TreeNode<T>* parentLocal = nullptr;

		if(root) {

		parentLocal = root.get();

		 }

		TreeNode<T>* toReturn = nullptr;


		if(parentLocal == nullptr) {return toReturn; }


		while(parentLocal) {

			if(dataIn < parentLocal->data) {

				if(parentLocal->leftChild) {

				parentLocal  = parentLocal->leftChild.get();

				} else {

					break;
				}

			} 

			else if(parentLocal->data  <  dataIn ) {
				if(parentLocal->rightChild) {
				parentLocal  = parentLocal->rightChild.get();
				} else {

					break;
				}
			}


			//if(parentLocal->data < dataIn && dataIn < parentLocal->data) {

			else {

				toReturn = parentLocal;
				break;

			}
			/*if(parentLocal->data == dataIn) {

				toReturn = parentLocal;
				break;
			} */

		}

		return toReturn;

	}

    TreeNodeIterator<T> begin() {

    	if(!root) {  TreeNodeIterator<T> toReturn(nullptr);   return toReturn;  }

    	TreeNode<T>* temp = nullptr;

    	TreeNode<T>* current = root.get();

    	TreeNode<T>* something = nullptr;
    	

    	if(current->leftChild) {

    		temp =  current->leftChild.get();
    		something = current->leftChild.get();


    	} else {

    		temp = current;

    		TreeNodeIterator<T> toReturn(temp);

    		return toReturn;

    	}

    	 
    	while(something->leftChild) {	

    		something = something->leftChild.get();
    	
    	} 

    	temp = something;


    	TreeNodeIterator<T> toReturn(temp);

    	return toReturn;


    }


    TreeNodeIterator<T> end()  {

    	TreeNodeIterator<T> toReturn(nullptr);

    	return toReturn;


    }

    int maxDepth() {

    	if(!root) {return 0;} else {

    	return root.get()->maxDepth();


    	}

    }


    int balanceFactor(TreeNode<T>* node ) const {
 
 		int max = 0;
 		int left = 0;
 		int right = 0;

    	if(node->leftChild.get()) {

    		left = node->leftChild.get()->maxDepth();
    	}

    	if(node->rightChild.get()) {

    		right = node->rightChild.get()->maxDepth();
    	}

    	max = left - right;

    	return max;

    }

  

    TreeNode<T>* getRoot() const  {

    	return root.get();

    }



};

// do not edit below this line

#endif
