/** @file Pixel2D class definition
 */

#ifndef PIXEL_2D_HH_
# define PIXEL_2D_HH_

# include "object-2d.hh"
# include "color.hh"

namespace opl
{

	///2D sdl object reprenting a single point
	class Pixel2D: public Object2D
	{

	public:

		Pixel2D (r_type x, r_type y, const Color& c,
				 Collider2D* collider = nullptr);
		virtual ~Pixel2D () = default;

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
		draw (Canvas2D *cv, r_type dx, r_type dy,
			  r_type sx, r_type sy) override;

		virtual void
		collider_set_default () override;

	private:
		r_type x_;
		r_type y_;
		Color color_;


	};

}

#endif //!PIXEL_2D_HH_