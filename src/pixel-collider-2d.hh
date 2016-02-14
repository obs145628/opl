/** @file PixelCollider2D class definitiion
 */

#ifndef PIXEL_COLLIDER_2D_HH_
# define PIXEL_COLLIDER_2D_HH_

# include "collider-2d.hh"

namespace opl
{

	///2D Pixel Collider
	class PixelCollider2D: public Collider2D
	{

	public:

		static const size_t ID;

		PixelCollider2D (r_type x, r_type y);

		r_type
		x_get () const;

		r_type
		y_get () const;

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


	};

}

#endif //!PIXEL_COLLIDER_2D_HH_