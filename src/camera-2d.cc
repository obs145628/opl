#include "camera-2d.hh"

namespace opl
{

	Camera2D::Camera2D (const Color& bg)
		: enabled_ (true), bg_ (bg)
	{

	}

	bool
	Camera2D::is_enabled () const
	{
		return enabled_;
	}

	void
	Camera2D::set_enabled (bool enabled)
	{
		enabled_ = enabled;
	}

	void
	Camera2D::enable ()
	{
		enabled_ = true;
	}

	void
	Camera2D::disable ()
	{
		enabled_ = false;
	}

	Color
	Camera2D::background_get () const
	{
		return bg_;
	}

	void
	Camera2D::background_set (const Color& bg)
	{
		bg_ = bg;
	}


	Vector2D
	Camera2D::src_position_get () const
	{
		return Vector2D (src_x_get (), src_y_get ());
	}

	Vector2D
	Camera2D::src_size_get () const
	{
		return Vector2D (src_width_get (), src_height_get ());
	}

	Vector2D
	Camera2D::dst_position_get () const
	{
		return Vector2D (dst_x_get (), dst_y_get ());
	}

	Vector2D
	Camera2D::dst_size_get () const
	{
		return Vector2D (dst_width_get (), dst_height_get ());
	}

}