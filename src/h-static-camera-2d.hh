/** @file HStaticCamera2D class definition
 */

#ifndef H_STATIC_CAMERA_2D_HH_
# define H_STATIC_CAMERA_2D_HH_

# include "camera-2d.hh"

namespace opl
{

	class HStaticCamera2D: public Camera2D
	{

	public:

		HStaticCamera2D (r_type src_x, r_type src_y,
						 r_type screen_w, r_type screen_h,
						 r_type height,
						 const Color& bg = Color::WHITE);

		r_type
		height_get () const;

		void
		height_set (r_type height);

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
		r_type height_;
		r_type ratio_;



	};

}


# endif //!H_STATIC_CAMERA_2D_HH_