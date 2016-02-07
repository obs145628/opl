#include <algorithm>
#include "sdl.hh"
#include "keyboard.hh"


namespace opl
{


	Keyboard* Keyboard::instance_ = nullptr;

	Keyboard*
	Keyboard::instance ()
	{
		if(!instance_)
			instance_ = new Keyboard;
		return instance_;
	}

	std::string
	Keyboard::key_name (int code)
	{
		return SDL_GetKeyName (code);
	}


	bool
	Keyboard::is_down (int code) const
	{
		return keys_down_.find (code) != keys_down_.end ();
	}

	bool
	Keyboard::just_down (int code) const
	{
		return frame_keys_down_.find (code) != frame_keys_down_.end ();
	}

	bool
	Keyboard::just_up (int code) const
	{
		return frame_keys_up_.find (code) != frame_keys_up_.end ();
	}


	void
	Keyboard::next_frame ()
	{
		frame_keys_down_.clear ();
		frame_keys_up_.clear ();
	}

	void
	Keyboard::key_down (int code)
	{
		frame_keys_down_.insert (code);
		keys_down_.insert (code);
	}

	void
	Keyboard::key_up (int code)
	{
		frame_keys_up_.insert (code);
		keys_down_.erase (code);
	}


	const int
	Keyboard::BACKSPACE (SDLK_BACKSPACE);

	const int
	Keyboard::TAB (SDLK_TAB);

	const int
	Keyboard::SPACE (SDLK_SPACE);

	const int
	Keyboard::LEFT (SDLK_LEFT);

	const int
	Keyboard::UP (SDLK_UP);

	const int
	Keyboard::RIGHT (SDLK_RIGHT);

	const int
	Keyboard::DOWN (SDLK_DOWN);

	const int
	Keyboard::A0 (SDLK_0);

	const int
	Keyboard::A1 (SDLK_1);

	const int
	Keyboard::A2 (SDLK_2);

	const int
	Keyboard::A3 (SDLK_3);

	const int
	Keyboard::A4 (SDLK_4);

	const int
	Keyboard::A5 (SDLK_5);

	const int
	Keyboard::A6 (SDLK_6);

	const int
	Keyboard::A7 (SDLK_7);

	const int
	Keyboard::A8 (SDLK_8);

	const int
	Keyboard::A9 (SDLK_9);

	const int
	Keyboard::A (SDLK_a);

	const int
	Keyboard::B (SDLK_b);

	const int
	Keyboard::C (SDLK_c);

	const int
	Keyboard::D (SDLK_d);

	const int
	Keyboard::E (SDLK_e);

	const int
	Keyboard::F (SDLK_f);

	const int
	Keyboard::G (SDLK_g);

	const int
	Keyboard::H (SDLK_h);

	const int
	Keyboard::I (SDLK_i);

	const int
	Keyboard::J (SDLK_j);

	const int
	Keyboard::K (SDLK_k);

	const int
	Keyboard::L (SDLK_l);

	const int
	Keyboard::M (SDLK_m);

	const int
	Keyboard::N (SDLK_n);

	const int
	Keyboard::O (SDLK_o);

	const int
	Keyboard::P (SDLK_p);

	const int
	Keyboard::Q (SDLK_q);

	const int
	Keyboard::R (SDLK_r);

	const int
	Keyboard::S (SDLK_s);

	const int
	Keyboard::T (SDLK_t);

	const int
	Keyboard::U (SDLK_u);

	const int
	Keyboard::V (SDLK_v);

	const int
	Keyboard::W (SDLK_w);

	const int
	Keyboard::X (SDLK_x);

	const int
	Keyboard::Y (SDLK_y);

	const int
	Keyboard::Z (SDLK_z);

	const int
	Keyboard::N0 (SDLK_KP_0);

	const int
	Keyboard::N1 (SDLK_KP_1);

	const int
	Keyboard::N2 (SDLK_KP_2);

	const int
	Keyboard::N3 (SDLK_KP_3);

	const int
	Keyboard::N4 (SDLK_KP_4);

	const int
	Keyboard::N5 (SDLK_KP_5);

	const int
	Keyboard::N6 (SDLK_KP_6);

	const int
	Keyboard::N7 (SDLK_KP_7);

	const int
	Keyboard::N8 (SDLK_KP_8);

	const int
	Keyboard::N9 (SDLK_KP_9);

}