/** @file Date class definition
 */

#ifndef DATE_HH_
# define DATE_HH_

# include <ctime>
# include <string>
# include "serialization.hh"


namespace opl
{

	/** Class for manipulating dates in milliseconds
	 */
	class Date
	{

	public:

		static time_t
		timestamp_ms ();

		static time_t
		timestamp_s ();

		Date();

		Date(time_t ms);
		Date(int year, int month, int day, int hour = 0, int min = 0,
			 int s = 0, int ms = 0);

		time_t
		ms_total_get() const;

		time_t
		s_total_get () const;

		time_t
		ms_get() const;

		time_t
		s_get () const;

		time_t
		min_get () const;

		time_t
		hour_get () const;

		///returns 0 (AM) or 1 (PM)
		time_t
		period_hour_get () const;

		///returns "AM" or "PM"
		std::string
		period_name_get () const;

		time_t
		week_day_get () const;

		std::string
		week_day_name_get () const;

		time_t
		day_get () const;

		time_t
		month_get () const;

		std::string
		month_name_get () const;

		time_t
		year_get () const;

		/** Returns a formatted string date
		 * Year: 2-Digits : Y/YY, 4 Digits : YYY...
		 * Month: Digits : M/MM, Name: MMM...
		 * Day: Digit : D
		 * Day of week : Digit : d, Name: dd...
		 * Hour: 24-hour : H, 12-hour: h
		 * Hour period : p
		 * Minute: m
		 * Second: s
		 * Millisecond: f
		 * Escape character: %
		 */
		std::string
		format(const std::string& format) const;

	private:

		void
		init_ ();

		time_t value_;
		int  ms_;
		int sec_;
		int min_;
		int hour_;
		int day_;
		int wday_;
		int month_;
		int year_;

		friend class SerialManager<Date>;


	};


	template <>
	class SerialManager<Date>
	{
	public:
		static void
		pack (std::ostream& os, const Date& data)
			{
				serialize (os, data.value_);
			}

		static Date
		unpack (std::istream& is)
		   	{
				time_t ms = unserialize<time_t> (is);
			    return Date {ms};
			}
	};

}

#endif //!DATE_HH_