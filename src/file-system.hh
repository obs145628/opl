/** @file set of files functions manipulation
 */

#ifndef FILE_SYSTEM_HH_
# define FILE_SYSTEM_HH_

# include <string>
# include <vector>
# include "file-stat.hh"

namespace opl
{


	std::vector<char>
	file_read (const std::string& path);

	void
	file_write (const std::string& path, const std::vector<char>& data);

	void
	file_append (const std::string& path, const std::vector<char>& data);

	std::string
	file_text_read (const std::string& path);

	void
	file_text_write (const std::string& path, const std::string& data);

	void
	file_text_append (const std::string& path, const std::string& data);

	void
	file_copy (const std::string& src, const std::string& dst);

	void
	file_remove (const std::string& path);

	void
	file_move (const std::string& src, const std::string& dst);

	FileStat
	file_stat (const std::string& path);

	bool
	file_exists (const std::string& path);


	std::vector<std::string>
	dir_read (const std::string& path);

	void
	dir_make (const std::string& path);

	void
    dir_remove_empty (const std::string& path);

	void
	dir_remove (const std::string& path);

	void
	dir_copy (const std::string& src, const std::string& dst);

	void
	dir_move (const std::string& src, const std::string& dst);

}


#endif //!FILE_SYSTEM_HH_