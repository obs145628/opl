/** *@file Component2D Class definition
 */

#ifndef COMPONENT_2D_HH_
# define COMPONENT_2D_HH_

# include <cstddef>
# include "scene-infos-2d.hh"

namespace opl
{

	class Object2D;

	///Extend capabilities of Object2D
	class Component2D
	{

	public:

		Component2D ();

		virtual ~Component2D () = default;

		virtual void
		init (Object2D* obj);

		virtual void
		will_update (const SceneInfos2D& infos);

		virtual void
		did_update (const SceneInfos2D& infos);

		virtual size_t
		id_get () = 0;

		bool
		is_enabled () const;

		void
		enabled_set (bool enabled);

		void
		enable ();

		void
		disable ();

	protected:
		Object2D* obj_;

	private:
		bool enabled_;

	};

}

#endif //!COMPONENT_2D_HH_