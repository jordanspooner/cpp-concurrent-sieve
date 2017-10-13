
#include "Index.hpp"

using namespace std;

// Node class implementation

Node::Node(int i) {
  item = i;
  prev = nullptr;
  next = nullptr;
}

Node* Node::getPrev() {
  return prev;
}

Node* Node::getNext() {
  return next;
}

int Node::getItem() {
  return item;
}

void Node::setPrev(Node* p) {
  prev = p;
}

void Node::setNext(Node* n) {
  next = n;
}

// Index class implementation

Index::Index(int seeds[], int length) {
  head = nullptr;
  tail = nullptr;

  // insert the seed elements into the index
  for(int i=0; i<length; i++) {
    bool ret = insert(seeds[i]);
  }
}

bool Index::search(int key) {
  Node* currentNode = head;

  while (currentNode != nullptr) {
    int currentVal = currentNode->getItem();

    if (currentVal == key) {
      return true;
    }
    else if (currentVal > key) {
      return false;
    }

    currentNode = currentNode->getNext();
  }

  return false;
}

bool Index::insert(int key) {
  auto* newNode = new Node(key);

  // If there are no nodes so far...
  if (head == nullptr) {
    head = newNode;
    tail = newNode;
    return true;
  }

  Node* currentNode = head;
  int currentVal = currentNode->getItem();

  // If this is the new head...
  if (key < currentVal) {
    head->setPrev(newNode);
    newNode->setNext(head);
    head = newNode;
    return true;
  }

  while (currentNode != nullptr) {
    currentVal = currentNode->getItem();

    // If this node is already present...
    if (key == currentVal) {
      return false;
    }

    // Simple insertion...
    if (key < currentVal) {
      Node* prevNode = currentNode->getPrev();
      Node* nextNode = currentNode;
      prevNode->setNext(newNode);
      newNode->setPrev(prevNode);
      nextNode->setPrev(newNode);
      newNode->setNext(nextNode);
      return true;
    }

    currentNode = currentNode->getNext();
  }

  // If this is the new tail...
  tail->setNext(newNode);
  newNode->setPrev(tail);
  tail = newNode;
  return true;

}


bool Index::remove(int key) {

  // If there are no nodes...
  if (head == nullptr) {
    return false;
  }

  Node* currentNode = head;
  int currentVal = currentNode->getItem();

  // If this is the head...
  if (key == currentVal) {
    Node* nextNode = head->getNext();
    nextNode->setPrev(nullptr);
    head = nextNode;
    return true;
  }

  while (currentNode != tail) {
    currentVal = currentNode->getItem();

    // If this node isn't present...
    if (key < currentVal) {
      return false;
    }

    // Simple deletion...
    if (key == currentVal) {
      Node* prevNode = currentNode->getPrev();
      Node* nextNode = currentNode->getNext();
      prevNode->setNext(nextNode);
      nextNode->setPrev(prevNode);
      return true;
    }

    currentNode = currentNode->getNext();
  }

  currentVal = currentNode->getItem();

  // If this is the tail...
  if (key == currentVal) {
    Node* prevNode = tail->getPrev();
    prevNode->setNext(nullptr);
    tail = prevNode;
    return true;
  }

  // Otherwise, node isn't present...
  return false;

}

void Index::printIndex(char order) {

  Node* start;

  // Configure traversal order
  if(order == '<') {
    start = head;
  } else if(order == '>') {
    start = tail;
  } else {
    cerr << "ERROR: unrecognised input order " << order << endl;
    return;
  } 
  
  Node* cur = nullptr;
  Node* nxt = start;
  cout << "|--";

  // Traverse the index elements
  while(nxt != nullptr) {

    if(nxt != start) {
      cout<< "<-->";
    } 

    cur = nxt;
    if(order == '<') {
      nxt = cur->getNext();
    } else {
      nxt = cur->getPrev();
    }
    
    cout << "|·|" << cur->getItem() << "|·|";
  }

  cout << "--|" << endl;
}




