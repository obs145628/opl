#include "h-static-camera-2d.hh"

namespace opl
{

	HStaticCamera2D::HStaticCamera2D (r_type src_x, r_type src_y,
									  r_type screen_w, r_type screen_h,
									  r_type height,
									  const Color& bg)
		: Camera2D (bg), src_x_ (src_x), src_y_ (src_y), height_ (height)
	{
		screen_resize (screen_w, screen_h);
	}

	r_type
	HStaticCamera2D::height_get () const
	{
		return height_;
	}

	void
	HStaticCamera2D::height_set (r_type height)
	{
		height_ = height;
		screen_resize (screen_w_, screen_h_);
	}

	r_type
	HStaticCamera2D::src_x_get () const
	{
		return src_x_;
	}

	r_type
	HStaticCamera2D::src_y_get () const
	{
		return src_y_;
	}

	r_type
	HStaticCamera2D::src_width_get () const
	{
		return screen_w_ / ratio_;
	}

	r_type
	HStaticCamera2D::src_height_get () const
	{
		return height_;
	}

	r_type
	HStaticCamera2D::dst_x_get () const
	{
		return 0;
	}

	r_type
	HStaticCamera2D::dst_y_get () const
	{
		return 0;
	}

	r_type
	HStaticCamera2D::dst_width_get () const
	{
		return screen_w_;
	}

	r_type
	HStaticCamera2D::dst_height_get () const
	{
		return screen_h_;
	}

	void
	HStaticCamera2D::screen_resize (size_t w, size_t h)
	{
		screen_w_ = w;
		screen_h_ = h;
		ratio_ = screen_h_ / height_;
	}

}