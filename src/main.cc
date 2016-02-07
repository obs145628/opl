#include <cstddef>
#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <set>
#include "vector.hh"
#include "algo.hh"
#include "matrix.hh"
#include "data-store.hh"
#include "math.hh"
#include "random-generator.hh"
#include "application.hh"
#include "date.hh"
#include "mouse.hh"
#include "music-player.hh"
#include "collider.hh"
#include "pixel-collider.hh"

using opl::r_type;
using opl::rvec_type;
using opl::rmat_type;
using opl::algo::log;
using opl::DataStore;

class MyApp: public opl::Application
{

protected:

	virtual void
   	on_init_ () override
	{
		Application::on_init_ ();
		std::cout << "App initialization !" << "\n";
		x_ = 100;
		y_ = 100;
		tetha_ = 0;
		dx_ = 50;
		dy_ = 10;
		dtetha_ = 120;
		mx_ = 0;
		my_ = 0;

	}

	virtual void
	on_update_ () override
   	{
		Application::on_update_ ();
		opl::Canvas *cvs = canvas_get ();
		r_type dt = delta_time_get();

		x_ += dt * dx_;
		y_ += dt * dy_;
		tetha_ += dt * dtetha_;

		cvs->draw_color_set (opl::Color::BLACK);

		cvs->draw_text("Hello World !", x_, y_, tetha_, "lazy",
					   opl::Color::BLACK, 36);




		mx_ = opl::Mouse::instance ()->x_get ();
		my_ = opl::Mouse::instance ()->y_get ();
		if (opl::Mouse::instance ()->is_down(opl::Mouse::LEFT))
			cvs->draw_color_set(opl::Color::GREEN);
		else
			cvs->draw_color_set (opl::Color::RED);
		cvs->fill_rect (mx_, my_, 50, 50);
	}

	virtual void
	on_quit_ () override
	{
		Application::on_quit_ ();
		std::cout << "Stopping app\n";
	}

	virtual void
	on_key_down_ (int code) override
   	{
		Application::on_key_down_ (code);
		if (code == opl::Keyboard::SPACE)
			quit ();
	}

private:
	r_type x_;
	r_type y_;
	r_type tetha_;
	r_type dx_;
	r_type dy_;
	r_type dtetha_;

	r_type mx_;
	r_type my_;

};


int
main ()
{

	opl::Application* app = new MyApp();
	app->init ();

}