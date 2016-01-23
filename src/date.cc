#define _POSIX_C_SOURCE 200809L
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif //!_GNU_SOURCE

#include <ctime>
#include <cstdlib>
#include "date.hh"
#include "cstr-utils.hh"

namespace
{

	static const int date_dmonths[] =
	{
		31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};

	static const char *date_ndays[] =
	{
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thurday",
		"Friday",
		"Saturday",
		"Synday"
	};

	static const char *date_nmonths[] =
	{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"Octember",
		"November",
		"December"
	};

	static const char *date_nhours[] =
	{
		"AM",
		"PM"
	};

	time_t gtm_offset_ms_get()
	{
		time_t t = time(0);
		struct tm lt;
		localtime_r(&t, &lt);
		return lt.tm_gmtoff * 1000;
	}

	bool leap_year(int y)
	{
		return y % 4 == 0 && (y % 100 || y % 400  == 0);
	}

	int days_in_year(int y)
	{
		return 365 + leap_year(y);
	}

	int days_in_month(int m, int y)
	{
		return date_dmonths[m] + (m == 1 && leap_year(y));
	}

}


namespace opl
{

	time_t
	Date::timestamp_ms ()
	{
		struct timespec spec;
		clock_gettime (CLOCK_REALTIME, &spec);
		time_t ms = spec.tv_nsec / 1.0e6;
		return 1000 * spec.tv_sec + ms;
	}

	time_t
	Date::timestamp_s ()
	{
		return Date::timestamp_ms() / 1000;
	}

	Date::Date ()
		: Date (Date::timestamp_ms ())
	{

	}

	Date::Date (time_t ms)
		: value_ (ms)
	{
		value_ = ms;
		init_ ();
	}

	Date::Date(int year, int month, int day,
			   int hour, int min, int s, int ms)
	{
	    time_t val = ms;
		val += 1000 * static_cast<time_t> (s);
		val += 60 * 1000 *  static_cast<time_t> (min);
		val += 3600 * 1000 * static_cast<time_t> (hour);
		--day;
		--month;

		for(int y = 1970; y < year; ++y)
			day += days_in_year(y);
		for(int m = 0; m < month; ++m)
			day += days_in_month(m, year);

		val += 24 * 3600 * 1000 * static_cast<time_t> (day);
		val -= gtm_offset_ms_get();
		value_ = val;
		init_ ();
	}

	time_t
	Date::ms_total_get() const
	{
		return value_;
	}

	time_t
	Date::s_total_get () const
	{
		return value_ / 1000;
	}

	time_t
	Date::ms_get() const
	{
		return ms_;
	}

	time_t
	Date::s_get () const
	{
		return sec_;
	}

	time_t
	Date::min_get () const
	{
		return min_;
	}

	time_t
	Date::hour_get () const
	{
		return hour_;
	}

	time_t
	Date::period_hour_get () const
	{
		return hour_ % 12;
	}


	std::string
	Date::period_name_get () const
	{
		return std::string (date_nhours[hour_ >= 12]);
	}

	time_t
	Date::week_day_get () const
	{
		return wday_;
	}

	std::string
	Date::week_day_name_get () const
	{
		return std::string (date_ndays[wday_]);
	}

	time_t
	Date::day_get () const
	{
		return day_;
	}

	time_t
	Date::month_get () const
	{
		return month_;
	}

	std::string
	Date::month_name_get () const
	{
		return std::string (date_nmonths[month_-1]);
	}

	time_t
	Date::year_get () const
	{
		return year_;
	}


	std::string
	Date::format(const std::string& format) const
	{
		const char *cstr = format.c_str();
	    const char *last = cstr;
		const char *it = cstr;
		char type = -1;
		size_t type_n = 0;
		std::string str = "";

		while (1)
		{
			char c = *it;
			if (c == type)
				++type_n;
			else
			{
				if (type_n)
				{
					const char *val_str;

					if (type == 'Y')
					{
						if (type_n <= 2)
						{
							val_str = cstrutils::from_ulong_fixed (year_
						        % 100, type_n);
						}
						else
						{
							val_str = cstrutils::from_ulong_fixed (year_,
								type_n);
						}
					}

					else if (type == 'M')
					{
						if (type_n <= 2)
							val_str = cstrutils::from_ulong_fixed(month_,
							    type_n);
						else
							val_str = month_name_get ().c_str ();
					}

					else if (type == 'D')
					{
						val_str = cstrutils::from_ulong_fixed (day_, type_n);
					}

					else if (type == 'd')
					{
						if (type_n <= 1)
							val_str = cstrutils::from_ulong_fixed (wday_,
							    type_n);
						else
							val_str = week_day_name_get ().c_str ();
					}

					else if (type == 'H')
					    val_str = cstrutils::from_ulong_fixed (hour_, type_n);
					else if (type == 'h')
					{
					    val_str = cstrutils::from_ulong_fixed (hour_ % 12,
						    type_n);
					}
					else if (type == 'p')
						val_str = period_name_get().c_str();
					else if (type == 'm')
						val_str = cstrutils::from_ulong_fixed (min_, type_n);
					else if (type == 's')
						val_str = cstrutils::from_ulong_fixed (sec_, type_n);
					else
						val_str = cstrutils::from_ulong_fixed (ms_, type_n);;

					str += std::string (val_str);
				    //delete val_str;
					type = -1;
					type_n = 0;
					last = it;
				}

				if (c == '%')
				{
					char *sub = cstrutils::sub (last, 0, it - last);
					str += std::string (sub);
				    delete sub;
					++it;
					c = *it;
					last = it;
				}

				else if (!c || c == 'Y' || c == 'M' || c == 'D' ||  c == 'd'
						 || c == 'H' || c == 'h' || c == 'p' || c == 'm'
						 || c == 's' || c == 'f')
				{
					type = c;
					type_n = 1;
					char *sub = cstrutils::sub (last, 0, it - last);
					str += std::string (sub);
				    delete sub;
				}
			}

			if (!c)
				break;
			++it;
		}

	    return str;
	}


	void
	Date::init_ ()
	{
		time_t val = value_ + gtm_offset_ms_get ();
		ms_ = val % 1000;
		val /= 1000;
		sec_ = val % 60;
		val /= 60;
		min_ = val % 60;
		val /= 60;
		hour_ = val % 24;
		val /= 24;

		wday_ = (val + 3) % 7;

		int year = 1970;
		while(1)
		{
			int days_y = days_in_year (year);
			if (val < days_y)
				break;
			++year;
			val -= days_y;
		}

		year_ = year;

		int month = 0;
		while(1)
		{
			int days_m = days_in_month (month, year);
			if (val < days_m)
				break;
			++month;
			val -= days_m;
		}

		month_ = month + 1;
		day_ = val+1;
	}

}