// Copyright 2018 Avsyankaa <Avsyankaa@gmail.com>
#define BOOST_LOG_DYN_LINK 1
#include <multithreads.hpp>

int main() {
	Multithreads m;
    m.Make_counting_in_threads(4);
}
