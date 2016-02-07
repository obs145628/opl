/** @file Vector2 class definition
 */

#ifndef VECTOR2_HH_
# define VECTOR2_HH_

# include <iostream>
# include "types.hh"

namespace opl
{

	///2 coordonates vector over the reals
	class Vector2
	{
	public:

		Vector2 (r_type x, r_type y);

		r_type
		x_get () const;

		r_type
		y_get () const;

		r_type
		norm () const;

		r_type
		norm_square () const;

		Vector2
		normalize () const;

		r_type
		dot_product (const Vector2& v) const;

		Vector2
		normal () const;

		r_type
		project_on (const Vector2& v) const;

		Vector2
		rotate (r_type angle) const;

		Vector2
		translate (r_type dx, r_type dy) const;

		Vector2
		translate (const Vector2& v) const;

		Vector2
		vector_to (r_type x2, r_type y2) const;

		Vector2
		vector_to (const Vector2& v) const;

		Vector2
		rotate_around (r_type x0, r_type y0, r_type angle) const;

		Vector2
		rotate_around (const Vector2& v, r_type angle) const;

		friend std::ostream&
		operator<< (std::ostream& os, const Vector2& v);


	private:
		r_type x_;
		r_type y_;

	};

}

#endif //!VECTOR2_HH_