#include <cassert>
#include <cmath>
#include "polygon-2d.hh"
#include "polygon-collider-2d.hh"

namespace opl
{


	Polygon2D
	Polygon2D::equilateral_triangle (r_type x, r_type y, r_type size,
									 bool filled, const Color& c)
	{
		r_type h = size * std::sqrt(3) / 2;
		std::vector<r_type> ver = { x - size / 2, y + h / 3,
									x, y - h * 2 / 3,
									x + size / 2, y - h / 3 };
		return Polygon2D(x, y, ver, filled, c);
	}

	Polygon2D
	Polygon2D::triangle (r_type x1, r_type y1,
						 r_type x2, r_type y2,
						 r_type x3, r_type y3,
						 bool filled, const Color& c)
	{
		r_type x = (x1 + x2 + x3) / 3;
		r_type y = (y1 + y2 + y3) / 3;
		std::vector<r_type> ver = { x1, y1, x2, y2, x3, y3 };
		return Polygon2D (x, y, ver, filled, c);
	}

	Polygon2D
	Polygon2D::rectangle (r_type x, r_type y,
						  r_type width, r_type height,
						  bool filled, const Color& c)
	{
		r_type w2 = width / 2;
		r_type h2 = height / 2;
		std::vector<r_type> ver = { x - w2, y - h2,
									x + w2, y - h2,
									x + w2, y + h2,
									x - w2, y + h2 };
		return Polygon2D (x, y, ver, filled, c);
	}


	Polygon2D::Polygon2D (r_type x, r_type y,
						  const std::vector<r_type>& vertices,
						  bool filled, const Color& c,
						  Collider2D* collider)
		: Object2D (collider),  x_ (x), y_ (y), vertices_ (vertices),
		filled_ (filled), color_ (c)
	{
		assert (vertices.size () % 2 == 0);
	}


	bool
	Polygon2D::is_filled () const
	{
		return filled_;
	}

	void
	Polygon2D::set_filled (bool filled)
	{
		filled_ = filled;
	}

	size_t
	Polygon2D::size () const
	{
		return vertices_.size () / 2;
	}

	Vector2D
	Polygon2D::vertex_get (size_t i) const
	{
		assert (i < size ());
		return Vector2D (vertices_[2 * i], vertices_[2 * i + 1]);

	}

	void
	Polygon2D::vertex_set (size_t i, Vector2D v)
	{
		assert (i < size ());
		vertices_[2 * i] = v.x_get ();
		vertices_[2 * i + 1] = v.y_get ();
	}

	void
	Polygon2D::vertex_set (size_t i, r_type x, r_type y)
	{
		assert (i < size ());
		vertices_[2 * i] = x;
		vertices_[2 * i + 1] = y;
	}

	void
	Polygon2D::rotate_around_vertex (size_t i, r_type angle)
	{
		assert (i < size ());

		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		r_type x = vertices_[i * 2];
		r_type y = vertices_[i * 2 + 1];

		for (size_t i = 0; i < vertices_.size (); i += 2)
		{
			if (i * 2 != i)
			{
				r_type t_x = vertices_[i];
				vertices_[i] = x + (t_x - x) * c
					- (vertices_[i + 1] - y) * s;
				vertices_[i + 1] = y + (t_x - x) * s
					+ (vertices_[i + 1] - y) * c;
			}
		}

		r_type t_x = x_;
		x_ = x + (t_x - x) * c - (y_ - y) * s;
		y_ = y + (t_x - x) * s + (y_ - y) * c;
	}

	Color
	Polygon2D::color_get () const
	{
		return color_;
	}

	void
	Polygon2D::color_set (const Color& c)
	{
		color_ = c;
	}


	r_type
	Polygon2D::x_get () const
	{
		return x_;
	}

	r_type
	Polygon2D::y_get () const
	{
		return y_;
	}

	void
	Polygon2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		r_type dx = x - x_;
		x_ = x;
		for (size_t i = 0; i < vertices_.size (); i += 2)
			vertices_[i] += dx;
	}

	void
	Polygon2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		r_type dy = y - y_;
		for (size_t i = 1; i < vertices_.size (); i += 2)
			vertices_[i] += dy;
	}

	void
	Polygon2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
		for (size_t i = 0; i < vertices_.size (); i += 2)
			vertices_[i] += dx;
	}

	void
	Polygon2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
		for (size_t i = 1; i < vertices_.size (); i += 2)
			vertices_[i] += dy;
	}

	void
	Polygon2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
		for (size_t i = 0; i < vertices_.size (); i += 2)
		{
			vertices_[i] += dx;
			vertices_[i + 1] += dy;
		}
	}

	void
	Polygon2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		r_type dx = x - x_;
		r_type dy = y - y_;
		x_ = x;
		y_ = y;
		for (size_t i = 0; i < vertices_.size (); i += 2)
		{
			vertices_[i] += dx;
			vertices_[i + 1] += dy;
		}
	}

	void
	Polygon2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		for (size_t i = 0; i < vertices_.size (); i += 2)
		{
			vertices_[i] = x_ + (vertices_[i] - x_) * sx;
			vertices_[i+1] = y_ + (vertices_[i + 1] - y_) * sy;
		}
	}

	void
	Polygon2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
		for (size_t i = 0; i < vertices_.size (); i += 2)
		{
			r_type t_x = vertices_[i];
			vertices_[i] = x_ + (t_x - x_) * c
				- (vertices_[i + 1] - y_) * s;
			vertices_[i+1] = y_ + (t_x - x_) * s
				+ (vertices_[i + 1] - y_) * c;
		}
	}

	void
	Polygon2D::draw (Canvas2D *cv, r_type dx, r_type dy,
					 r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		cv->draw_color_set (color_);
		size_t n = vertices_.size ();

		for (size_t i = 0; i < n; i += 2)
		{
			r_type x1 = dx + vertices_[i] * sx;
			r_type y1 = dy + vertices_[i + 1] * sy;
			r_type x2 = dx + vertices_[(i + 2) % n] * sx;
			r_type y2 = dy + vertices_[(i + 3) % n] * sy;
			cv->draw_line (x1, y1, x2, y2);
		}
	}

	void
	Polygon2D::collider_set_default ()
	{
	    collider_set (new PolygonCollider2D (x_, y_, vertices_));
	}

}