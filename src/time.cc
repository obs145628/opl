#include <chrono>
#include <thread>
#include "time.hh"
#include "cstr-utils.hh"

namespace opl
{

	const time_t Time::secd = 1000;
	const time_t Time::mind = 60000;
    const time_t Time::hourd = 3600000;
	const time_t Time::dayd = 24 * 3600000;
	const time_t Time::weekd = 7 * 24 * 3600000;

    void
	Time::sleep (time_t t)
	{
		std::this_thread::sleep_for (std::chrono::milliseconds (t));
	}

	Time
	Time::fromHMS (time_t h, time_t m, time_t s, time_t ms)
	{
		return Time::fromDHMS (0, h, m, s, ms);
	}


	Time
	Time::fromDHMS (time_t d, time_t h, time_t m, time_t s, time_t ms)
	{
		return Time (d * Time::dayd + h * Time::hourd + m * Time::mind
					 + s * Time::secd + ms);
	}


	Time::Time (time_t ms)
		: ms_(ms)
	{

	}

	time_t
	Time::ms_get () const
	{
		return ms_ % 1000;
	}

	time_t
	Time::s_get () const
	{
		return s_total_get() % 60;
	}

	time_t
	Time::min_get () const
	{
		return min_total_get() % 60;
	}

	time_t
	Time::h_get () const
	{
		return h_total_get() % 24;
	}

	time_t
	Time::d_get () const
	{
		return d_total_get();
	}

	time_t
	Time::ms_total_get () const
	{
		return ms_;
	}

	time_t
	Time::s_total_get () const
	{
		return ms_ / Time::secd;
	}

	time_t
	Time::min_total_get () const
	{
		return ms_ / Time::mind;
	}

	time_t
	Time::h_total_get () const
	{
		return ms_ / Time::hourd;
	}

	time_t
	Time::d_total_get () const
	{
		return ms_ / Time::dayd;
	}


	std::string
	Time::format (const std::string& format)
	{
		time_t d = d_get ();
		time_t h = h_get ();
		time_t m = min_get ();
		time_t s = s_get ();
		time_t ms = ms_get ();

		const char *cstr = format.c_str();
		const char *last = cstr;
		const char *it = cstr;

		char type = -1;
		size_t type_n = 0;
		std::string str = "";

		while(1)
		{
			char c = *it;
			if (c == type)
				++type_n;
			else
			{
				if (type_n)
				{
					time_t val;
					if (type == 'd')
						val = d;
					else if (type == 'h')
						val = h;
					else if (type == 'm')
						val = m;
					else if (type == 's')
						val = s;
					else
						val = ms;

					char* val_str = cstrutils::from_ulong_fixed (val, type_n);
				    str += std::string (val_str);
					delete val_str;
					type = -1;
					type_n = 0;
					last = it;
				}

				if(c == '%')
				{
					char* sub = cstrutils::sub (last, 0, it - last);
				    str += std::string (sub);
					delete sub;
					++it;
					c = *it;
					last = it;
				}

				else if (!c || c == 'd' || c == 'h'
						|| c == 'm' || c == 's' || c == 'f')
				{
					type = c;
					type_n = 1;
					char* sub = cstrutils::sub (last, 0, it - last);
				    str += std::string (sub);
					delete sub;
				}
			}

			if(!c)
				break;
			++it;
		}

		return str;
	}

}