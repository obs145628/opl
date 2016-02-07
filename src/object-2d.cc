#include <cmath>
#include <algorithm>
#include "object-2d.hh"

namespace opl
{

	void
	Object2D::x_set (r_type x)
	{
		r_type dx = x - x_get ();
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->x_move (dx);
	}

	void
	Object2D::y_set (r_type y)
	{
		r_type dy = y - y_get ();
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->y_move (dy);
	}

	void
	Object2D::x_move (r_type dx)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->x_move (dx);
	}

	void
	Object2D::y_move (r_type dy)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->y_move (dy);
	}

	void
	Object2D::move (r_type dx, r_type dy)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->move (dx, dy);
	}

	void
	Object2D::move_to (r_type x, r_type y)
	{
		r_type dx = x - x_get ();
		r_type dy = y - y_get ();
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->move (dx, dy);
	}

	void
	Object2D::scale (r_type sx, r_type sy)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
		{
			Object2D* child = *it;
			child->move_to (x_get () + (child->x_get () - x_get ())*sx,
							y_get () + (child->y_get () - y_get ())*sy);
			child->scale (sx, sy);
		}
	}

	void
	Object2D::rotate (r_type angle)
	{
		r_type c = std::cos (angle);
		r_type s = std::sin (angle);
	    for (auto it = children_.begin (); it != children_.end (); ++it)
		{
			Object2D* child = *it;
			child->move_to(
				x_get () + (child->x_get () - x_get ()) * c
				- (child->y_get () - y_get ()) * s,
				y_get () + (child->y_get () - x_get ()) * s
				+ (child->y_get () - y_get ()) * c
				);
			child->rotate (angle);
		}
	}

	void
	Object2D::draw (Canvas *cv, r_type dx, r_type dy, r_type sx, r_type sy)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
		{
			Object2D* child = *it;
			if(child->enabled_ && child->visible_)
				child->draw (cv, dx, dy, sx, sy);
		}
	}


	Vector2
	Object2D::position_get () const
	{
		return Vector2 (x_get (), y_get ());
	}

	void
	Object2D::move (Vector2 v)
	{
		move (v.x_get (), v.y_get ());
	}

	void
	Object2D::move_to (Vector2 v)
	{
		move_to (v.x_get (), v.y_get ());
	}

	void
	Object2D::scale (Vector2 v)
	{
		scale (v.x_get (), v.y_get ());
	}




	std::string
	Object2D::name_get () const
	{
		return name_;
	}

	void
	Object2D::name_set (const std::string& name)
	{
		name_ = name;
	}

	bool
	Object2D::is_named (const std::string& name) const
	{
		return name_ == name;
	}

	Collider*
	Object2D::collider_get () const
	{
		return collider_;
	}

	void
	Object2D::collider_set (Collider* collider)
	{
		if(collider != collider_)
			delete collider_;
		collider_ = collider;
	}

	void
	Object2D::collider_remove ()
	{
		delete collider_;
		collider_ = nullptr;
	}

	bool
	Object2D::is_enabled () const
	{
		return enabled_;
	}

	bool
	Object2D::is_visible () const
	{
		return visible_;
	}

	void
	Object2D::set_enabled (bool enabled)
	{
		enabled_ = enabled;
	}

	void
	Object2D::set_visible (bool visible)
	{
		visible_ = visible;
	}

	void
	Object2D::enable ()
	{
		enabled_ = true;
	}

	void
	Object2D::disable ()
	{
		enabled_ = false;
	}

	void
	Object2D::show ()
	{
		visible_ = true;
	}

	void
	Object2D::hide ()
	{
		visible_ = false;
	}



	std::vector<Object2D*>
	Object2D::children_get () const
	{
		return children_;
	}

	size_t
	Object2D::children_size () const
	{
		return children_.size ();
	}

	Object2D*
	Object2D::child_get (size_t i) const
	{
		return children_[i];
	}

	void
	Object2D::insert_child (Object2D* child)
	{
		children_.push_back (child);
	}

	void
	Object2D::remove_child (Object2D* child)
	{
		auto it = std::find (children_.begin (), children_.end (), child);
		if (it != children_.end ())
			children_.erase (it);
	}

	bool
	Object2D::has_child (Object2D* child) const
	{
		return std::find (children_.begin (), children_.end (), child)
			!= children_.end ();
	}

	void
	Object2D::clear_children ()
	{
		children_.clear ();
	}

}