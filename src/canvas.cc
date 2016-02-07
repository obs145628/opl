#include <cassert>
#include "canvas.hh"


namespace opl
{

	Canvas::Canvas (SDL_Renderer* renderer, r_type width, r_type height)
		: renderer_ (renderer), width_ (width), height_ (height),
		  sprites_ ()
	{

	}

	Canvas::~Canvas ()
	{
		for (auto it = sprites_.begin (); it != sprites_.end (); ++it)
			SDL_DestroyTexture (it->second);

		for (auto it = fonts_.begin (); it != fonts_.end (); ++it)
			TTF_CloseFont (it->second);
	}

	void
	Canvas::init ()
	{
		SDL_SetRenderDrawColor (renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
		on_init_();
	}

	void
	Canvas::clear ()
	{
		SDL_SetRenderDrawColor (renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear (renderer_);
	}

	void
	Canvas::render ()
	{
		SDL_RenderPresent (renderer_);
	}

	void
	Canvas::preload_sprite(const std::string& path)
	{
		texture_get_(path);
	}

	void
	Canvas::preload_sprites (const std::vector<std::string>& paths)
	{
		for (auto it = paths.begin (); it != paths.end (); ++it)
			texture_get_ (*it);
	}

	void
	Canvas::preload_font (const std::string& font, int size)
	{
		font_get_(font, size);
	}

	r_type
	Canvas::width_get () const
	{
		return width_;
	}

	r_type
	Canvas::hight_get () const
	{
		return height_;
	}

	void
	Canvas::resize (r_type width, r_type height)
	{
		width_ = width;
		height_ = height;
	}

	void
	Canvas::width_set (r_type width)
	{
		width_ = width;
	}

	void
	Canvas::height_set (r_type height)
	{
		height_ = height;
	}

	Color
	Canvas::draw_color_get ()
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		SDL_GetRenderDrawColor (renderer_, &r, &g, &b, &a);
		return Color (r, g, b, a);
	}

	void
	Canvas::draw_color_set(const Color& c)
	{
		SDL_SetRenderDrawColor(renderer_, c.red (), c.green (),
							   c.blue (), c.alpha ());
	}

	void
	Canvas::draw_point (r_type x, r_type y)
	{
		SDL_RenderDrawPoint (renderer_,
							 static_cast<int> (x), static_cast<int> (y));
	}

	void
	Canvas::draw_line (r_type x1, r_type y1, r_type x2, r_type y2)
	{
		SDL_RenderDrawLine (renderer_,
							static_cast<int> (x1), static_cast<int> (y1),
							static_cast<int> (x2), static_cast<int> (y2));
	}

	void
	Canvas::draw_rect (r_type x, r_type y, r_type w, r_type h)
	{
		SDL_Rect rect;
		rect.x = static_cast<int> (x);
		rect.y = static_cast<int> (y);
		rect.w = static_cast<int> (w);
		rect.h = static_cast<int> (h);
		SDL_RenderDrawRect (renderer_, &rect);
	}

	void
	Canvas::fill_rect (r_type x, r_type y, r_type w, r_type h)
	{
		SDL_Rect rect;
		rect.x = static_cast<int> (x);
		rect.y = static_cast<int> (y);
		rect.w = static_cast<int> (w);
		rect.h = static_cast<int> (h);
		SDL_RenderFillRect (renderer_, &rect);
	}

	void
	Canvas::draw_circle (r_type x, r_type y, r_type r)
	{
		draw_circle_(static_cast<int> (x), static_cast<int> (y),
					 static_cast<int> (r));
	}

	void
	Canvas::fill_circle (r_type x, r_type y, r_type r)
	{
		fill_circle_(static_cast<int> (x), static_cast<int> (y),
					 static_cast<int> (r));
	}

	void
	Canvas::draw_sprite (const std::string& path, r_type x, r_type y,
						 r_type w, r_type h, r_type angle, const Color& c)
	{
		SDL_Texture* texture = texture_get_ (path);
		SDL_Rect rect;
		rect.x = static_cast<int> (x);
		rect.y = static_cast<int> (y);
		rect.w = static_cast<int> (w);
		rect.h = static_cast<int> (h);

		SDL_SetTextureColorMod (texture, c.red (), c.green (), c.blue ());
		SDL_SetTextureAlphaMod (texture, c.alpha ());
		SDL_RenderCopyEx(renderer_, texture, NULL, &rect,
						 static_cast<double> (angle), NULL, SDL_FLIP_NONE);
	}

	void
	Canvas::draw_text (const std::string& text, r_type x, r_type y,
					   r_type angle, const std::string& font, const Color& c,
					   n_type size)
	{
		TTF_Font* ttf = font_get_ (font, static_cast<int> (size));
		SDL_Color color;
		color.a = c.alpha ();
		color.r = c.red ();
		color.g = c.green ();
		color.b = c.blue ();
		SDL_Surface* text_surface = TTF_RenderText_Solid(ttf, text.c_str (),
														  color);
		assert (text_surface);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_,
															text_surface);
		assert (texture);

		SDL_Rect rect;
		rect.x = static_cast<int> (x);
		rect.y = static_cast<int> (y);
		rect.w = text_surface->w;
		rect.h = text_surface->h;

		SDL_RenderCopyEx (renderer_, texture, NULL, &rect,
						  static_cast<double> (angle), NULL, SDL_FLIP_NONE);
		SDL_FreeSurface (text_surface);
		SDL_DestroyTexture (texture);
	}




