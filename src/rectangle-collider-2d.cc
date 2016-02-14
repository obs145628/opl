#include "rectangle-collider-2d.hh"

namespace opl
{
	const size_t RectangleCollider2D::ID = 5;

	RectangleCollider2D::RectangleCollider2D (r_type x, r_type y,
											  r_type w, r_type h)
		: Collider2D (), x_ (x), y_ (y), w_ (w), h_ (h)
	{

	}

	r_type
	RectangleCollider2D::x0_get () const
	{
		return x_ - w_ / 2;
	}

	r_type
	RectangleCollider2D::y0_get () const
	{
		return y_ - h_ / 2;
	}

	r_type
	RectangleCollider2D::w_get () const
	{
		return w_;
	}

	r_type
	RectangleCollider2D::h_get () const
	{
		return h_;
	}

	void
	RectangleCollider2D::x_set (r_type x)
	{
		x_ = x;
	}

	void
	RectangleCollider2D::y_set (r_type y)
	{
		y_ = y;
	}

	void
	RectangleCollider2D::x_move (r_type dx)
	{
		x_ += dx;
	}

	void
	RectangleCollider2D::y_move (r_type dy)
	{
		y_ += dy;
	}

	void
	RectangleCollider2D::move (r_type dx, r_type dy)
	{
		x_ += dx;
		y_ += dy;
	}

	void
	RectangleCollider2D::move_to (r_type x, r_type y)
	{
		x_ = x;
		y_ = y;
	}

	void
	RectangleCollider2D::scale (r_type sx, r_type sy)
	{
		w_ *= sx;
		h_ *= sy;
	}

	void
	RectangleCollider2D::rotate (r_type)
	{

	}

	size_t
	RectangleCollider2D::id_get () const
	{
		return ID;
	}
}