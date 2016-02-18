/** @file Canvas2D file definition
 */

#ifndef CANVAS_2D_HH_
# define CANVAS_2D_HH_

# include <map>
# include <vector>
# include "sdl.hh"
# include "types.hh"
# include "color.hh"
# include "vector-2d.hh"

namespace opl
{

	///SDL Canvas for drawing different shapes
	class Canvas2D
	{

	public:

		static Canvas2D*
		instance ();

		void
		init (SDL_Renderer* renderer);

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
				   const std::string& font, const Color& c, r_type size);

		Vector2D
		text_size_get (const std::string& text, const std::string& font,
					   r_type size);

		void
		draw_polygon (const std::vector<r_type>& coords);

		void
		fill_polygon (const std::vector<r_type>& coords);

	private:
		static Canvas2D* instance_;
		SDL_Renderer* renderer_;
		std::map<std::string, SDL_Texture*> sprites_;
		std::map<std::string, TTF_Font*> fonts_;

		Canvas2D () = default;
		Canvas2D (const Canvas2D&) = delete;

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

		static r_type
		deg_to_rad_ (r_type deg);

		static r_type
		rad_to_deg_ (r_type rad);

	};

}

#endif //!CANVAS_2D_HH_