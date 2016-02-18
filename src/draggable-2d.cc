#include "draggable-2d.hh"

namespace opl
{

	size_t Draggable2D::ID = 2;

	Draggable2D::Draggable2D ()
		: dragging_ (false)
	{
		mouse_ = Mouse2D::instance ();
	}

	Draggable2D::~Draggable2D ()
	{
		delete emc_;
	}

	void
	Draggable2D::init (Object2D* obj)
	{
		Component2D::init (obj);
		emc_ = new EmComponent2D ();
		emc_->init (obj);
	}

	void
	Draggable2D::will_update (const SceneInfos2D& infos)
	{
		emc_->will_update (infos);

		if (!dragging_)
		{
			if (emc_->is_button_pressed (Mouse2D::LEFT))
			{
				dragging_ = true;
				mouse_last_ = infos.mouse->position_get ();
				obj_last_ = obj_->position_get ();
			}
		}

		else if (!mouse_->is_down (Mouse2D::LEFT))
		{
			dragging_ = false;
		}

		else
		{
			Vector2D mouse_pos = infos.mouse->position_get ();
			Vector2D dm = mouse_pos - mouse_last_;
			mouse_last_ = mouse_pos;
			obj_->position_move (dm);
		}
	}

	size_t
	Draggable2D::id_get ()
	{
		return ID;
	}

	bool
	Draggable2D::is_dragged () const
	{
		return dragging_;
	}

	void
	Draggable2D::stop_drag ()
	{
		dragging_ = false;
	}

	///stop drag and then replace object to initial position
	void
	Draggable2D::cancel_drag ()
	{
		if (dragging_)
		{
			dragging_ = false;
			obj_->position_set (obj_last_);
		}
	}


}