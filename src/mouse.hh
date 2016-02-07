/** @File Mouse class definition
 */

#ifndef MOUSE_HH_
# define MOUSE_HH_

# include <set>
# include <string>
# include "vector2.hh"

namespace opl
{

	/// Mouse state representation
	class Mouse
	{

	public:

		static Mouse*
		instance ();


		bool
		is_down (int code) const;

		bool
		just_down (int code) const;

		bool
		just_up (int code) const;

		r_type
		x_get () const;

		r_type
		y_get () const;

		Vector2
		position () const;

		void
		next_frame ();

		void
		button_down (int code);

		void
		button_up (int code);

		void
		mouse_move (r_type x, r_type y);

		static const int LEFT;
		static const int MIDDLE;
		static const int RIGHT;
		static const int X1;
		static const int X2;



	private:
		r_type x_;
		r_type y_;
		std::set<int> bts_down_;
		std::set<int> frame_bts_down_;
		std::set<int> frame_bts_up_;

		Mouse () = default;
		Mouse (const Mouse&) = delete;
		static Mouse* instance_;


};

}

#endif //!MOUSE_HH_