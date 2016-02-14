/** @file Collider2D class definitiion
 */

#ifndef COLLIDER_2D_HH_
# define COLLIDER_2D_HH_

# include <cstddef>
# include "types.hh"

namespace opl
{

	///2D base Collider
	class Collider2D
	{

	public:

		virtual ~Collider2D () = default;

		virtual void
		x_set (r_type x) = 0;

		virtual void
		y_set (r_type y) = 0;

		virtual void
		x_move (r_type dx) = 0;

		virtual void
		y_move (r_type dy) = 0;

		virtual void
		move (r_type dx, r_type dy) = 0;

		virtual void
		move_to (r_type x, r_type y) = 0;

		virtual void
		scale (r_type sx, r_type sy) = 0;

		virtual void
		rotate (r_type angle) = 0;

		virtual size_t
		id_get () const = 0;


	};

}

#endif //!COLLIDER_2D_HH_