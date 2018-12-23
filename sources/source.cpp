// Copyright 2018 Avsyankaa <Avsyankaa@gmail.com>
#include <multithreads.hpp>
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;


std::vector<unsigned char> Multithreads::Fill_vector_by_random() {
    std::vector<unsigned char> char_vector_random;
    unsigned int size = std::rand() % 10 + 4;
    for (unsigned i = 0; i < size; i++) {
        char_vector_random.push_back(
        static_cast<unsigned char>(std::rand() % 256));
    }
    return char_vector_random;
}

bool Multithreads::Is_hash_needable(const std::string& hash) {
    for (unsigned i = hash.size() - 4; i < hash.size(); i++) {
        if (hash[i] != '0') return false;
    }
    return true;
}

void Multithreads::init()
{
    boost::shared_ptr< logging::core > core = logging::core::get();

    boost::shared_ptr< sinks::text_file_backend > backend =
        boost::make_shared< sinks::text_file_backend >(
            keywords::file_name = "file_%5N.log",
            keywords::rotation_size = 5 * 1024 * 1024,
            keywords::format = "[%TimeStamp%]: %Message%",
            keywords::time_based_rotation =
            sinks::file::rotation_at_time_point(12, 0, 0));

    typedef sinks::synchronous_sink< sinks::text_file_backend > sink_t;
    boost::shared_ptr< sink_t > sink(new sink_t(backend));
    core->add_sink(sink);
}

void Multithreads::Do_counting() {
    std::srand(std::time(0));
    for (unsigned int i = 0; i < 1500; i++) {
        std::vector<unsigned char> char_vector_random = Fill_vector_by_random();
        const std::string hash =
        picosha2::hash256_hex_string(char_vector_random);
        std::lock_guard<std::recursive_mutex> lock(m);
        BOOST_LOG_TRIVIAL(trace)  << "ID thread: "
        << std::this_thread::get_id();
        std::string prototype = "";
        for (unsigned z = 0; z < char_vector_random.size(); z++) {
        prototype += char_vector_random[z];
        }
        BOOST_LOG_TRIVIAL(trace) << "prototype = " << prototype;
        BOOST_LOG_TRIVIAL(trace)  << "HASH- function: " << hash;
        if (Is_hash_needable(hash)) {
            BOOST_LOG_TRIVIAL(info) << "ID thread: "
             << std::this_thread::get_id();
            BOOST_LOG_TRIVIAL(info) << "prototype = " << prototype;
            BOOST_LOG_TRIVIAL(info)  << "HASH- function: " << hash;
        }
    }
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
