// Copyright 2018 Avsyankaa <Avsyankaa@gmail.com>

#ifndef INCLUDE_MULTITHREADS_HPP_
#define INCLUDE_MULTITHREADS_HPP_

#include <picosha2.h>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <iostream>
#include <thread>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <mutex>

class Multithreads {
 private:
  std::recursive_mutex m;
  std::vector<unsigned char> Fill_vector_by_random();
  bool Is_hash_needable(const std::string& hash);
  void Do_counting();

 public:
unsigned threads_number;
Multithreads() { 
	threads_number = std::thread::hardware_concurrency();
  }
void Make_counting_in_threads(unsigned threads_count);
};

#endif  // INCLUDE_MULTITHREADS_HPP_
