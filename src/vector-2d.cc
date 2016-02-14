#include <cmath>
#include "vector-2d.hh"

namespace opl
{

	Vector2D::Vector2D ()
		: x_ (0), y_ (0)
	{

	}


	Vector2D::Vector2D (r_type x, r_type y)
		: x_ (x), y_ (y)
	{

	}


	r_type
	Vector2D::x_get () const
	{
		return x_;
	}

	r_type
	Vector2D::y_get () const
	{
		return y_;
	}

	r_type
	Vector2D::norm () const
	{
		return std::sqrt (x_ * x_ + y_ * y_);
	}

	r_type
	Vector2D::norm_square () const
	{
		return x_ * x_ + y_ * y_;
	}

	Vector2D
	Vector2D::normalize () const
	{
		r_type n = norm ();
		return Vector2D (x_ / n, y_ / n);
	}

	r_type
	Vector2D::dot_product (const Vector2D& v) const
	{
		return x_ * v.x_ + y_ * v.y_;
	}

	Vector2D
	Vector2D::normal () const
	{
		return Vector2D (y_, -x_);
	}

	r_type
	Vector2D::project_on (const Vector2D& v) const
	{
		return dot_product (v.normalize ());
	}

	Vector2D
	Vector2D::rotate (r_type angle) const
	{
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		return Vector2D (x_ * c - y_ * s, x_ * s + y_ * c);
	}

	Vector2D
	Vector2D::translate (r_type dx, r_type dy) const
	{
		return Vector2D (x_ + dx, y_ + dy);
	}

	Vector2D
	Vector2D::translate (const Vector2D& v) const
	{
		return Vector2D (x_ + v.x_, y_ + v.y_);
	}

	Vector2D
	Vector2D::vector_to (r_type x2, r_type y2) const
	{
		return Vector2D (x2 - x_, y2 - y_);
	}

	Vector2D
	Vector2D::vector_to (const Vector2D& v) const
	{
		return Vector2D (v.x_ - x_, v.y_ - y_);
	}

	Vector2D
	Vector2D::rotate_around (r_type x0, r_type y0, r_type angle) const
	{
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		return Vector2D (
			x0 + (x_ - x0) * c - (y_ - y0) * s,
			y0 + (x_ - x0) * s + (y_ - y0) * c
			);
	}

	Vector2D
	Vector2D::rotate_around (const Vector2D& v, r_type angle) const
	{
		return rotate_around (v.x_, v.y_, angle);
	}

	std::ostream&
	operator<< (std::ostream& os, const Vector2D& v)
	{
		os << "{" << v.x_ << ", " << v.y_ << "}";
		return os;
	}


	bool
	operator== (const Vector2D& a, const Vector2D& b)
	{
		return a.x_ == b.x_ && a.y_ == b.y_;
	}

	bool
	operator!= (const Vector2D& a, const Vector2D& b)
	{
		return a.x_ != b.x_ || a.y_ != b.y_;
	}

	Vector2D
	operator+ (const Vector2D& a, const Vector2D& b)
	{
		return Vector2D (a.x_ + b.x_, a.y_ + b.y_);
	}

	Vector2D
	operator- (const Vector2D& a, const Vector2D& b)
	{
		return Vector2D (a.x_ - b.x_, a.y_ - b.y_);
	}

	Vector2D
	operator+ (const Vector2D& v, r_type x)
	{
		return Vector2D (v.x_ + x, v.y_ + x);
	}

	Vector2D
	operator+ (r_type x, const Vector2D& v)
	{
		return Vector2D (x + v.x_, x + v.y_);
	}

	Vector2D
	operator- (const Vector2D& v, r_type x)
	{
		return Vector2D (v.x_ - x, v.y_ - x);
	}

	Vector2D
	operator- (r_type x, const Vector2D& v)
	{
		return Vector2D (x - v.x_, x - v.y_);
	}

	Vector2D
	operator* (const Vector2D& v, r_type x)
	{
		return Vector2D (v.x_ * x, v.y_ * x);
	}

	Vector2D
	operator* (r_type x, const Vector2D& v)
	{
		return Vector2D (x * v.x_, x * v.y_);
	}

	Vector2D
	operator/ (const Vector2D& v, r_type x)
	{
		return Vector2D(v.x_ / x, v.y_ / x);
	}

	Vector2D
	operator/ (r_type x, const Vector2D& v)
	{
		return Vector2D (x / v.x_, x / v.y_);
	}

}