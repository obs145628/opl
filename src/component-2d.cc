#include "component-2d.hh"

namespace opl
{

	Component2D::Component2D ()
		: enabled_ (true)
	{

	}


	void
	Component2D::init (Object2D* obj)
	{
		obj_ = obj;
	}


	void
	Component2D::will_update (const SceneInfos2D&)
	{

	}

	void
	Component2D::did_update (const SceneInfos2D&)
	{

	}

	bool
	Component2D::is_enabled () const
	{
		return enabled_;
	}

	void
	Component2D::enabled_set (bool enabled)
	{
		enabled_ = enabled;
	}

	void
	Component2D::enable ()
	{
		enabled_ = true;
	}

	void
	Component2D::disable ()
	{
		enabled_ = false;
	}

}