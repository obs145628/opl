#include <algorithm>
#include "fixed-camera-2d.hh"

namespace opl
{

	FixedCamera2D::FixedCamera2D (r_type src_x, r_type src_y,
								  r_type screen_w, r_type screen_h,
								  r_type width, r_type height,
								  const Color& bg)
		: Camera2D (bg), src_x_ (src_x), src_y_ (src_y),
		  width_ (width), height_ (height)
	{
		screen_resize (screen_w, screen_h);
	}

	r_type
	FixedCamera2D::width_get () const
	{
		return width_;
	}

	void
	FixedCamera2D::width_set (r_type width)
	{
		width_ = width;
		screen_resize (screen_w_, screen_h_);
	}

	r_type
	FixedCamera2D::height_get () const
	{
		return height_;
	}

	void
	FixedCamera2D::height_set (r_type height)
	{
		height_ = height;
		screen_resize (screen_w_, screen_h_);
	}

	r_type
	FixedCamera2D::src_x_get () const
	{
		return src_x_;
	}

	r_type
	FixedCamera2D::src_y_get () const
	{
		return src_y_;
	}

	r_type
	FixedCamera2D::src_width_get () const
	{
		return width_;
	}

	r_type
	FixedCamera2D::src_height_get () const
	{
		return height_;
	}

	r_type
	FixedCamera2D::dst_x_get () const
	{
		return (screen_w_ - width_ * ratio_) / 2;
	}

	r_type
	FixedCamera2D::dst_y_get () const
	{
		return (screen_h_ - height_ * ratio_) / 2;
	}

	r_type
	FixedCamera2D::dst_width_get () const
	{
		return width_ * ratio_;
	}

	r_type
	FixedCamera2D::dst_height_get () const
	{
		return height_ * ratio_;
	}

	void
	FixedCamera2D::screen_resize (size_t w, size_t h)
	{
		screen_w_ = w;
		screen_h_ = h;
		r_type x_ratio = screen_w_ / width_;
		r_type y_ratio = screen_h_ / height_;
		ratio_ = std::min (x_ratio, y_ratio);
	}

}