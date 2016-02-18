/** @file SceneInfos2d strutc definition
 */

#ifndef SCENE_INFOS_2D_HH_
# define SCENE_INFOS_2D_HH_

# include "types.hh"

namespace opl
{

	class Object2D;
	class Camera2D;
	class Canvas2D;

	struct SceneInfos2D
	{
		Object2D* root;
		Object2D* mouse;
		Camera2D* cam;
		Canvas2D* canvas;
		r_type delta;
	};

}

#endif //!SCENE_INFOS_2D_HH_