/** @File Mouse2D class definition
 */

#ifndef MOUSE2D_HH_
# define MOUSE2D_HH_

# include <set>
# include "vector-2d.hh"
# include "game-observer-2d.hh"

namespace opl
{

	/// Mouse state representation from 2D programming
	class Mouse2D: public GameObserver2D
	{

	public:

		static Mouse2D*
		instance ();


		bool
		is_down (int code) const;

		///Returns if button has been pressed on the current frame
		bool
		is_pressed (int code) const;

		///Returns if button has been released on the current frame
		bool
		is_released (int code) const;

		r_type
		x_get () const;

		r_type
		y_get () const;

		Vector2D
		position () const;


		virtual void
		notify_mouse_move (r_type x, r_type y) override;

		virtual void
		notify_mouse_down (int code) override;

		virtual void
		notify_mouse_up (int code) override;

		virtual void
		notify_update () override;

		static const int LEFT;
		static const int MIDDLE;
		static const int RIGHT;
		static const int X1;
		static const int X2;



	private:
		r_type x_;
		r_type y_;
		std::set<int> next_down_;
		std::set<int> next_up_;
		std::set<int> bts_down_;
		std::set<int> bts_pressed_;
		std::set<int> bts_released_;

		Mouse2D ();
		Mouse2D (const Mouse2D&) = delete;
		static Mouse2D* instance_;


	};

}

#endif //!MOUSE_HH_