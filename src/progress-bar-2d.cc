#include <cassert>
#include <cmath>
#include "progress-bar-2d.hh"

namespace opl
{

	ProgressBar2D::ProgressBar2D (r_type x, r_type y, r_type w, r_type h,
								  r_type value, const Color& border_color,
								  const Color& empty_color,
								  const Color& full_color)
		: empty_color_ (empty_color), full_color_ (full_color)
	{
		border_ = new Rectangle2D (x, y, w, h, false, border_color);
		bar_ = new Rectangle2D (x, y, w, h, true, full_color);
		value_set (value);
	}

	ProgressBar2D::~ProgressBar2D ()
	{
		delete border_;
		delete bar_;
	}

    r_type
	ProgressBar2D::width_get () const
	{
		return border_->width_get ();
	}

	void
	ProgressBar2D::width_set (r_type width)
	{
		r_type value = value_get ();
		border_->width_set (width);
		width_update_ (value);
	}

	r_type
	ProgressBar2D::height_get () const
	{
		return border_->height_get ();
	}

	void
	ProgressBar2D::height_set (r_type height)
	{
		border_->height_set (height);
		bar_->height_set (height);
	}

	r_type
	ProgressBar2D::value_get () const
	{
		return bar_->width_get () / border_->width_get ();
	}

	void
	ProgressBar2D::value_set (r_type value)
	{
		assert (value >= 0 && value <= 1);
		width_update_ (value);
		color_update_ (value);
	}

	Color
	ProgressBar2D::border_color_get () const
	{
		return border_->color_get ();
	}

	void
	ProgressBar2D::border_color_set (const Color& c)
	{
		border_->color_set (c);
	}

	Color
	ProgressBar2D::empty_color_get () const
	{
		return empty_color_;
	}

	void
	ProgressBar2D::empty_color_set (const Color& c)
	{
		empty_color_ = c;
		color_update_ (value_get ());
	}

	Color
	ProgressBar2D::full_color_get () const
	{
		return full_color_;
	}

	void
	ProgressBar2D::full_color_set (const Color& c)
	{
		full_color_ = c;
		color_update_ (value_get ());
	}

	r_type
	ProgressBar2D::x_get () const
	{
		return bar_->x_get ();
	}

	r_type
	ProgressBar2D::y_get () const
	{
		return bar_->y_get ();
	}

	void
	ProgressBar2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		border_->x_set (x);
		bar_->x_set (x);
	}

	void
	ProgressBar2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		border_->y_set (y);
		bar_->y_set (y);
	}

	void
	ProgressBar2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		border_->x_move (dx);
		bar_->x_move (dx);
	}

	void
	ProgressBar2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		border_->y_move (dy);
		bar_->y_move (dy);
	}

	void
	ProgressBar2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		border_->move (dx, dy);
		bar_->move (dx, dy);
	}

	void
	ProgressBar2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
		border_->move_to (x, y);
		bar_->move_to (x, y);
	}

	void
	ProgressBar2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		border_->scale (sx, sy);
		bar_->scale (sx, sy);
	}

	void
	ProgressBar2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
		border_->rotate (angle);
		bar_->rotate (angle);
	}

	void
	ProgressBar2D::draw (Canvas2D *cv, r_type dx, r_type dy,
						 r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		bar_->draw (cv, dx, dy, sx, sy);
		border_->draw (cv, dx, dy, sx, sy);
	}



	void
	ProgressBar2D::width_update_ (r_type value)
	{
		bar_->width_set (value * border_->width_get ());
	}

	void
	ProgressBar2D::color_update_ (r_type value)
	{
		bar_->color_set (Color::progression (empty_color_, full_color_,
											 value));
	}

}