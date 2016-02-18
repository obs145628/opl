#include <cassert>
#include <cmath>
#include "rectangle-2d.hh"
#include "polygon-collider-2d.hh"

namespace opl
{

	Rectangle2D::Rectangle2D (r_type x, r_type y, r_type w, r_type h,
							  bool filled, const Color& c,
							  Collider2D* collider)
		: Object2D (collider), x_ (x), y_ (y), w_ (w), h_ (h),
		  filled_ (filled), color_ (c), angle_ (0)
	{

	}

	r_type
	Rectangle2D::width_get () const
	{
		return w_;
	}

	void
	Rectangle2D::width_set (r_type width)
	{
		w_ = width;
	}

	r_type
	Rectangle2D::height_get () const
	{
		return h_;
	}

	void
	Rectangle2D::height_set (r_type height)
	{
		h_ = height;
	}

	bool
	Rectangle2D::is_filled () const
	{
		return filled_;
	}

	void
	Rectangle2D::filled_set (bool filled)
	{
		filled_ = filled;
	}

	Color
	Rectangle2D::color_get () const
	{
		return color_;
	}

	void
	Rectangle2D::color_set (const Color& c)
	{
		color_ = c;
	}


	r_type
	Rectangle2D::x_get () const
	{
		return x_;
	}

	r_type
	Rectangle2D::y_get () const
	{
		return y_;
	}

	void
	Rectangle2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		x_ = x;
	}

	void
	Rectangle2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		y_ = y;
	}

	void
	Rectangle2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
	}

	void
	Rectangle2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
	}

	void
	Rectangle2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
	}

	void
	Rectangle2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		x_ = x;
		y_ = y;
	}

	void
	Rectangle2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		w_ *= sx;
		h_ *= sy;
	}

	void
	Rectangle2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
		angle_ += angle;
	}

	void
	Rectangle2D::draw (Canvas2D *cv, r_type dx, r_type dy,
						r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		cv->draw_color_set (color_);

		r_type x = dx + x_ * sx;
		r_type y = dy + y_ * sy;
		r_type w2 = (w_ / 2) * sx;
		r_type h2 = (h_ / 2) * sy;

		std::vector<r_type> coords {
			x - w2, y - h2,
		   	x + w2, y - h2,
	   		x + w2, y + h2,
   			x - w2, y + h2
	   	};

		r_type c = std::cos (angle_);
		r_type s = std::sin (angle_);

		for (size_t i = 0; i < 8; i += 2)
		{
			r_type t_x = coords[i];
			coords[i] = x + (t_x - x) * c
				- (coords[i + 1] - y) * s;
			coords[i + 1] = y + (t_x - x) * s
				+ (coords[i + 1] - y) * c;
		}


		if (filled_)
			cv->fill_polygon (coords);
		else
			cv->draw_polygon(coords);
	}

	void
	Rectangle2D::collider_set_default ()
	{
		r_type w2 = w_ / 2;
		r_type h2 = h_ / 2;
		std::vector<r_type> coords {
			x_ - w2, y_ - h2,
		   	x_ + w2, y_ - h2,
	   		x_ + w2, y_ + h2,
   			x_ - w2, y_ + h2
	   	};

		PolygonCollider2D* pl = new PolygonCollider2D (x_, y_, coords);
		pl->rotate (angle_);
		collider_set (pl);
	}

}