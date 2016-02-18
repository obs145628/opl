#include "path.hh"
#include "str-utils.hh"

namespace
{

	bool
	is_posix (const std::string& s)
	{
		return opl::str::contains (s, '/');
	}

	char
	delimiter_char (const std::string& s)
	{
		return is_posix (s) ? '/' : '\\';
	}

	std::string
	delimiter (const std::string& s)
	{
		return is_posix (s) ? "/" : "\\";
	}

	bool
	has_lector (const std::string& s)
	{
		return s.size () >= 3 && s[1] == ':' && s[2] == '\\';
	}

	std::string
	lector_extract (std::string& s)
	{
		if (has_lector (s))
		{
			std::string lector = s.substr (0, 3);
			s.erase (0, 3);
			return lector;
		}
		else if (!s.empty () && s[0] == '/')
		{
			s.erase (0, 1);
			return "/";
		}
		else
		{
			return "";
		}
	}

}
std::string
opl::path::normalize (const std::string& s)
{
	std::string del = delimiter (s);
	std::string path (s);
	std::string lector = lector_extract (path);

	std::vector<std::string> parts = str::split (path, del);
	size_t size = parts.size();

	bool path_started = false;

	for (size_t i = 0; i < size; ++i)
	{
		if (i && (parts[i].empty () || parts[i] == "."))
		{
			--size;
			parts.erase (parts.begin () + i);
			--i;
		}
		else if (parts[i] == ".." )
		{
			if (path_started)
			{
				size -= 2;
				parts.erase (parts.begin () + i - 1,
							 parts.begin () + i + 1);
				i -= 2;
			}
		}
		else
			path_started = true;
	}

	return lector + str::merge (parts, del);
}

std::string
opl::path::join (const std::string& s1, const std::string& s2)
{
	if (s2[0] == '/' || has_lector (s2))
		return s2;
	else
		return normalize (s1 + delimiter (s1) + s2);
}

std::string
opl::path::dirname (const std::string& s)
{
	size_t del_pos = s.find_last_of (delimiter_char (s));
	if (del_pos == std::string::npos)
		return "";
	else
		return s.substr (0, del_pos);
}

std::string
opl::path::basename (const std::string& s)
{
	size_t del_pos = s.find_last_of (delimiter_char (s));
	if (del_pos == std::string::npos)
		return s;
	else
		return s.substr (del_pos + 1);
}

std::string
opl::path::extname (const std::string& s)
{
	size_t dot_pos = s.find_last_of ('.');
	if (dot_pos == std::string::npos)
		return "";
	else
		return s.substr (dot_pos);
}