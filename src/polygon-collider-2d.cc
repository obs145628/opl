#include <cmath>
#include "polygon-collider-2d.hh"

namespace opl
{
	const size_t PolygonCollider2D::ID = 4;

	PolygonCollider2D::PolygonCollider2D (r_type x, r_type y,
										  const std::vector<r_type>& vertices)
		: Collider2D (), x_ (x), y_ (y), vertices_ (vertices)
	{

	}

	r_type
	PolygonCollider2D::x_get () const
	{
		return x_;
	}

	r_type
	PolygonCollider2D::y_get () const
	{
		return y_;
	}

	std::vector<r_type>
	PolygonCollider2D::vertices_get () const
	{
		return vertices_;
	}

	void
	PolygonCollider2D::x_set (r_type x)
	{
		r_type dx = x - x_;
		x_ = x;
		for (size_t i = 0; i < vertices_.size (); i += 2)
			vertices_[i] += dx;
	}

	void
	PolygonCollider2D::y_set (r_type y)
	{
	    r_type dy = y - y_;
		for (size_t i = 1; i < vertices_.size (); i += 2)
			vertices_[i] += dy;
	}

	void
	PolygonCollider2D::x_move (r_type dx)
	{
	    x_ += dx;
		for (size_t i = 0; i < vertices_.size (); i += 2)
			vertices_[i] += dx;
	}

	void
	PolygonCollider2D::y_move (r_type dy)
	{
	    y_ += dy;
		for (size_t i = 1; i < vertices_.size (); i += 2)
			vertices_[i] += dy;
	}

	void
	PolygonCollider2D::move (r_type dx, r_type dy)
	{
	    x_ += dx;
		y_ += dy;
		for (size_t i = 0; i < vertices_.size (); i += 2)
		{
			vertices_[i] += dx;
			vertices_[i + 1] += dy;
		}
	}

	void
	PolygonCollider2D::move_to (r_type x, r_type y)
	{
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
	PolygonCollider2D::scale (r_type sx, r_type sy)
	{
		for (size_t i = 0; i < vertices_.size (); i += 2)
		{
			vertices_[i] = x_ + (vertices_[i] - x_) * sx;
			vertices_[i+1] = y_ + (vertices_[i + 1] - y_) * sy;
		}
	}

	void
	PolygonCollider2D::rotate (r_type angle)
	{
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

	size_t
	PolygonCollider2D::id_get () const
	{
		return ID;
	}
}