#include <cstring>
#include "posix-path-manager.hh"
#include "cstr-utils.hh"

namespace opl
{


	PathManager* PosixPathManager::instance_ = nullptr;

	PathManager*
	PosixPathManager::instance()
	{
		if (!PosixPathManager::instance_)
			PosixPathManager::instance_ = new PosixPathManager;
		return PosixPathManager::instance_;
	}



	char*
	PosixPathManager::normalize (const char* s)
	{
		std::vector<char*> parts = cstrutils::split(s, "/");
		size_t size = parts.size();

		bool path_started = false;

		for (size_t i = 0; i < size; ++i)
		{
			if (i && (!strcmp (parts[i], "") || !strcmp (parts[i], ".")))
			{
				--size;
				delete parts[i];
				parts.erase (parts.begin () + i);
				--i;
			}
			else if (!strcmp (parts[i], ".."))
			{
				if (path_started)
				{
					size -= 2;
					delete parts[i-1];
					delete parts[i];
					parts.erase (parts.begin () + i - 1,
								 parts.begin () + i + 1);
					i -= 2;
				}
			}
			else
				path_started = true;
		}

		char* res = cstrutils::merge(parts, "/");
		for(size_t i = 0; i < size; ++i)
			delete parts[i];
		return res;
	}

	char*
	PosixPathManager::join (const char* s1, const char* s2)
	{
		if (*s2 == '/')
			return cstrutils::clone (s2);

		char *s3 = cstrutils::concat (s1, "/");
		char *s4 = cstrutils::concat (s3, s2);
		delete s3;
		char* res = normalize (s4);
		delete s4;
		return res;
	}

	char*
	PosixPathManager::dirname (const char* s)
	{
		size_t slash_pos = cstrutils::last_index_of (s, "/");
		if (slash_pos == cstrutils::negative_search)
			return cstrutils::clone ("");
		else
			return cstrutils::sub (s, 0, slash_pos);
	}

	char*
	PosixPathManager::basename (const char* s)
	{
		size_t pos = cstrutils::last_index_of (s, "/");
		if (pos == cstrutils::negative_search)
			return cstrutils::clone (s);
		else
			return cstrutils::sub(s, pos + 1, strlen (s) - pos - 1);
	}

	char*
	PosixPathManager::extname (const char* s)
	{
		size_t dot_pos = cstrutils::last_index_of (s, ".");
		if (dot_pos == cstrutils::negative_search)
			return cstrutils::clone ("");
		else
			return cstrutils::sub (s, dot_pos, strlen (s) - dot_pos);
	}


}