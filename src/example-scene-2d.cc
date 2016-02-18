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
		fixed_camera_set (39.5, -54.18, 1200, 500);

		//cam_->background_set(Color::BLACK);

		std::string text ("Hello me\nGo to sleep and never go home, lolipop. Everything starts where everything stops, and nothing ends as long as the end didn't came.");

		obj_ = insert_multi_label(text, 0, 0, 24, "lazy", 400, Color::BLACK);

		MultiLabel2D* multi = static_cast<MultiLabel2D*> (obj_);

		border_ = insert_rectangle (0, 0,
									multi->width_get(), multi->height_get (),
									false, Color::BLACK);

	}

	void
	ExampleScene2D::update_ ()
	{
		//if(keyboard_->is_released (keyboard_->SPACE))
		//	app_->quit ();

		obj_->position_set(mouse_position ());
		border_->position_set (mouse_position ());
		//obj_->rotate (-0.35 * pi_ * delta_);
		//border_->rotate (-0.35 * pi_ * delta_);
	}

	void
	ExampleScene2D::destroy_ ()
   	{
		std::cout << "Destroy ExampleScene2D\n";
	}

}