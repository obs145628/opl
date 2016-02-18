/** @file Button2D class definition
 */

#ifndef BUTTON_2D_HH_
# define BUTTON_2D_HH_

# include <string>
# include "object-2d.hh"
# include "color.hh"
# include "types.hh"
# include "label-2d.hh"
# include "rectangle-2d.hh"
# include "em-component-2d.hh"

namespace opl
{

	///2D sdl object reprenting a clickable button with label
	class Button2D: public Object2D
	{

	public:

		Button2D (const std::string& text, r_type x, r_type y, r_type size,
				  r_type w, r_type h);

		virtual ~Button2D ();

		std::string
		text_get () const;

		void
		text_set (const std::string& text);

		r_type
		size_get () const;

		void
		size_set (r_type size);

		std::string
		font_get () const;

		void
		font_set (const std::string& font);

		r_type
		width_get () const;

		void
		width_set (r_type width);

		r_type
		height_get () const;

		void
		height_set (r_type height);

		Color
		text_color_get () const;

		void
		text_color_set (const Color& c);

		Color
		bg_color_get () const;

		void
		bg_color_set (const Color &c);

		Color
		border_color_get () const;

		void
		border_color_set (const Color& c);

		r_type
		text_width_get () const;

		r_type
		text_height_get () const;

		bool
		is_clickable () const;

		void
		clickable_set (bool clickable);

		bool
		is_mouse_on () const;

		//Returns if the mouse entered on the current frame
		bool
		is_mouse_entered () const;

		///Returns if the mouse exited on the current frame
		bool
		is_mouse_exited () const;

		///Returns if button is down with mouse on
		bool
		is_button_down (int code = Mouse2D::LEFT) const;

		///Returns if button is pressed on object on the current frame
		bool
		is_button_pressed (int code = Mouse2D::LEFT) const;

		///Returns if button is released on object on the current frame
		bool
		is_button_released (int code = Mouse2D::LEFT) const;

		///Returns if button is half-clicked (down but not released)
		bool
		is_button_clickdown (int code = Mouse2D::LEFT) const;

		///Returns if button is pressed then released
		bool
		is_button_clicked (int code = Mouse2D::LEFT) const;


		virtual r_type
		x_get () const override;

		virtual r_type
		y_get () const override;

		virtual void
		x_set (r_type x) override;

		virtual void
		y_set (r_type y) override;

		virtual void
		x_move (r_type dx) override;

		virtual void
		y_move (r_type dy) override;

		virtual void
		move (r_type dx, r_type dy) override;

		virtual void
		move_to (r_type x, r_type y) override;


		virtual void
		scale (r_type sx, r_type sy) override;

		virtual void
		rotate (r_type angle) override;

		virtual void
		draw (Canvas2D *cv, r_type dx, r_type dy,
			  r_type sx, r_type sy) override;

		virtual void
		will_update (const SceneInfos2D& infos) override;

		virtual void
		did_update (const SceneInfos2D& infos) override;

	private:
		bool clickable_;
		Label2D* label_;
		Rectangle2D* background_;
		Rectangle2D* border_;
		EmComponent2D* emc_;



	};

}

#endif //!BUTTON_2D_HH_