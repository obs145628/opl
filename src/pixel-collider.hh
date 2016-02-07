/** @file PixelCollider class definitiion
 */

#ifndef PIXEL_COLLIDER_HH_
# define PIXEL_COLLIDER_HH_

# include "collider.hh"

namespace opl
{

	///2D Pixel Collider
	class PixelCollider: public Collider
	{

	public:

		static const int ID;

		PixelCollider (r_type x, r_type y);

		virtual void
		x_set (r_type x);

		virtual void
		y_set (r_type y);

		virtual void
		move (r_type dx, r_type dy);

		virtual void
		move_to (r_type x, r_type y);

		virtual void
		scale (r_type sx, r_type sy);

		virtual void
		rotate (r_type angle);

		virtual int
		id_get () const;

	private:
		r_type x_;
		r_type y_;


	};

}

#endif //!PIXEL_COLLIDER_HH_