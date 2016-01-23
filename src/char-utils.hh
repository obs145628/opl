/** @file Set un functions for manipulaing characters
 */

#ifndef CHAR_UTILS_HH_
# define CHAR_UTILS_HH_

namespace opl
{

	namespace charutils
	{


		bool
		is_letter (char c);

		bool
		is_upper (char c);

		bool
		is_lower (char c);

		char
		to_lower (char c);

		char
		to_upper (char c);

		bool
		is_digit (char c);

		int
		to_digit (char c);

		///Convert a letter to it's representation 0-25
		int
		to_alpha (char c);

		char
		from_Digit (int n);

		///Convert a letter 0-25 to it's lower char code
		char
		lower_from_alpha (int alpha);

		///Convert a letter 0-25 to it's upper char code
		char
		upper_from_alpha (int alpha);

	}
}

#endif //!CHAR_UTILS_HH_