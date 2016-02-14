/** @file StaticCamera2D class definition
 */

#ifndef STATIC_CAMERA_2D_HH_
# define STATIC_CAMERA_2D_HH_

# include "camera-2d.hh"

namespace opl
{

	class StaticCamera2D: public Camera2D
	{

	public:

		StaticCamera2D (r_type src_x, r_type src_y,
						  r_type screen_w, r_type screen_h,
						  const Color& bg = Color::WHITE);

		virtual r_type
		src_x_get () const override;

		virtual r_type
		src_y_get () const override;

		virtual r_type
		src_width_get () const override;

		virtual r_type
		src_height_get () const override;

		virtual r_type
		dst_x_get () const override;

		virtual r_type
		dst_y_get () const override;

		virtual r_type
		dst_width_get () const override;

		virtual r_type
		dst_height_get () const override;

		virtual void
		screen_resize (size_t w, size_t h) override;

	private:
		r_type src_x_;
		r_type src_y_;
		r_type screen_w_;
		r_type screen_h_;



	};

}


# endif //!STATIC_CAMERA_2D_HH_