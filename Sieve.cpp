#include <cassert>
#include <iostream>
#include <cmath>
#include <thread>

#include "Index.hpp"

using namespace std;

void sieve_worker(Index* index, int base, int max){
  for(int i = base * 2; i <= max; i += base) {
    index->remove(i);
  }
}

int main(int argc, char ** argv)
{
  if (argc != 2) {
    cerr << "Usage: sieve [N]" << endl;
    cerr << "Returns a list of all prime numbers less than or equal to N." << endl;
    exit(EXIT_FAILURE);
  }

  int n = 0;
  try {
    n = stoi(argv[1]);
    assert(n > 0);
  }
  catch (...) {
    cerr << "sieve: Argument N must be a positive integer." << endl;
    exit(EXIT_FAILURE);
  }

  auto* sieve_data = new Index(nullptr, 0);

  for (int i = n; i > 1; i--) {
    sieve_data->insert(i);
  }

  auto max = (int)sqrt(n);
  auto* threadPool = new thread[max + 1];

  for(int i = max; i > 1; i--) {
    threadPool[i] = thread(sieve_worker, sieve_data, i, n);
  }

  for(int i = max; i > 1; i--) {
    threadPool[i].join();
  }

  delete[] threadPool;

  // When all sieve workers have terminated, print out the final state of the index.
  // All of the values that are left in the index must be prime numbers.
  cout << "  print index forwards:" << endl;
  sieve_data->printIndex('<');

  cout << endl;

  cout << "  print index backwards:" << endl;
  sieve_data->printIndex('>');

  delete(sieve_data);

}
