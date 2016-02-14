#include <algorithm>
#include "game-subject-2d.hh"

namespace opl
{

	void
	GameSubject2D::subscribe (GameObserver2D* observer)
	{
		observers_.push_back (observer);
	}

	void
	GameSubject2D::unsusribe (GameObserver2D* observer)
	{
		auto it = std::find(observers_.begin (), observers_.end (), observer);
		if(it != observers_.end ())
			observers_.erase (it);
	}

	void
	GameSubject2D::publish_init_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_init ();
	}

	void
	GameSubject2D::publish_update_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_update ();
	}

	void
	GameSubject2D::publish_destroy_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_destroy ();
	}

	void
	GameSubject2D::publish_resize_ (r_type width, r_type height)
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_resize (width, height);
	}

	void
	GameSubject2D::publish_key_down_ (int code)
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_key_down (code);
	}

	void
	GameSubject2D::publish_key_up_ (int code)
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_key_up (code);
	}

	void
	GameSubject2D::publish_mouse_move_ (r_type x, r_type y)
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_mouse_move (x, y);
	}

	void
	GameSubject2D::publish_mouse_down_ (int code)
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_mouse_down (code);
	}

	void
	GameSubject2D::publish_mouse_up_ (int code)
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_mouse_up (code);
	}

}