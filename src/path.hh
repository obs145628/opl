/** @file set of functions to manipulate file paths
 */

#ifndef PATH_HH_
# define PATH_HH_

# include <string>

namespace opl
{
	namespace path
	{


		///Remove useless '.', '..', multiples '/' or '\'
		std::string
		normalize (const std::string& s);

		///Concatene the two paths and normalize the result
		std::string
		join (const std::string& s1, const std::string& s2);

		///Returns the directory path
		std::string
		dirname (const std::string& s);

		///Returns the last portion of the path
		std::string
		basename (const std::string& s);

		///Returns the file extension (. included)
		std::string
		extname (const std::string& s);

	}
}


#endif //!PATH_HH_