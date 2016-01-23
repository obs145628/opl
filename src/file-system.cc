#include <cstdio>
#include <stdexcept>
#include <iterator>
#include <fstream>
#include <sstream>
#include "file-system.hh"

namespace opl
{

	const char FileStat::type_unknown = 0;
	const char FileStat::type_file = 1;
	const char FileStat::type_dir = 2;

	FileSystem::data_type
	FileSystem::read_file (const std::string& path)
	{
		std::ifstream fs(path, std::ios::binary);
		return data_type (std::istreambuf_iterator<char> (fs),
						  std::istreambuf_iterator<char> ());
	}

	void
	FileSystem::write_file (const std::string& path, const data_type& data)
	{
		std::ofstream fs (path, std::ios::out | std::ios::binary);
		fs.write (&data[0], data.size ());
	}

	void
	FileSystem::append_file (const std::string& path, const data_type& data)
	{
		std::ofstream fs (path, std::ios::app | std::ios::binary);
		fs.write (&data[0], data.size ());
	}

	std::string
	FileSystem::read_text_file (const std::string& path)
	{
		std::ifstream fs (path);
		std::stringstream buffer;
		buffer << fs.rdbuf ();
		return buffer.str ();
	}

	void
	FileSystem::write_text_file (const std::string& path,
								 const std::string& data)
	{
		std::ofstream fs (path);
		fs << data;
	}

	void
	FileSystem::append_text_file (const std::string& path,
								  const std::string& data)
	{
		std::ofstream fs (path, std::ios_base::app);
		fs << data;
	}


	void
	FileSystem::copy_file (const std::string& src,
						   const std::string& dst)
	{
		std::ifstream ifs (src, std::ios::binary);
		std::ofstream ofs (dst, std::ios::binary);
		ofs << ifs.rdbuf ();
	}

	void
	FileSystem::move_file (const std::string& src, const std::string& dst)
	{
		if (std::rename (src.c_str (), dst.c_str ()))
		{
			throw std::runtime_error ("move_file error");
		}
	}

	void
	FileSystem::remove_file (const std::string& path)
	{
		if (std::remove (path.c_str ()))
			throw std::runtime_error ("remove_file error");
	}

	bool
	FileSystem::exists (const std::string& path)
	{
		return stat (path).type != FileStat::type_unknown;
	}

	void
	FileSystem::remove_empty_dir(const std::string& path)
	{
		if (std::remove (path.c_str ()))
			throw std::runtime_error ("remove_empty_dir error");
	}

	void
	FileSystem::remove_dir (const std::string& path)
	{
		std::vector<std::string> files = read_dir (path);
		for (auto it = files.begin (); it != files.end (); ++it)
		{
			std::string file = std::string (path_manager_
			   ->join (path.c_str (), (*it).c_str ()));
			FileStat fs = stat (file);

			if (fs.type == FileStat::type_file)
				remove_file (file);
			else if (fs.type == FileStat::type_dir)
				remove_dir (file);
			else
				throw std::runtime_error ("remove_dir");
		}

		remove_empty_dir (path);
	}

	void
	FileSystem::copy_dir (const std::string& src, const std::string& dst)
	{
		std::vector<std::string> files = read_dir (src);
		make_dir(dst);

		for (auto it = files.begin (); it != files.end (); ++it)
		{

		    std::string src_file = std::string (path_manager_
			   ->join (src.c_str (), (*it).c_str ()));
			std::string dst_file = std::string (path_manager_
			   ->join (dst.c_str (), (*it).c_str ()));
			FileStat fs = stat (src_file);

			if (fs.type == FileStat::type_file)
				copy_file (src_file, dst_file);
			else if (fs.type == FileStat::type_dir)
				copy_dir (src_file, dst_file);
			else
				throw std::runtime_error ("copy_dir");
		}
	}

	void
	FileSystem::move_dir (const std::string& src, const std::string& dst)
	{
		if (std::rename (src.c_str (), dst.c_str ()))
			throw std::runtime_error ("move_dir error");
	}




}