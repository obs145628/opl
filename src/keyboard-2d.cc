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
		: next_down_ (), next_up_ (), keys_down_ (),
		  keys_pressed_ (), keys_released_ (), chars_map_ ()
	{
		Application2D::instance ()->subscribe (this);

		chars_map_[A] = 'a';
		chars_map_[B] = 'b';
		chars_map_[C] = 'c';
		chars_map_[D] = 'd';
		chars_map_[E] = 'e';
		chars_map_[F] = 'f';
		chars_map_[G] = 'g';
		chars_map_[H] = 'h';
		chars_map_[I] = 'i';
		chars_map_[J] = 'j';
		chars_map_[K] = 'k';
		chars_map_[L] = 'l';
		chars_map_[M] = 'm';
		chars_map_[N] = 'n';
		chars_map_[O] = 'o';
		chars_map_[P] = 'p';
		chars_map_[Q] = 'q';
		chars_map_[R] = 'r';
		chars_map_[S] = 's';
		chars_map_[T] = 't';
		chars_map_[U] = 'u';
		chars_map_[V] = 'v';
		chars_map_[W] = 'w';
		chars_map_[X] = 'x';
		chars_map_[Y] = 'y';
		chars_map_[Z] = 'z';
		chars_map_[A0] = '0';
		chars_map_[A1] = '1';
		chars_map_[A2] = '2';
		chars_map_[A3] = '3';
		chars_map_[A4] = '4';
		chars_map_[A5] = '5';
		chars_map_[A6] = '6';
		chars_map_[A7] = '7';
		chars_map_[A8] = '8';
		chars_map_[A9] = '9';
		chars_map_[N0] = '0';
		chars_map_[N1] = '1';
		chars_map_[N2] = '2';
		chars_map_[N3] = '3';
		chars_map_[N4] = '4';
		chars_map_[N5] = '5';
		chars_map_[N6] = '6';
		chars_map_[N7] = '7';
		chars_map_[N8] = '8';
		chars_map_[N9] = '9';
		chars_map_[SPACE] = ' ';
		chars_map_[MINUS] = '-';
		chars_map_[SLASH] = '/';
		chars_map_[BACKSLASH] = '\\';

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

	bool
	Keyboard2D::is_pressed (int code) const
	{
		return keys_pressed_.find (code) != keys_pressed_.end ();
	}

	bool
	Keyboard2D::is_released (int code) const
	{
		return keys_released_.find (code) != keys_released_.end ();
	}

	std::vector<int>
	Keyboard2D::down_keys () const
	{
		return std::vector<int> (keys_down_.begin (),
								 keys_down_.end ());
	}

	std::vector<int>
	Keyboard2D::pressed_keys () const
	{
		return std::vector<int> (keys_pressed_.begin (),
								 keys_pressed_.end ());
	}

	std::vector<int>
	Keyboard2D::released_keys () const
	{
		return std::vector<int> (keys_released_.begin (),
								 keys_released_.end ());
	}

	char
	Keyboard2D::char_get (int code) const
	{
		auto it = chars_map_.find (code);
		if (it == chars_map_.end ())
			return 0;
		else
			return it->second;
	}

	void
	Keyboard2D::notify_key_down (int code)
	{
		next_down_.insert (code);
	}

	void
	Keyboard2D::notify_key_up (int code)
	{
		next_up_.insert (code);
	}

	void
	Keyboard2D::notify_update ()
	{
		keys_pressed_.clear ();
		keys_released_.clear ();

		for (auto it = next_down_.begin (); it != next_down_.end (); ++it)
		{
			int code = *it;
			keys_pressed_.insert (code);
			keys_down_.insert (code);
		}

		for (auto it = next_up_.begin (); it != next_up_.end (); ++it)
		{
			int code = *it;
			keys_released_.insert (code);
			keys_down_.erase (code);
		}

		next_down_.clear ();
		next_up_.clear ();
	}


	const int
	Keyboard2D::BACKSPACE (SDLK_BACKSPACE);

	const int
	Keyboard2D::DELETE (SDLK_DELETE);

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
	Keyboard2D::BACKSLASH (SDLK_BACKSLASH);

	const int
	Keyboard2D::COMMA (SDLK_COMMA);

	const int
	Keyboard2D::EQUALS (SDLK_EQUALS);

	const int
	Keyboard2D::ESCAPE (SDLK_ESCAPE);

	const int
	Keyboard2D::F1 (SDLK_F1);

	const int
	Keyboard2D::F2 (SDLK_F2);

	const int
	Keyboard2D::F3 (SDLK_F3);

	const int
	Keyboard2D::F4 (SDLK_F4);

	const int
	Keyboard2D::F5 (SDLK_F5);

	const int
	Keyboard2D::F6 (SDLK_F6);

	const int
	Keyboard2D::F7 (SDLK_F7);

	const int
	Keyboard2D::F8 (SDLK_F8);

	const int
	Keyboard2D::F9 (SDLK_F9);

	const int
	Keyboard2D::F10 (SDLK_F10);

	const int
	Keyboard2D::F11 (SDLK_F11);

	const int
	Keyboard2D::F12 (SDLK_F12);

	const int
	Keyboard2D::F13 (SDLK_F13);

	const int
	Keyboard2D::F14 (SDLK_F14);

	const int
	Keyboard2D::F15 (SDLK_F15);

	const int
	Keyboard2D::F16 (SDLK_F16);

	const int
	Keyboard2D::F17 (SDLK_F17);

	const int
	Keyboard2D::F18 (SDLK_F18);

	const int
	Keyboard2D::F19 (SDLK_F19);

	const int
	Keyboard2D::F20 (SDLK_F20);

	const int
	Keyboard2D::F21 (SDLK_F21);

	const int
	Keyboard2D::F22 (SDLK_F22);

	const int
	Keyboard2D::F23 (SDLK_F23);

	const int
	Keyboard2D::F24 (SDLK_F24);

	const int
	Keyboard2D::BACKQUOTE (SDLK_BACKQUOTE);

	const int
	Keyboard2D::HELP (SDLK_HELP);

	const int
	Keyboard2D::HOME (SDLK_HOME);

	const int
	Keyboard2D::INSERT (SDLK_INSERT);

	const int
	Keyboard2D::LALT (SDLK_LALT);

	const int
	Keyboard2D::LCTRL (SDLK_LCTRL);

	const int
	Keyboard2D::LBRACKET (SDLK_LEFTBRACKET);

	const int
	Keyboard2D::LGUI (SDLK_LGUI);

	const int
	Keyboard2D::LSHIFT (SDLK_LSHIFT);

	const int
	Keyboard2D::MENU (SDLK_MENU);

	const int
	Keyboard2D::MINUS (SDLK_MINUS);

	const int
	Keyboard2D::PAGEDOWN (SDLK_PAGEDOWN);

	const int
	Keyboard2D::PAGEUP (SDLK_PAGEUP);

	const int
	Keyboard2D::PAUSE (SDLK_PAUSE);

	const int
	Keyboard2D::PERIOD (SDLK_PERIOD);

	const int
	Keyboard2D::PRINTSCREEN (SDLK_PRINTSCREEN);

	const int
	Keyboard2D::RALT (SDLK_RALT);

	const int
	Keyboard2D::RCTRL (SDLK_RCTRL);

	const int
	Keyboard2D::RETURN (SDLK_RETURN);

	const int
	Keyboard2D::RETURN2 (SDLK_RETURN2);

	const int
	Keyboard2D::RGUI (SDLK_RGUI);

	const int
	Keyboard2D::RBRACKET (SDLK_RIGHTBRACKET);

	const int
	Keyboard2D::RSHIFT (SDLK_RSHIFT);

	const int
	Keyboard2D::SELECT (SDLK_SELECT);

	const int
	Keyboard2D::SEMICOLON (SDLK_SEMICOLON);

	const int
	Keyboard2D::SLASH (SDLK_SLASH);




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