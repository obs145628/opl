#include <cassert>
#include "em-component-2d.hh"
#include "pixel-collider-2d.hh"

namespace opl
{

	EmComponent2D::EmComponent2D ()
		: mouse_on_ (false), mouse_entered_ (false), mouse_exited_ (false),
		  bts_on_ (), bts_entered_ (), bts_exited_ (),
		  bts_click1_ (), bts_clicked_ ()
	{
		cm_ = ColliderManager2D::instance ();
		mouse_ = Mouse2D::instance ();

		bts_on_[Mouse2D::LEFT] = false;
		bts_on_[Mouse2D::MIDDLE] = false;
		bts_on_[Mouse2D::RIGHT] = false;
		bts_on_[Mouse2D::X1] = false;
		bts_on_[Mouse2D::X2] = false;

		bts_entered_[Mouse2D::LEFT] = false;
		bts_entered_[Mouse2D::MIDDLE] = false;
		bts_entered_[Mouse2D::RIGHT] = false;
		bts_entered_[Mouse2D::X1] = false;
		bts_entered_[Mouse2D::X2] = false;

		bts_exited_[Mouse2D::LEFT] = false;
		bts_exited_[Mouse2D::MIDDLE] = false;
		bts_exited_[Mouse2D::RIGHT] = false;
		bts_exited_[Mouse2D::X1] = false;
		bts_exited_[Mouse2D::X2] = false;

		bts_click1_[Mouse2D::LEFT] = false;
		bts_click1_[Mouse2D::MIDDLE] = false;
		bts_click1_[Mouse2D::RIGHT] = false;
		bts_click1_[Mouse2D::X1] = false;
		bts_click1_[Mouse2D::X2] = false;

		bts_clicked_[Mouse2D::LEFT] = false;
		bts_clicked_[Mouse2D::MIDDLE] = false;
		bts_clicked_[Mouse2D::RIGHT] = false;
		bts_clicked_[Mouse2D::X1] = false;
		bts_clicked_[Mouse2D::X2] = false;
	}

	size_t EmComponent2D::ID = 1;

	void
	EmComponent2D::will_update ()
	{
		bool on = cm_->are_colliding (obj_, obj_->mouse_get ());

		mouse_entered_ = !mouse_on_ && on;
		mouse_exited_ = mouse_on_ && !on;
		mouse_on_ = on;

		for (auto it = bts_on_.begin (); it != bts_on_.end (); ++it)
		{
			it->second = on && mouse_->is_down (it->first);
		}

		for (auto it = bts_entered_.begin (); it != bts_entered_.end (); ++it)
		{
			it->second = on && mouse_->is_pressed (it->first);
		}

		for (auto it = bts_exited_.begin (); it != bts_exited_.end (); ++it)
		{
			it->second = on && mouse_->is_released (it->first);
		}

		for (auto it = bts_clicked_.begin (); it != bts_clicked_.end (); ++it)
		{
			it->second = bts_click1_[it->first]
				&& is_button_released (it->first);
		}

		for (auto it = bts_click1_.begin (); it != bts_click1_.end (); ++it)
		{
			it->second = is_button_pressed (it->first)
				|| (it->second && is_button_down (it->first));
		}
	}

	size_t
	EmComponent2D::id_get ()
	{
		return ID;
	}


	bool
	EmComponent2D::is_mouse_on () const
	{
		return mouse_on_;
	}

	bool
	EmComponent2D::is_mouse_entered () const
	{
		return mouse_entered_;
	}

   	bool
	EmComponent2D::is_mouse_exited () const
	{
		return mouse_exited_;
	}

	bool
	EmComponent2D::is_button_down (int code) const
	{
		auto it = bts_on_.find (code);
		assert (it != bts_on_.end ());
	   	return it->second;
	}


	bool
	EmComponent2D::is_button_pressed (int code) const
	{
		auto it = bts_entered_.find (code);
		assert (it != bts_entered_.end ());
	   	return it->second;
	}


	bool
	EmComponent2D::is_button_released (int code) const
	{
		auto it = bts_exited_.find (code);
		assert (it != bts_exited_.end ());
	   	return it->second;
	}

	bool
	EmComponent2D::is_button_clickdown (int code) const
	{
		auto it = bts_click1_.find (code);
		assert (it != bts_click1_.end ());
	   	return it->second;
	}

	bool
	EmComponent2D::is_button_clicked (int code) const
	{
		auto it = bts_clicked_.find (code);
		assert (it != bts_clicked_.end ());
	   	return it->second;
	}

}