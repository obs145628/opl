/** @file Console class definition
 */

#ifndef CONSOLE_HH_
# define CONSOLE_HH_

# include <string>

 namespace opl
 {

	 ///Manage console I/O user interractions
	 class Console
	 {

	 public:

		 virtual std::string
		 read_line ();

		 virtual char
		 read_char ();

		 virtual int
		 read_int ();

		 virtual long
		 read_long ();

		 virtual double
		 read_double ();

		 virtual std::string
		 prompt_line (const std::string& question);

		 virtual char
		 prompt_char (const std::string& question);

		 virtual int
		 prompt_int (const std::string& question);

		 virtual long
		 prompt_long (const std::string& question);

		 virtual double
		 prompt_double (const std::string& question);

		 virtual std::string
		 prompt_default_line (const std::string& question,
							  const std::string& base);

		 virtual char
		 prompt_default_char (const std::string& question, char base);

		 virtual int
		 prompt_default_int (const std::string& question, int base);

		 virtual long
		 prompt_default_long (const std::string& question, long base);

		 virtual double
		 prompt_default_double (const std::string& question, double base);
	 };

 }



#endif