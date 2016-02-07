/**
 * @file Application class deifinition
 */

#ifndef APPLICATION_HH_
# define APPLICATION_HH_

# include <cstddef>
# include "sdl.hh"
# include "keyboard.hh"
# include "canvas.hh"
# include "date.hh"
# include "mouse.hh"

namespace opl
{

	/**
	 * Facade for creating and managing an SDL window
	 */
	class Application
	{

	public:

		virtual
		~Application ();

		void
		init ();

		void
		quit ();

		int
		width_get () const;

		int
		height_get () const;

		r_type
		delta_time_get () const;

		Canvas*
		canvas_get ();

	protected:

		virtual void
		on_init_ ();

		virtual void
		on_update_ ();

		virtual void
		on_quit_ ();

		virtual void
		on_key_down_ (int code);

		virtual void
		on_key_up_ (int code);

		virtual void
		on_mouse_button_down_ (int code);

		virtual void
		on_mouse_button_up_ (int code);

		virtual void
		on_mouse_move_ (r_type x, r_type y);

		virtual void
		on_resize_ (int width, int height);





	private:
		SDL_Window* win_;
		SDL_Renderer* renderer_;
		Canvas* canvas_;
		Keyboard* keyboard_;
		Mouse* mouse_;

		int width_;
		int height_;
		bool quitted_;
		time_t last_frame_;
		r_type delta_time_;

		void
		loop_ ();

		void
		process_event_ (const SDL_Event& e);

		void
		process_window_event_ (const SDL_WindowEvent& e);

		void
		update_time_ ();

	};

}

#endif //!APPLICATION_HH_