/** @file EmptyObject2D class definition
 */

#ifndef EMPTY_OBJECT_2D_HH_
# define EMPTY_OBJECT_2D_HH_

# include "object-2d.hh"

namespace opl
{

	///Invisible 2D object, used for children
	class EmptyObject2D: public Object2D
	{

	public:

		EmptyObject2D (r_type x, r_type y,
					   Collider2D* collider = nullptr);
		virtual ~EmptyObject2D () = default;


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

	private:
		r_type x_;
		r_type y_;


	};

}

#endif //!EMPTY_OBJECT_2D_HH_