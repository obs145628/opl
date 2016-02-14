#include <cassert>
#include "pixel-2d.hh"
#include "pixel-collider-2d.hh"

namespace opl
{

	Pixel2D::Pixel2D (r_type x, r_type y, const Color& c,
				  Collider2D* collider)
		: Object2D (collider), x_ (x), y_(y), color_ (c)
	{

	}

	Color
	Pixel2D::color_get () const
	{
		return color_;
	}

	void
	Pixel2D::color_set (const Color& c)
	{
		color_ = c;
	}

	r_type
	Pixel2D::x_get () const
	{
		return x_;
	}

	r_type
	Pixel2D::y_get () const
	{
		return y_;
	}

	void
	Pixel2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		x_ = x;
	}

	void
	Pixel2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		y_ = y;
	}

	void
	Pixel2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
	}

	void
	Pixel2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
	}

	void
	Pixel2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
	}

	void
	Pixel2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		x_ = x;
		y_ = y;
	}

	void
	Pixel2D::draw (Canvas2D *cv, r_type dx, r_type dy, r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		cv->draw_color_set (color_);
		r_type x = dx + x_ * sx;
		r_type y = dy + y_ * sy;
		cv->draw_point (x, y);
	}

	void
	Pixel2D::collider_set_default ()
	{
		collider_set (new PixelCollider2D (x_, y_));
	}

}