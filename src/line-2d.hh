/** @file Line2D class definition
 */

#ifndef LINE_2D_HH_
# define LINE_2D_HH_

# include "object-2d.hh"
# include "color.hh"

namespace opl
{

	///2D sdl object representing a line
	class Line2D: public Object2D
	{

	public:

		Line2D (r_type x1, r_type y1, r_type x2, r_type y2, const Color& c,
				Collider2D* collider = nullptr);
		virtual ~Line2D () = default;

		Color
		color_get () const;

		void
		color_set (const Color& c);

		void
		p1_move (r_type dx, r_type dy);

		void
		p1_move (Vector2D v);

		void
		p2_move (r_type dx, r_type dy);

		void
		p2_move (Vector2D v);

		void
		p1_set (r_type x, r_type y);

		void
		p1_set (Vector2D v);

		void
		p2_set (r_type x, r_type y);

		void
		p2_set (Vector2D v);

		r_type
		p1_x_get () const;

		r_type
		p1_y_get () const;

		r_type
		p2_x_get () const;

		r_type
		p2_y_get () const;

		Vector2D
		p1_get () const;

		Vector2D
		p2_get () const;

		void
		rotate_around_p1 (r_type angle);

		void
		rotate_aroung_p2 (r_type angle);




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
		r_type x1_;
		r_type y1_;
		r_type x2_;
		r_type y2_;
		Color color_;


	};

}

#endif //!LINE_2D_HH_