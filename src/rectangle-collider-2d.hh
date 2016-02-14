/** @file RectangleCollider2D class definitiion
 */

#ifndef RECTANGLE_COLLIDER_2D_HH_
# define RECTANGLE_COLLIDER_2D_HH_

# include "collider-2d.hh"

namespace opl
{

	///2D Rectangle Collider
	class RectangleCollider2D: public Collider2D
	{

	public:

		static const size_t ID;

		RectangleCollider2D (r_type x, r_type y, r_type w, r_type h);

		///Returns top-left x coordonate
		r_type
		x0_get () const;

		///Returns top-left y coordonate
		r_type
		y0_get () const;

		r_type
		w_get () const;

		r_type
		h_get () const;

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
		r_type w_;
		r_type h_;


	};

}

#endif //!RECTANGLE_COLLIDER_2D_HH_