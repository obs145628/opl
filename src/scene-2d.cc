#include <algorithm>
#include <cassert>
#include "scene-2d.hh"
#include "scene-infos-2d.hh"
#include "math.hh"

namespace opl
{

	Scene2D::Scene2D ()
	{
	    cv_ = Canvas2D::instance ();
		keyboard_ = Keyboard2D::instance ();
		mouse_ = Mouse2D::instance ();
		music_ = MusicPlayer2D::instance ();
		app_ = Application2D::instance ();
		cm_ = ColliderManager2D::instance ();
		pi_ = math::pi<r_type> ();
	}

	void
	Scene2D::build ()
	{
		root_ = new EmptyObject2D (0, 0);
		mouse_pix_ = new Pixel2D (0, 0, Color::BLACK);
		mouse_pix_->hide ();
		mouse_pix_->collider_set_default ();
		init_ ();
	}

	void
	Scene2D::unbuild ()
	{
		destroy_ ();

		if (cam_)
		{
			delete cam_;
			cam_ = nullptr;
		}

		delete mouse_pix_;
		delete root_;
	}

	void
	Scene2D::render (r_type delta_time)
	{

		w_ = app_->width_get ();
		h_ = app_->height_get ();
		delta_ = delta_time;
		if(cam_)
			cam_->screen_resize (w_, h_);
		update_mouse_ ();

		SceneInfos2D infos;
		infos.cam = cam_;
		infos.mouse = mouse_pix_;
		infos.root = root_;
		infos.canvas = cv_;
		infos.delta = delta_;

		root_->will_update (infos);
		update_ ();
		root_->did_update (infos);



		cv_->draw_color_set (Color::BLACK);
		cv_->fill_rect (0, 0, w_, h_);

		if (cam_)
		{
			r_type src_x = cam_->src_x_get ();
			r_type src_y = cam_->src_y_get ();
			r_type src_w = cam_->src_width_get ();
			r_type src_h = cam_->src_height_get ();
			r_type dst_x = cam_->dst_x_get ();
			r_type dst_y = cam_->dst_y_get ();
			r_type dst_w = cam_->dst_width_get ();
			r_type dst_h = cam_->dst_height_get ();

			r_type sx = dst_w / src_w;
			r_type sy = dst_h / src_h;
			r_type dx = dst_x + dst_w / 2 - sx * src_x;
			r_type dy = dst_y + dst_h / 2 - sy * src_y;

			cv_->draw_color_set (cam_->background_get ());
			cv_->fill_rect (dst_x, dst_y, dst_w, dst_h);
			root_->draw (cv_, dx, dy, sx, sy);
		}

	}



	void
	Scene2D::insert_object (Object2D* obj)
	{
		root_->insert_child (obj);
	}

	void
	Scene2D::remove_object (Object2D* obj)
	{
		root_->remove_child (obj);
	}

	bool
	Scene2D::has_object (Object2D* obj) const
	{
		return root_->has_child (obj);
	}

	size_t
	Scene2D::objects_size () const
	{
		return root_->children_size ();
	}

	void
	Scene2D::clear_objects ()
	{
		root_->clear_children ();
	}

	r_type
	Scene2D::width_get () const
	{
		return w_;
	}

	r_type
	Scene2D::height_get () const
	{
		return h_;
	}

    Vector2D
	Scene2D::scene_to_screen_position (r_type x, r_type y) const
	{
		r_type src_x = cam_->src_x_get ();
		r_type src_y = cam_->src_y_get ();
		r_type src_w = cam_->src_width_get ();
		r_type src_h = cam_->src_height_get ();
		r_type dst_x = cam_->dst_x_get ();
		r_type dst_y = cam_->dst_y_get ();
		r_type dst_w = cam_->dst_width_get ();
		r_type dst_h = cam_->dst_height_get ();
		r_type sx = dst_w / src_w;
		r_type sy = dst_h / src_h;

		r_type x_screen = dst_x + dst_w / 2 + (x - src_x) * sx;
		r_type y_screen = dst_y + dst_h / 2 + (y - src_y) * sy;

		return Vector2D (x_screen, y_screen);
	}

    Vector2D
	Scene2D::scene_to_screen_position (Vector2D v) const
	{
		return scene_to_screen_position (v.x_get (), v.y_get ());
	}

	Vector2D
	Scene2D::screen_to_scene_position (r_type x, r_type y) const
	{
	    r_type src_x = cam_->src_x_get ();
		r_type src_y = cam_->src_y_get ();
		r_type src_w = cam_->src_width_get ();
		r_type src_h = cam_->src_height_get ();
		r_type dst_x = cam_->dst_x_get ();
		r_type dst_y = cam_->dst_y_get ();
		r_type dst_w = cam_->dst_width_get ();
		r_type dst_h = cam_->dst_height_get ();
		r_type sx = dst_w / src_w;
		r_type sy = dst_h / src_h;

		r_type x_scene = (x - dst_x - dst_w / 2) / sx + src_x;
		r_type y_scene = (y - dst_y - dst_h / 2) / sy + src_y;
		return Vector2D (x_scene, y_scene);
	}

