#include <cassert>
#include <iostream>
#include "application-2d.hh"
#include "canvas-2d.hh"


namespace opl
{

	Application2D* Application2D::instance_ = nullptr;

	Application2D*
	Application2D::instance ()
	{
		if (!instance_)
			instance_ = new Application2D;
		return instance_;
	}


	void
	Application2D::init ()
	{
		assert (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) >=0);

		assert (SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "1"));

		int img_flags = IMG_INIT_PNG;
		assert (IMG_Init (img_flags) & img_flags);

		assert (TTF_Init () != -1);

		assert (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0);

		SDL_Rect bounds;
		SDL_GetDisplayBounds (0, &bounds);
		width_ = static_cast<r_type> (bounds.w);
		height_ = static_cast<r_type> (bounds.h);

		win_ = SDL_CreateWindow ("OPL", SDL_WINDOWPOS_UNDEFINED,
								 SDL_WINDOWPOS_UNDEFINED, width_, height_,
								 SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		assert (win_);


		renderer_ = SDL_CreateRenderer (win_, -1, SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
		assert (renderer_);



		Canvas2D::instance ()->init (renderer_);
		publish_init_ ();
	    loop_ ();
	}

	void
	Application2D::quit ()
	{
		quitted_ = true;
	}

	r_type
	Application2D::width_get () const
	{
		return width_;
	}

	r_type
	Application2D::height_get () const
	{
		return height_;
	}

	void
	Application2D::on_quit_ ()
	{
	    publish_destroy_ ();
		SDL_DestroyRenderer (renderer_);
		SDL_DestroyWindow (win_);
		IMG_Quit ();
		TTF_Quit ();
		Mix_Quit ();
		SDL_Quit ();
	}



	void
	Application2D::loop_ ()
	{
		SDL_Event e;

		while (!quitted_)
		{

			while (SDL_PollEvent (&e) != 0 )
				process_event_(e);

		    publish_update_ ();
		}

		on_quit_ ();
	}

	void
	Application2D::process_event_ (const SDL_Event& e)
	{
		if (e.type == SDL_QUIT )
			quit ();

		else if(e.type == SDL_KEYDOWN)
			publish_key_down_ (e.key.keysym.sym);
		else if(e.type == SDL_KEYUP)
			publish_key_up_ (e.key.keysym.sym);

		else if (e.type == SDL_MOUSEMOTION)
		{
			publish_mouse_move_ (static_cast<r_type> (e.motion.x),
								 static_cast<r_type> (e.motion.y));
		}

		else if (e.type == SDL_MOUSEBUTTONDOWN)
			publish_mouse_down_ (e.button.button);
		else if (e.type == SDL_MOUSEBUTTONUP)
		    publish_mouse_up_ (e.button.button);

		else if (e.type == SDL_WINDOWEVENT)
			process_window_event_ (e.window);
	}

	void
	Application2D::process_window_event_ (const SDL_WindowEvent& e)
	{
		if(e.type == SDL_WINDOWEVENT_RESIZED)
		{
			width_ = static_cast<r_type> (e.data1);
			height_ = static_cast<r_type> (e.data2);
		    publish_resize_ (width_, height_);
		}
	}



}