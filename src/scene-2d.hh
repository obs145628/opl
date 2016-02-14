/** @file Scene2D class definition
 */

#ifndef SCENE_2D_HH_
# define SCENE_2D_HH_

# include "canvas-2d.hh"
# include "object-2d.hh"
# include "camera-2d.hh"
# include "static-camera-2d.hh"
# include "rect.hh"
# include "mouse-2d.hh"
# include "keyboard-2d.hh"
# include "application-2d.hh"
# include "music-player-2d.hh"
# include "collider-manager-2d.hh"
# include "empty-object-2d.hh"
# include "pixel-2d.hh"
# include "line-2d.hh"
# include "circle-2d.hh"
# include "label-2d.hh"
# include "polygon-2d.hh"
# include "sprite-2d.hh"
# include "keyboard-controller-2d.hh"

namespace opl
{

	///SDL Scene representation
	class Scene2D
	{

	public:

		Scene2D ();
		virtual ~Scene2D () = default;

		void
		render (r_type delta_time);

		void
		build ();

		void
		unbuild ();

		void
		insert_object (Object2D* obj);

		void
		remove_object (Object2D* obj);

		bool
		has_object (Object2D* obj) const;

		size_t
		objects_size () const;

		void
		clear_objects ();

		r_type
		width_get () const;

		r_type
		height_get () const;

		Vector2D
		scene_to_screen_position (r_type x, r_type y) const;

		Vector2D
		scene_to_screen_position (Vector2D v) const;

		Vector2D
		screen_to_scene_position (r_type x, r_type y) const;

		Vector2D
		screen_to_scene_position (Vector2D v) const;

		Vector2D
		mouse_position () const;



		Camera2D*
		camera_get () const;

		void
		camera_set (Camera2D* cam);

	    void
		static_camera_set (r_type x, r_type y);





		EmptyObject2D*
		create_empty (r_type x, r_type y) const;

		EmptyObject2D*
		insert_empty (r_type x, r_type y);

		Pixel2D*
		create_pixel (r_type x, r_type y, const Color& c) const;


		Pixel2D*
		insert_pixel (r_type x, r_type y, const Color& c);

		Line2D*
		create_line (r_type x1, r_type y1, r_type x2, r_type y2,
					 const Color& c);

		Line2D*
		insert_line (r_type x1, r_type y1, r_type x2, r_type y2,
					 const Color& c);

		Circle2D*
		create_circle (r_type x, r_type y, r_type r,
					   bool filled, const Color& c) const;

		Circle2D*
		insert_circle (r_type x, r_type y, r_type r,
					   bool filled, const Color& c);

		Label2D*
		create_label (const std::string& text, r_type x, r_type y,
					  n_type size, const std::string& font, const Color& c);

		Label2D*
		insert_label (const std::string& text, r_type x, r_type y,
					  n_type size, const std::string& font, const Color& c);

		Polygon2D*
		create_polygon (r_type x, r_type y,
						const std::vector<r_type>& vertices,
						bool filled, const Color& c);

		Polygon2D*
		insert_polygon (r_type x, r_type y,
						const std::vector<r_type>& vertices,
						bool filled, const Color& c);

		Polygon2D*
		create_equilateral_triangle (r_type x, r_type y, r_type size,
									 bool filled, const Color& c);

		Polygon2D*
		insert_equilateral_triangle (r_type x, r_type y, r_type size,
									 bool filled, const Color& c);

		Polygon2D*
		create_triangle (r_type x1, r_type y1,
						 r_type x2, r_type y2,
						 r_type x3, r_type y3,
						 bool filled, const Color& c);

		Polygon2D*
		insert_triangle (r_type x1, r_type y1,
						 r_type x2, r_type y2,
						 r_type x3, r_type y3,
						 bool filled, const Color& c);

		Polygon2D*
		create_rectangle (r_type x, r_type y, r_type width, r_type height,
						  bool filled, const Color& c);

		Polygon2D*
		insert_rectangle (r_type x, r_type y, r_type width, r_type height,
						  bool filled, const Color& c);

		Sprite2D*
		create_sprite (const std::string& path, r_type x, r_type y,
					   r_type w, r_type h, const Color&c = Color::WHITE);

		Sprite2D*
		insert_sprite (const std::string& path, r_type x, r_type y,
					   r_type w, r_type h, const Color&c = Color::WHITE);




		KeyboardController2D*
		zqsd_controller () const;




	protected:
		Keyboard2D* keyboard_;
		Mouse2D* mouse_;
		MusicPlayer2D* music_;
		Application2D* app_;
		ColliderManager2D* cm_;
		Camera2D* cam_;

		r_type delta_;
		r_type pi_;

		virtual void
		init_ ();

		virtual void
		update_ ();

		virtual void
		destroy_ ();


	private:
		Canvas2D* cv_;
	    Object2D* root_;
	    r_type w_;
		r_type h_;

		void
		update_mouse_ ();




	};

}


#endif //!SCENE_2D_HH_