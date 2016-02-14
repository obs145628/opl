/** @file GameSubject2D class definition
 */

#ifndef GAME_SUBJECT_2D_HH_
# define GAME_SUBJECT_2D_HH_

# include <vector>
# include "game-observer-2d.hh"

namespace opl
{

	///subject of 2D game-like events (Observer pattern)
	class GameSubject2D
	{

	public:

		void
		subscribe (GameObserver2D* observer);

		void
		unsusribe (GameObserver2D* observer);

	protected:

		void
		publish_init_ ();

		void
		publish_update_ ();

		void
		publish_destroy_ ();

		void
		publish_resize_ (r_type width, r_type height);

		void
		publish_key_down_ (int code);

		void
		publish_key_up_ (int code);

		void
		publish_mouse_move_ (r_type x, r_type y);

		void
		publish_mouse_down_ (int code);

		void
		publish_mouse_up_ (int code);


	private:
		std::vector<GameObserver2D*> observers_;




	};

}

# endif //ÂÂ!GAME_SUECT_2D_HH_