	Vector2D
	Scene2D::screen_to_scene_position (Vector2D v) const
	{
		return screen_to_scene_position (v.x_get (), v.y_get ());
	}

	Vector2D
	Scene2D::mouse_position () const
	{
		return mouse_pix_->position_get ();
	}


	Camera2D*
	Scene2D::camera_get () const
	{
		return cam_;
	}

	void
	Scene2D::camera_set (Camera2D* cam)
	{
		if (cam_ && cam_ != cam)
			delete cam_;
		cam_ = cam;
	}

	void
	Scene2D::static_camera_set (r_type x, r_type y)
	{
		Camera2D* cam = new StaticCamera2D (x, y, w_, h_);
		camera_set (cam);
	}

	void
	Scene2D::w_static_camera_set (r_type x, r_type y, r_type width)
	{
		Camera2D* cam = new WStaticCamera2D (x, y, w_, h_, width);
		camera_set (cam);
	}

	void
	Scene2D::h_static_camera_set (r_type x, r_type y, r_type height)
	{
		Camera2D* cam = new HStaticCamera2D (x, y, w_, h_, height);
		camera_set (cam);
	}

	void
	Scene2D::fixed_camera_set (r_type x, r_type y,
							   r_type width, r_type height)
	{
		Camera2D* cam = new FixedCamera2D (x, y, w_, h_, width, height);
		camera_set (cam);
	}




	EmptyObject2D*
	Scene2D::create_empty (r_type x, r_type y) const
	{
		return new EmptyObject2D (x, y);
	}

	EmptyObject2D*
	Scene2D::insert_empty (r_type x, r_type y)
	{
		EmptyObject2D* obj = create_empty (x, y);
		insert_object (obj);
		return obj;
	}


	Pixel2D*
	Scene2D::create_pixel (r_type x, r_type y, const Color& c) const
	{
		return new Pixel2D (x, y, c);
	}

	Pixel2D*
	Scene2D::insert_pixel (r_type x, r_type y, const Color& c)
	{
		Pixel2D* obj = create_pixel (x, y, c);
		insert_object (obj);
		return obj;
	}

	Line2D*
	Scene2D::create_line (r_type x1, r_type y1, r_type x2, r_type y2,
						  const Color& c)
	{
		return new Line2D (x1, y1, x2, y2, c);
	}

	Line2D*
	Scene2D::insert_line (r_type x1, r_type y1, r_type x2, r_type y2,
						  const Color& c)
	{
		Line2D* obj = create_line (x1, y1, x2, y2, c);
		insert_object (obj);
		return obj;
	}

	Circle2D*
	Scene2D::create_circle (r_type x, r_type y, r_type r,
							bool filled, const Color& c) const
	{
		return new Circle2D (x, y, r, filled, c);
	}

	Circle2D*
	Scene2D::insert_circle (r_type x, r_type y, r_type r,
							bool filled, const Color& c)
	{
		Circle2D* obj = create_circle (x, y, r, filled, c);
		insert_object (obj);
		return obj;
	}

	Label2D*
	Scene2D::create_label (const std::string& text, r_type x, r_type y,
						   n_type size, const std::string& font,
						   const Color& c)
	{
		return new Label2D (text, x, y, size, font, c);
	}

	Label2D*
	Scene2D::insert_label (const std::string& text, r_type x, r_type y,
						   n_type size, const std::string& font,
						   const Color& c)
	{
		Label2D* obj = create_label (text, x, y, size, font, c);
		insert_object (obj);
		return obj;
	}

	Polygon2D*
	Scene2D::create_polygon (r_type x, r_type y,
							 const std::vector<r_type>& vertices,
							 bool filled, const Color& c)
	{
		return new Polygon2D (x, y, vertices, filled, c);
	}

	Polygon2D*
	Scene2D::insert_polygon (r_type x, r_type y,
							 const std::vector<r_type>& vertices,
							 bool filled, const Color& c)
	{
		Polygon2D* obj = create_polygon (x, y, vertices, filled, c);
		insert_object (obj);
		return obj;
	}

	Polygon2D*
	Scene2D::create_equilateral_triangle (r_type x, r_type y, r_type size,
										  bool filled, const Color& c)
	{
		return new Polygon2D (Polygon2D::equilateral_triangle(x, y, size,
															  filled, c));
	}

