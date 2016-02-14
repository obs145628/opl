/** @file Camera2D class definition
 */

#ifndef CAMERA_2D_HH_
# define CAMERA_2D_HH_

#include "types.hh"
#include "vector-2d.hh"
#include "color.hh"

namespace opl
{

	/// Scene 2D Camera
	class Camera2D
	{

	public:
		Camera2D (const Color& bg = Color::WHITE);
		virtual ~Camera2D () = default;

		bool
		is_enabled () const;

		void
		set_enabled (bool enabled);

		void
		enable ();

		void
		disable ();

		Color
		background_get () const;

		void
		background_set (const Color& bg);

		///x center position on the scene
		virtual r_type
		src_x_get () const = 0;

		///y center position on the scene
		virtual r_type
		src_y_get () const = 0;

		virtual Vector2D
		src_position_get () const;

		///with of the captured rectangle in the scene
		virtual r_type
		src_width_get () const = 0;

		///height of the captured rectangle in the scene
		virtual r_type
		src_height_get () const = 0;

		virtual Vector2D
		src_size_get () const;


		///x top-left position on the screen
		virtual r_type
		dst_x_get () const = 0;

		///y top-left position on the screen
		virtual r_type
		dst_y_get () const = 0;

		virtual Vector2D
		dst_position_get () const;

		///with of the rendered rectangle on the screen
		virtual r_type
		dst_width_get () const = 0;

		///height of the rendered rectangle on the screen
		virtual r_type
		dst_height_get () const = 0;

		virtual Vector2D
		dst_size_get () const;

		virtual void
		screen_resize (size_t w, size_t h) = 0;

	private:
		bool enabled_;
		Color bg_;




	};

}

#endif //!CAMERA_2D_HH_