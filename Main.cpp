#include <iostream>
#include <thread>

#include "Index.hpp"

using namespace std;

int main(int argc, char ** argv)
{

  cout << "Basic Index Tests" << endl << endl;

  // Main idea: create a simple index, search for some things, remove some things then search again

  cout << "Testing the Index class basics" << endl;

  int seed_data[] = {2,4,1,3,9,11,2,2,2,20};
  Index my_index(seed_data, 10);

  cout << endl;

  cout << "print index forwards:" << endl;
  my_index.printIndex('<');

  cout << endl;

  cout << "print index backwards:" << endl;
  my_index.printIndex('>');
  cout << endl;

  for(int i = 0; i<10; i++){
    cout << "search " << i << ": " << my_index.search(i) << endl;
  }

  cout << "----------" << endl;

  for(int i = 0; i<10; i++){
    cout << "remove " << i << ": " << my_index.remove(i) << endl;
  }

  cout << "----------" << endl;

  for(int i = 0; i<10; i++){
    cout << "search " << i << ": " << my_index.search(i) << endl;
  }

  cout << endl;

  cout << "print index forwards:" << endl;
  my_index.printIndex('<');

  cout << endl;

  cout << "print index backwards:" << endl;
  my_index.printIndex('>');

}
