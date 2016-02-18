/** @file Rectangle2D class definition
 */

#ifndef RECTANGLE_2D_HH_
# define RECTANGLE_2D_HH_

# include "object-2d.hh"
# include "color.hh"

namespace opl
{

	///2D sdl object reprenting a rectangle
	class Rectangle2D: public Object2D
	{

	public:

		Rectangle2D (r_type x, r_type y, r_type w, r_type h,
					 bool filled, const Color& c,
					 Collider2D* collider = nullptr);

		virtual ~Rectangle2D () = default;

		r_type
		width_get () const;

		void
		width_set (r_type width);

		r_type
		height_get () const;

		void
		height_set (r_type height);

		bool
		is_filled () const;

		void
		filled_set (bool filled);

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

		virtual void
		collider_set_default () override;

	private:
		r_type x_;
		r_type y_;
		r_type w_;
		r_type h_;
		bool filled_;
		Color color_;
		r_type angle_;


	};

}

#endif //!PIXEL_2D_HH_