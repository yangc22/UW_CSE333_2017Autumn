/*
 * Copyright ©2017 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Autumn Quarter 2017 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <ctime>

#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;

const int NUM_PIES = 6;
static SimpleQueue queue;
static unsigned int seed = time(NULL);
static pthread_mutex_t write_lock;

// Thread safe print that prints the given str on a line
void thread_safe_print(string str) {
  pthread_mutex_lock(&write_lock);
  // Only one thread can hold the lock at a time, making it safe to
  // use cout. If we didn't lock before using cout, the order of things
  // put into the stream could be mixed up.
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

// Produces NUM_PIES pies of the given type
// You should NOT modify this method at all
void producer(string pie_type) {
  for (int i = 0; i < NUM_PIES; i++) {
    queue.Enqueue(pie_type);
    thread_safe_print(pie_type + " pie ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

// Eats 2 * NUM_PIES pies
// You should NOT modify this method at all
void consumer() {
  for (int i = 0; i < NUM_PIES * 2; i++) {
    bool successful = false;
    string pie_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        // Sleep for a bit and then check again
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&pie_type);
    }
    thread_safe_print(pie_type + " pie eaten!");
  }
}

int main(int argc, char **argv) {
  pthread_mutex_init(&write_lock, NULL);
  // Your task: Make the two producers and the single consumer
  // all run concurrently (hint: use pthreads)
  // producer("Apple");
  // producer("Blackberry");
  // consumer();

  pthread_t producer1;
  string *argument = new string("Apple");
  if (pthread_create(&thr, nullptr, &producer1,
                     reinterpret_cast<void *>(argument)) != 0) {
    std::cerr << "pthread_create() failed." << std::endl;
    return EXIT_FAILURE;
  }

  pthread_t producer2;
  *argument = new string("Blackberry");
  if (pthread_create(&thr, nullptr, &producer2,
                     reinterpret_cast<void *>(argument)) != 0) {
    std::cerr << "pthread_create() failed." << std::endl;
    return EXIT_FAILURE;
  }

  pthread_t consumer1;
  if (pthread_create(&consumer, nullptr, &thread_start, NULL) != 0) {
    std::cerr << "pthread_create() failed." << std::endl;
    return EXIT_FAILURE;
  }

  if ((pthread_join(producer1, NULL) || (pthread_join(producer2, NULL))
       || pthread_join(consumer1, NULL) != 0) {
      cerr << "pthread_join failed" << endl;
  }

  pthread_mutex_destroy(&write_lock);
  return 0;
}
