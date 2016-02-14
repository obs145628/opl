#include <cassert>
#include <algorithm>
#include "loader-2d.hh"
#include "date.hh"
#include "application-2d.hh"

namespace opl
{

	Loader2D* Loader2D::instance_ = nullptr;

	Loader2D*
	Loader2D::instance ()
	{
		if (!instance_)
			instance_ = new Loader2D;
		return instance_;
	}

	Loader2D::Loader2D ()
	{
		last_frame_ = Date::timestamp_ms ();
		canvas_ = Canvas2D::instance ();
		Application2D::instance ()->subscribe (this);
	}

	void
	Loader2D::define_scene (const std::string& name, Scene2D* scene)
	{
		scenes_[name] = scene;
	}

	void
	Loader2D::define_start_scene (const std::string& name, Scene2D* scene)
	{
		define_scene (name, scene);
		start_ = name;
	}

	void
	Loader2D::load_scene (const std::string& name)
	{
		scene_next_ = scenes_[name];
	}

	void
	Loader2D::load_start_scene ()
	{
		load_scene (start_);
	}

	Scene2D*
	Loader2D::current_scene_get () const
	{
		return scene_current_;
	}

	void
	Loader2D::notify_init ()
	{
		load_start_scene ();
	}

	void
	Loader2D::notify_update ()
	{
		if (scene_next_)
		{
			if (scene_current_)
				scene_current_->unbuild ();
			scene_current_ = scene_next_;
			scene_current_->build ();
			scene_next_ = nullptr;
		}

		update_time_ ();

		canvas_->clear ();
		scene_current_->render (delta_time_);
		canvas_->render ();
	}

	void
	Loader2D::notify_destroy ()
	{
		if (scene_current_)
			scene_current_->unbuild ();

		for (auto it = scenes_.begin (); it != scenes_.end (); ++it)
			delete it->second;
	}

	void
	Loader2D::subscribe (LoaderObserver2D* observer)
	{
		observers_.push_back (observer);
	}

	void
	Loader2D::unsuscribe (LoaderObserver2D* observer)
	{
		auto it = std::find(observers_.begin (), observers_.end (), observer);
		if(it != observers_.end ())
			observers_.erase (it);
	}


	void
	Loader2D::publish_will_load_scene_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_will_load_scene ();
	}

	void
	Loader2D::publish_did_load_scene_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_did_load_scene ();
	}

	void
	Loader2D::publish_will_unload_scene_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_will_unload_scene ();
	}

	void
	Loader2D::publish_did_unload_scene_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_did_unload_scene ();
	}

	void
	Loader2D::publish_will_update_scene_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_will_update_scene ();
	}

	void
	Loader2D::publish_did_update_scene_ ()
	{
		for (auto it = observers_.begin (); it != observers_.end (); ++it)
			(*it)->notify_did_update_scene ();
	}

	void
	Loader2D::update_time_ ()
	{
		time_t now = Date::timestamp_ms ();
		time_t dt_ms = now - last_frame_;
		delta_time_ = static_cast<r_type> (dt_ms)
			/ static_cast<r_type> (1000);
		last_frame_ = now;
	}

}