/** @file Set of maths function
 */

#ifndef MATH_HH_
# define MATH_HH_

# define OPL_ZERO 1e-10
# define OPL_PI 3.14159265358979323846

#include <cmath>
#include <cassert>

namespace opl
{

	namespace math
	{

		///returns (-1)^n
		template <class T>
		constexpr T
		powm1 (const T& n)
		{
			if (n % static_cast<T> (2))
				return static_cast<T> (-1);
			else
				return static_cast<T> (1);
		}

		///returns if n ~ 0 knowing n >= 0
		template <class T>
		constexpr bool
		is_pnull (const T& n)
		{
			return n <= static_cast<T> (OPL_ZERO);
		}

		///returns if n ~ 0 knowing n <= 0
	    template <class T>
		constexpr bool
		is_nnull (const T& n)
		{
			return n >= static_cast<T> (-OPL_ZERO);
		}

		///returns if n ~ 0
		template <class T>
		constexpr bool
		is_null (const T& n)
		{
			return std::abs (n) <= static_cast<T> (OPL_ZERO);
		}

		///returns if a ~ b knowing a >= b
		template <class T>
		constexpr bool
		is_pequal (const T& a, const T& b)
		{
			return is_pnull (a - b);
		}

		///returns if a ~ b knowing a <= b
		template <class T>
		constexpr bool
		is_nequal (const T& a, const T& b)
		{
			return is_nnull (a - b);
		}

		///returns if a ~ b
		template <class T>
		constexpr bool
		is_equal (const T& a, const T& b)
		{
			return is_null (a - b);
		}


		template <class T>
		constexpr T
		factorial (const T& n)
		{
			T fact = static_cast <T> (1);
			T i = static_cast <T> (2);
			while (i <= n)
			{
				fact *= i;
				i += static_cast <T> (1);
			}
			return fact;
		}

		template <class T>
		constexpr T
		binomial_coefficient (const T& n, const T& k)
		{
			T num = static_cast <T> (1);
			T i = n - k + static_cast <T> (1);
			while (i <= n)
			{
				num *= i;
				i += static_cast <T> (1);
			}

			return num / factorial (k);
		}

		template <class T>
		constexpr T
		binomial_distribution (const T& k, const T& n, const T& p)
		{
			return binomial_coefficient (n, k) * std::pow (p, k)
				* std::pow (static_cast <T> (1) - p, n - k);
		}

		template <class T>
		constexpr T
		nd_pdensity (const T& s2, const T& u, const T& x)
		{
			T pi =static_cast <T> (OPL_PI);
			T norm = static_cast <T> (1)
				/ std::sqrt (static_cast<T> (2) * pi * s2);
			T pow = - (x - u) * (x - u) / (2 * s2);
			return std::exp (pow) / norm;
		}

		template <class T>
		constexpr T
		confidence_interval (size_t n, const T& var)
		{
			return static_cast<T> (1.96)
				* std::sqrt (var / static_cast <T> (n));
		}


	}

}


#endif //!MATH_HH_