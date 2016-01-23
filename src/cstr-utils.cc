#include <cstring>
#include <algorithm>
#include "cstr-utils.hh"
#include "char-utils.hh"


namespace
{

	std::vector<size_t>
	matches (const char* str, const char* sub, size_t &str_size)
	{
		std::vector<size_t> v;
		size_t i_sub = 0;
		size_t i = 0;

		for (i = 0; str[i]; ++i)
		{
			if (str[i] == sub[i_sub])
			{
				if (!sub[++i_sub])
					v.push_back (i - i_sub + 1);
			}
			else
				i_sub = 0;
		}

		str_size = i;
		return v;
	}
}

namespace opl
{

	namespace cstrutils
	{

		const size_t negative_search = -1;

		char*
		clone (const char* str)
		{
			size_t size = strlen (str);
			char* res = new char[size + 1];
			strncpy (res, str, size + 1);
			return res;
		}

		std::vector<char*>
		split (const char* str, const char* separator)
		{
			size_t start_sub = 0;
			size_t sep_i = 0;
			size_t i = 0;
			std::vector<char*> v;

			while (1)
			{
				if (!str[i] || str[i] == separator[sep_i])
				{
					if (!str[i] || !separator[++sep_i])
					{
						size_t sub_size = i - sep_i - start_sub + !!str[i];
						char *sub = new char[sub_size + 1];
						memcpy (sub, str + start_sub, sub_size);
						sub[sub_size] = 0;
						v.push_back (sub);
						start_sub = i+1;
						sep_i = 0;
					}
				}

				if (!str[i])
				{
					break;
				}

				++i;
			}

		    return v;
		}

		size_t
		index_of (const char* str, const char* sub)
		{
			size_t i_sub = 0;

			for (size_t i = 0; str[i]; ++i)
			{
				if (str[i] == sub[i_sub])
				{
					if (!sub[++i_sub])
						return i - i_sub + 1;
				}
				else
					i_sub = 0;
			}

			return negative_search;
		}

		size_t
		last_index_of (const char* str, const char* sub)
		{
			size_t i_sub = 0;
			size_t last = negative_search;

			for (size_t i = 0; str[i]; ++i)
			{
				if (str[i] == sub[i_sub])
				{
					if (!sub[++i_sub])
					{
					 	last = i - i_sub + 1;
					 	i_sub = 0;
					}
				}
				else
					i_sub = 0;
			}

			return last;
		}

		char*
		sub (const char* str, size_t start, size_t size)
		{
			char* res = new char[size + 1];
			strncpy (res, str + start, size);
			return res;
		}

		char*
		reverse (const char* str)
		{
			size_t size = strlen (str);
			char* res = new char[size + 1 ];
			for (size_t i = 0; i < size; ++i)
			{
				res[size - 1 - i] = str[i];
			}

			res[size] = 0;
			return res;
		}

		char*
		replace (const char* src, char* find, const char* repl)
		{
			size_t src_size;
			std::vector<size_t> v = matches (src, find, src_size);
			size_t find_size = strlen (find);
			size_t repl_size = strlen (repl);
			size_t nb_matches = v.size ();

			size_t res_size = src_size + (repl_size - find_size) * nb_matches;
			char* res = new char[res_size + 1];
			size_t src_i = 0;
			size_t res_i = 0;

			for (size_t i = 0; i < nb_matches; ++i)
			{
				size_t val = v[i];
				strncpy (res + res_i, src + src_i, val - src_i);
				res_i += (val - src_i);
				strncpy (res + res_i, repl, repl_size);
				src_i  = val + find_size;
				res_i += repl_size;
			}

			strncpy (res + res_i, src + src_i, src_size - src_i);
			res[res_size] = 0;
			return res;
		}

		char*
		concat (const char* s1, const char* s2)
		{
			size_t c1 = strlen (s1);
			size_t c2 = strlen (s2);
			size_t size = c1 + c2 +1;
			char* res = new char[size];
			memcpy (res, s1, c1);
			memcpy (res + c1, s2, c2);
			res[size - 1] = 0;
			return res;
		}


		char*
		merge (const std::vector<char*>& strs, const char* sep)
		{
			size_t size = strs.size();
			std::vector<size_t> sizes (size);
			size_t sep_size = strlen (sep);
			size_t total_size = sep_size * (size - 1);

			for (size_t i = 0; i < size; ++i)
			{
				sizes[i] = strlen (strs[i]);
				total_size += sizes[i];
			}

			char* res = new char[total_size + 1];
			size_t i = sizes[0];

			strncpy(res, strs[0], i);

			for (size_t j = 1; j < size; ++j)
			{
				strncpy (res + i, sep, sep_size);
				i += sep_size;
				strncpy (res + i, strs[j], sizes[j]);
				i += sizes[j];
			}

			res[total_size] = 0;
			return res;
		}


