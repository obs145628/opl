#include "keyboard-controller-2d.hh"

namespace opl
{

	KeyboardController2D::KeyboardController2D (int left_code,
												int right_code,
												int up_code,
												int down_code)
		: left_code_ (left_code), right_code_ (right_code),
		  up_code_ (up_code), down_code_ (down_code)
	{
		keyboard_ = Keyboard2D::instance ();
	}


	r_type
	KeyboardController2D::x_get () const
	{
		if (keyboard_->is_down (left_code_))
	   	{
			return -1;
		}
		else if (keyboard_->is_down (right_code_))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}


	r_type
	KeyboardController2D::y_get () const
	{
		if( keyboard_->is_down (up_code_))
		{
			return -1;
		}
		else if(keyboard_->is_down (down_code_))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

}