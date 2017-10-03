#include <iostream>
#include <math.h>
#include <thread>

#include "Index.hpp"

using namespace std;

void sieve_worker(Index* index, int base, int max){
  cerr << "TODO: implement the sieve workers" << endl;
  exit(-1);
}

int main(int argc, char ** argv)
{

  cerr << "TODO: implement the Sieve of Eratosthenes algorithm" << endl;

  Index* sieve_data = new Index(NULL, 0);

  // TODO: write code here...

  // When all sieve workers have terminated, print out the final state of the index.
  // All of the values that are left in the index must be prime numbers.
  cout << "  print index forwards:" << endl;
  sieve_data->printIndex('<');

  cout << endl;

  cout << "  print index backwards:" << endl;
  sieve_data->printIndex('>');

  delete(sieve_data);

}
