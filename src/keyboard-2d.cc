#include "sdl.hh"
#include "keyboard-2d.hh"
#include "application-2d.hh"


namespace opl
{


	Keyboard2D* Keyboard2D::instance_ = nullptr;

	Keyboard2D*
	Keyboard2D::instance ()
	{
		if(!instance_)
			instance_ = new Keyboard2D;
		return instance_;
	}

	Keyboard2D::Keyboard2D ()
	{
		Application2D::instance ()->subscribe (this);
	}

	std::string
	Keyboard2D::key_name (int code)
	{
		return SDL_GetKeyName (code);
	}


	bool
	Keyboard2D::is_down (int code) const
	{
		return keys_down_.find (code) != keys_down_.end ();
	}

	void
	Keyboard2D::notify_key_down (int code)
	{
		keys_down_.insert (code);
	}

	void
	Keyboard2D::notify_key_up (int code)
	{
		keys_down_.erase (code);
	}


	const int
	Keyboard2D::BACKSPACE (SDLK_BACKSPACE);

	const int
	Keyboard2D::TAB (SDLK_TAB);

	const int
	Keyboard2D::SPACE (SDLK_SPACE);

	const int
	Keyboard2D::LEFT (SDLK_LEFT);

	const int
	Keyboard2D::UP (SDLK_UP);

	const int
	Keyboard2D::RIGHT (SDLK_RIGHT);

	const int
	Keyboard2D::DOWN (SDLK_DOWN);

	const int
	Keyboard2D::A0 (SDLK_0);

	const int
	Keyboard2D::A1 (SDLK_1);

	const int
	Keyboard2D::A2 (SDLK_2);

	const int
	Keyboard2D::A3 (SDLK_3);

	const int
	Keyboard2D::A4 (SDLK_4);

	const int
	Keyboard2D::A5 (SDLK_5);

	const int
	Keyboard2D::A6 (SDLK_6);

	const int
	Keyboard2D::A7 (SDLK_7);

	const int
	Keyboard2D::A8 (SDLK_8);

	const int
	Keyboard2D::A9 (SDLK_9);

	const int
	Keyboard2D::A (SDLK_a);

	const int
	Keyboard2D::B (SDLK_b);

	const int
	Keyboard2D::C (SDLK_c);

	const int
	Keyboard2D::D (SDLK_d);

	const int
	Keyboard2D::E (SDLK_e);

	const int
	Keyboard2D::F (SDLK_f);

	const int
	Keyboard2D::G (SDLK_g);

	const int
	Keyboard2D::H (SDLK_h);

	const int
	Keyboard2D::I (SDLK_i);

	const int
	Keyboard2D::J (SDLK_j);

	const int
	Keyboard2D::K (SDLK_k);

	const int
	Keyboard2D::L (SDLK_l);

	const int
	Keyboard2D::M (SDLK_m);

	const int
	Keyboard2D::N (SDLK_n);

	const int
	Keyboard2D::O (SDLK_o);

	const int
	Keyboard2D::P (SDLK_p);

	const int
	Keyboard2D::Q (SDLK_q);

	const int
	Keyboard2D::R (SDLK_r);

	const int
	Keyboard2D::S (SDLK_s);

	const int
	Keyboard2D::T (SDLK_t);

	const int
	Keyboard2D::U (SDLK_u);

	const int
	Keyboard2D::V (SDLK_v);

	const int
	Keyboard2D::W (SDLK_w);

	const int
	Keyboard2D::X (SDLK_x);

	const int
	Keyboard2D::Y (SDLK_y);

	const int
	Keyboard2D::Z (SDLK_z);

	const int
	Keyboard2D::N0 (SDLK_KP_0);

	const int
	Keyboard2D::N1 (SDLK_KP_1);

	const int
	Keyboard2D::N2 (SDLK_KP_2);

	const int
	Keyboard2D::N3 (SDLK_KP_3);

	const int
	Keyboard2D::N4 (SDLK_KP_4);

	const int
	Keyboard2D::N5 (SDLK_KP_5);

	const int
	Keyboard2D::N6 (SDLK_KP_6);

	const int
	Keyboard2D::N7 (SDLK_KP_7);

	const int
	Keyboard2D::N8 (SDLK_KP_8);

	const int
	Keyboard2D::N9 (SDLK_KP_9);

}