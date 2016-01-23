/** @file Set of maths function
 */

#ifndef MATH_HH_
# define MATH_HH_

namespace opl
{

	namespace math
	{

		template <class T>
		T powm1 (T n)
		{
			if (n % static_cast<T> (2))
				return static_cast<T> (-1);
			else
				return static_cast<T> (1);
		}


	}

}


#endif //!MATH_HH_