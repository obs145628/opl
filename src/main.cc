#include <iostream>
#include <cstddef>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include "vector.hh"
#include "algo.hh"
#include "matrix.hh"
#include "data-store.hh"

using opl::vect_type;
using opl::mat_type;
using opl::algo::log;
using opl::DataStore;

int
main ()
{

    mat_type m (2, 3, {
			4, 6, 9,
		    2, 3, 8
	});

	std::cout << m;




}