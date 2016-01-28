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

    mat_type m (3, 6, {
		    0, 3, -6, 6, 4, -5,
			3, -7, 8, -5, 8, 9,
   			3, -9, 12, -9, 6, 15
	});


	std::cout << m.region_matrix (1, 2, 2, 3);




}