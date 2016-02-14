/** @file Polygon2D class definition
 */

#ifndef POLYGON_2D_HH_
# define POLYGON_2D_HH_

# include <vector>
# include "object-2d.hh"
# include "color.hh"


namespace opl
{

	///2D sdl object reprenting a polygon
	class Polygon2D: public Object2D
	{

	public:

		static Polygon2D
		equilateral_triangle (r_type x, r_type y, r_type size,
							  bool filled, const Color& c);

		static Polygon2D
		triangle (r_type x1, r_type y1,
				  r_type x2, r_type y2,
				  r_type x3, r_type y3,
				  bool filled, const Color& c);

		static Polygon2D
		rectangle (r_type x, r_type y,
				   r_type width, r_type height,
				   bool filled, const Color& c);



		Polygon2D (r_type x, r_type y, const std::vector<r_type>& vertices,
				   bool filled, const Color& c,
				   Collider2D* collider = nullptr);
		virtual ~Polygon2D () = default;

		bool
		is_filled () const;

		void
		set_filled (bool filled);

		size_t
		size () const;

		Vector2D
		vertex_get (size_t i) const;

		void
		vertex_set (size_t i, Vector2D v);

		void
		vertex_set (size_t i, r_type x, r_type y);

		void
		rotate_around_vertex (size_t i, r_type angle);

		Color
		color_get () const;

		void
		color_set (const Color& c);


		virtual r_type
		x_get () const override;

		virtual r_type
		y_get () const override;

		virtual void
		x_set (r_type x) override;

		virtual void
		y_set (r_type y) override;

		virtual void
		x_move (r_type dx) override;

		virtual void
		y_move (r_type dy) override;

		virtual void
		move (r_type dx, r_type dy) override;

		virtual void
		move_to (r_type x, r_type y) override;

		virtual void
		scale (r_type sx, r_type sy) override;

		virtual void
		rotate (r_type angle) override;

		virtual void
		draw (Canvas2D *cv, r_type dx, r_type dy,
			  r_type sx, r_type sy) override;

		virtual void
		collider_set_default ();

	private:
		r_type x_;
		r_type y_;
		std::vector<r_type> vertices_;
		bool filled_;
		Color color_;


	};

}

#endif //!POLYGON_2D_HH_