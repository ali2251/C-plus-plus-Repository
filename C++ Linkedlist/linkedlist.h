#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <initializer_list>




// TODO your code goes here:

template<typename T>
class LinkedList{

public:
	Node<T>* head;
	Node<T>* tail;
	int count = 0;
	std::initializer_list<T> list;
	


	LinkedList() 
	:head(nullptr),tail(nullptr)
	{

	}

	LinkedList(std::initializer_list<T> l) 
	:list(l) 
	{ 
		 for (auto & n : list) {
            
            	push_back(n);

        }



	 }

	 NodeIterator<T> insert(const NodeIterator<T>&  nd, const T & elem) {


		Node<T>* local = nd.getCurrent();

		Node<T>* dataNode = new Node<T>(elem);


		if(count == 0) {


			head = dataNode;
			tail = dataNode;
			++count;

			 NodeIterator<T> firstIterator(dataNode);

			return firstIterator;
			

			
		}


		if(local->previous != nullptr ) {


			//general insertion

		Node<T>* pre = local->previous;

		local->previous = dataNode;

		dataNode->previous = pre;

		pre->next = dataNode;

		local->previous = dataNode;

		dataNode->next = local;

		++count;

		 NodeIterator<T> pointer(dataNode); 

		return pointer;

		} 
		if(local == head && local == tail) {

		
			//Inserting into an empty list


		

			if(head == nullptr && tail == nullptr) {
				//nothing in the list
				head = dataNode;
				tail = dataNode;

				++count;

				 NodeIterator<T> first(dataNode);

				return first;

			} else {

			

				//one element in the list

				Node<T>* reserv = head;

				head = dataNode;

				tail = reserv;

				tail->previous = head;

				head->next = tail;

				++count;

				 NodeIterator<T> second(dataNode);

				return second;


			}
			

		}

		if(local == head) {
			//trying to insert at the first element

			head = dataNode;

			head->next = local;
			local->previous = head;

			++count;

			 NodeIterator<T> first(dataNode);

			return first;


		} 
		if(local == tail) {


			Node<T>* oldTailPrevious = tail->previous;

			tail->previous = dataNode;

			dataNode->next = tail;

			dataNode->previous = oldTailPrevious;

			oldTailPrevious->next  = dataNode;

			++count;

			 NodeIterator<T> last(dataNode);

			return last;


		}

		 NodeIterator<T> some(dataNode);
		return some;


	}


	 NodeIterator<T> erase(const NodeIterator<T>&  ni) {

		Node<T>* loc = ni.getCurrent();
		

		if(loc->previous != nullptr && loc->next != nullptr) {

		Node<T>* preserved = loc->next;

		(loc->previous)->next = loc->next;

		(loc->next)->previous = loc->previous;

		loc->next = nullptr;
		loc->previous = nullptr;

		delete loc;

		--count;

		 NodeIterator<T> a(preserved);

		return a;
	
		} 

		if(loc == head && loc == tail) {
			//one element inside the list
			
			//delete loc;

			 NodeIterator<T> emptyIterator(tail->next);

			--count;

			//delete loc;

			return emptyIterator;

		}

		if(loc == head) {

			//cout << "   the first element is trying to be deleted" << endl;

			Node<T>* newHead = head->next;

			(head->next)->previous = nullptr;
			
			head->next = nullptr;

			head  = newHead;

			

			--count;

			//head->next = newHead->next;

			//newHead->previous = head;


		    NodeIterator<T> temp(newHead);

			delete loc;			

			return temp;


		}

		if(loc == tail) {

			//cout << " last element trying to be deleted" << endl;


			Node<T>* newTail = tail->previous;

			(tail->previous)->next = nullptr;

			tail->previous = nullptr;
			
			tail = newTail;

			//tail->previous = newTail->previous;

			//newTail->next

			//delete loc;

			--count;

		    NodeIterator<T> something(tail->next);

			delete loc;

			return something;




		}


		/* if(loc->next == nullptr) {
			//trying to delete last element

			Node<T>* preservedLocal = loc->previous;

			(loc->previous)->next = nullptr;
			loc->previous = nullptr;

			//delete loc;

			NodeIterator<T> i(preservedLocal);

			return i;






		} */ 

			 NodeIterator<T> rubbish(head);

			return rubbish;
		
	}



	void push_front(const T & item) {

		if(count != 0 ) {

		Node<T>* previousHead = head;					
		Node<T>* temp1 = new Node<T>(item);
		head = temp1;
		head->next = previousHead;
		++count;

		} else {

			Node<T>* temp2 = new Node<T>(item);
			head = temp2;
			tail = temp2;
			++count;
			
			
		}

		
	}

	T& front() const {

		T& temp = head->data;

		return temp;

	}

	void push_back(const T & item) {


		Node<T>* temp = new Node<T>(item);

		if(count == 0) {

		//Node<T>* temp = new Node<T>(item);
		head = temp;
		tail = temp;
		
		++count;

		} else {

			if(count == 1) {

				Node<T>* previousTail = tail;
		//		Node<T>* temp4 = new Node<T>(item);
				tail = temp;
				tail->previous  = previousTail;
				head->next = tail;
				++count;

			} else {

			Node<T>* previousTail = tail;
		//	Node<T>* temp4 = new Node<T>(item);
			tail = temp;
			tail->previous  = previousTail;
			previousTail->next = tail;
			tail->next = nullptr;
			++count;

			}
		}

	}

	T& back() const {

		return tail->data;

	}

	int size() const {
		return count;
	}

	 NodeIterator<T> begin() const {
		
		 NodeIterator<T> t(head);

		return t;


	}

	 NodeIterator<T> end() const {

		 NodeIterator<T> temp5(tail->next);
		return temp5;

	}

	~LinkedList() {

		
		Node<T>* current = head;

		while( current !=   nullptr ) { 
			 Node<T>* next = current->next;
   			 delete current;
    		 current = next;
		
		}

		head = nullptr;
		
		

	}




}; 


// do not edit below this line

#endif
