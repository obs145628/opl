/** @file Class definition of abstract class PathManager
 */

#ifndef PATH_MANAGER_HH_
# define PATH_MANAGER_HH_

# include <cstddef>
# include <set>
# include <string>

namespace opl
{

	///Manage system file path. string opertatons only.
	class PathManager
	{


	public:


		///Remove useless '.', '..', multiples '/' or '\'
		virtual char*
		normalize (const char* s) = 0;

		///Concatene the two paths and normalize the result
		virtual char*
		join (const char* s1, const char* s2) = 0;

		///Returns the directory path
		virtual char*
		dirname (const char* s) = 0;

		///Returns the last portion of the path
		virtual char*
		basename (const char* s) = 0;

		///Returns the file extension (. included)
		virtual char*
		extname (const char* s) = 0;

		virtual ~PathManager ()
		{

		}

	};

}


#endif //!PATH_MANAGER_HH_