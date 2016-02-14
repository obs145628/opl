/** @file Label2D class definition
 */

#ifndef LABEL_2D_HH_
# define LABEL_2D_HH_

# include <string>
# include "object-2d.hh"
# include "color.hh"
# include "types.hh"

namespace opl
{

	///2D sdl object reprenting a text label
	class Label2D: public Object2D
	{

	public:

		Label2D (const std::string& text, r_type x, r_type y, r_type size,
				 const std::string& font, const Color& c,
				 Collider2D* collider = nullptr);
		virtual ~Label2D () = default;

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

		Color
		color_get () const;

		void
		color_set (const Color& c);

		r_type
		width_get () const;

		r_type
		height_get () const;


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

	private:
		std::string text_;
		r_type x_;
		r_type y_;
		r_type size_;
		std::string font_;
		Color color_;

		r_type angle_;
		r_type w_;
		r_type h_;

		void
		size_update_ ();


	};

}

#endif //!PIXEL_2D_HH_