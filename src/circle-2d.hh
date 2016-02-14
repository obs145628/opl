/** @file Circle2D class definition
 */

#ifndef CIRCLE_2D_HH_
# define CIRCLE_2D_HH_

# include "object-2d.hh"
# include "color.hh"

namespace opl
{

	///2D sdl object representing a circle
	class Circle2D: public Object2D
	{

	public:

		Circle2D (r_type x, r_type y, r_type r, bool filled, const Color& c,
			   Collider2D* collider = nullptr);
		virtual ~Circle2D () = default;

		r_type
		radius_get () const;

		void
		radius_set (r_type radius);

		bool
		is_filled () const;

		void
		set_filled (bool filled);

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
		draw (Canvas2D *cv, r_type dx, r_type dy,
			  r_type sx, r_type sy) override;

		virtual void
		collider_set_default () override;

	private:
		r_type x_;
		r_type y_;
		r_type r_;
		bool filled_;
		Color color_;


	};

}

#endif //!CIRCLE_2D_HH_