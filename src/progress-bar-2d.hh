/** @file ProgressBar2D class definition
 */

#ifndef PROGRESS_BAR_2D_HH_
# define PROGRESS_BAR_2D_HH_

# include "object-2d.hh"
# include "rectangle-2d.hh"
# include "color.hh"

namespace opl
{

	///2D sdl object representin a progress bar
	class ProgressBar2D: public Object2D
	{

	public:

		ProgressBar2D (r_type x, r_type y, r_type w, r_type h, r_type value,
					   const Color& border_color, const Color& empty_color,
					   const Color& full_color);

		virtual ~ProgressBar2D ();

		r_type
		width_get () const;

		void
		width_set (r_type width);

		r_type
		height_get () const;

		void
		height_set (r_type height);

		r_type
		value_get () const;

		void
		value_set(r_type value);

		Color
		border_color_get () const;

		void
		border_color_set (const Color& c);

		Color
		empty_color_get () const;

		void
		empty_color_set (const Color& c);

		Color
		full_color_get () const;

		void
		full_color_set (const Color& c);

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
		Color empty_color_;
		Color full_color_;
		Rectangle2D* border_;
		Rectangle2D* bar_;

		void
		width_update_ (r_type value);

		void
		color_update_ (r_type value);


	};

}

#endif //!PROGRESS_BAR_2D_HH_