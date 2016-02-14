#include "pixel-collider-2d.hh"

namespace opl
{
	const size_t PixelCollider2D::ID = 1;

	PixelCollider2D::PixelCollider2D (r_type x, r_type y)
		: Collider2D (), x_ (x), y_ (y)
	{

	}

	r_type
	PixelCollider2D::x_get () const
	{
		return x_;
	}

	r_type
	PixelCollider2D::y_get () const
	{
		return y_;
	}

	void
	PixelCollider2D::x_set (r_type x)
	{
		x_ = x;
	}

	void
	PixelCollider2D::y_set (r_type y)
	{
		y_ = y;
	}

	void
	PixelCollider2D::x_move (r_type dx)
	{
		x_ += dx;
	}

	void
	PixelCollider2D::y_move (r_type dy)
	{
		y_ += dy;
	}

	void
	PixelCollider2D::move (r_type dx, r_type dy)
	{
		x_ += dx;
		y_ += dy;
	}

	void
	PixelCollider2D::move_to (r_type x, r_type y)
	{
		x_ = x;
		y_ = y;
	}

	void
	PixelCollider2D::scale (r_type, r_type)
	{

	}

	void
	PixelCollider2D::rotate (r_type)
	{

	}

	size_t
	PixelCollider2D::id_get () const
	{
		return ID;
	}
}