/** @file Time class definition
 **/

#ifndef TIME_HH_
# define TIME_HH_

# include <ctime>
# include <string>

namespace opl
{

	/** Class for manipulating durations in ms
	 */
	class Time
	{

	public:


		static const time_t secd;
		static const time_t mind;
		static const time_t hourd;
		static const time_t dayd;
		static const time_t weekd;

		///Put the programe in pause for t ms
		static void
		sleep (time_t t);

		/** Returns a time object
		 * @param h number of hours
		 * @param m number of minutes
		 * @param s number of seconds
		 * @param ms number of milliseconds
		 **/
		static Time
		fromHMS (time_t h = 0, time_t m = 0, time_t s = 0, time_t ms = 0);

		/** Returns a time object
		 * @param d number of days
		 * @param h number of hours
		 * @param m number of minutes
		 * @param s number of seconds
		 * @param ms number of milliseconds
		 **/
		static Time
		fromDHMS (time_t d = 0, time_t h = 0, time_t m = 0,
				  time_t s = 0, time_t ms = 0);


		Time (time_t ms);

		time_t
		ms_get () const;

		time_t
		s_get () const;

		time_t
		min_get () const;

		time_t
		h_get () const;

		time_t
		d_get () const;

		time_t
		ms_total_get () const;

		time_t
		s_total_get () const;

		time_t
		min_total_get () const;

		time_t
		h_total_get () const;

		time_t
		d_total_get () const;

		/** Get a formatted string according to the format
		 *	Day: d
		 *	Hour: h
		 *	Minute: m
		 *	Second: s
		 *	Millisecond: f
		 *	Escape character: %
		 */
		std::string
		format (const std::string& format);

	private:
		time_t ms_;

	};
}

#endif //!TIME_HH_