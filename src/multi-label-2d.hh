/** @file MultiLabel2D class definition
 */

#ifndef MULTI_LABEL_2D_HH_
# define MULTI_LABEL_2D_HH_

# include <string>
# include <vector>
# include "object-2d.hh"


namespace opl
{

	///Dsiplay 2D text on multiple lignes
	class MultiLabel2D: public Object2D
	{

		public:

		MultiLabel2D (const std::string& str, r_type x, r_type y, r_type size,
				 const std::string& font, r_type w, const Color& c,
				 Collider2D* collider = nullptr);

		virtual ~MultiLabel2D () = default;

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

		Color
		color_get () const;

		void
		color_set (const Color& c);


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
		r_type width_;
		Color color_;
		r_type angle_;
		r_type hline_;

		std::vector<std::string> texts_;
		Canvas2D* canvas_;
		r_type height_;


		Vector2D
		text_size_ (const std::string& text);

		void
		update_text_ ();


	};

}


#endif //!MULTI_LABEL_2D_HH_