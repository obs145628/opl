/** @File Keyboard2D class definition
 */

#ifndef KEYBOARD_2D_HH_
# define KEYBOARD_2D_HH_

# include <set>
# include <string>
# include <vector>
# include <map>
# include "game-observer-2d.hh"

namespace opl
{

	/// Keyboard state representation for 2D programming
	class Keyboard2D : public GameObserver2D
	{

	public:

		static Keyboard2D*
		instance ();

		static std::string
		key_name (int code);

	    bool
		is_down (int code) const;

		///Returns if key has been pressed on the current frame
		bool
		is_pressed (int code) const;

		///Returns if key has been released on the current frame
		bool
		is_released (int code) const;

		std::vector<int>
		down_keys () const;

		std::vector<int>
		pressed_keys () const;

		std::vector<int>
		released_keys () const;

		char
		char_get (int code) const;

		virtual void
		notify_key_down (int code) override;

		virtual void
		notify_key_up (int code) override;

		virtual void
		notify_update () override;

		static const int BACKSPACE;
		static const int DELETE;
		static const int TAB;
		static const int SPACE;
		static const int LEFT;
		static const int UP;
		static const int RIGHT;
		static const int DOWN;
		static const int BACKSLASH;
		static const int COMMA;
		static const int EQUALS;
		static const int ESCAPE;
		static const int F1;
		static const int F2;
		static const int F3;
		static const int F4;
		static const int F5;
		static const int F6;
		static const int F7;
		static const int F8;
		static const int F9;
		static const int F10;
		static const int F11;
		static const int F12;
		static const int F13;
		static const int F14;
		static const int F15;
		static const int F16;
		static const int F17;
		static const int F18;
		static const int F19;
		static const int F20;
		static const int F21;
		static const int F22;
		static const int F23;
		static const int F24;
		static const int BACKQUOTE;
		static const int HELP;
		static const int HOME;
		static const int INSERT;
		static const int LALT;
		static const int LCTRL;
		static const int LBRACKET;
		static const int LGUI;
		static const int LSHIFT;
		static const int MENU;
		static const int MINUS;
		static const int PAGEDOWN;
		static const int PAGEUP;
		static const int PAUSE;
		static const int PERIOD;
		static const int PRINTSCREEN;
		static const int RALT;
		static const int RCTRL;
		static const int RETURN;
		static const int RETURN2;
		static const int RGUI;
		static const int RBRACKET;
		static const int RSHIFT;
		static const int SELECT;
		static const int SEMICOLON;
		static const int SLASH;
		static const int A0;
		static const int A1;
		static const int A2;
		static const int A3;
		static const int A4;
		static const int A5;
		static const int A6;
		static const int A7;
		static const int A8;
		static const int A9;
		static const int A;
		static const int B;
		static const int C;
		static const int D;
		static const int E;
		static const int F;
		static const int G;
		static const int H;
		static const int I;
		static const int J;
		static const int K;
		static const int L;
		static const int M;
		static const int N;
		static const int O;
		static const int P;
		static const int Q;
		static const int R;
		static const int S;
		static const int T;
		static const int U;
		static const int V;
		static const int W;
		static const int X;
		static const int Y;
		static const int Z;
		static const int N0;
		static const int N1;
		static const int N2;
		static const int N3;
		static const int N4;
		static const int N5;
		static const int N6;
		static const int N7;
		static const int N8;
		static const int N9;



	private:
	    std::set<int> next_down_;
		std::set<int> next_up_;
		std::set<int> keys_down_;
		std::set<int> keys_pressed_;
		std::set<int> keys_released_;
		std::map<int, char> chars_map_;

		Keyboard2D ();
		Keyboard2D (const Keyboard2D&) = delete;
		static Keyboard2D* instance_;

};

}

#endif //!KEYBOARD_2D_HH_