#include <cassert>
#include "button-2d.hh"

#define OPL_BUTTON_BASE 0x00f4f4f4
#define OPL_BUTTON_OVER 0x00e2e2e2
#define OPL_BUTTON_FOCUSED 0x00cfcfcf
#define OPL_BUTTON_DISABLED 0x00505050

namespace opl
{


	Button2D::Button2D (const std::string& text, r_type x, r_type y,
						r_type size, r_type w, r_type h)
		: Object2D (), clickable_ (true)
	{
		label_ = new Label2D (text, x, y, size, "lazy", Color::BLACK);
		background_ = new Rectangle2D (x, y, w, h, true,
									   Color (OPL_BUTTON_BASE));
		background_->collider_set_default ();
		border_ = new Rectangle2D (x, y, w, h, false, Color::BLACK);
		emc_ = new EmComponent2D ();
		background_->component_insert (emc_);
	}

	Button2D::~Button2D ()
	{
		delete label_;
		delete background_;
		delete border_;
	}

	std::string
	Button2D::text_get () const
	{
		return label_->text_get ();
	}

	void
	Button2D::text_set (const std::string& text)
	{
		label_->text_set (text);
	}

	r_type
	Button2D::size_get () const
	{
		return label_->size_get ();
	}

	void
	Button2D::size_set (r_type size)
	{
		label_->size_set (size);
	}

	std::string
	Button2D::font_get () const
	{
		return label_->font_get ();
	}

	void
	Button2D::font_set (const std::string& font)
	{
		label_->font_set (font);
	}

	r_type
	Button2D::width_get () const
	{
		return background_->width_get ();
	}

	void
	Button2D::width_set (r_type width)
	{
		background_->width_set (width);
		border_->width_set (width);
	}

	r_type
	Button2D::height_get () const
	{
		return background_->height_get ();
	}

	void
	Button2D::height_set (r_type height)
	{
		background_->height_set (height);
		border_->height_set (height);
	}

	Color
	Button2D::text_color_get () const
	{
		return label_->color_get ();
	}

	void
	Button2D::text_color_set (const Color& c)
	{
		label_->color_set (c);
	}

	Color
	Button2D::bg_color_get () const
	{
		return background_->color_get ();
	}

	void
	Button2D::bg_color_set (const Color &c)
	{
		background_->color_set (c);
	}

	Color
	Button2D::border_color_get () const
	{
		return border_->color_get ();
	}

	void
	Button2D::border_color_set (const Color& c)
	{
		border_->color_set (c);
	}

	r_type
	Button2D::text_width_get () const
	{
		return label_->width_get ();
	}

	r_type
	Button2D::text_height_get () const
	{
		return label_->height_get ();
	}

	bool
	Button2D::is_clickable () const
	{
		return clickable_;
	}

	void
	Button2D::clickable_set (bool clickable)
	{
		clickable_ = clickable;
	}

	bool
	Button2D::is_mouse_on () const
	{
		return emc_->is_mouse_on ();
	}

	bool
	Button2D::is_mouse_entered () const
	{
		return emc_->is_mouse_entered ();
	}


	bool
	Button2D::is_mouse_exited () const
	{
		return emc_->is_mouse_exited ();
	}


	bool
	Button2D::is_button_down (int code) const
	{
		return clickable_ && emc_->is_button_down (code);
	}

	bool
	Button2D::is_button_pressed (int code) const
	{
		return clickable_ && emc_->is_button_pressed (code);
	}

	bool
	Button2D::is_button_released (int code) const
	{
		return clickable_ && emc_->is_button_released (code);
	}

	bool
	Button2D::is_button_clickdown (int code) const
	{
		return clickable_ && emc_->is_button_clickdown (code);
	}

	bool
	Button2D::is_button_clicked (int code) const
	{
		return clickable_ && emc_->is_button_clicked (code);
	}


	r_type
	Button2D::x_get () const
	{
		return label_->x_get ();
	}

	r_type
	Button2D::y_get () const
	{
		return label_->y_get ();
	}

	void
	Button2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		label_->x_set (x);
		background_->x_set (x);
		border_->x_set (x);
	}

	void
	Button2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		label_->y_set (y);
		background_->y_set (y);
		border_->y_set (y);
	}

	void
	Button2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		label_->x_move (dx);
		background_->x_move (dx);
		border_->x_move (dx);
	}

	void
	Button2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		label_->y_move (dy);
		background_->y_move (dy);
		border_->y_move (dy);
	}

	void
	Button2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		label_->move (dx, dy);
		background_->move (dx, dy);
		border_->move (dx, dy);
	}

	void
	Button2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
	    label_->move_to (x, y);
		background_->move_to (x, y);
		border_->move_to (x, y);
	}


	void
	Button2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		label_->scale (sx, sy);
		background_->scale (sx, sy);
		border_->scale (sx, sy);
	}

	void
	Button2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
	    label_->rotate (angle);
		background_->rotate (angle);
		border_->rotate (angle);
	}

	void
	Button2D::draw (Canvas2D *cv, r_type dx, r_type dy,
		  r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		background_->draw (cv, dx, dy, sx, sy);
		border_->draw (cv, dx, dy, sx, sy);
		label_->draw (cv, dx, dy, sx, sy);
	}

	void
	Button2D::will_update (const SceneInfos2D& infos)
	{
		Object2D::will_update (infos);
		background_->will_update (infos);
		border_->will_update (infos);
		label_->will_update (infos);
	}

	void
	Button2D::did_update (const SceneInfos2D& infos)
	{
		Object2D::did_update (infos);
		background_->did_update (infos);
		border_->did_update (infos);
		label_->did_update (infos);

		if (!is_clickable ())
		{
			background_->color_set (Color (OPL_BUTTON_DISABLED));
		}
		else if (is_button_clickdown ())
		{
			background_->color_set (Color (OPL_BUTTON_FOCUSED));
		}
		else if (is_mouse_on ())
		{
			background_->color_set (Color (OPL_BUTTON_OVER));
		}
		else
		{
			background_->color_set (Color (OPL_BUTTON_BASE));
		}
	}

}