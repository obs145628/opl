/** @file Loader2D class deifnition
 */

#ifndef LOADER_2D_HH_
# define LOADER_2D_HH_

# include <map>
# include <string>
# include <vector>
# include "scene-2d.hh"
# include "canvas-2d.hh"
# include "game-observer-2d.hh"
# include "loader-observer-2d.hh"

namespace opl
{

	///Load and manage 2D scenes
	class Loader2D : public GameObserver2D
	{

	public:
		static Loader2D*
		instance ();

		void
		define_scene (const std::string& name, Scene2D* scene);

		void
		define_start_scene (const std::string& name, Scene2D* scene);

		void
		load_scene (const std::string& name);

		void
		load_start_scene ();

		Scene2D*
		current_scene_get () const;

		virtual void
		notify_init () override;

		virtual void
		notify_update () override;

		virtual void
		notify_destroy () override;


		void
		subscribe (LoaderObserver2D* observer);

		void
		unsuscribe (LoaderObserver2D* observer);

	protected:

		void
		publish_will_load_scene_ ();

		void
		publish_did_load_scene_ ();

		void
		publish_will_unload_scene_ ();

		void
		publish_did_unload_scene_ ();

		void
		publish_will_update_scene_ ();

		void
		publish_did_update_scene_ ();






	private:

		static Loader2D* instance_;
		Loader2D ();
		Loader2D (const Loader2D&) = delete;

		Canvas2D* canvas_;

		std::map<std::string, Scene2D*> scenes_;
		std::vector<LoaderObserver2D*> observers_;
		Scene2D* scene_current_;
		Scene2D* scene_next_;
		std::string start_;

		time_t last_frame_;
		r_type delta_time_;

		void
		update_time_ ();


	};

}


#endif //!LOADER_2D_HH_