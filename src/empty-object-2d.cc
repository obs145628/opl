#include "empty-object-2d.hh"

namespace opl
{

	EmptyObject2D::EmptyObject2D (r_type x, r_type y,
								  Collider2D* collider)
		: Object2D (collider), x_ (x), y_(y)
	{

	}

	r_type
	EmptyObject2D::x_get () const
	{
		return x_;
	}

	r_type
	EmptyObject2D::y_get () const
	{
		return y_;
	}

	void
	EmptyObject2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		x_ = x;
	}

	void
	EmptyObject2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		y_ = y;
	}

	void
	EmptyObject2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
	}

	void
	EmptyObject2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
	}

	void
	EmptyObject2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
	}

	void
	EmptyObject2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		x_ = x;
		y_ = y;
	}

}