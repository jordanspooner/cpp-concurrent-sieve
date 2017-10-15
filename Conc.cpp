#include <iostream>
#include <thread>
#include <chrono>

#include "Index.hpp"

using namespace std;
using namespace std::chrono;

void thread_1_work(Index* index){
  // loops adding and removing 1 from the index with pauses to search
  for(int cnt = 1; cnt <= 100; cnt++){
    cout << "t1:insert 1 : " << index->insert(1) << endl;
    cout << "t1:search 1 : " << index->search(1) << endl;
    cout << "t1:remove 1 : " << index->remove(1) << endl;
    cout << "t1:search 1 : " << index->search(1) << endl;
    cout << "t1:insert 1 : " << index->insert(1) << endl;
    cout << "t1:search 1 : " << index->search(1) << endl;
  }
}

void thread_2_work(Index* index){
  // loops adding and removing 2 from the index with pauses to search
  for(int cnt = 1; cnt<=100; cnt++){
    cout << "t2:insert 2 : " << index->insert(2) << endl;
    cout << "t2:search 2 : " << index->search(2) << endl;
    cout << "t2:remove 2 : " << index->remove(2) << endl;
    cout << "t2:search 2 : " << index->search(2) << endl;
    cout << "t2:insert 2 : " << index->insert(2) << endl;
    cout << "t2:search 2 : " << index->search(2) << endl;
  }
}

void thread_3_work(Index* index){
  // disruptive loop adding and removing 1 and 2 from the index
  for(int cnt = 1; cnt<=100; cnt++){
    cout << "t3:insert 1 : " << index->insert(1) << endl;
    cout << "t3:insert 2 : " << index->insert(2) << endl;
    cout << "t3:remove 1 : " << index->remove(1) << endl;
    cout << "t3:remove 2 : " << index->remove(2) << endl;
    cout << "t3:insert 1 : " << index->insert(1) << endl;
    cout << "t3:insert 2 : " << index->insert(2) << endl;
  }
}

int main(int argc, char ** argv)
{

  cout << "Basic Concurrent Index Test" << endl;

  // Main idea: start up 3 threads and have them all hit the index simultaniously.

  auto* index = new Index(nullptr, 0);

  cout << "starting 3 threads that concurrently modify the index..." << endl;

  // run this test 10 times and profile the execution times (for interest)
  int times[10];
  for (int &time : times) {

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    thread first(thread_1_work, index);
    thread second(thread_2_work, index);
    thread third(thread_3_work, index);

    first.join();
    second.join();
    third.join();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    int duration = (int)duration_cast<microseconds>( t2 - t1 ).count();
    cout << "execution of threads took: " << duration << " microseconds" << endl;

    time = duration;
  }

  int sum = 0;
  for (int time : times) {
    sum = sum + time;
  }
  int avg = sum/10;
  cout << "average execution time = " << avg << " microseconds" << endl;
  
  // check the final state of the index at the end of all 10 runs
  cout << "print index forwards:" << endl;
  index->printIndex('<');

  cout << endl;

  cout << "print index backwards:" << endl;
  index->printIndex('>');

  delete(index);

}
