#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <iterator>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "file-system.hh"
#include "path.hh"
#include "system.hh"

#if defined (PLATFORM_UNIX_)
# include <dirent.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>
#else
# include <windows.h>
#endif





namespace opl
{

	std::vector<char>
	file_read (const std::string& path)
	{
		std::ifstream fs (path, std::ios::binary);
		return std::vector<char> (std::istreambuf_iterator<char> (fs),
								  std::istreambuf_iterator<char> ());
	}

	void
	file_write (const std::string& path, const std::vector<char>& data)
	{
		std::ofstream fs (path, std::ios::out | std::ios::binary);
		fs.write (&data[0], data.size ());
	}

	void
	file_append (const std::string& path, const std::vector<char>& data)
	{
		std::ofstream fs (path, std::ios::app | std::ios::binary);
		fs.write (&data[0], data.size ());
	}

	std::string
	file_text_read (const std::string& path)
	{
		std::ifstream fs (path);
		std::stringstream buffer;
		buffer << fs.rdbuf ();
		return buffer.str ();
	}

	void
	file_text_write (const std::string& path, const std::string& data)
	{
		std::ofstream fs (path);
		fs << data;
	}

	void
	file_text_append (const std::string& path, const std::string& data)
	{
		std::ofstream fs (path, std::ios_base::app);
		fs << data;
	}

	void
	file_copy (const std::string& src, const std::string& dst)
	{
		std::ifstream ifs (src, std::ios::binary);
		std::ofstream ofs (dst, std::ios::binary);
		ofs << ifs.rdbuf ();
	}

	void
	file_remove (const std::string& path)
	{
		if (std::remove (path.c_str ()))
			throw std::runtime_error ("remove_file error");
	}

	void
	file_move (const std::string& src, const std::string& dst)
	{
		if (std::rename (src.c_str (), dst.c_str ()))
		{
			throw std::runtime_error ("move_file error");
		}
	}

	FileStat
	file_stat (const std::string& path)
	{
		FileStat fs;

#if defined (PLATFORM_UNIX_)

		struct stat buffer;

		if (stat (path.c_str (), &buffer))
		{
			fs.type = FileStat::type_unknown;
			return fs;
		}

		if (S_ISREG (buffer.st_mode))
			fs.type = FileStat::type_file;
		else if (S_ISDIR (buffer.st_mode))
			fs.type = FileStat::type_dir;
		else
			fs.type = FileStat::type_unknown;

		fs.size = buffer.st_size;
		fs.atime = buffer.st_atime;
		fs.ctime = buffer.st_ctime;
		fs.mtime = buffer.st_mtime;

#else

		throw std::runtime_error ("file_stat win not implemented");

#endif

		return fs;
	}

	bool
	file_exists (const std::string& path)
	{
		return file_stat (path).type != FileStat::type_unknown;
	}


	std::vector<std::string>
	dir_read (const std::string& path)
	{
		std::vector<std::string> files;

#if defined (PLATFORM_UNIX_)

		DIR *d;
		struct dirent *dir;
		d = opendir (path.c_str ());
		if (!d)
			throw std::runtime_error ("read_dir error");

		while ((dir = readdir (d)))
			if (strcmp (dir->d_name, ".") && strcmp (dir->d_name, ".."))
				files.push_back (std::string (dir->d_name));

#else

		throw std::runtime_error ("dir_read win not implemented");

#endif

	    return files;
	}

	void
	dir_make (const std::string& path)
	{
#if defined (PLATFORM_UNIX_)
		if (mkdir (path.c_str(), 0700))
			throw std::runtime_error ("make_dir error");
#else
		CreateDirectory (path, 0);
#endif

	}

	void
    dir_remove_empty (const std::string& path)
	{
		if (std::remove (path.c_str ()))
			throw std::runtime_error ("remove_empty_dir error");
	}

	void
	dir_remove (const std::string& path)
	{
		std::vector<std::string> files = dir_read (path);
		for (auto it = files.begin (); it != files.end (); ++it)
		{
			std::string file = opl::path::join (path, *it);
			FileStat fs =file_stat (file);

			if (fs.type == FileStat::type_file)
				file_remove (file);
			else if (fs.type == FileStat::type_dir)
				dir_remove (file);
			else
				throw std::runtime_error ("remove_dir");
		}

		dir_remove_empty (path);
	}

	void
	dir_copy (const std::string& src, const std::string& dst)
	{
		std::vector<std::string> files = dir_read (src);
		dir_make (dst);

		for (auto it = files.begin (); it != files.end (); ++it)
		{

		    std::string src_file = opl::path::join (src, *it);
			std::string dst_file = opl::path::join (dst, *it);
			FileStat fs = file_stat (src_file);

			if (fs.type == FileStat::type_file)
				file_copy (src_file, dst_file);
			else if (fs.type == FileStat::type_dir)
				dir_copy (src_file, dst_file);
			else
				throw std::runtime_error ("copy_dir");
		}
	}

	void
	dir_move (const std::string& src, const std::string& dst)
	{
		if (std::rename (src.c_str (), dst.c_str ()))
			throw std::runtime_error ("move_dir error");
	}




}