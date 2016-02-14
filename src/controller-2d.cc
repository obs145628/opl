#include "controller-2d.hh"

namespace opl
{

	Vector2D
	Controller2D::axis_get () const
	{
		return Vector2D (x_get (), y_get ());
	}

}