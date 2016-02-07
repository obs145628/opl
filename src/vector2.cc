#include <cmath>
#include "vector2.hh"

namespace opl
{



	Vector2::Vector2 (r_type x, r_type y)
		: x_ (x), y_ (y)
	{

	}

	r_type
	Vector2::x_get () const
	{
		return x_;
	}

	r_type
	Vector2::y_get () const
	{
		return y_;
	}

	r_type
	Vector2::norm () const
	{
		return std::sqrt (x_ * x_ + y_ * y_);
	}

	r_type
	Vector2::norm_square () const
	{
		return x_ * x_ + y_ * y_;
	}

	Vector2
	Vector2::normalize () const
	{
		r_type n = norm ();
		return Vector2 (x_ / n, y_ / n);
	}

	r_type
	Vector2::dot_product (const Vector2& v) const
	{
		return x_ * v.x_ + y_ * v.y_;
	}

	Vector2
	Vector2::normal () const
	{
		return Vector2 (y_, -x_);
	}

	r_type
	Vector2::project_on (const Vector2& v) const
	{
		return dot_product (v.normalize ());
	}

	Vector2
	Vector2::rotate (r_type angle) const
	{
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		return Vector2 (x_ * c - y_ * s, x_ * s + y_ * c);
	}

	Vector2
	Vector2::translate (r_type dx, r_type dy) const
	{
		return Vector2 (x_ + dx, y_ + dy);
	}

	Vector2
	Vector2::translate (const Vector2& v) const
	{
		return Vector2 (x_ + v.x_, y_ + v.y_);
	}

	Vector2
	Vector2::vector_to (r_type x2, r_type y2) const
	{
		return Vector2 (x2 - x_, y2 - y_);
	}

	Vector2
	Vector2::vector_to (const Vector2& v) const
	{
		return Vector2 (v.x_ - x_, v.y_ - y_);
	}

	Vector2
	Vector2::rotate_around (r_type x0, r_type y0, r_type angle) const
	{
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		return Vector2 (
			x0 + (x_ - x0) * c - (y_ - y0) * s,
			y0 + (x_ - x0) * s + (y_ - y0) * c
			);
	}

	Vector2
	Vector2::rotate_around (const Vector2& v, r_type angle) const
	{
		return rotate_around (v.x_, v.y_, angle);
	}

	std::ostream&
	operator<< (std::ostream& os, const Vector2& v)
	{
		os << "{" << v.x_ << ", " << v.y_ << "}";
		return os;
	}

}