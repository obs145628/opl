/** @file PosixPathManager class implementation
 */

#ifndef POSIX_PATH_MANAGER_HH_
# define POSIX_PATH_MANAGER_HH_

#include "path-manager.hh"
#include <map>
#include <string>

namespace opl
{

	class PosixPathManager: public PathManager
	{

	public:
		using super_type = PathManager;

		static PathManager*
		instance ();

		virtual char*
		normalize (const char* s) override;

		virtual char*
		join (const char* s1, const char* s2) override;

		virtual char*
		dirname (const char* s) override;

		virtual char*
		basename (const char* s) override;

		virtual char*
		extname (const char* s) override;

	private:

		PosixPathManager ()
		{

		}

		PosixPathManager (const PosixPathManager&) = delete;

		static PathManager* instance_;



	};

}

#endif //!POSIX_PATH_MANAGER_HH_