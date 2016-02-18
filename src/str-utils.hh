/** @file string functions manipulations
 */

#ifndef STR_UTILS_HH_
# define STR_UTILS_HH_

#include <string>
#include <vector>

namespace opl
{

	namespace str
	{

		char*
		to_c_str (const std::string& str);

		std::vector<std::string>
		split (const std::string& str, const std::string& del);

		bool
		contains (const std::string& str, const std::string& sub);

		bool
		contains (const std::string& str, char c);

		std::string
		merge (const std::vector<std::string>& vec, const std::string& del);
	}

}


#endif //!STR_UTILS_HH_