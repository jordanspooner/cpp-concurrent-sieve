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

    // mutex for node
    std::mutex* mutex;

  public:

    // class constructor, takes key value and prev/next list elements
    explicit Node(int item);
    ~Node();

    // node query methods
    Node* getPrev();
    Node* getNext();
    int getItem();
    
    // node update methods
    void setPrev(Node* prev);
    void setNext(Node* next);

    // mutex methods
    std::mutex* getMutex();
  
};

class Index {

  private:

    // pointers to the head and tail of the doubly linked list
    Node* head;
    Node* tail;

    // mutexes for head and tail of list
    mutex* headMutex;
    mutex* tailMutex;
    
  public:

    // class constructor, loads an image from a provided file (or URL?)
    Index(int seeds[], int length);
    ~Index();

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
