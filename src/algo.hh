/** @file Iterators algorithms
 */

#ifndef ALGO_HH_
# define ALGO_HH_

# include <cmath>
# include <cstddef>
# include <algorithm>
# include <iostream>


#define OPL_ALGO_ZERO 1e-10

namespace opl
{

	namespace algo
	{

		template<class It>
		void
		log (It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				std::cout << *i << "\n";
		}

		///a++
		template<class It>
		void
		increment(It begin, It end)
		{
			for(It i = begin; i != end; ++i)
				(*i)++;
		}

		///a--
		template<class It>
		void
		decrement(It begin, It end)
		{
			for(It i = begin; i != end; ++i)
				(*i)--;
		}

		///b = ++a
		template<class It1, class It2>
		void
		pre_increment(It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for(; i1 != end1; ++i1, ++i2)
				*i2 = ++(*i1);
		}

		///b = --a
		template<class It1, class It2>
		void
		pre_decrement(It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for(; i1 != end1; ++i1, ++i2)
				*i2 = --(*i1);
		}

		///b = a++
		template<class It1, class It2>
		void
		post_increment(It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for(; i1 != end1; ++i1, ++i2)
				*i2 = (*i1)++;
		}

		///b = a--
		template<class It1, class It2>
		void
		post_decrement(It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for(; i1 != end1; ++i1, ++i2)
				*i2 = (*i1)--;
		}

		///a <- a + b
		template<class It1, class It2>
		void
		plus (It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 = *i1 + *i2;
		}

		///c <- a + b
		template<class It1, class It2, class It3>
		void
		plus (It1 begin1, It1 end1, It2 begin2, It3 begin3)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i1 + *i2;
		}

		///a <- a - b
		template<class It1, class It2>
		void
		minus (It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 = *i1 - *i2;
		}

