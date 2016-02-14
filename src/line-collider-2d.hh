/** @file LineCollider2D class definitiion
 */

#ifndef Line_COLLIDER_2D_HH_
# define Line_COLLIDER_2D_HH_

# include "collider-2d.hh"

namespace opl
{

	///2D Line Collider
	class LineCollider2D: public Collider2D
	{

	public:

		static const size_t ID;

		LineCollider2D (r_type x1, r_type y1, r_type x2, r_type y2);

		r_type
		x_get () const;

		r_type
		y_get () const;

		r_type
		x1_get () const;

		r_type
		y1_get () const;

		r_type
		x2_get () const;

		r_type
		y2_get () const;

		virtual void
		x_set (r_type x);

		virtual void
		y_set (r_type y);

		virtual void
		x_move (r_type dx) override;

		virtual void
		y_move (r_type dy) override;

		virtual void
		move (r_type dx, r_type dy);

		virtual void
		move_to (r_type x, r_type y);

		virtual void
		scale (r_type sx, r_type sy);

		virtual void
		rotate (r_type angle);

		virtual size_t
		id_get () const;

	private:
		r_type x1_;
		r_type y1_;
		r_type x2_;
		r_type y2_;


	};

}

#endif //!LINE_COLLIDER_2DÃ_HH_