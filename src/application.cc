#include <cassert>
#include <iostream>
#include "application.hh"


namespace opl
{


	void
	Application::init ()
	{
		assert (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) >=0);

		assert (SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "1"));

		int img_flags = IMG_INIT_PNG;
		assert (IMG_Init (img_flags) & img_flags);

		assert (TTF_Init () != -1);

		assert (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0);

		SDL_Rect bounds;
		SDL_GetDisplayBounds (0, &bounds);
		width_ = bounds.w;
		height_ = bounds.h;

		win_ = SDL_CreateWindow ("OPL", SDL_WINDOWPOS_UNDEFINED,
								 SDL_WINDOWPOS_UNDEFINED, width_, height_,
								 SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		assert (win_);


		renderer_ = SDL_CreateRenderer (win_, -1, SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
		assert (renderer_);

		canvas_ = new Canvas (renderer_,
							  static_cast<r_type> (width_),
							  static_cast<r_type> (height_));


		on_init_ ();
		last_frame_ = Date::timestamp_ms ();
		keyboard_ = Keyboard::instance ();
		mouse_ = Mouse::instance ();
		canvas_->init ();
	    loop_ ();
	}

	Application::~Application ()
	{
		SDL_DestroyRenderer (renderer_);
		SDL_DestroyWindow (win_);
		IMG_Quit ();
		TTF_Quit ();
		Mix_Quit ();
		SDL_Quit ();
	}

	void
	Application::quit ()
	{
		quitted_ = true;
	}

	int
	Application::width_get () const
	{
		return width_;
	}

	int
	Application::height_get () const
	{
		return height_;
	}

	r_type
	Application::delta_time_get () const
	{
		return delta_time_;
	}

	Canvas*
	Application::canvas_get ()
	{
		return canvas_;
	}


	void
	Application::on_init_ ()
	{

	}

	void
	Application::on_update_ ()
	{

	}

	void
	Application::on_quit_ ()
	{

	}

	void
	Application::on_key_down_ (int code)
	{
		keyboard_->key_up (code);
	}

	void
	Application::on_key_up_ (int code)
	{
		keyboard_->key_down (code);
	}

	void
	Application::on_mouse_button_down_ (int code)
	{
		mouse_->button_down (code);
	}

	void
	Application::on_mouse_button_up_ (int code)
	{
		mouse_->button_up (code);
	}

	void
	Application::on_mouse_move_ (r_type x, r_type y)
	{
		mouse_->mouse_move (x, y);
	}

	void
	Application::on_resize_ (int width, int height)
	{
		width_ = width;
		height_ = height;
		canvas_->resize(static_cast<r_type> (width),
						static_cast<r_type> (height));
	}





	void
	Application::loop_ ()
	{
		SDL_Event e;

		while (!quitted_)
		{

			keyboard_->next_frame ();
			mouse_->next_frame ();

			while (SDL_PollEvent (&e) != 0 )
				process_event_(e);

			canvas_->clear ();
			update_time_();

			on_update_ ();
			canvas_->render ();
		}

		on_quit_ ();
	}

	void
	Application::process_event_ (const SDL_Event& e)
	{
		if (e.type == SDL_QUIT )
			quit ();

		else if(e.type == SDL_KEYDOWN)
			on_key_down_ (e.key.keysym.sym);
		else if(e.type == SDL_KEYUP)
			on_key_up_ (e.key.keysym.sym);

		else if (e.type == SDL_MOUSEMOTION)
		{
			on_mouse_move_(static_cast<r_type> (e.motion.x),
						   static_cast<r_type> (e.motion.y));
		}

		else if (e.type == SDL_MOUSEBUTTONDOWN)
			on_mouse_button_down_ (e.button.button);
		else if (e.type == SDL_MOUSEBUTTONUP)
			on_mouse_button_up_ (e.button.button);

		else if (e.type == SDL_WINDOWEVENT)
			process_window_event_ (e.window);
	}

	void
	Application::process_window_event_ (const SDL_WindowEvent& e)
	{
		if(e.type == SDL_WINDOWEVENT_RESIZED)
		{
			on_resize_ (e.data1, e.data2);
		}
	}

	void
	Application::update_time_ ()
	{
		time_t now = Date::timestamp_ms ();
		time_t dt_ms = now - last_frame_;
		delta_time_ = static_cast<r_type> (dt_ms)
			/ static_cast<r_type> (1000);
		last_frame_ = now;
	}



}