#include <cassert>
#include <cmath>
#include "line-2d.hh"
#include "line-collider-2d.hh"

namespace opl
{

	Line2D::Line2D (r_type x1, r_type y1, r_type x2, r_type y2, const Color& c,
				Collider2D* collider)
		: Object2D (collider), x1_ (x1), y1_(y1), x2_ (x2), y2_(y2),
		  color_ (c)
	{

	}


	Color
	Line2D::color_get () const
	{
		return color_;
	}

	void
	Line2D::color_set (const Color& c)
	{
		color_ = c;
	}

	void
	Line2D::p1_move (r_type dx, r_type dy)
	{
		x1_ += dx;
		y1_ += dy;
	}

	void
	Line2D::p1_move (Vector2D v)
	{
		x1_ += v.x_get ();
		y1_ += v.y_get ();
	}

	void
	Line2D::p2_move (r_type dx, r_type dy)
	{
		x2_ += dx;
		y2_ += dy;
	}

	void
	Line2D::p2_move (Vector2D v)
	{
		x2_ += v.x_get ();
		y2_ += v.y_get ();
	}

	void
	Line2D::p1_set (r_type x, r_type y)
	{
		x1_ = x;
		y1_ = y;
	}

	void
	Line2D::p1_set (Vector2D v)
	{
		x1_ = v.x_get ();
		y1_ = v.y_get ();
	}

	void
	Line2D::p2_set (r_type x, r_type y)
	{
		x2_ = x;
		y2_ = y;
	}

	void
	Line2D::p2_set (Vector2D v)
	{
		x2_ = v.x_get ();
		y2_ = v.y_get ();
	}

	r_type
	Line2D::p1_x_get () const
	{
		return x1_;
	}

	r_type
	Line2D::p1_y_get () const
	{
		return y1_;
	}

	r_type
	Line2D::p2_x_get () const
	{
		return x2_;
	}

	r_type
	Line2D::p2_y_get () const
	{
		return y2_;
	}

	Vector2D
	Line2D::p1_get () const
	{
		return Vector2D (x1_, y1_);
	}

	Vector2D
	Line2D::p2_get () const
	{
		return Vector2D (x2_, y2_);
	}

	void
	Line2D::rotate_around_p1 (r_type angle)
	{
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		r_type x = x2_;
		r_type y = y2_;

		x2_ = x1_ + (x - x1_) * c - (y - y1_) * s;
		y2_ = y1_ + (x - x1_) * s + (y - y1_) * c;
	}

	void
	Line2D::rotate_aroung_p2 (r_type angle)
	{
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		r_type x = x1_;
		r_type y = y1_;

		x1_ = x2_ + (x - x2_) * c - (y - y2_) * s;
		y1_ = y2_ + (x - x2_) * s + (y - y2_) * c;
	}



	r_type
	Line2D::x_get () const
	{
		return (x1_ + x2_) / 2;
	}

	r_type
	Line2D::y_get () const
	{
		return (y1_ + y2_) / 2;
	}

	void
	Line2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		r_type dx = x - x_get ();
		x1_ += dx;
		x2_ += dx;
	}

	void
	Line2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		r_type dy = y - y_get ();
		y1_ += dy;
		y2_ += dy;
	}

	void
	Line2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x1_ += dx;
		x2_ += dx;
	}

	void
	Line2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y1_ += dy;
		y2_ += dy;
	}

	void
	Line2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x1_ += dx;
		x2_ += dx;
		y1_ += dx;
		y2_ += dy;
	}

	void
	Line2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
	    r_type dx = x - x_get ();
		x1_ += dx;
		x2_ += dx;
		r_type dy = y - y_get ();
		y1_ += dy;
		y2_ += dy;
	}

	void
	Line2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		r_type x = x_get ();
		r_type y = y_get ();

		x1_ = x + (x1_ - x) * sx;
		y1_ = y + (y1_ - y) * sy;

		x2_ = x + (x2_ - x) * sx;
		y2_ = y + (y2_ - y) * sy;
	}

	void
	Line2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
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

	void
	Line2D::draw (Canvas2D *cv, r_type dx, r_type dy, r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		cv->draw_color_set (color_);

		r_type x1 = dx + x1_ * sx;
		r_type y1 = dy + y1_ * sy;
		r_type x2 = dx + x2_ * sx;
		r_type y2 = dy + y2_ * sy;

		cv->draw_line (x1, y1, x2, y2);
	}

	void
	Line2D::collider_set_default ()
	{
		collider_set (new LineCollider2D (x1_, y1_, x2_, y2_));
	}

}