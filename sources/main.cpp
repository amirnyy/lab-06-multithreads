// Copyright 2018 Avsyankaa <Avsyankaa@gmail.com>
#include <multithreads.hpp>

int main() {
	Multithreads m;
	init();
  logging::add_common_attributes();
  src::severity_logger< severity_level > lg;
    m.Make_counting_in_threads(4, lg);
}
