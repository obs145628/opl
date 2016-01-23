#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>
#include "linux-file-system.hh"
#include "posix-path-manager.hh"

namespace opl
{

	FileSystem*
	LinuxFileSystem::instance()
	{
		if (!LinuxFileSystem::instance_)
			LinuxFileSystem::instance_ = new LinuxFileSystem ();
		return LinuxFileSystem::instance_;
	}

    FileStat
	LinuxFileSystem::stat (const std::string& path)
	{
		struct stat buffer;
		FileStat fs;
		if (::stat (path.c_str (), &buffer))
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
		return fs;
	}

	std::vector<std::string>
	LinuxFileSystem::read_dir (const std::string& path)
	{
		std::vector<std::string> files;

		DIR *d;
		struct dirent *dir;
		d = opendir (path.c_str ());
		if (!d)
			throw std::runtime_error ("read_dir error");

		while ((dir = readdir (d)))
			if (strcmp (dir->d_name, ".") && strcmp (dir->d_name, ".."))
				files.push_back (std::string (dir->d_name));

	    return files;
	}

	void
	LinuxFileSystem::make_dir (const std::string& path)
	{
		if (mkdir (path.c_str(), 0700))
			throw std::runtime_error ("make_dir error");
	}


	FileSystem* LinuxFileSystem::instance_ = nullptr;

	LinuxFileSystem::LinuxFileSystem ()
	{
		path_manager_ = PosixPathManager::instance ();
	}

}