		char*
		trim (const char* str)
		{
			size_t start = 0;
			while (str[start] == ' ')
				++start;

			size_t end = start;
			for(size_t i = start + 1; str[i]; ++i)
				if(str[i] != ' ')
					end = i+1;

			size_t size = end-start;
			char* res = new char[size + 1];
			strncpy (res, str + start, size);
			res[size] = 0;
			return res;
		}

		char*
		to_lower (const char* str)
		{
			size_t size = strlen (str);
			char* res = new char[size + 1];

			for(size_t i = 0; i < size; ++i)
				res[i] = charutils::to_lower (str[i]);
			res[size] = 0;
			return res;
		}

		char*
		to_upper (const char* str)
		{
			size_t size = strlen (str);
			char* res = new char[size + 1];

			for(size_t i = 0; i < size; ++i)
				res[i] = charutils::to_upper (str[i]);
			res[size] = 0;
			return res;
		}

		char*
	    longest_common_subsequence (const char* s1, const char* s2)
		{
			size_t n1 = strlen (s1) + 1;
			size_t n2 = strlen (s2) + 1;

			std::vector<size_t> a1 (n1 * n2);
			std::vector<char> a2 (n1 * n2);

			for (size_t i = 1; i < n1; ++i)
				a1[i * n2] = 0;
			for (size_t i = 0; i < n2; ++i)
				a1[i] = 0;



			for (size_t i = 1; i < n1; ++i)
				for (size_t j = 1; j < n2; ++j)
				{
					if (s1[i - 1] == s2[ j - 1])
					{
						a1[i * n2 + j] = a1[(i - 1) * n2 + j - 1] + 1;
						a2[i * n2 + j] = 3;
					}
					else if (a1[(i - 1) * n2 + j] >= a1[i * n2 + j - 1])
					{
						a1[i * n2 + j] = a1[(i - 1) * n2 + j];
						a2[i * n2 + j] = 2;
					}
					else
					{
						a1[i * n2 + j] = a1[i * n2 + j - 1];
						a2[i * n2 + j] = 1;
					}
				}


			std::vector<char> temp (n1 + 1);
			size_t k = 0;
			for (size_t i = n1 - 1, j = n2 - 1; i && j; )
			{
				char code = a2[i * n2 + j];
				if (code == 3)
				{
					temp[k++] = s1[i - 1];
					--i;
					--j;
				}
				else if (code == 2)
					--i;
				else
					--j;
			}

			char *res = new char[k+1];
			for (size_t i = 0; i < k; ++i)
				res[i] = temp[k-1-i];

			res[k] = 0;
			return res;
		}

		char*
		longest_common_prefix (const char* s1, const char* s2)
		{
			size_t i = 0;
			while (s1[i] && s2[i] && s1[i] == s2[i])
				++i;

			return sub (s1, 0, i);
		}

		char*
		longest_common_sufix (const char* s1, const char* s2)
		{
			size_t n1 = strlen (s1);
			size_t n2 = strlen (s2);
			size_t i1 = n1-1;
			size_t i2 = n2-1;

			while (i1 < n1 && i2 < n2 && s1[i1] == s2[i2])
			{
				--i1;
				--i2;
			}

			return sub (s1, i1 + 1, n1 - i1 - 1);
		}


		char*
		from_long (long int n)
		{
			size_t size = 2;
			long int an = n;
			if (n < 0)
			{
				++size;
				an = -n;
			}

			long int temp = an;
			while (an >= 10)
			{
				an /= 10;
				++size;
			}

			char* res = new char[size];
			size_t i = size-1;
			res[i--] = 0;
			while (i < size)
			{
				res[i--] = (temp % 10) + '0';
				temp /= 10;
			}
			if (n < 0)
				*res = '-';
			return res;
		}

		long int
		to_long (const char* str)
		{
			if (!*str)
				return 0;
			int sign = 0;
			if (*str == '-')
			{
				sign = 1;
				++str;
			}

			long int n = 0;
			while (*str >= '0' && *str <= '9')
			{
				n = 10 * n + *str - '0';
				++str;
			}

			return sign ? -n : n;
		}

		char*
		from_ulong (unsigned long int n)
		{
			return from_ulong_fixed (n, 1);
		}


		char*
		from_ulong_fixed (unsigned long int n, size_t min_size)
		{
			++min_size;
			size_t size = 2;
			unsigned long int temp = n;
			while (n >= 10)
			{
				n /= 10;
				++size;
			}

			size = std::max(min_size, size);
			char* res = new char[size];
			size_t i = size - 1;
			n = temp;
			res[i--] = 0;
			while (i < size)
			{
				res[i--] = (n % 10) + '0';
				n /= 10;
			}
			return res;
		}

		unsigned long int
		to_ulong (const char* str)
		{
			unsigned long int n = 0;
			while (*str >= '0' && *str <= '9')
			{
				n = 10 * n + *str - '0';
				++str;
			}
			return n;
		}

	}

}