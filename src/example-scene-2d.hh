/** @file An example of 2D scene subclass
 */

#ifndef EXAMPLE_SCENE_2D_HH_
# define EXAMPLE_SCENE_2D_HH_

# include "scene-2d.hh"

namespace opl
{

	class ExampleScene2D: public Scene2D
	{

	public:
		virtual void
		init_ () override;

		virtual void
		update_ () override;

		virtual void
		destroy_ () override;

	private:
		KeyboardController2D* ctrl_;
		TextField2D* player_;
		Polygon2D* other_;
		Object2D* obj_;
		Rectangle2D* border_;

	};


}

#endif //!EXAMPLE_SCENE_2D_HH_