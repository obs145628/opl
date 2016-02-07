/** @File Object2D class definition
 */

#ifndef OBJECT_2D_HH_
# define OBJECT_2D_HH_

# include <cstddef>
# include <vector>
# include <string>
# include "collider.hh"
# include "canvas.hh"
# include "tagable.hh"
# include "types.hh"
# include "vector2.hh"

namespace opl
{

	///SDL game object
	class Object2D: public Tagable
	{
	public:
		Object2D (const std::string& name, Collider* collider = nullptr);
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
		move (r_type x, r_type y);

		virtual void
		move_to (r_type x, r_type y);

		virtual void
		scale (r_type sx, r_type sy);

		virtual void
		rotate (r_type angle);

		virtual void
		draw (Canvas *cv, r_type dx, r_type dy, r_type sx, r_type sy);



		virtual Vector2
		position_get () const;

		virtual void
		move (Vector2 v);

		virtual void
		move_to (Vector2 v);

		virtual void
		scale (Vector2 v);




		std::string
		name_get () const;

		void
		name_set (const std::string& name);

		bool
		is_named (const std::string& name) const;

		Collider*
		collider_get () const;

		void
		collider_set (Collider* collider);

		void
		collider_remove ();

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
		remove_child (Object2D* child);

		bool
		has_child (Object2D* child) const;

		void
		clear_children ();


	private:
		std::string name_;
		bool enabled_;
		bool visible_;
		Collider *collider_;
		std::vector<Object2D*> children_;

	};

}


#endif //!OBJECT_2D_HH_