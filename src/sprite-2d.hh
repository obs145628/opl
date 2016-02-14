/** @file Sprite2D class definition
 */

#ifndef SPRITE_2D_HH_
# define SPRITE_2D_HH_

# include <string>
# include "object-2d.hh"
# include "color.hh"

namespace opl
{

	///2D sdl object reprenting a sprite image
	class Sprite2D: public Object2D
	{

	public:

		Sprite2D (const std::string& path, r_type x, r_type y,
				  r_type w, r_type h, const Color& c,
				  Collider2D* collider = nullptr);
		virtual ~Sprite2D () = default;

		std::string
		path_get () const;

		void
		path_set (const std::string& path);

		r_type
		width_get () const;

		void
		width_set (r_type w);

		r_type
		height_get () const;

		void
		height_set (r_type h);

		Color
		color_get () const;

		void
		color_set (const Color& c);


		virtual r_type
		x_get () const override;

		virtual r_type
		y_get () const override;

		virtual void
		x_set (r_type x) override;

		virtual void
		y_set (r_type y) override;

		virtual void
		x_move (r_type dx) override;

		virtual void
		y_move (r_type dy) override;

		virtual void
		move (r_type dx, r_type dy) override;

		virtual void
		move_to (r_type x, r_type y) override;

		virtual void
		scale (r_type sx, r_type sy) override;

		virtual void
		rotate (r_type angle) override;

		virtual void
		draw (Canvas2D *cv, r_type dx, r_type dy,
			  r_type sx, r_type sy) override;

	private:
		std::string path_;
		r_type x_;
		r_type y_;
		r_type w_;
		r_type h_;
		Color color_;

		r_type angle_;


	};

}

#endif //!SPRITE_2D_HH_