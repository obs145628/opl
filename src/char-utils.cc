#include <cassert>
#include "char-utils.hh"

namespace opl
{

	namespace charutils
	{


		bool
		is_letter (char c)
		{
			return (c >= 65 && c <= 90)
				|| (c >= 97 && c <= 122);
		}

		bool
		is_upper (char c)
		{
			return c >= 65 && c <= 90;
		}

		bool
		is_lower (char c)
		{
			return c >= 97 && c <= 122;
		}

		char
		to_lower (char c)
		{
			return is_upper (c) ? c + 32 : c;
		}

		char
		to_upper (char c)
		{
			return is_lower (c) ? c - 32 : c;
		}

		bool
		is_digit (char c)
		{
			return c >= 48 && c <= 57;
		}

		int
		to_digit (char c)
		{
			assert (is_digit (c));
			return c - 48;
		}

		int
		to_alpha (char c)
		{
			assert (is_letter (c));
			return c >= 97 ? c - 97 : c - 65;
		}

		char
		from_Digit (int n)
		{
			assert (n >= 0 && n <= 9);
			return n + 48;
		}

		char
		lower_from_alpha (int alpha)
		{
			assert (alpha >= 0 && alpha <= 25);
			return alpha + 97;
		}

		char
		upper_from_alpha (int alpha)
		{
			assert (alpha >= 0 && alpha <= 25);
			return alpha + 65;
		}

	}
}