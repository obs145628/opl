#include "timer.hh"
#include "date.hh"


namespace opl
{

	Timer::Timer (bool auto_start)
	{
		reset ();
		if (auto_start)
			start ();
	}

	void
	Timer::start ()
	{
		if (start_ != -1)
			return;

		start_ = Date::timestamp_ms () - stop_;
		stop_ = -1;
	}

	void
	Timer::stop ()
	{
		if (stop_ != -1)
			return;

		stop_ = Date::timestamp_ms () - start_;
		start_ = -1;
	}

	void
	Timer::reset ()
	{
		start_ = -1;
		stop_ = 0;
	}

	bool
	Timer::is_active () const
	{
		return stop_ == -1;
	}

	time_t
	Timer::get () const
	{
		return is_active () ? Date::timestamp_ms () - start_ : stop_;
	}

}