	Polygon2D*
	Scene2D::insert_equilateral_triangle (r_type x, r_type y, r_type size,
										  bool filled, const Color& c)
	{
		Polygon2D* obj = create_equilateral_triangle (x, y, size, filled, c);
		insert_object (obj);
		return obj;
	}

	Polygon2D*
	Scene2D::create_triangle (r_type x1, r_type y1,
							  r_type x2, r_type y2,
							  r_type x3, r_type y3,
							  bool filled, const Color& c)
	{
		return new Polygon2D (Polygon2D::triangle(x1, y1, x2, y2, x3, y3,
												  filled, c));
	}

	Polygon2D*
	Scene2D::insert_triangle (r_type x1, r_type y1,
							  r_type x2, r_type y2,
							  r_type x3, r_type y3,
							  bool filled, const Color& c)
	{
	    Polygon2D* obj = create_triangle(x1, y1, x2, y2, x3, y3, filled, c);
		insert_object (obj);
		return obj;
	}

	Rectangle2D*
	Scene2D::create_rectangle (r_type x, r_type y,
							   r_type width, r_type height,
							   bool filled, const Color& c)
	{
		return new Rectangle2D (x, y, width, height, filled, c);
	}

	Rectangle2D*
	Scene2D::insert_rectangle (r_type x, r_type y,
							   r_type width, r_type height,
							   bool filled, const Color& c)
	{
		Rectangle2D* obj = create_rectangle (x, y, width, height, filled, c);
		insert_object (obj);
		return obj;
	}

	Sprite2D*
	Scene2D::create_sprite (const std::string& path, r_type x, r_type y,
							r_type w, r_type h, const Color&c)
	{
		return new Sprite2D (path, x, y, w, h, c);
	}

	Sprite2D*
	Scene2D::insert_sprite (const std::string& path, r_type x, r_type y,
							r_type w, r_type h, const Color&c)
	{
		Sprite2D* obj = create_sprite (path, x, y, w, h, c);
		insert_object (obj);
		return obj;
	}

	Button2D*
	Scene2D::create_button (const std::string& text, r_type x, r_type y,
							r_type size, r_type w, r_type h)
	{
		return new Button2D (text, x, y, size, w, h);
	}

	Button2D*
	Scene2D::insert_button (const std::string& text, r_type x, r_type y,
							r_type size, r_type w, r_type h)
	{
		Button2D* obj = create_button (text, x, y, size, w, h);
		insert_object (obj);
		return obj;
	}

	TextField2D*
	Scene2D::create_text_field (const std::string& text, r_type x, r_type y,
								r_type size, r_type w, r_type h)
	{
		return new TextField2D (text, x, y, size, w, h);
	}

	TextField2D*
	Scene2D::insert_text_field (const std::string& text, r_type x, r_type y,
								r_type size, r_type w, r_type h)
	{
		TextField2D* obj = create_text_field (text, x, y, size, w, h);
		insert_object (obj);
		return obj;
	}

	MultiLabel2D*
	Scene2D::create_multi_label (const std::string& text, r_type x,
								 r_type y,
								 n_type size, const std::string& font,
								 r_type width, const Color& c)
	{
		return new MultiLabel2D (text, x, y, size, font, width, c);
	}

	MultiLabel2D*
	Scene2D::insert_multi_label (const std::string& text, r_type x,
								 r_type y,
								 n_type size, const std::string& font,
								 r_type width, const Color& c)
	{
		MultiLabel2D* obj = create_multi_label (text, x, y, size,
												font, width, c);
		insert_object (obj);
		return obj;
	}

	ProgressBar2D*
	Scene2D::create_progress_bar (r_type x, r_type y, r_type w, r_type h,
								  r_type value, const Color& border_color,
								  const Color& empty_color,
								  const Color& full_color)
	{
		return new ProgressBar2D (x, y, w, h, value, border_color,
								  empty_color, full_color);
	}

	ProgressBar2D*
	Scene2D::insert_progress_bar (r_type x, r_type y, r_type w, r_type h,
								  r_type value, const Color& border_color,
								  const Color& empty_color,
								  const Color& full_color)
	{
		ProgressBar2D* obj = create_progress_bar (x, y, w, h, value,
												  border_color, empty_color,
												  full_color);
		insert_object (obj);
		return obj;
	}


	KeyboardController2D*
	Scene2D::zqsd_controller () const
	{
		return new KeyboardController2D(Keyboard2D::Q, Keyboard2D::D,
										Keyboard2D::Z, Keyboard2D::S);
	}






	void
	Scene2D::init_ ()
	{

	}

	void
	Scene2D::update_ ()
	{

	}

	void
	Scene2D::destroy_ ()
	{

	}

	void
	Scene2D::update_mouse_ ()
	{
		Vector2D pos = screen_to_scene_position (mouse_->position ());
		mouse_pix_->position_set (pos);
	}



}