		///c <- a - b
		template<class It1, class It2, class It3>
		void
		minus (It1 begin1, It1 end1, It2 begin2, It3 begin3)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i1 - *i2;
		}

		///a <- a * b
		template<class It1, class It2>
		void
		multiplies (It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 = *i1 * *i2;
		}

		///c <- a * b
		template<class It1, class It2, class It3>
		void
		multiplies (It1 begin1, It1 end1, It2 begin2, It3 begin3)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i1 * *i2;
		}

		///a <- a / b
		template<class It1, class It2>
		void
		divides (It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 = *i1 / *i2;
		}

		///c <- a / b
		template<class It1, class It2, class It3>
		void
		divides (It1 begin1, It1 end1, It2 begin2, It3 begin3)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i1 / *i2;
		}

		///a <- a % b
		template<class It1, class It2>
		void
		modulus (It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 = *i1 % *i2;
		}

		///c <- a % b
		template<class It1, class It2, class It3>
		void
		modulus (It1 begin1, It1 end1, It2 begin2, It3 begin3)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i1 % *i2;
		}


		///a <- a + x
		template<class It, class T>
		void
		plus_x (It begin, It end, const T& x)
		{
			for (It i = begin; i != end; ++i)
				*i = *i + x;
		}

		///b <- a + x
		template<class It1, class It2, class T>
		void
		plus_x (It1 begin1, It1 end1, const T& x, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = *i1 + x;
		}

		///a <- a - x
		template<class It, class T>
		void
		minus_x (It begin, It end, const T& x)
		{
			for (It i = begin; i != end; ++i)
				*i = *i - x;
		}

		///b <- a - x
		template<class It1, class It2, class T>
		void
		minus_x (It1 begin1, It1 end1, const T& x, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = *i1 - x;
		}

		///a <- a * x
		template<class It, class T>
		void
		multiplies_x (It begin, It end, const T& x)
		{
			for (It i = begin; i != end; ++i)
				*i = *i * x;
		}

		///b <- a * x
		template<class It1, class It2, class T>
		void
		multiplies_x (It1 begin1, It1 end1, const T& x, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = *i1 * x;
		}

		///a <- a / x
		template<class It, class T>
		void
		divides_x (It begin, It end, const T& x)
		{
			for (It i = begin; i != end; ++i)
				*i = *i / x;
		}

		///b <- a / x
		template<class It1, class It2, class T>
		void
		divides_x (It1 begin1, It1 end1, const T& x, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = *i1 / x;
		}

		///a <- a % x
		template<class It, class T>
		void
		modulus_x (It begin, It end, const T& x)
		{
			for (It i = begin; i != end; ++i)
				*i = *i % x;
		}

		///b <- a % x
		template<class It1, class It2, class T>
		void
		modulus_x (It1 begin1, It1 end1, const T& x, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = *i1 % x;
		}

		///a <- x + a
		template<class It, class T>
		void
		x_plus (const T& x, It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				*i = x + *i;
		}

		///b <- x + a
		template<class It1, class It2, class T>
		void
		x_plus (const T& x, It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = x + *i1;
		}

		///a <- x - a
		template<class It, class T>
		void
		x_minus (const T& x, It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				*i = x - *i;
		}

		///b <- x - a
		template<class It1, class It2, class T>
		void
		x_minus (const T& x, It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = x - *i1;
		}

		///a <- x * a
		template<class It, class T>
		void
		x_multiplies (const T& x, It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				*i = x * *i;
		}

		///b <- x * a
		template<class It1, class It2, class T>
		void
		x_multiplies (const T& x, It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = x * *i1;
		}

		///a <- x / a
		template<class It, class T>
		void
		x_divides (const T& x, It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				*i = x / *i;
		}

		///b <- x / a
		template<class It1, class It2, class T>
		void
		x_divides (const T& x, It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = x / *i1;
		}

		///a <- x % a
		template<class It, class T>
		void
		x_modulus (const T& x, It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				*i = x % *i;
		}

		///b <- x % a
		template<class It1, class It2, class T>
		void
		x_modulus (const T& x, It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = x % *i1;
		}

		///a = -a
		template<class It>
		void
		negate (It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				*i = - *i;
		}

		///b = -a
		template<class It1, class It2>
		void
		negate (It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = - *i1;
		}

		///a = |a|
		template<class It>
		void
		abs (It begin, It end)
		{
			for (It i = begin; i != end; ++i)
				*i = std::abs (*i);
		}

		///b = |a|
		template<class It1, class It2>
		void
		abs (It1 begin1, It1 end1, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = std::abs (*i2);
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		min (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type min = *begin;

			for (It i = ++begin; i != end; ++i)
				if (*i < min)
					min = *i;
			return min;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		max (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type max = *begin;

			for (It i = ++begin; i != end; ++i)
				if (*i > max)
					max = *i;
			return max;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		min_abs (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type min = *begin;

			for (It i = ++begin; i != end; ++i)
				if (std::abs (*i) < std::abs (min))
					min = *i;
			return min;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		max_abs (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type max = *begin;

			for (It i = ++begin; i != end; ++i)
				if (std::abs (*i) > std::abs (max))
					max = *i;
			return max;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		norm_square (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type ns = 0;
			for (It i = begin; i != end; ++i)
				ns += *i * *i;
			return ns;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		norm (It begin, It end)
		{
			return std::sqrt (norm_square (begin, end));
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		p_norm (It begin, It end, size_t p)
		{
			using value_type = typename std::iterator_traits<It>::value_type;

			if(p == static_cast<size_t> (-1))
				return std::abs (max_abs (begin, end));

		    value_type norm = 0;
			value_type pow (p);
			for (It i = begin; i != end; ++i)
				norm += std::pow (std::abs (*i), pow);
			return std::pow (norm, 1 / pow);
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		sum (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type x = 0;
			for (It i = begin; i != end; ++i)
				x += *i;
			return x;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		sum_abs (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type x = 0;
			for (It i = begin; i != end; ++i)
				x += std::abs(*i);
			return x;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		product (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type x = 1;
			for (It i = begin; i != end; ++i)
				x *= *i;
			return x;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		product_abs (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type x = 1;
			for (It i = begin; i != end; ++i)
				x *= std::abs(*i);
			return x;
		}


		template <class It>
	    void
		normalize (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
		    value_type x = norm (begin, end);
			for (It i = begin; i != end; ++i)
				*i /= x;
		}

		template <class It1, class It2>
	    void
		normalize (It1 begin1, It1 end1, It2 begin2)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
		    value_type x = norm (begin1, end1);
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i2 = *i1 / x;
		}

		template <class It>
	    bool
		is_unit (It begin, It end)
		{
			return std::abs (norm_square (begin, end) - 1) < OPL_ALGO_ZERO;
		}

		template <class It1, class It2>
		typename std::iterator_traits<It1>::value_type
		dot_product (It1 begin1, It1 end1, It2 begin2)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
		    value_type x = 0;
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				x += *i1 * *i2;
			return x;
		}

		template <class It1, class It2>
		typename std::iterator_traits<It1>::value_type
		distance_square (It1 begin1, It1 end1, It2 begin2)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
		    value_type x = 0;
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				x += (*i1 - *i2) * (*i1 - *i2);
			return x;
		}

		template <class It1, class It2>
		typename std::iterator_traits<It1>::value_type
		distance (It1 begin1, It1 end1, It2 begin2)
		{
		    return std::sqrt (distance_square (begin1, end1, begin2));
		}

		template <class It1, class It2>
	    bool
		is_orthogonal (It1 begin1, It1 end1, It2 begin2)
		{
		    return dot_product (begin1, end1, begin2) < OPL_ALGO_ZERO;
		}


		template <class It1, class It2>
		typename std::iterator_traits<It1>::value_type
		is_orthonormal (It1 begin1, It1 end1, It2 begin2)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
		    value_type dot = 0;
			value_type norm1 = 0;
			value_type norm2 = 0;
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
			{
				dot += *i1 * *i2;
				norm1 += *i1 * *i1;
				norm2 += *i2 * *i2;
			}

			return dot < OPL_ALGO_ZERO && std::abs (1 - norm1) < OPL_ALGO_ZERO
			    && std::abs (1 - norm2) < OPL_ALGO_ZERO;

		}

		template <class It>
		bool
		is_null (It begin, It end)
		{
			return norm_square (begin, end) < OPL_ALGO_ZERO;
		}

		template <class It1, class It2>
		bool
		equals (It1 begin1, It1 end1, It2 begin2)
		{
			return distance_square (begin1, end1, begin2) < OPL_ALGO_ZERO;
		}

		template <class It1, class It2>
	    void
		project_along (It1 begin1, It1 end1, It2 begin2)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
			value_type den = 0;
			value_type alpha = 0;
			It1 i1 = begin1;
			It2 i2 = begin2;

			for (; i1 != end1; ++i1, ++i2)
			{
				den += *i2 * *i2;
				alpha += *i1 * *i2;
			}

			if (den < OPL_ALGO_ZERO)
			{
				std::fill (begin1, end1, 0);
				return;
			}

			alpha /= den;
			i1 = begin1;
			i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 = *i2 * alpha;
		}

		template <class It1, class It2, class It3>
	    void
		project_along (It1 begin1, It1 end1, It2 begin2, It3 begin3)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
			value_type den = 0;
			value_type alpha = 0;
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;

			for (; i1 != end1; ++i1, ++i2)
			{
				den += *i2 * *i2;
				alpha += *i1 * *i2;
			}

			if (den < OPL_ALGO_ZERO)
			{
				i1 = begin1;
				for (; i1 != end1; ++i1, ++i3)
					*i3 = 0;
				return;
			}

			alpha /= den;
			i1 = begin1;
			i2 = begin2;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i2 * alpha;
		}

		template <class It1, class It2>
	    void
		project_orthogonal (It1 begin1, It1 end1, It2 begin2)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
			value_type den = 0;
			value_type alpha = 0;
			It1 i1 = begin1;
			It2 i2 = begin2;

			for (; i1 != end1; ++i1, ++i2)
			{
				den += *i2 * *i2;
				alpha += *i1 * *i2;
			}

			if (den < OPL_ALGO_ZERO)
				return;

			alpha /= den;
			i1 = begin1;
			i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 -= *i2 * alpha;
		}

		template <class It1, class It2, class It3>
	    void
		project_orthogonal (It1 begin1, It1 end1, It2 begin2, It3 begin3)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
			value_type den = 0;
			value_type alpha = 0;
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;

			for (; i1 != end1; ++i1, ++i2)
			{
				den += *i2 * *i2;
				alpha += *i1 * *i2;
			}

			if (den < OPL_ALGO_ZERO)
			{
				std::copy (begin1, end1, begin3);
				return;
			}

			alpha /= den;
			i1 = begin1;
			i2 = begin2;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i1 - *i2 * alpha;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		mean (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
			value_type sum = 0;
			value_type size = 0;
			for (It i = begin; i != end; ++i)
			{
				sum += *i;
				size += 1;
			}

			return sum / size;
		}

	    template <class It>
		typename std::iterator_traits<It>::value_type
		median (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
			std::vector<value_type> v (begin, end);
			std::sort (v.begin (), v.end ());
		    return v[v.size () / 2];
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		quartile1 (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
			std::vector<value_type> v (begin, end);
			std::sort (v.begin (), v.end ());
		    return v[v.size () / 4];
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		quartile3 (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
			std::vector<value_type> v (begin, end);
			std::sort (v.begin (), v.end ());
		    return v[v.size () * 3 / 4];
		}

		template <class It1, class It2>
		void
		interquartile (It1 begin1, It1 end1, It2 begin2)
		{
			using value_type = typename std::iterator_traits<It1>::value_type;
			std::vector<value_type> v (begin1, end1);
			std::sort (v.begin (), v.end ());
			std::copy (v.begin () + v.size () / 4,
					   v.begin () + v.size () * 3 / 4 + 1,
					   begin2);
		}

	    template <class It>
		typename std::iterator_traits<It>::value_type
		interquartile_range (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
			std::vector<value_type> v (begin, end);
			std::sort (v.begin (), v.end ());
		    return v[v.size () * 3 / 4] - v[v.size () / 4];
		}


		template <class It>
		typename std::iterator_traits<It>::value_type
		mode (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
			std::vector<value_type> v (begin, end);
			std::sort (v.begin (), v.end ());

			value_type mode = v[0];
			value_type current = mode;
			size_t mode_n = 1;
			size_t current_n = 1;

			for (size_t i = 1; i < v.size (); ++i)
			{
				if (current == v[i])
				{
					++current_n;
					if (current_n > mode_n)
					{
						mode_n = current_n;
						mode = current;
					}
				}
				else
				{
					current_n = 1;
					current = v[i];
				}
			}

		    return mode;
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		variance (It begin, It end)
		{
			using value_type = typename std::iterator_traits<It>::value_type;
			value_type n = static_cast<value_type> (0);
			value_type sum = static_cast<value_type> (0);
			value_type square = static_cast<value_type> (0);

			for (It i = begin; i != end; ++i)
			{
				sum += *i;
				square += *i * *i;
				n += static_cast<value_type> (1);
			}

			return square / n - (sum * sum) / (n * n);
		}

		template <class It>
		typename std::iterator_traits<It>::value_type
		standard_deviation (It begin, It end)
		{
		    return std::sqrt (variance (begin, end));
		}

		///a <- a + xb
		template <class It1, class It2, class T>
		void
		saxpy (It1 begin1, It1 end1, const T& x, It2 begin2)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			for (; i1 != end1; ++i1, ++i2)
				*i1 += x * *i2;
		}

		///c <- a + xb
		template <class It1, class It2, class It3, class T>
		void
		saxpy (It1 begin1, It1 end1, const T& x, It2 begin2, It3 begin3)
		{
			It1 i1 = begin1;
			It2 i2 = begin2;
			It3 i3 = begin3;
			for (; i1 != end1; ++i1, ++i2, ++i3)
				*i3 = *i1 + x * *i2;
		}

	}

}


#endif //!ALGO_HH_