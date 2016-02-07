#include "pixel-collider.hh"

namespace opl
{
	const int PixelCollider::ID = 1;

	PixelCollider::PixelCollider (r_type x, r_type y)
		: x_ (x), y_ (y)
	{

	}

	void
	PixelCollider::x_set (r_type x)
	{
		x_ = x;
	}

	void
	PixelCollider::y_set (r_type y)
	{
		y_ = y;
	}

	void
	PixelCollider::move (r_type dx, r_type dy)
	{
		x_ += dx;
		y_ += dy;
	}

	void
	PixelCollider::move_to (r_type x, r_type y)
	{
		x_ = x;
		y_ = y;
	}

	void
	PixelCollider::scale (r_type, r_type)
	{

	}

	void
	PixelCollider::rotate (r_type)
	{

	}

	int
	PixelCollider::id_get () const
	{
		return ID;
	}
}