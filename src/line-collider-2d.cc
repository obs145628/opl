#include <cmath>
#include "line-collider-2d.hh"

namespace opl
{
	const size_t LineCollider2D::ID = 2;

	LineCollider2D::LineCollider2D (r_type x1, r_type y1,
									r_type x2, r_type y2)
		: Collider2D (), x1_ (x1), y1_ (y1), x2_ (x2), y2_ (y2)
	{

	}

	r_type
	LineCollider2D::x_get () const
	{
		return (x1_ + x2_) / 2;
	}

	r_type
	LineCollider2D::y_get () const
	{
		return (y1_ + y2_) / 2;
	}

	r_type
	LineCollider2D::x1_get () const
	{
		return x1_;
	}

	r_type
	LineCollider2D::y1_get () const
	{
		return y1_;
	}

	r_type
	LineCollider2D::x2_get () const
	{
		return x2_;
	}

	r_type
	LineCollider2D::y2_get () const
	{
		return y2_;
	}

	void
	LineCollider2D::x_set (r_type x)
	{
		r_type dx = x - x_get ();
		x1_ += dx;
		x2_ += dx;
	}

	void
	LineCollider2D::y_set (r_type y)
	{
		r_type dy = y - y_get ();
		y1_ += dy;
		y2_ += dy;
	}

	void
	LineCollider2D::x_move (r_type dx)
	{
		x1_ += dx;
		x2_ += dx;
	}

	void
	LineCollider2D::y_move (r_type dy)
	{
		y1_ += dy;
		y2_ += dy;
	}

	void
	LineCollider2D::move (r_type dx, r_type dy)
	{
	    x1_ += dx;
		x2_ += dx;
		y1_ += dx;
		y2_ += dy;
	}

	void
	LineCollider2D::move_to (r_type x, r_type y)
	{
	    r_type dx = x - x_get ();
		x1_ += dx;
		x2_ += dx;
		r_type dy = y - y_get ();
		y1_ += dy;
		y2_ += dy;
	}

	void
	LineCollider2D::scale (r_type sx, r_type sy)
	{
		r_type x = x_get ();
		r_type y = y_get ();

		x1_ = x + (x1_ - x) * sx;
		y1_ = y + (y1_ - y) * sy;

		x2_ = x + (x2_ - x) * sx;
		y2_ = y + (y2_ - y) * sy;
	}

	void
	LineCollider2D::rotate (r_type angle)
	{
		r_type x = x_get ();
		r_type y = y_get ();
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);

		r_type x1 = x1_;
		r_type y1 = y1_;
		r_type x2 = x2_;
	    r_type y2 = y2_;

		x1_ = x + (x1 - x) * c - (y1 - y) * s;
		y1_ = y + (x1 - x) * s + (y1 - y) * c;
		x2_ = x + (x2 - x) * c - (y2 - y) * s;
		y2_ = y + (x2 - x) * s + (y2 - y) * c;
	}

	size_t
	LineCollider2D::id_get () const
	{
		return ID;
	}
}