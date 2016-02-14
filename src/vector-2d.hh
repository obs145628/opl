/** @file Vector2D class definition
 */

#ifndef VECTOR_2D_HH_
# define VECTOR_2D_HH_

# include <iostream>
# include "types.hh"

namespace opl
{

	///2D coordonates vector over the reals
	class Vector2D
	{
	public:

		Vector2D ();

		Vector2D (r_type x, r_type y);

		r_type
		x_get () const;

		r_type
		y_get () const;

		r_type
		norm () const;

		r_type
		norm_square () const;

		Vector2D
		normalize () const;

		r_type
		dot_product (const Vector2D& v) const;

		Vector2D
		normal () const;

		r_type
		project_on (const Vector2D& v) const;

		Vector2D
		rotate (r_type angle) const;

		Vector2D
		translate (r_type dx, r_type dy) const;

		Vector2D
		translate (const Vector2D& v) const;

		Vector2D
		vector_to (r_type x2, r_type y2) const;

		Vector2D
		vector_to (const Vector2D& v) const;

		Vector2D
		rotate_around (r_type x0, r_type y0, r_type angle) const;

		Vector2D
		rotate_around (const Vector2D& v, r_type angle) const;

		friend std::ostream&
		operator<< (std::ostream& os, const Vector2D& v);

		friend bool
		operator== (const Vector2D& a, const Vector2D& b);

		friend bool
		operator!= (const Vector2D& a, const Vector2D& b);

		friend Vector2D
		operator+ (const Vector2D& a, const Vector2D& b);

		friend Vector2D
		operator- (const Vector2D& a, const Vector2D& b);

		friend Vector2D
		operator+ (const Vector2D& v, r_type x);

		friend Vector2D
		operator+ (r_type x, const Vector2D& v);

		friend Vector2D
		operator- (const Vector2D& v, r_type x);

		friend Vector2D
		operator- (r_type x, const Vector2D& v);

		friend Vector2D
		operator* (const Vector2D& v, r_type x);

		friend Vector2D
		operator* (r_type x, const Vector2D& v);

		friend Vector2D
		operator/ (const Vector2D& v, r_type x);

		friend Vector2D
		operator/ (r_type x, const Vector2D& v);


	private:
		r_type x_;
		r_type y_;

	};

}

#endif //!VECTOR_2D_HH_