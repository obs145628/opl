/** @file SDL example application
 */

#ifndef EXAMPLE_APP_2D_HH_
# define EXAMPLE_APP_2D_HH_

#include "application-2d.hh"
#include "loader-2d.hh"
#include "example-scene-2d.hh"

namespace opl
{

	class ExampleApp2D
	{
	public:

		ExampleApp2D()
	   	{
			Loader2D* loader = Loader2D::instance ();
			loader->define_start_scene ("index", new ExampleScene2D);

			Application2D::instance ()->init ();
   		}

	};

}


#endif //!EXAMPLE_APP_2D_HH_