#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <thread>
#include <mutex>

// The Index class provides a wrapper for a Concurrent Doubely-Linked-List 
// implementation

using namespace std;

class Node {

  private:

    // index key of the node  
    int item;

    // pointers to next/previous nodes in the list
    Node* prev;
    Node* next;

  public:

    // class constructor, takes key value and prev/next list elements
    Node(int item);

    // node query methods
    Node* getPrev();
    Node* getNext();
    int getItem();
    
    // node update methods
    void setPrev(Node* prev);
    void setNext(Node* next);
  
};

class Index {

  private:

    // pointers to the head and tail of the doubly linked list
    Node* head;
    Node* tail;
    
  public:

    // class constructor, loads an image from a provided file (or URL?)
    Index(int seeds[], int length);

    // look for element in the index
    bool search(int key);

    // add element (in order) to the index
    bool insert(int key);

    // remove element from the index
    bool remove(int key);

    // output the contents of the index (pretty-printed)
    void printIndex(char order);

};


#endif
