/** @File Keyboard class definition
 */

#ifndef KEYBOARD_HH_
# define KEYBOARD_HH_

# include <set>
# include <string>

namespace opl
{

	/// Keyboard state representation
	class Keyboard
	{

	public:

		static Keyboard*
		instance ();

		static std::string
		key_name (int code);


		bool
		is_down (int code) const;

		bool
		just_down (int code) const;

		bool
		just_up (int code) const;


		void
		next_frame ();

		void
		key_down (int code);

		void
		key_up (int code);

		static const int BACKSPACE;
		static const int TAB;
		static const int SPACE;
		static const int LEFT;
		static const int UP;
		static const int RIGHT;
		static const int DOWN;
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
		std::set<int> keys_down_;
		std::set<int> frame_keys_down_;
		std::set<int> frame_keys_up_;

		Keyboard () = default;
		Keyboard (const Keyboard&) = delete;
		static Keyboard* instance_;

};

}

#endif //!KEYBOARD_HH_