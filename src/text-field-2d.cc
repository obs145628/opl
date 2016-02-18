#include <cassert>
#include <cmath>
#include <iostream>
#include "text-field-2d.hh"



namespace opl
{


	TextField2D::TextField2D (const std::string& text, r_type x, r_type y,
						r_type size, r_type w, r_type h)
		: Object2D (), editable_ (true), cursor_ (-1), counter_ (0),
		  cursor_speed_ (1), text_ (text), validated_ (false)
	{
		label_ = new Label2D (text, x, y, size, "lazy", Color::BLACK);
		background_ = new Rectangle2D (x, y, w, h, true, Color::WHITE);
		background_->collider_set_default ();
		border_ = new Rectangle2D (x, y, w, h, false, Color::BLACK);
		emc_ = new EmComponent2D ();
		background_->component_insert (emc_);
		keyboard_ = Keyboard2D::instance ();
	}

	TextField2D::~TextField2D ()
	{
		delete label_;
		delete background_;
		delete border_;
	}

	std::string
	TextField2D::text_get () const
	{
	    return text_;
	}

	void
	TextField2D::text_set (const std::string& text)
	{
		text_ = text;
	}

	r_type
	TextField2D::size_get () const
	{
		return label_->size_get ();
	}

	void
	TextField2D::size_set (r_type size)
	{
		label_->size_set (size);
	}

	std::string
	TextField2D::font_get () const
	{
		return label_->font_get ();
	}

	void
	TextField2D::font_set (const std::string& font)
	{
		label_->font_set (font);
	}

	r_type
	TextField2D::width_get () const
	{
		return background_->width_get ();
	}

	void
	TextField2D::width_set (r_type width)
	{
		background_->width_set (width);
		border_->width_set (width);
	}

	r_type
	TextField2D::height_get () const
	{
		return background_->height_get ();
	}

	void
	TextField2D::height_set (r_type height)
	{
		background_->height_set (height);
		border_->height_set (height);
	}

	Color
	TextField2D::text_color_get () const
	{
		return label_->color_get ();
	}

	void
	TextField2D::text_color_set (const Color& c)
	{
		label_->color_set (c);
	}

	Color
	TextField2D::bg_color_get () const
	{
		return background_->color_get ();
	}

	void
	TextField2D::bg_color_set (const Color &c)
	{
		background_->color_set (c);
	}

	Color
	TextField2D::border_color_get () const
	{
		return border_->color_get ();
	}

	void
	TextField2D::border_color_set (const Color& c)
	{
		border_->color_set (c);
	}

	r_type
	TextField2D::text_width_get () const
	{
		return label_->width_get ();
	}

	r_type
	TextField2D::text_height_get () const
	{
		return label_->height_get ();
	}

	bool
	TextField2D::is_editable () const
	{
		return editable_;
	}

	void
	TextField2D::editable_set (bool editable)
	{
		editable_ = editable;
	}

	bool
	TextField2D::has_focus () const
	{
		return cursor_ != -1;
	}

	void
	TextField2D::focus_set (bool focus)
	{
		if (focus)
		{
			if (cursor_ == -1)
				cursor_ = text_.size ();
		}
		else
			cursor_ = -1;
	}

	bool
	TextField2D::is_validated () const
	{
		return validated_;
	}


	r_type
	TextField2D::x_get () const
	{
		return label_->x_get ();
	}

	r_type
	TextField2D::y_get () const
	{
		return label_->y_get ();
	}

	void
	TextField2D::x_set (r_type x)
	{
		Object2D::x_set (x);
		label_->x_set (x);
		background_->x_set (x);
		border_->x_set (x);
	}

	void
	TextField2D::y_set (r_type y)
	{
		Object2D::y_set (y);
		label_->y_set (y);
		background_->y_set (y);
		border_->y_set (y);
	}

	void
	TextField2D::x_move (r_type dx)
	{
		Object2D::x_move (dx);
		label_->x_move (dx);
		background_->x_move (dx);
		border_->x_move (dx);
	}

