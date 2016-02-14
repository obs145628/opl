/** @file CircleCollider2D class definitiion
 */

#ifndef CIRCLE_COLLIDER_2D_HH_
# define CIRCLE_COLLIDER_2D_HH_

# include "collider-2d.hh"

namespace opl
{

	///2D Circle Collider
	class CircleCollider2D: public Collider2D
	{

	public:

		static const size_t ID;

		CircleCollider2D (r_type x, r_type y, r_type r);

		r_type
		x_get () const;

		r_type
		y_get () const;

		r_type
		r_get () const;

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

		virtual size_t
		id_get () const;

	private:
		r_type x_;
		r_type y_;
		r_type r_;


	};

}

#endif //!CIRCLE_COLLIDER_2D_HH_