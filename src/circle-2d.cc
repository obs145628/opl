#include <cassert>
#include "circle-2d.hh"
#include "circle-collider-2d.hh"

namespace opl
{

	Circle2D::Circle2D (r_type x, r_type y, r_type r, bool filled, const Color& c,
					Collider2D* collider)
		: Object2D (collider), x_ (x), y_(y), r_ (r), filled_ (filled),
		  color_ (c)
	{

	}

	r_type
	Circle2D::radius_get () const
	{
		return r_;
	}

	void
	Circle2D::radius_set (r_type radius)
	{
		r_ = radius;
	}

	bool
	Circle2D::is_filled () const
	{
		return filled_;
	}

	void
	Circle2D::set_filled (bool filled)
	{
		filled_ = filled;
	}

	Color
	Circle2D::color_get () const
	{
		return color_;
	}

	void
	Circle2D::color_set (const Color& c)
	{
		color_ = c;
	}

	r_type
	Circle2D::x_get () const
	{
		return x_;
	}

	r_type
	Circle2D::y_get () const
	{
		return y_;
	}

	void
	Circle2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		x_ = x;
	}

	void
	Circle2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		y_ = y;
	}

	void
	Circle2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
	}

	void
	Circle2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
	}

	void
	Circle2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
	}

	void
	Circle2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		x_ = x;
		y_ = y;
	}

	void
	Circle2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		r_ *= sx;
	}

	void
	Circle2D::draw (Canvas2D *cv, r_type dx, r_type dy, r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);

		cv->draw_color_set (color_);
		r_type x = dx + x_ * sx;
		r_type y = dy + y_ * sy;
		r_type r = r_ * sx;

		if (filled_)
			cv->fill_circle (x, y, r);
		else
			cv->draw_circle (x, y, r);

	}

	void
	Circle2D::collider_set_default ()
	{
		collider_set (new CircleCollider2D (x_, y_, r_));
	}

}