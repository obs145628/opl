/** @file LoaderObserver2D Class definition
 */

#ifndef LOADER_OBSERVER_2D_HH_
# define LOADER_OBSERVER_2D_HH_

namespace opl
{
	class LoaderObserver2D
	{

	public:
		virtual ~LoaderObserver2D () = default;

		virtual void
		notify_will_load_scene ();

		virtual void
		notify_did_load_scene ();

		virtual void
		notify_will_unload_scene ();

		virtual void
		notify_did_unload_scene ();

		virtual void
		notify_will_update_scene ();

		virtual void
		notify_did_update_scene ();




	};
}

#endif //!LOAER_OBSERVER_2D_HH_