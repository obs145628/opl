/** @file Controller2D class definition
 */

#ifndef CONTROLLER_2D_HH_
# define CONTROLLER_2D_HH_

# include "vector-2d.hh"

namespace opl
{

	///2D game controller for getting mouvement
	class Controller2D
	{

	public:
		virtual ~Controller2D () = default;

		///Returns x-axis position between -1 and 1
		virtual r_type
		x_get () const = 0;

		///Returns y-axis position between -1 and 1
		virtual r_type
		y_get () const = 0;

		virtual Vector2D
		axis_get () const;





	};

}


#endif //!CONTROLLER_2D_HH_