	void
	TextField2D::y_move (r_type dy)
	{
		Object2D::y_move (dy);
		label_->y_move (dy);
		background_->y_move (dy);
		border_->y_move (dy);
	}

	void
	TextField2D::move (r_type dx, r_type dy)
	{
		Object2D::move (dx, dy);
		label_->move (dx, dy);
		background_->move (dx, dy);
		border_->move (dx, dy);
	}

	void
	TextField2D::move_to (r_type x, r_type y)
	{
		Object2D::move_to (x, y);
	    label_->move_to (x, y);
		background_->move_to (x, y);
		border_->move_to (x, y);
	}


	void
	TextField2D::scale (r_type sx, r_type sy)
	{
		Object2D::scale (sx, sy);
		label_->scale (sx, sy);
		background_->scale (sx, sy);
		border_->scale (sx, sy);
	}

	void
	TextField2D::rotate (r_type angle)
	{
		Object2D::rotate (angle);
	    label_->rotate (angle);
		background_->rotate (angle);
		border_->rotate (angle);
	}

	void
	TextField2D::draw (Canvas2D *cv, r_type dx, r_type dy,
		  r_type sx, r_type sy)
	{
		Object2D::draw (cv, dx, dy, sx, sy);
		field_update_ ();
		background_->draw (cv, dx, dy, sx, sy);
		border_->draw (cv, dx, dy, sx, sy);
		label_->draw (cv, dx, dy, sx, sy);
	}

	void
	TextField2D::will_update (const SceneInfos2D& infos)
	{
		Object2D::will_update (infos);
		background_->will_update (infos);
		border_->will_update (infos);
		label_->will_update (infos);

		validated_ = false;

		if ( emc_->is_button_clicked (Mouse2D::LEFT))
		{
			focus_set (true);
		}

		counter_ += infos.delta;

		if (!has_focus ())
			return;

		std::vector<int> keys = keyboard_->pressed_keys ();

		if (keys.size () == 1)
		{
			int key = keys[0];

			if (key == Keyboard2D::LEFT)
				move_left_ ();
			else if (key == Keyboard2D::RIGHT)
				move_right_ ();
			else if (key == Keyboard2D::BACKSPACE)
				remove_left_ ();
			else if (key == Keyboard2D::DELETE)
				remove_right_ ();
			else if(key == Keyboard2D::RETURN)
				validated_ = true;

			else
			{
				char c = keyboard_->char_get (key);
				if (c)
				{
					insert_text_ (std::string (1, c));
				}
			}
		}
	}

	void
	TextField2D::did_update (const SceneInfos2D& infos)
	{
		Object2D::did_update (infos);
		background_->did_update (infos);
		border_->did_update (infos);
		label_->did_update (infos);
	}

	void
	TextField2D::field_update_ ()
	{
		if (cursor_ == -1)
			label_->text_set (text_);
		else
		{
			std::string left = text_.substr (0, cursor_);
			std::string right = text_.substr (cursor_);
			r_type diff =  std::fmod (counter_, cursor_speed_);
			bool disp_cur =	diff < cursor_speed_ / 2;
			std::string cur = disp_cur ? "|" : " ";

			label_->text_set (left + cur + right);
		}
	}

	void
	TextField2D::move_left_ ()
	{
		if (cursor_ != 0)
			cursor_--;
	}

	void
	TextField2D::move_right_ ()
	{
		if (cursor_ != static_cast<int> (text_.size ()))
			cursor_++;
	}

	void
	TextField2D::insert_text_ (const std::string& text)
	{
		text_ = text_.substr (0, cursor_)
			+ text
			+ text_.substr (cursor_);
		cursor_ += text.size ();
	}

	void
	TextField2D::remove_left_ ()
	{
		if (cursor_ == 0)
			return;
		text_ = text_.substr (0, cursor_ - 1) + text_.substr (cursor_);
		--cursor_;
	}

	void
	TextField2D::remove_right_ ()
	{
		if (cursor_ == static_cast<int> (text_.size ()))
			return;
		text_ = text_.substr(0, cursor_) + text_.substr( cursor_ + 1);
	}
}