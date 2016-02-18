#include <cstdio>
#include <cstring>
#include <algorithm>
#include "str-utils.hh"

char*
opl::str::to_c_str (const std::string& str)
{
	char* c_str = new char[str.size () + 1];
	std::copy (str.begin (), str.end (), c_str);
	c_str[str.size ()] = 0;
	return c_str;
}

std::vector<std::string>
opl::str::split (const std::string &str, const std::string &del)
{
	std::vector<std::string> res;
	const char* c_del = del.c_str ();

    char* c_str = to_c_str (str);
	const char* sub = strtok (c_str, c_del);

	while (sub)
	{
		res.push_back (std::string (sub));
		sub = strtok (0, c_del);
	}

	delete c_str;
	return res;
}

bool
opl::str::contains (const std::string& str, const std::string& sub)
{
	return str.find (sub) != std::string::npos;
}

bool
opl::str::contains (const std::string& str, char c)
{
	return str.find (c) != std::string::npos;
}

std::string
opl::str::merge (const std::vector<std::string>& vec, const std::string& del)
{
	std::string res = "";
	for (size_t i = 0; i < vec.size (); ++i)
	{
		if (i)
			res += del;
		res += vec[i];
	}
	return res;
}