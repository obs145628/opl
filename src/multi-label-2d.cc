#include <cassert>
#include "multi-label-2d.hh"
#include "empty-object-2d.hh"
#include "label-2d.hh"


namespace opl
{

	MultiLabel2D::MultiLabel2D (const std::string& str, r_type x, r_type y,
								r_type size,
								const std::string& font, r_type w,
								const Color& c,
								Collider2D* collider)
		: Object2D (collider), text_ (str), x_ (x), y_ (y), size_ (size),
		  font_ (font),  width_ (w), color_ (c), angle_ (0), hline_ (2),
		  texts_ ()
	{
		canvas_ = Canvas2D::instance ();
		update_text_ ();
	}

	std::string
	MultiLabel2D::text_get () const
	{
		return text_;
	}

	void
	MultiLabel2D::text_set (const std::string& text)
	{
		text_ = text;
		update_text_ ();
	}

	r_type
	MultiLabel2D::size_get () const
	{
		return size_;
	}

	void
	MultiLabel2D::size_set (r_type size)
	{
		size_ = size;
		update_text_ ();
	}

	std::string
	MultiLabel2D::font_get () const
	{
		return font_;
	}

	void
	MultiLabel2D::font_set (const std::string& font)
	{
		font_ = font;
		update_text_ ();
	}

	r_type
	MultiLabel2D::width_get () const
	{
		return width_;
	}

	void
	MultiLabel2D::width_set (r_type width)
	{
		width_ = width;
		update_text_ ();
	}

	r_type
	MultiLabel2D::height_get () const
	{
		return height_;
	}

	Color
	MultiLabel2D::color_get () const
	{
		return color_;
	}

	void
	MultiLabel2D::color_set (const Color& c)
	{
		color_ = c;
	}


	r_type
	MultiLabel2D::x_get () const
	{
		return x_;
	}

	r_type
	MultiLabel2D::y_get () const
	{
		return y_;
	}

	void
	MultiLabel2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		x_ = x;
	}

	void
	MultiLabel2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		y_ = y;
	}

	void
	MultiLabel2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		x_ += dx;
	}

	void
	MultiLabel2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		y_ += dy;
	}

	void
	MultiLabel2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		x_ += dx;
		y_ += dy;
	}

	void
	MultiLabel2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		x_ = x;
		y_ = y;
	}


	void
	MultiLabel2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);

		size_ *= sx;
	}

	void
	MultiLabel2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
		angle_ += angle;
	}

	void
	MultiLabel2D::draw (Canvas2D *cv, r_type dx, r_type dy,
		  r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);

		EmptyObject2D* parent = new EmptyObject2D (x_, y_);

		r_type nr = static_cast<r_type> (texts_.size ());
		r_type middle = nr / 2;
		r_type part_h = height_ / nr;

		for (size_t i = 0; i < texts_.size (); ++i)
		{
			r_type diff = static_cast<r_type> (i) - middle + 0.5;
			r_type dy = part_h * diff;
			Label2D* line = new Label2D (texts_[i], 0, dy, size_,
										 font_, color_);
			parent->insert_relative_child(line);
		}


		parent->rotate (angle_);
		parent->draw (cv, dx, dy, sx, sy);
		delete parent;
	}

	Vector2D
	MultiLabel2D::text_size_ (const std::string& text)
	{
		return canvas_->text_size_get (text, font_, size_);
	}

	void
	MultiLabel2D::update_text_ ()
	{
		texts_.clear ();

		r_type total_width = text_size_ (text_).x_get ();
		r_type c_width = total_width / text_.size ();
		r_type parts_len = width_ / c_width;

		size_t parts_pred = static_cast<size_t> (parts_len - 1);

		size_t current = 0;
		height_ = 0;

		while (current != text_.size())
		{
			size_t part_len = current + parts_pred > text_.size () ?
				text_.size () - current : parts_pred;

			bool last_line = current + part_len == text_.size ();

			while (true) {

				size_t n = 0;
				size_t sub_size = part_len;
				size_t sub_d = part_len;
				while (n < part_len)
				{
					char c = text_[current + n];
					if (c == ' ' && !last_line)
					{
						sub_size = n;
						sub_d  = sub_size + 1;
					}
					if (c == '\n')
					{
					    sub_size = n;
						sub_d  = sub_size + 1;
						break;
					}
					++n;
				}

				std::string part = text_.substr (current, sub_size);

				Vector2D size = text_size_ (part);

				if (size.x_get () > width_)
				{
					part_len--;
				}
				else
				{
					texts_.push_back (part);
					height_ += size.y_get ();
					current += sub_d;
					break;
				}
			}
		}


		height_ += hline_ * (text_.size () - 1);
	}

}