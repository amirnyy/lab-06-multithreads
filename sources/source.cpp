// Copyright 2018 Avsyankaa <Avsyankaa@gmail.com>

#include <multithreads.hpp>

std::vector<unsigned char> Multithreads::Fill_vector_by_random() {
  std::vector<unsigned char> char_vector_random;
  unsigned int size = std::rand() % 5 + 1;
  for (unsigned i = 0; i < size; i++) {
    char_vector_random.push_back(static_cast<unsigned char>(std::rand() % 256));
  }
  return char_vector_random;
}

bool Multithreads::Is_hash_needable(const std::string& hash) {
  for (unsigned i = hash.size(); i < hash.size(); i++) {
    if (hash[i] != '0') return false;
  }
  return true;
}

void init() {
  logging::add_file_log("home/travis/build/bmstu-iu8-34-cpp-2018/lab-06-multithreads-Avsyankaa/sample.log");
  logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
} 

void Multithreads::Do_counting() { 
    init();
    logging::add_common_attributes();

    ;
    src::severity_logger< severity_level > lg;
    std::lock_guard<std::recursive_mutex> lock(m);
    BOOST_LOG_SEV(lg, trace) << "puck" << std::endl;
/*
  for (unsigned int i = 0; i < 5000; i++) {
    std::vector<unsigned char> char_vector_random = Fill_vector_by_random();
    const std::string hash = picosha2::hash256_hex_string(char_vector_random);
    my_mutex.lock();
    //boost::log::add_file_log("sample.log");
    //BOOST_LOG_TRIVIAL(trace)
        << "ID ïîòîêà: " << std::this_thread::get_id() << std::endl;
    BOOST_LOG_TRIVIAL(trace) << "Ïðîîáðàç: ";
    for (unsigned z = 0; z < char_vector_random.size(); z++) {
      BOOST_LOG_TRIVIAL(trace) << char_vector_random[z];
    }
    BOOST_LOG_TRIVIAL(trace) << std::endl;
    BOOST_LOG_TRIVIAL(trace) << "HASH- çíà÷åíèå: " << hash;
    BOOST_LOG_TRIVIAL(trace) << std::endl << std::endl;
    if (Is_hash_needable(hash)) {
      BOOST_LOG_TRIVIAL(info) << "Ïðîîáðàç: ";
      for (unsigned z = 0; z < char_vector_random.size(); z++) {
        BOOST_LOG_TRIVIAL(info) << char_vector_random[z];
      }
      BOOST_LOG_TRIVIAL(info) << std::endl;
      BOOST_LOG_TRIVIAL(info) << "HASH- çíà÷åíèå: " << hash;
      BOOST_LOG_TRIVIAL(info) << std::endl << std::endl;
    }
    my_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }*/
  
}

void Multithreads::Make_counting_in_threads(unsigned threads_count) {
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < threads_count; i++) {
    threads.push_back(std::thread{&Multithreads::Do_counting, this});
  }
  for (unsigned i = 0; i < threads.size(); i++) {
    threads[i].join();
  }
}
