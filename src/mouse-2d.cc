#include <iostream>
#include "sdl.hh"
#include "mouse-2d.hh"
#include "application-2d.hh"


namespace opl
{

	Mouse2D* Mouse2D::instance_ = nullptr;

	Mouse2D*
	Mouse2D::instance ()
	{
		if (!instance_)
			instance_ = new Mouse2D;
		return instance_;
	}

	Mouse2D::Mouse2D ()
		:   next_down_ (), next_up_ (), bts_down_ (),
			bts_pressed_ (), bts_released_ ()
	{
		Application2D::instance ()->subscribe (this);
	}



	bool
	Mouse2D::is_down (int code) const
	{
		return bts_down_.find (code) != bts_down_.end ();
	}


   	bool
   	Mouse2D::is_pressed (int code) const
	{
		return bts_pressed_.find (code) != bts_pressed_.end ();
	}

	bool
	Mouse2D::is_released (int code) const
	{
		return bts_released_.find (code) != bts_released_.end ();
	}

	r_type
	Mouse2D::x_get () const
	{
		return x_;
	}

	r_type
	Mouse2D::y_get () const
	{
		return y_;
	}



	Vector2D
	Mouse2D::position () const
	{
		return Vector2D (x_, y_);
	}

	void
	Mouse2D::notify_mouse_move (r_type x, r_type y)
	{
		x_ = x;
		y_ = y;
	}

	void
	Mouse2D::notify_mouse_down (int code)
	{
		next_down_.insert (code);
	}

	void
	Mouse2D::notify_mouse_up (int code)
	{
		next_up_.insert (code);
	}

	void
	Mouse2D::notify_update ()
	{

		bts_pressed_.clear ();
		bts_released_.clear ();

		for (auto it = next_down_.begin (); it != next_down_.end (); ++it)
		{
			int code = *it;
			bts_pressed_.insert (code);
			bts_down_.insert (code);
		}

		for (auto it = next_up_.begin (); it != next_up_.end (); ++it)
		{
			int code = *it;
			bts_released_.insert (code);
			bts_down_.erase (code);
		}

		next_down_.clear ();
		next_up_.clear ();
	}



	const int Mouse2D::LEFT (SDL_BUTTON_LEFT);
	const int Mouse2D::MIDDLE (SDL_BUTTON_MIDDLE);
	const int Mouse2D::RIGHT (SDL_BUTTON_RIGHT);
	const int Mouse2D::X1 (SDL_BUTTON_X1);
	const int Mouse2D::X2 (SDL_BUTTON_X2);

}