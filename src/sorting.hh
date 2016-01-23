/** @file set of sorting functions
 */

#ifndef SORTING_HH_
# define SORTING_HH_

# include <cstring>
# include <algorithm>
# include <vector>


namespace
{

	template <class It>
	static It choose_pivot(It begin, It end)
	{
		It i1 = begin;
		It i2 = begin + (end-begin)/2;
		It i3 = end-1;
		if ( (*i1 > *i2) == (*i1 < *i3))
			return i1;
		else if ((*i2 > *i1) == (*i2 < *i3))
			return i2;
		else
			return i3;
	}

	template <class It>
	static It quicksort_partition(It begin, It end)
	{
		It r = end - 1;
		It pivot = choose_pivot (begin, end);
		auto pivot_value = *pivot;
		std::swap (*pivot, *r);


		It i = begin - 1;

		for (It j = begin; j != end; ++j)
		{
			if (*j < pivot_value)
			{
				++i;
				std::swap (*i, *j);
			}
		}

		std::swap (*(++i), *r);
		return i;
	}

}

namespace opl
{
	namespace sorting
	{

		template <class It>
		void
		insertion (It begin, It end)
		{
		    for(It i = begin + 1; i != end; ++i)
			{
				auto key = *i;
				It j = i - 1;
				while(j >= begin && *j > key)
				{
					*(j+1) = *j;
					--j;
				}
				*(j+1) = key;
			}
		}

		template <class It>
		void
		selection (It begin, It end)
		{
			for (It i = begin; i+1 != end; ++i)
			{
				It min_j = i;
				for (It j = i + 1; j != end; ++j)
				{
					if (*j < *min_j)
						min_j = j;
				}
				std::swap (*i, *min_j);
			}
		}

		template <class It>
		void
		merge (It begin, It end)
		{
			if (begin + 1 >= end)
				return;

			It q = begin + (end - begin) / 2;
			merge (begin, q);
			merge (q, end);

			std::vector<decltype (*begin)> temp (begin, end);
			auto i = temp.begin ();
			auto j = temp.begin() + (temp.end () - temp.begin ()) / 2;
			auto q2 = j;

			for (It k = begin; k != end; ++k)
			{
				if (j == temp.end() || (i < q2 && *i < *j))
					*k = *(i++);
				else
					*k = *(j++);
			}

		}

		template <class It>
		void
		bubble(It begin, It end)
		{
			bool swapped;
			do
			{
				swapped = false;
				--end;
				for (It i = begin; i != end; ++i)
				{
					if (*i > *(i+1))
					{
						std::swap (*i, *(i+1));
						swapped = true;
					}
				}
			}
			while (swapped);
		}

		template<class It>
		void quicksort(It begin, It end)
		{
			if (begin + 1 >= end)
				return;

			It pivot = quicksort_partition (begin, end);
			quicksort (begin, pivot);
			quicksort (pivot+1, end);
		}


		/** Linear sorting (O(n+k)), only works for positive integers
		 * @param k maximum value inside the array
		 **/
		template <class It>
		void counting(It begin, It end, size_t k)
		{
			size_t n = end-begin;
			std::vector<size_t> out (n);
			std::vector<size_t> temp (k + 1, 0);


			for (It i = begin; i != end; ++i)
			  ++temp[*i];


			for (auto i = temp.begin () + 1; i != temp.end (); ++i)
				*i += *(i-1);



			for (size_t i = n-1; i < n; --i)
				out[--temp[*(begin+i)]] = *(begin+i);

			std::copy (out.begin (), out.end (), begin);
		}



	}
}

#endif //!SORTING_HH_