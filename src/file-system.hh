/** @file FileSystem class definition
 */

#ifndef FILE_SYSTEM_HH_
# define FILE_SYSTEM_HH_

# include <string>
# include <vector>
# include "path-manager.hh"

namespace opl
{

	class FileStat
	{
	public:
		static const char type_unknown;
		static const char type_file;
		static const char type_dir;

		char type;
		size_t size;
		time_t atime;
		time_t mtime;
		time_t ctime;
	};

	/**
	 * Handle basic file i/o operations
	 */
	class FileSystem
	{

	public:
		using data_type = std::vector<char>;


	    virtual data_type
		read_file (const std::string& path);

		virtual void
		write_file (const std::string& path, const data_type& data);

		virtual void
		append_file (const std::string& path, const data_type& data);

		virtual std::string
		read_text_file (const std::string& path);

		virtual void
		write_text_file (const std::string& path, const std::string& data);

		virtual void
		append_text_file (const std::string& path, const std::string& data);


		virtual void
		copy_file (const std::string& src, const std::string& dst);

		virtual void
		remove_file (const std::string& path);

		virtual void
		move_file (const std::string& src, const std::string& dst);

		virtual FileStat
		stat (const std::string& path) = 0;

		virtual bool
		exists (const std::string& path);



		virtual std::vector<std::string>
		read_dir (const std::string& path) = 0;

		virtual void
		make_dir (const std::string& path) = 0;

		virtual void
		remove_empty_dir(const std::string& path);

		virtual void
		remove_dir (const std::string& path);

		virtual void
		copy_dir (const std::string& src, const std::string& dst);

		virtual void
		move_dir (const std::string& src, const std::string& dst);

	protected:
		PathManager* path_manager_;


	};

}


#endif //!FILE_SYSTEM_HH_