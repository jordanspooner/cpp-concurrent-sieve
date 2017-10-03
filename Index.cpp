
#include "Index.hpp"

using namespace std;

// Node class implementation

Node::Node(int i){
  item = i;
  prev = NULL;
  next = NULL;
}

Node* Node::getPrev(){
  return prev;
}

Node* Node::getNext(){
  return next;
}

int Node::getItem(){
  return item;
}

void Node::setPrev(Node* p){
  prev = p;
}

void Node::setNext(Node* n){
  next = n;
}

// Index class implementation

Index::Index(int seeds[], int length){
  head = NULL;
  tail = NULL;

  // insert the seed elements into the index
  for(int i=0; i<length; i++){
    bool ret = insert(seeds[i]);
  }
}

bool Index::search(int key){
  cerr << "TODO: implement the index search function" << endl;
  exit(-1);
}

bool Index::insert(int key){
  cerr << "TODO: implement the index insert function" << endl;
  exit(-1);
}


bool Index::remove(int key){
  cerr << "TODO: implement the index remove function" << endl;
  exit(-1);
}

void Index::printIndex(char order){

  Node* start;

  // configure traversal order
  if(order == '<'){
    start = head;
  } else if(order == '>'){
    start = tail;
  } else {
    cerr << "ERROR: unrecognised input order " << order << endl;
    return;
  } 
  
  Node* cur = NULL; 
  Node* nxt = start;
  cout << "|--";

  // traverse the index elements
  while(nxt != NULL){

    if(nxt != start){
      cout<< "<-->";
    } 

    cur = nxt;
    if(order == '<'){
      nxt = cur->getNext();
    } else {
      nxt = cur->getPrev();
    }
    
    cout << "|·|" << cur->getItem() << "|·|";
  }

  cout << "--|" << endl;
}




