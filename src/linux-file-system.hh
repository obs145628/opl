/** @file LinuxFileSystem class definition
 */

#ifndef LINUX_FILE_SYSTEM_HH_
# define LINUX_FILE_SYSTEM_HH_

# include "file-system.hh"

namespace opl
{

	class LinuxFileSystem: public FileSystem
	{

	public:

		static FileSystem*
		instance ();

		virtual FileStat
		stat (const std::string& path) override;

		virtual std::vector<std::string>
		read_dir (const std::string& path) override;

		virtual void
		make_dir (const std::string& path) override;

	private:
		static FileSystem* instance_;
		LinuxFileSystem ();
		LinuxFileSystem (const LinuxFileSystem&) = delete;


	};

}

#endif