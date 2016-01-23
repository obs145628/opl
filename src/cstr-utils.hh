/** @file Set of functions for manipulating native C strings (char*)
 */

#ifndef CSTR_UTILS_HH_
# define CSTR_UTILS_HH_

#include <cstddef>
#include <vector>



namespace opl
{

	namespace cstrutils
	{

		extern const size_t negative_search;

		char*
		clone (const char* str);

		std::vector<char*>
		split (const char* str, const char* separator);

		size_t
		index_of (const char* str, const char* sub);

		size_t
		last_index_of (const char* str, const char* sub);

		/// Return a substring of str from start included
		char*
		sub (const char* str, size_t start, size_t size);

		char*
		reverse (const char* str);

		///Return a new string with all occurences of find replaced by repl
		char*
		replace (const char* src, char* find, const char* repl);

		char*
		concat (const char* s1, const char* s2);

		///Do the opposite of split
		char*
		merge (const std::vector<char*>& strs, const char* sep);

		///Remove all spaces at begin and end of str
		char*
		trim (const char* str);

		char*
		to_lower (const char* str);

		char*
		to_upper (const char* str);

		char*
	    longest_common_subsequence (const char* s1, const char* s2);

		char*
		longest_common_prefix (const char* s1, const char* s2);

		char*
		longest_common_sufix (const char* s1, const char* s2);


		char*
		from_long (long int n);

		long int
		to_long (const char* str);

		char*
		from_ulong (unsigned long int n);

		///Return a string of at least minSize starting with 0s
		char*
		from_ulong_fixed (unsigned long int n, size_t min_size);

		unsigned long int
		to_ulong (const char* str);

	}

}



#endif //!CSTR_UTILS_HH_