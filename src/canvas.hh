/** @file Canvas file definition
 */

#ifndef CANVAS_HH_
# define CANVAS_HH_

# include <map>
# include <vector>
# include "sdl.hh"
# include "types.hh"
# include "color.hh"

namespace opl
{

	///SDL Canvas for drawing different shapes
	class Canvas
	{

	public:
		Canvas (SDL_Renderer* renderer, r_type width, r_type height);
		virtual ~Canvas();

		void
		init ();

		void
		clear ();

		void
		render ();

		void
		preload_sprite (const std::string& path);

		void
		preload_sprites (const std::vector<std::string>& paths);

		void
		preload_font (const std::string& font, int size);

		r_type
		width_get () const;

		r_type
		hight_get () const;

		void
		resize (r_type width, r_type height);

		void
		width_set (r_type width);

		void
		height_set (r_type height);

		Color
		draw_color_get ();

		void
		draw_color_set(const Color& c);

		void
		draw_point (r_type x, r_type y);

		void
		draw_line (r_type x1, r_type y1, r_type x2, r_type y2);

		void
		draw_rect (r_type x, r_type y, r_type w, r_type h);

		void
		fill_rect (r_type x, r_type y, r_type w, r_type h);

		void
		draw_circle (r_type x, r_type y, r_type r);

		void
		fill_circle (r_type x, r_type y, r_type r);

		void
		draw_sprite (const std::string& path, r_type x, r_type y,
					 r_type w, r_type h, r_type angle, const Color& c);

		void
		draw_text (const std::string& text, r_type x, r_type y, r_type angle,
				   const std::string& font, const Color& c, n_type size);

	protected:
		virtual void
		on_init_ ();

	private:
		SDL_Renderer* renderer_;
		r_type width_;
		r_type height_;
		std::map<std::string, SDL_Texture*> sprites_;
		std::map<std::string, TTF_Font*> fonts_;

		void
		draw_circle_ (int n_cx, int n_cy, int radius);

		void
		fill_circle_ (int xc, int yc, int radius);

		SDL_Texture*
		texture_get_ (const std::string& path);

		SDL_Texture*
		load_texture_ (const std::string& path);

		TTF_Font*
		font_get_ (const std::string& font, int size);

	};

}

#endif //!CANVAS_HH_