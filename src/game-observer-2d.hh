/** @file GameObserver2D class definition
 */

#ifndef GAME_OBSERVER_2D_HH_
# define GAME_OBSERVER_2D_HH_

# include "types.hh"

namespace opl
{

	///observer of 2D game-like events (Observer Pattern)
	class GameObserver2D
	{

	public:

		virtual ~GameObserver2D () = default;

		virtual void
		notify_init ();

		virtual void
		notify_update ();

		virtual void
		notify_destroy ();

		virtual void
		notify_resize (r_type width, r_type height);

		virtual void
		notify_key_down (int code);

		virtual void
		notify_key_up (int code);

		virtual void
		notify_mouse_move (r_type x, r_type y);

		virtual void
		notify_mouse_down (int code);

		virtual void
		notify_mouse_up (int code);


	};

}


# endif //!GAME_OBSERVER_2D_HH_