/**
 * @file Application2D class deifinition
 */

#ifndef APPLICATION_2D_HH_
# define APPLICATION_2D_HH_

# include "types.hh"
# include "sdl.hh"
# include "game-subject-2d.hh"

namespace opl
{

	/**
	 * Facade for creating and managing an SDL window
	 */
	class Application2D: public GameSubject2D
	{

	public:

		static Application2D*
		instance ();

		void
		init ();

		void
		quit ();

		r_type
		width_get () const;

		r_type
		height_get () const;

	private:

		static Application2D* instance_;

		SDL_Window* win_;
		SDL_Renderer* renderer_;

		r_type width_;
		r_type height_;
		bool quitted_;

		Application2D () = default;
		Application2D (const Application2D&) = delete;

		void
		loop_ ();

		void
		process_event_ (const SDL_Event& e);

		void
		process_window_event_ (const SDL_WindowEvent& e);

		void
		on_quit_ ();

	};

}

#endif //!APPLICATION_2D_HH_