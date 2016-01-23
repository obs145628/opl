#include "console.hh"
#include <iostream>
#include <string>

namespace opl
{
	 std::string
	 Console::read_line ()
	 {
		 std::string str;
		 std::getline (std::cin, str);
		 return str;
	 }

	char
	Console::read_char ()
	{
		std::string str = read_line();
		return str.empty() ? 0 : str[0];
	}

	int
	Console::read_int ()
	{
		return std::stoi (read_line ());
	}

	long
	Console::read_long ()
	{
		return std::stol (read_line ());
	}

	double
	Console::read_double ()
	{
		return std::stod (read_line ());
	}


    std::string
	Console::prompt_line (const std::string& question)
	{
		std::cout << question;
		return read_line ();
	}

	char
	Console::prompt_char (const std::string& question)
	{
		std::cout << question;
		return read_char ();
	}

	int
	Console::prompt_int (const std::string& question)
	{
		std::cout << question;
		return read_int ();
	}

	long
	Console::prompt_long (const std::string& question)
	{
		std::cout << question;
		return read_long ();
	}

    double
	Console::prompt_double (const std::string& question)
	{
		std::cout << question;
		return read_double ();
	}

	std::string
	Console::prompt_default_line (const std::string& question,
								  const std::string& base)
	{
		std::cout << question << "[" << base << "]";
		std::string str = read_line ();
		return str.empty() ? base : str;
	}

	char
	Console::prompt_default_char (const std::string& question, char base)
	{
		std::cout << question << "[" << base << "]";
		char c = read_char ();
		return c ? c : base;
	}

	int
	Console::prompt_default_int (const std::string& question, int base)
	{
		std::cout << question << "[" << base << "]";
		std::string str = read_line ();
		return str.empty() ? base : std::stoi (str);
	}

	long
	Console::prompt_default_long (const std::string& question, long base)
	{
		std::cout << question << "[" << base << "]";
		std::string str = read_line ();
		return str.empty () ? base : std::stol (str);
	}

	double
	Console::prompt_default_double (const std::string& question, double base)
	{
		std::cout << question << "[" << base << "]";
		std::string str = read_line ();
		return str.empty() ? base : std::stod (str);
	}
}