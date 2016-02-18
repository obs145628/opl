/** @file Draggable2D class definition
 */

#ifndef DRAGGABLE_2D_HH_
# define DRAGGABLE_2D_HH_

# include "component-2d.hh"
# include "em-component-2d.hh"
# include "vector-2d.hh"
# include "mouse-2d.hh"

namespace opl
{

	class Draggable2D: public Component2D
	{

	public:

		static size_t ID;

		Draggable2D ();
		virtual ~Draggable2D ();

		virtual void
		init (Object2D* obj) override;

		virtual void
		will_update (const SceneInfos2D& infos) override;

		virtual size_t
		id_get () override;

		bool
		is_dragged () const;

		void
		stop_drag ();

		///stop drag and then replace object to initial position
		void
		cancel_drag ();



	private:
		EmComponent2D* emc_;
		bool dragging_;
		Vector2D mouse_last_;
		Vector2D obj_last_;
		Mouse2D* mouse_;

	};

}

#endif //!DRAGGABLE_2D_HH_