#include <cassert>
#include "canvas-2d.hh"
#include "math.hh"

namespace opl
{

	Canvas2D* Canvas2D::instance_ = nullptr;

	Canvas2D*
	Canvas2D::instance ()
	{
		if (!instance_)
			instance_ = new Canvas2D;
		return instance_;
	}

	void
	Canvas2D::init (SDL_Renderer* renderer)
	{
		renderer_ = renderer;
		SDL_SetRenderDrawColor (renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	void
	Canvas2D::clear ()
	{
		SDL_SetRenderDrawColor (renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear (renderer_);
	}

	void
	Canvas2D::render ()
	{
		SDL_RenderPresent (renderer_);
	}

	void
	Canvas2D::preload_sprite(const std::string& path)
	{
		texture_get_(path);
	}

	void
	Canvas2D::preload_sprites (const std::vector<std::string>& paths)
	{
		for (auto it = paths.begin (); it != paths.end (); ++it)
			texture_get_ (*it);
	}

	void
	Canvas2D::preload_font (const std::string& font, int size)
	{
		font_get_(font, size);
	}

	Color
	Canvas2D::draw_color_get ()
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		SDL_GetRenderDrawColor (renderer_, &r, &g, &b, &a);
		return Color (r, g, b, a);
	}

	void
	Canvas2D::draw_color_set(const Color& c)
	{
		SDL_SetRenderDrawColor(renderer_, c.red (), c.green (),
							   c.blue (), c.alpha ());
	}

	void
	Canvas2D::draw_point (r_type x, r_type y)
	{
		SDL_RenderDrawPoint (renderer_,
							 static_cast<int> (x), static_cast<int> (y));
	}

	void
	Canvas2D::draw_line (r_type x1, r_type y1, r_type x2, r_type y2)
	{
		SDL_RenderDrawLine (renderer_,
							static_cast<int> (x1), static_cast<int> (y1),
							static_cast<int> (x2), static_cast<int> (y2));
	}

	void
	Canvas2D::draw_rect (r_type x, r_type y, r_type w, r_type h)
	{
		SDL_Rect rect;
		rect.x = static_cast<int> (x);
		rect.y = static_cast<int> (y);
		rect.w = static_cast<int> (w);
		rect.h = static_cast<int> (h);
		SDL_RenderDrawRect (renderer_, &rect);
	}

	void
	Canvas2D::fill_rect (r_type x, r_type y, r_type w, r_type h)
	{
		SDL_Rect rect;
		rect.x = static_cast<int> (x);
		rect.y = static_cast<int> (y);
		rect.w = static_cast<int> (w);
		rect.h = static_cast<int> (h);
		SDL_RenderFillRect (renderer_, &rect);
	}

	void
	Canvas2D::draw_circle (r_type x, r_type y, r_type r)
	{
		draw_circle_(static_cast<int> (x), static_cast<int> (y),
					 static_cast<int> (r));
	}

	void
	Canvas2D::fill_circle (r_type x, r_type y, r_type r)
	{
		fill_circle_(static_cast<int> (x), static_cast<int> (y),
					 static_cast<int> (r));
	}

	void
	Canvas2D::draw_sprite (const std::string& path, r_type x, r_type y,
						 r_type w, r_type h, r_type angle, const Color& c)
	{
		angle = rad_to_deg_ (angle);
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
	Canvas2D::draw_text (const std::string& text, r_type x, r_type y,
					   r_type angle, const std::string& font, const Color& c,
					   r_type size)
	{
		angle = rad_to_deg_ (angle);
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

	Vector2D
	Canvas2D::text_size_get (const std::string& text, const std::string& font,
						   r_type size)
	{
		TTF_Font* ttf = font_get_ (font, static_cast<int> (size));
		SDL_Color color;
		SDL_Surface* text_surface = TTF_RenderText_Solid(ttf, text.c_str (),
														  color);
		assert (text_surface);

		Vector2D res (text_surface->w, text_surface->h);
		SDL_FreeSurface (text_surface);
		return res;
	}


	void
	Canvas2D::draw_circle_ (int n_cx, int n_cy, int radius)
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
	Canvas2D::fill_circle_ (int xc, int yc, int radius)
	{
		for (int y = -radius; y <= radius; ++y)
			for (int x = -radius; x <= radius; ++x)
				if(x * x + y * y <= radius * radius)
					SDL_RenderDrawPoint (renderer_, xc + x, yc + y);
	}

	SDL_Texture*
	Canvas2D::texture_get_ (const std::string& path)
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
	Canvas2D::load_texture_ (const std::string& path)
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
	Canvas2D::font_get_ (const std::string& font, int size)
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

	r_type
	Canvas2D::deg_to_rad_ (r_type deg)
	{
		return deg * math::pi<r_type> () / static_cast<r_type> (180);
	}

	r_type
	Canvas2D::rad_to_deg_ (r_type rad)
	{
		return rad * static_cast<r_type> (180) / math::pi<r_type> ();
	}



}