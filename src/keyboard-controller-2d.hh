/** @file KeyboardController2D class definition
 */

#ifndef KEYBOARD_CONTROLLER_2D_HH_
# define KEYBOARD_CONTROLLER_2D_HH_

# include "controller-2d.hh"
# include "keyboard-2d.hh"

namespace opl
{

	///2D Game controller using predefined keys
	class KeyboardController2D: public Controller2D
	{

	public:
	    KeyboardController2D (int left_code, int right_code,
								int up_code, int down_code);


		virtual r_type
		x_get () const override;


		virtual r_type
		y_get () const override;

	private:
		Keyboard2D* keyboard_;
		int left_code_;
		int right_code_;
		int up_code_;
		int down_code_;







	};

}


#endif //!KEYBOARD_CONTROLLER_2D_HH_