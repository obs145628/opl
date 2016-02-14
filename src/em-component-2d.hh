/** @file EMComponent2D class definition
 */

#ifndef EM_COMPONENT_2D_HH_
# define EM_COMPONENT_2D_HH_

# include <map>
# include "component-2d.hh"
# include "object-2d.hh"
# include "collider-manager-2d.hh"
# include "mouse-2d.hh"

namespace opl
{

	class EmComponent2D: public Component2D
	{

	public:
		static size_t ID;

		EmComponent2D ();

		virtual void
		will_update () override;

		virtual size_t
		id_get () override;

		bool
		is_mouse_on () const;

		//Returns if the mouse entered on the current frame
		bool
		is_mouse_entered () const;

		///Returns if the mouse exited on the current frame
		bool
		is_mouse_exited () const;

		///Returns if button is down with mouse on
		bool
		is_button_down (int code) const;

		///Returns if button is pressed on object on the current frame
		bool
		is_button_pressed (int code) const;

		///Returns if button is released on object on the current frame
		bool
		is_button_released (int code) const;

		///Returns if button is half-clicked (down but not released)
		bool
		is_button_clickdown (int code) const;

		///Returns if button is pressed then released
		bool
		is_button_clicked (int code) const;


	private:
		ColliderManager2D* cm_;
		Mouse2D* mouse_;
		bool mouse_on_;
		bool mouse_entered_;
		bool mouse_exited_;
		std::map<int, bool> bts_on_;
		std::map<int, bool> bts_entered_;
		std::map<int, bool> bts_exited_;
		std::map<int, bool> bts_click1_;
		std::map<int, bool> bts_clicked_;


	};

}

# endif