#include <cassert>
#include "label-2d.hh"

namespace opl
{

	Label2D::Label2D (const std::string& text, r_type x, r_type y,
					  r_type size, const std::string& font, const Color& c,
					  Collider2D* collider)
		: Object2D (collider), text_ (text), x_ (x), y_ (y), size_ (size),
		  font_ (font), color_ (c), angle_ (0)
	{
		size_update_ ();
	}

	std::string
	Label2D::text_get () const
	{
		return text_;
	}

	void
	Label2D::text_set (const std::string& text)
	{
		text_ = text;
		size_update_();
	}

	r_type
	Label2D::size_get () const
	{
		return size_;
	}

	void
	Label2D::size_set (r_type size)
	{
		size_ = size;
		size_update_ ();
	}

	std::string
	Label2D::font_get () const
	{
		return font_;
	}

	void
	Label2D::font_set (const std::string& font)
	{
		font_ = font;
		size_update_ ();
	}

	Color
	Label2D::color_get () const
	{
		return color_;
	}

	void
	Label2D::color_set (const Color& c)
	{
		color_ = c;
	}

	r_type
	Label2D::width_get () const
	{
		return w_;
	}

	r_type
	Label2D::height_get () const
	{
		return h_;
	}


	r_type
	Label2D::x_get () const
	{
		return x_;
	}

	r_type
	Label2D::y_get () const
	{
		return y_;
	}

	void
	Label2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		x_ = x;
	}

	void
	Label2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		y_ = y;
	}

	void
	Label2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
	}

	void
	Label2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
	}

	void
	Label2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
	}

	void
	Label2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		x_ = x;
		y_ = y;
	}


	void
	Label2D::scale (r_type sx, r_type sy)
	{
		assert (sx == sy);
		Object2D::scale (sx, sy);

		size_ *= sx;
		size_update_ ();
	}

	void
	Label2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
		angle_ += angle;
	}

	void
	Label2D::draw (Canvas2D *cv, r_type dx, r_type dy,
		  r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		assert (sx == sy);
		r_type x_c = dx + x_ * sx;
		r_type y_c = dy + y_ * sy;
		r_type size = size_ * sx;

		Vector2D dims = cv->text_size_get(text_, font_ ,size);
		r_type x = x_c - dims.x_get () / 2;
		r_type y = y_c - dims.y_get () / 2;

		cv->draw_text(text_, x, y, angle_, font_, color_, size);
	}

	void
	Label2D::size_update_ ()
	{
	    Vector2D dims = Canvas2D::instance ()->text_size_get(text_, font_,
															 size_);
		w_ = dims.x_get ();
		h_ = dims.y_get ();
	}

}