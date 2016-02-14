/** @File Object2D class definition
 */

#ifndef OBJECT_2D_HH_
# define OBJECT_2D_HH_

# include <cstddef>
# include <vector>
# include <string>
# include <map>
# include "collider-2d.hh"
# include "canvas-2d.hh"
# include "tagable.hh"
# include "types.hh"
# include "vector-2d.hh"
# include "component-2d.hh"

namespace opl
{

	///SDL game object
	class Object2D: public Tagable
	{
	public:
		Object2D (Collider2D* collider = nullptr);
		virtual ~Object2D ();


		virtual r_type
		x_get () const = 0;

		virtual r_type
		y_get () const = 0;

		virtual void
		x_set (r_type x);

		virtual void
		y_set (r_type y);

		virtual void
		x_move (r_type dx);

		virtual void
		y_move (r_type dy);

		virtual void
		move (r_type dx, r_type dy);

		virtual void
		move_to (r_type x, r_type y);

		virtual void
		scale (r_type sx, r_type sy);

		virtual void
		rotate (r_type angle);

		virtual void
		draw (Canvas2D *cv, r_type dx, r_type dy, r_type sx, r_type sy);



		virtual Vector2D
		position_get () const;

		virtual void
		position_move (Vector2D v);

		virtual void
		position_set (Vector2D v);

		virtual void
		scale (Vector2D v);

		virtual void
		will_update ();

		virtual void
		did_update ();





		Collider2D*
		collider_get () const;

		void
		collider_set (Collider2D* collider);

		///Select the default collider for the object, or null if none exists
		virtual void
		collider_set_default ();

		void
		collider_remove ();

		bool
		is_collider_enabled () const;

		void
		set_collider_enabled (bool collider_enabled);

		void
		collider_enable ();

		void
		collider_disable ();





		bool
		is_enabled () const;

		bool
		is_visible () const;

		void
		set_enabled (bool enabled);

		void
		set_visible (bool visible);

		void
		enable ();

		void
		disable ();

		void
		show ();

		void
		hide ();



		std::vector<Object2D*>
		children_get () const;

		size_t
		children_size () const;

		Object2D*
		child_get (size_t i) const;

		void
		insert_child (Object2D* child);

		void
		insert_relative_child (Object2D* child);

		void
		remove_child (Object2D* child);

		bool
		has_child (Object2D* child) const;

		void
		clear_children ();

		Object2D*
		parent_get () const;

		Object2D*
		root_get () const;

		Object2D*
		mouse_get () const;

		void
		mouse_set (Object2D* mouse);

		void
		component_insert (Component2D* component);

		template <class T>
		T*
		component_get ();

		template <class T>
		void
		component_remove ();



	private:
		bool enabled_;
		bool visible_;
		bool collider_enabled_;
		Collider2D* collider_;
		std::vector<Object2D*> children_;
		std::map<size_t, Component2D*> components_;
		Object2D* parent_;
		Object2D* root_;
		Object2D* mouse_;

	};

	template <class T>
	T*
	Object2D::component_get ()
	{
		size_t id = T::ID;
		auto it = components_.find (id);
		return static_cast<T*> (it->second);
	}

	template <class T>
	void
	Object2D::component_remove ()
	{
		size_t id = T::ID;
		auto it = components_.find (id);
		if (it != components_.end ())
			components_.erase (it);
	}

}


#endif //!OBJECT_2D_HH_