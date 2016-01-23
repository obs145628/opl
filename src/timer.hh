/** @file Timer Class implementation
 */

#ifndef TIMER_HH_
#define TIMER_HH_

# include <ctime>

namespace opl
{

	/// Mesurate executions durations
	class Timer
	{

	public:
		Timer (bool auto_start = false);

		void
		start ();

		void
		stop ();

		void
		reset ();

		bool
		is_active () const;

		///Return duration in milliseconds
		time_t
		get () const;

	private:
		time_t start_;
		time_t stop_;

	};


}

#endif //!TIMER_HH_