	void
	Canvas::on_init_ ()
	{

	}


	void
	Canvas::draw_circle_ (int n_cx, int n_cy, int radius)
	{

		r_type error = static_cast<r_type> (-radius);
		r_type x = static_cast<r_type> (radius - 0.5);
		r_type y = 0.5;
		r_type cx = n_cx - 0.5;
		r_type cy = n_cy - 0.5;

		while (x >= y)
		{
			draw_point (cx + x, cy + y);
			draw_point (cx + y, cy + x);

			if (x != 0)
			{
				draw_point (cx - x, cy + y);
				draw_point (cx + y, cy - x);
			}

			if (y != 0)
			{
				draw_point (cx + x, cy - y);
				draw_point (cx - y, cy + x);
			}

			if (x != 0 && y != 0)
			{
				draw_point (cx - x, cy - y);
				draw_point (cx - y, cy - x);
			}

			error += y;
			++y;
			error += y;

			if (error >= 0)
			{
				--x;
				error -= x;
				error -= x;
			}

		}
	}

	void
	Canvas::fill_circle_ (int xc, int yc, int radius)
	{
		for (int y = -radius; y <= radius; ++y)
			for (int x = -radius; x <= radius; ++x)
				if(x * x + y * y <= radius * radius)
					SDL_RenderDrawPoint (renderer_, xc + x, yc + y);
	}

	SDL_Texture*
	Canvas::texture_get_ (const std::string& path)
	{
		auto it = sprites_.find (path);
		if(it == sprites_.end ())
		{
			SDL_Texture* texture = load_texture_ (path);
			sprites_[path] = texture;
			return texture;
		}
		return it->second;
	}


	SDL_Texture*
	Canvas::load_texture_ (const std::string& path)
	{
		SDL_Texture* new_texture = NULL;
		SDL_Surface* loaded_surface = IMG_Load (path.c_str());
		assert (loaded_surface);

		SDL_SetColorKey (loaded_surface, SDL_TRUE,
						 SDL_MapRGB (loaded_surface->format, 0, 0xFF, 0xFF));

		new_texture = SDL_CreateTextureFromSurface (renderer_,
													loaded_surface);
		assert (new_texture);

		SDL_FreeSurface (loaded_surface );
		return new_texture;
	}

	TTF_Font*
	Canvas::font_get_ (const std::string& font, int size)
	{
		std::string id = "///_" + std::to_string (size) + "_" + font;
		auto it = fonts_.find (id);
		if (it == fonts_.end ())
		{
			TTF_Font* ttf = TTF_OpenFont(("misc/fonts/" + font + ".ttf").c_str ()
										 , size);

			assert (ttf);
			fonts_[id] = ttf;
			return ttf;
		}
		return it->second;

	}



}