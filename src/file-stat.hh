/** @file FileStat struct definition
 */

#ifndef FILE_STAT_HH_
# define FILE_STAT_HH_

# include <ctime>

namespace opl
{

	///stat of system file / directory
	struct FileStat
	{
		static const char type_unknown;
		static const char type_file;
		static const char type_dir;

		char type;
		size_t size;
		time_t atime;
		time_t mtime;
		time_t ctime;
	};

}

#endif //!FILE_STAT_HH_