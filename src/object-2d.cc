#include <cmath>
#include <cassert>
#include <algorithm>
#include "object-2d.hh"

namespace opl
{

	Object2D::Object2D (Collider2D* collider)
		: Tagable (), enabled_ (true), visible_ (true),
		  collider_enabled_ (true), collider_ (collider),
		  children_ (), components_ (),
		  parent_ (nullptr), root_ (this), mouse_ (nullptr)
	{

	}

	Object2D::~Object2D ()
	{
		if(collider_)
			delete collider_;
		for (auto it = children_.begin (); it != children_.end (); ++it)
			delete *it;

		for (auto it = components_.begin (); it != components_.end (); ++it)
			delete it->second;
	}

	void
	Object2D::x_set (r_type x)
	{
		r_type dx = x - x_get ();
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->x_move (dx);
		if (collider_)
			collider_->x_set (x);
	}

	void
	Object2D::y_set (r_type y)
	{
		r_type dy = y - y_get ();
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->y_move (dy);
		if (collider_)
			collider_->y_set (y);
	}

	void
	Object2D::x_move (r_type dx)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->x_move (dx);
		if (collider_)
			collider_->x_move (dx);
	}

	void
	Object2D::y_move (r_type dy)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->y_move (dy);
		if (collider_)
			collider_->y_move (dy);
	}

	void
	Object2D::move (r_type dx, r_type dy)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->move (dx, dy);
		if (collider_)
			collider_->move (dx, dy);
	}

	void
	Object2D::move_to (r_type x, r_type y)
	{
		r_type dx = x - x_get ();
		r_type dy = y - y_get ();
		for (auto it = children_.begin (); it != children_.end (); ++it)
			(*it)->move (dx, dy);
		if (collider_)
			collider_->move_to (x, y);
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
		if (collider_)
			collider_->scale (sx, sy);
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
				y_get () + (child->x_get () - x_get ()) * s
				+ (child->y_get () - y_get ()) * c
				);
			child->rotate (angle);
		}
		if (collider_)
			collider_->rotate (angle);
	}

	void
	Object2D::draw (Canvas2D *cv, r_type dx, r_type dy, r_type sx, r_type sy)
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
		{
			Object2D* child = *it;
			if(child->enabled_ && child->visible_)
				child->draw (cv, dx, dy, sx, sy);
		}
	}


	Vector2D
	Object2D::position_get () const
	{
		return Vector2D (x_get (), y_get ());
	}

	void
	Object2D::position_move (Vector2D v)
	{
		move (v.x_get (), v.y_get ());
	}

	void
	Object2D::position_set (Vector2D v)
	{
		move_to (v.x_get (), v.y_get ());
	}

	void
	Object2D::scale (Vector2D v)
	{
		scale (v.x_get (), v.y_get ());
	}

	void
	Object2D::will_update ()
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			if ((*it)->enabled_)
				(*it)->will_update ();

		for (auto it = components_.begin (); it != components_. end(); ++it)
			if (it->second->is_enabled ())
				it->second->will_update ();
	}

	void
	Object2D::did_update ()
	{
		for (auto it = children_.begin (); it != children_.end (); ++it)
			if ((*it)->enabled_)
				(*it)->did_update ();

		for (auto it = components_.begin (); it != components_. end(); ++it)
			if (it->second->is_enabled ())
				it->second->did_update ();
	}



	Collider2D*
	Object2D::collider_get () const
	{
		return collider_;
	}

	void
	Object2D::collider_set (Collider2D* collider)
	{
		if(collider != collider_)
			delete collider_;
		collider_ = collider;
	}

	void
	Object2D::collider_set_default ()
	{
		collider_set (nullptr);
	}

	void
	Object2D::collider_remove ()
	{
		delete collider_;
		collider_ = nullptr;
	}

	bool
	Object2D::is_collider_enabled () const
	{
		return collider_enabled_;
	}

	void
	Object2D::set_collider_enabled (bool collider_enabled)
	{
		collider_enabled_ = collider_enabled;
	}

	void
	Object2D::collider_enable ()
	{
		collider_enabled_ = true;
	}

	void
	Object2D::collider_disable ()
	{
		collider_enabled_ = false;
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
		child->parent_ = this;
		child->root_ = root_;
		child->mouse_ = mouse_;
	}

	void
	Object2D::insert_relative_child (Object2D* child)
	{
		insert_child (child);
		child->move (x_get (), y_get ());
	}

	void
	Object2D::remove_child (Object2D* child)
	{
		auto it = std::find (children_.begin (), children_.end (), child);
		if (it != children_.end ())
		{
			delete *it;
			children_.erase (it);
		}
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

	Object2D*
	Object2D::parent_get () const
	{
		return parent_;
	}

	Object2D*
	Object2D::root_get () const
	{
		return root_;
	}

	Object2D*
	Object2D::mouse_get () const
	{
		return mouse_;
	}

	void
	Object2D::mouse_set (Object2D* mouse)
	{
		mouse_ = mouse;
	}


	void
	Object2D::component_insert (Component2D* component)
	{
		size_t id = component->id_get ();
		assert (components_.find (id) == components_.end ());
		components_[id] = component;
		component->init (this);
	}

}