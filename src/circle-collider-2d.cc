#include <cassert>
#include "circle-collider-2d.hh"

namespace opl
{
	const size_t CircleCollider2D::ID = 3;

	CircleCollider2D::CircleCollider2D (r_type x, r_type y, r_type r)
		: Collider2D (), x_ (x), y_ (y), r_ (r)
	{

	}

	r_type
	CircleCollider2D::x_get () const
	{
		return x_;
	}

	r_type
	CircleCollider2D::y_get () const
	{
		return y_;
	}

	r_type
	CircleCollider2D::r_get () const
	{
		return r_;
	}

	void
	CircleCollider2D::x_set (r_type x)
	{
		x_ = x;
	}

	void
	CircleCollider2D::y_set (r_type y)
	{
		y_ = y;
	}

	void
	CircleCollider2D::x_move (r_type dx)
	{
		x_ += dx;
	}

	void
	CircleCollider2D::y_move (r_type dy)
	{
		y_ += dy;
	}

	void
	CircleCollider2D::move (r_type dx, r_type dy)
	{
		x_ += dx;
		y_ += dy;
	}

	void
	CircleCollider2D::move_to (r_type x, r_type y)
	{
		x_ = x;
		y_ = y;
	}

	void
	CircleCollider2D::scale (r_type sx, r_type)
	{
		r_ *= sx;
	}

	void
	CircleCollider2D::rotate (r_type)
	{

	}

	size_t
	CircleCollider2D::id_get () const
	{
		return ID;
	}
}