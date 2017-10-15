#include "Index.hpp"

using namespace std;

// Node class implementation

Node::Node(int i) {
  item = i;
  prev = nullptr;
  next = nullptr;
  mutex = new std::mutex();
}

Node::~Node() {
  delete(mutex);
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

std::mutex* Node::getMutex() {
  return mutex;
}

// Index class implementation

Index::Index(int seeds[], int length) {
  head = nullptr;
  tail = nullptr;

  headMutex = new std::mutex();
  tailMutex = new std::mutex();

  // Insert the seed elements into the index
  for(int i=0; i<length; i++) {
    insert(seeds[i]);
  }
}

Index::~Index() {
  delete(headMutex);
  delete(tailMutex);

  Node* currentNode = head;
  while (currentNode != nullptr) {
    Node* toDelete = currentNode;
    currentNode = currentNode->getNext();
    delete(toDelete);
  }
}

bool Index::search(int key) {
  cout << "search" << endl;
  headMutex->lock();
  Node* currentNode = head;
  if (head == nullptr) {
     // If there are no nodes...
    headMutex->unlock();
    return false;
  }
  currentNode->getMutex()->lock();
  headMutex->unlock();
  while (currentNode != nullptr) {
    int currentVal = currentNode->getItem();
    if (currentVal == key) {
      // Found it...
      currentNode->getMutex()->unlock();
      return true;
    }
    else if (currentVal > key) {
      // We passed it, so it can't have been present...
      currentNode->getMutex()->unlock();
      return false;
    }
    Node* nextNode = currentNode->getNext();
    if (nextNode != nullptr) {
      nextNode->getMutex()->lock();
    }
    currentNode->getMutex()->unlock();
    currentNode = nextNode;
  }
  return false;
}

bool Index::insert(int key) {
  auto* newNode = new Node(key);

  headMutex->lock();
  tailMutex->lock();
  if (head == nullptr) {
    // If there are no nodes so far...
    head = newNode;
    tail = newNode;
    headMutex->unlock();
    tailMutex->unlock();
    return true;
  }
  tailMutex->unlock();

  Node* currentNode = head;
  int currentVal = currentNode->getItem();
  currentNode->getMutex()->lock();
  if (key == currentVal) {
    // If this node is already present (as the head)...
    delete(newNode);
    headMutex->unlock();
    currentNode->getMutex()->unlock();
    return false;
  }
  if (key < currentVal) {
    // If this is the new head...
    head->setPrev(newNode);
    newNode->setNext(head);
    head = newNode;
    headMutex->unlock();
    currentNode->getMutex()->unlock();
    return true;
  }
  headMutex->unlock();

  Node* prevNode = currentNode;
  currentNode = currentNode->getNext();
  while (currentNode != nullptr) {
    currentNode->getMutex()->lock();
    currentVal = currentNode->getItem();
    if (key == currentVal) {
      // If this node is already present...
      delete(newNode);
      prevNode->getMutex()->unlock();
      currentNode->getMutex()->unlock();
      return false;
    }
    if (key < currentVal) {
      // Simple insertion...
      prevNode->setNext(newNode);
      newNode->setPrev(prevNode);
      currentNode->setPrev(newNode);
      newNode->setNext(currentNode);
      prevNode->getMutex()->unlock();
      currentNode->getMutex()->unlock();
      return true;
    }
    prevNode->getMutex()->unlock();
    prevNode = currentNode;
    currentNode = currentNode->getNext();
  }

  // Otherwise this is the new tail...
  tailMutex->lock();
  tail = newNode;
  tailMutex->unlock();
  prevNode->setNext(newNode);
  newNode->setPrev(prevNode);
  prevNode->getMutex()->unlock();
  return true;
}


bool Index::remove(int key) {
  headMutex->lock();
  if (head == nullptr) {
    // If there are no nodes...
    headMutex->unlock();
    return false;
  }

  Node* currentNode = head;
  Node* nextNode = head->getNext();
  int currentVal = currentNode->getItem();
  currentNode->getMutex()->lock();
  if (nextNode == nullptr) {
    // If this is the only node...
    if (key == currentVal) {
      tailMutex->lock();
      delete (currentNode);
      head = nullptr;
      tail = nullptr;
      headMutex->unlock();
      tailMutex->unlock();
      return true;
    }
    headMutex->unlock();
    currentNode->getMutex()->unlock();
    return false;
  }

  nextNode->getMutex()->lock();
  if (key == currentVal) {
    // If this is the head...
    nextNode->setPrev(nullptr);
    delete(currentNode);
    head = nextNode;
    nextNode->getMutex()->unlock();
    headMutex->unlock();
    return true;
  }
  headMutex->unlock();

  Node* prevNode = currentNode;
  currentNode = nextNode;
  nextNode = currentNode->getNext();
  while (nextNode != nullptr) {
    nextNode->getMutex()->lock();
    currentVal = currentNode->getItem();
    if (key < currentVal) {
      // If this node isn't present...
      prevNode->getMutex()->unlock();
      currentNode->getMutex()->unlock();
      nextNode->getMutex()->unlock();
      return false;
    }
    if (key == currentVal) {
      // Simple deletion...
      prevNode->setNext(nextNode);
      nextNode->setPrev(prevNode);
      delete(currentNode);
      prevNode->getMutex()->unlock();
      nextNode->getMutex()->unlock();
      return true;
    }
    prevNode->getMutex()->unlock();
    prevNode = currentNode;
    currentNode = nextNode;
    nextNode = currentNode->getNext();
  }

  currentVal = currentNode->getItem();
  if (key == currentVal) {
    // If this is the tail...
    tailMutex->lock();
    tail = prevNode;
    tailMutex->unlock();
    prevNode->setNext(nullptr);
    delete(currentNode);
    prevNode->getMutex()->unlock();
    return true;
  }

  // Otherwise, node isn't present...
  prevNode->getMutex()->unlock();
  currentNode->getMutex()->unlock();
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
    }
    else {
      nxt = cur->getPrev();
    }
    
    cout << "|·|" << cur->getItem() << "|·|";
  }

  cout << "--|" << endl;
}




