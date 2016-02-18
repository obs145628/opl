/** @file TextField2D Class definition
 */

#ifndef TEXT_FIELD_HH_
# define TEXT_FIELD_HH_

# include <string>
# include "object-2d.hh"
# include "color.hh"
# include "types.hh"
# include "label-2d.hh"
# include "rectangle-2d.hh"
# include "em-component-2d.hh"
# include "keyboard-2d.hh"


namespace opl
{
	///SDL 2D object for handling inline text input
	class TextField2D: public Object2D
	{

	public:

		TextField2D (const std::string& text, r_type x, r_type y, r_type size,
				  r_type w, r_type h);

		virtual ~TextField2D ();

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
		is_editable () const;

		void
		editable_set (bool editable);

		bool
		has_focus () const;

		void
		focus_set (bool focus);

		bool
		is_validated () const;


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
		bool editable_;
		int cursor_;
		r_type counter_;
		r_type cursor_speed_;
		std::string text_;
		bool validated_;
		Label2D* label_;
		Rectangle2D* background_;
		Rectangle2D* border_;
		EmComponent2D* emc_;
		Keyboard2D* keyboard_;

		void
		field_update_ ();

		void
		move_left_ ();

		void
		move_right_ ();

		void
		insert_text_ (const std::string& text);

		void
		remove_left_ ();

		void
		remove_right_ ();


	};
}

#endif //!TEXT_FIELD_HH_