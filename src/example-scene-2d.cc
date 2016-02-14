#include <cassert>
#include <iostream>
#include "example-scene-2d.hh"
#include "draggable-2d.hh"

namespace opl
{
	void
	ExampleScene2D::init_ ()
   	{
		std::cout << "Init ExampleScene2D\n";
		static_camera_set(39.5, -54.18);

		cam_->background_set(Color::BLACK);

		player_ = insert_rectangle (0, 0, 90, 60, false, Color::WHITE);

		player_->collider_set_default ();

		other_ = insert_triangle(80, 60, 220, 340, 190, 55 , false, Color::WHITE);
		other_->collider_set_default ();

		other_->component_insert (new Draggable2D ());

	}

	void
	ExampleScene2D::update_ ()
	{
		if(keyboard_->is_down (keyboard_->SPACE))
			app_->quit ();

		Draggable2D* drag = other_->component_get<Draggable2D> ();

		if (cm_->are_colliding(player_, other_))
			drag->cancel_drag ();



		//player_->position_set (mouse_position ());
		player_->rotate (-0.35 * pi_ * delta_);
		other_->rotate (0.5 * pi_ * delta_);


	}

	void
	ExampleScene2D::destroy_ ()
   	{
		std::cout << "Destroy ExampleScene2D\n";
	}

}