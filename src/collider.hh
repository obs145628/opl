/** @file Collider class definitiion
 */

#ifndef COLLIDER_HH_
# define COLLIDER_HH_

# include "types.hh"

namespace opl
{

	///2D base Collider
	class Collider
	{

	public:

		virtual ~Collider () = default;

		virtual void
		x_set (r_type x) = 0;

		virtual void
		y_set (r_type y) = 0;

		virtual void
		move (r_type dx, r_type dy) = 0;

		virtual void
		move_to (r_type x, r_type y) = 0;

		virtual void
		scale (r_type sx, r_type sy) = 0;

		virtual void
		rotate (r_type angle) = 0;

		virtual int
		id_get () const = 0;


	};

}

#endif //!COLLIDER_HH_