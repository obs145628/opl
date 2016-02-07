#include <algorithm>
#include "sdl.hh"
#include "mouse.hh"


namespace opl
{

	Mouse* Mouse::instance_ = nullptr;

	Mouse*
	Mouse::instance ()
	{
		if (!instance_)
			instance_ = new Mouse;
		return instance_;
	}

	bool
	Mouse::is_down (int code) const
	{
		return bts_down_.find (code) != bts_down_.end ();
	}

	bool
	Mouse::just_down (int code) const
	{
		return frame_bts_down_.find (code) != frame_bts_down_.end ();
	}

	bool
	Mouse::just_up (int code) const
	{
		return frame_bts_up_.find (code) != frame_bts_up_.end ();
	}

	r_type
	Mouse::x_get () const
	{
		return x_;
	}

	r_type
	Mouse::y_get () const
	{
		return y_;
	}

	Vector2
	Mouse::position () const
	{
		return Vector2 (x_, y_);
	}


	void
	Mouse::next_frame ()
	{
		frame_bts_down_.clear ();
		frame_bts_up_.clear ();
	}

	void
	Mouse::button_down (int code)
	{
		frame_bts_down_.insert (code);
		bts_down_.insert (code);
	}

	void
	Mouse::button_up (int code)
	{
		frame_bts_up_.insert (code);
		bts_down_.erase (code);
	}

	void
	Mouse::mouse_move (r_type x, r_type y)
	{
		x_ = x;
		y_ = y;
	}

	const int Mouse::LEFT (SDL_BUTTON_LEFT);
	const int Mouse::MIDDLE (SDL_BUTTON_MIDDLE);
	const int Mouse::RIGHT (SDL_BUTTON_RIGHT);
	const int Mouse::X1 (SDL_BUTTON_X1);
	const int Mouse::X2 (SDL_BUTTON_X2);

}