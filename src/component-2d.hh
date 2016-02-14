/** *@file Component2D Class definition
 */

#ifndef COMPONENT_2D_HH_
# define COMPONENT_2D_HH_

# include <cstddef>

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
		will_update ();

		virtual void
		did_update ();

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