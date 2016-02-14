#include <cassert>
#include "sprite-2d.hh"

namespace opl
{

	Sprite2D::Sprite2D (const std::string& path, r_type x, r_type y,
						r_type w, r_type h, const Color& c,
						Collider2D* collider)
		: Object2D (collider), path_ (path), x_ (x), y_ (y), w_ (w), h_ (h),
		  color_ (c), angle_ (0)
	{

	}


	std::string
	Sprite2D::path_get () const
	{
		return path_;
	}

	void
	Sprite2D::path_set (const std::string& path)
	{
		path_ = path;
	}

	r_type
	Sprite2D::width_get () const
	{
		return w_;
	}

	void
	Sprite2D::width_set (r_type w)
	{
		w_ = w;
	}

	r_type
	Sprite2D::height_get () const
	{
		return h_;
	}

	void
	Sprite2D::height_set (r_type h)
	{
		h_ = h;
	}

	Color
	Sprite2D::color_get () const
	{
		return color_;
	}

	void
	Sprite2D::color_set (const Color& c)
	{
		color_ = c;
	}


	r_type
	Sprite2D::x_get () const
	{
		return x_;
	}

	r_type
	Sprite2D::y_get () const
	{
		return y_;
	}

	void
	Sprite2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		x_ = x;
	}

	void
	Sprite2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		y_ = y;
	}


	void
	Sprite2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
	}

	void
	Sprite2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
	}

	void
	Sprite2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
	}

	void
	Sprite2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		x_ = x;
		y_ = y;
	}

	void
	Sprite2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		w_ *= sx;
		h_ *= sy;
	}

	void
	Sprite2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
		angle_ += angle;
	}

	void
	Sprite2D::draw (Canvas2D *cv, r_type dx, r_type dy,
					r_type sx, r_type sy)
	{

		Object2D::draw (cv, dx, dy, sx, sy);

		r_type w = w_ * sx;
		r_type h = h_ * sy;
		r_type x = dx + x_ * sx - w / 2;
		r_type y = dy + y_ * sy - h / 2;


		cv->draw_sprite (path_, x, y, w, h, angle_, color_);
	}

}