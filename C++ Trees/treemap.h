#ifndef TREEMAP_H
#define TREEMAP_H

#include "tree.h"

template<typename Key, typename Value>
class KeyValuePair {
    
public:
    
    const Key k;
    Value v;

    KeyValuePair(const Key kIn, Value vIn) 
    :k(kIn), v(vIn) {

    }
    KeyValuePair(const Key kIn) 
    :k(kIn) {


    }

    bool operator<(const KeyValuePair & kvp) const {

        return k < kvp.k;

    }
    
    // TODO your code for KeyValuePair goes here
    
    
    
};



template<typename Key, typename Value>
ostream & operator<< (ostream & o, const KeyValuePair<Key,Value> & kv){
    o << kv.k << "," << kv.v;
    return o;
}



template<typename Key, typename Value>
class TreeMap {
  
private:
    BinarySearchTree<KeyValuePair<Key,Value> > tree;
    
public:
    
    KeyValuePair<Key,Value> * insert(const Key & k, const Value & v) {
        return &(tree.insert(KeyValuePair<Key,Value>(k,v))->data);
    }
    
    void write(ostream & o) const {
        tree.write(o);
    }
    
    // TODO your code for TreeMap goes here:

      KeyValuePair<Key,Value>* find(const Key lKey) const {

            KeyValuePair<Key,Value>* pair = new KeyValuePair<Key,Value>(lKey);

             TreeNode<KeyValuePair<Key,Value>>* p =  tree.find(*pair);

             return &(p->data);
        }
    
    
    
    
};


// do not edit below this line

#endif
