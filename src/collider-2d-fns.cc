#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include "collider-2d-fns.hh"

namespace opl
{

	bool
	coll2d::coll_test (PixelCollider2D *a,
			   PixelCollider2D *b)
	{
		return a->x_get () == b->x_get()
			&& a->y_get () == b->y_get ();
	}

	bool
	coll2d::coll_test (PixelCollider2D *p,
			   LineCollider2D *l)
	{
	    r_type abx = l->x2_get () - l->x1_get ();
		r_type aby = l->y2_get () - l->y1_get ();
		r_type acx = p->x_get () - l->x1_get ();
		r_type acy = p->y_get () - l->y1_get ();

		if (abx * acy - acx * aby != 0)
		{
			return false;
		}

		r_type dot = abx * acx + aby * acy;
		return dot > 0 && dot <= (abx * abx + aby * aby);
	}

	bool
	coll2d::coll_test (PixelCollider2D *p,
			   CircleCollider2D *c)
	{
		r_type px = p->x_get ();
		r_type py = p->y_get ();
		r_type cx = c->x_get ();
		r_type cy = c->y_get ();
		r_type cr = c->r_get ();

		return (px - cx) * (px - cx) + (py - cy) * (py - cy) <= cr * cr;
	}

	bool
	coll2d::coll_test (PixelCollider2D *px,
			   PolygonCollider2D *pl)
	{
	    bool b = false;
		std::vector<r_type> vertices = pl->vertices_get ();
		size_t n = vertices.size ();

		r_type x = px->x_get ();
		r_type y = px->y_get ();

		for (size_t i = 0, j = n - 2; i < n; j = i, i += 2)
		{
			if( ( (y >= vertices[i + 1]) != (y >= vertices[j + 1]) ) &&
				( (y - vertices[i + 1]) * (vertices[j] - vertices[i])
				  / (vertices[j + 1] - vertices[i + 1]) + vertices[i]) >= x)
			{
				b = !b;
			}
		}
		return b;
	}

	bool
	coll2d::coll_test (PixelCollider2D *p,
			   RectangleCollider2D *r)
	{
	    return p->x_get () >= r->x0_get ()
			&& p->x_get () <= r->x0_get () + r->w_get ()
			&& p->y_get () >= r->y0_get ()
			&& p->y_get () <= r->y0_get () + r->h_get ();
	}

	bool
	coll2d::coll_test (LineCollider2D *l,
									  PixelCollider2D *p)
	{
		return coll2d::coll_test (p, l);
	}

	bool
	coll2d::coll_test (LineCollider2D *l1,
			   LineCollider2D *l2)
	{


		r_type s1x = l1->x2_get () - l1->x1_get ();
		r_type s1y = l1->y2_get () - l1->y1_get ();
		r_type s2x = l2->x2_get () - l2->x1_get ();
		r_type s2y = l2->y2_get () - l2->y1_get ();
		r_type det = -s2x * s1y + s1x * s2y;

		r_type s = (-s1y * (l1->x1_get () - l2->x1_get ())
					+ s1x * (l1->y1_get () - l2->y1_get ())) / det;
		r_type t = ( s2x * (l1->y1_get () - l2->y1_get ())
					 - s2y * (l1->x1_get () - l2->x1_get ())) / det;

		return s >= 0 && s <= 1 && t >= 0 && t <= 1;
	}

	bool
	coll2d::coll_test (LineCollider2D *l,
			   CircleCollider2D *c)
	{

		r_type px = l->x1_get ();
		r_type py = l->y1_get ();
		r_type cx = c->x_get ();
		r_type cy = c->y_get ();
		r_type cr = c->r_get ();

		if ((px - cx) * (px - cx) + (py - cy) * (py - cy) <= cr * cr)
			return true;

	    r_type a = (l->y2_get () - l->y1_get())
			/ (l->x2_get ()- l->x1_get ());
		r_type b = l->y1_get () - a * l->x1_get ();
		r_type u = 1 + a*a;
		r_type v = 2 * (-c->x_get() + a * (b - c->y_get ()));
		r_type w = c->x_get () * c->x_get ()
			+ (b - c->y_get ()) * (b - c->y_get ())
			- c->r_get () * c->r_get ();
		r_type d = v*v - 4*u*w;
		if(d < 0)
		{
			return false;
		}

		r_type sq_d = std::sqrt(d);
		r_type x1 = (-v - sq_d) / (2 * u);
		r_type x2 = (-v + sq_d) / (2 * u);


		return ((x1 >= l->x1_get ()) != (x1 >= l->x2_get ()))
			|| ((x2 >= l->x1_get ()) != (x2 >= l->x2_get ()));
	}

	bool
	coll2d::coll_test (LineCollider2D *l, PolygonCollider2D *p)
	{
		bool b = false;
		std::vector<r_type> vertices = p->vertices_get ();
		size_t n = vertices.size ();

		r_type x = l->x1_get ();
		r_type y = l->y1_get ();

		for (size_t i = 0, j = n - 2; i < n; j = i, i += 2)
		{
			if( ( (y >= vertices[i + 1]) != (y >= vertices[j + 1]) ) &&
				( (y - vertices[i + 1]) * (vertices[j] - vertices[i])
				  / (vertices[j + 1] - vertices[i + 1]) + vertices[i]) >= x)
			{
				b = !b;
			}
		}

		if (b)
		{
			return true;
		}

		r_type s1x = l->x2_get () - l->x1_get ();
		r_type s1y = l->y2_get () - l->y1_get ();

		for (size_t i = 2, c = n; i <= c; i += 2)
		{
			r_type s2x = vertices[i % c] - vertices[i - 2];
			r_type s2y = vertices[i % c + 1] - vertices[i - 1];
			r_type det = -s2x * s1y + s1x * s2y;

			r_type s = (-s1y * (x - vertices[i - 2]) + s1x
						* (y - vertices[i - 1])) / det;
			r_type t = ( s2x * (y - vertices[i - 1]) - s2y
						 * (x - vertices[i - 2])) / det;

			if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
			{
				return true;
			}
		}
		return false;


	}

	bool
	coll2d::coll_test (LineCollider2D *l,
			   RectangleCollider2D *r)
	{
		r_type u1 = std::numeric_limits<r_type>::min ();
		r_type u2 = std::numeric_limits<r_type>::max ();

		if (l->x1_get () == l->x2_get ())
		{
			if (l->x1_get() < r->x0_get())
			{
				return false;
			}
		}
		else
		{
			r_type t = (l->x1_get () - r->x0_get ())
				/ (l->x1_get () - l->x2_get ());
			if (l->x1_get () < l->x2_get() && u1 < t)
			{
				u1 = t;
			}
			else if (l->x1_get () > l->x2_get () && u2 > t)
			{
				u2 = t;
			}
		}

		if (l->x1_get () == l->x2_get ())
		{
			if (r->x0_get () + r->w_get () < l->x1_get ())
			{
				return false;
			}
		}
		else
		{
			r_type t = (r->x0_get () + r->w_get () - l->x1_get ())
				/ (l->x2_get () - l->x1_get ());
			if (l->x2_get () < l->x1_get () && u1 < t)
			{
				u1 = t;
			}
			else if (l->x2_get () > l->x1_get () && u2 > t)
			{
				u2 = t;
			}
		}

		if (l->y1_get() == l->y2_get ())
		{
			if (l->y1_get () < r->y0_get ())
			{
				return false;
			}
		}
		else
		{
			r_type t = (l->y1_get () - r->y0_get ())
				/ (l->y1_get () - l->y2_get ());
			if (l->y1_get () < l->y2_get () && u1 < t)
			{
				u1 = t;
			}
			else if (l->y1_get () > l->y2_get () && u2 > t)
			{
				u2 = t;
			}
		}

		if (l->y1_get() == l->y2_get ())
		{
			if (r->y0_get () + r->h_get () < l->y1_get ())
			{
				return false;
			}
		}
		else
		{
			r_type t = (r->y0_get () + r->h_get () - l->y1_get ())
				/ (l->y2_get () - l->y1_get ());
			if (l->y2_get () < l->y1_get () && u1 < t)
			{
				u1 = t;
			}
			else if (l->y2_get () > l->y1_get () && u2 > t)
			{
				u2 = t;
			}
		}

		return u2 >= u1 && u1 >= 0 && u1 <= 1;
	}

	bool
	coll2d::coll_test (CircleCollider2D *c,
			   PixelCollider2D *p)
	{
		return coll2d::coll_test (p, c);
	}

	bool
	coll2d::coll_test (CircleCollider2D *c,
			   LineCollider2D *l)
	{
	    return coll2d::coll_test (l, c);
	}

	bool
	coll2d::coll_test (CircleCollider2D *c1,
			   CircleCollider2D *c2)
	{
		r_type x1 = c1->x_get ();
		r_type y1 = c1->y_get ();
		r_type r1 = c1->r_get ();
		r_type x2 = c2->x_get ();
		r_type y2 = c2->y_get ();
		r_type r2 = c2->r_get ();

	    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)
			<= (r1 + r2) * (r1 + r2);
	}

	bool
	coll2d::coll_test (CircleCollider2D *c,
			   PolygonCollider2D *p)
	{
		bool b = false;
		std::vector<r_type> vertices = p->vertices_get ();
		size_t n = vertices.size ();

		r_type x = c->x_get ();
		r_type y = c->y_get ();
		r_type r = c->r_get ();

		for (size_t i = 0, j = n - 2; i < n; j = i, i += 2)
		{
			if( ( (y >= vertices[i + 1]) != (y >= vertices[j + 1]) ) &&
				( (y - vertices[i + 1]) * (vertices[j] - vertices[i])
				  / (vertices[j + 1] - vertices[i + 1]) + vertices[i]) >= x)
			{
				b = !b;
			}
		}

		if (b)
		{
			return true;
		}


		for (size_t i = 2; i <= n; i += 2)
		{

			r_type xf = vertices[i % n] - vertices[i - 2];
			r_type yf = vertices[i % n + 1] - vertices[i - 1];

			r_type xac = x - vertices[i - 2];
			r_type yac = y - vertices[i - 1];

			r_type xbc = x - vertices[i % n];
			r_type ybc = y - vertices[i % n + 1];

			r_type len = xf * xf + yf * yf;
			r_type sqlen = std::sqrt (len);
			r_type dp = xac * xf + yac * yf;

			if(dp < 0 && xac * xac + yac * yac <= r * r)
			{
				return true;
			}
			else if (dp > len && xbc * xbc + ybc * ybc <= r * r)
			{
				return true;
			}
			else if (dp >= 0 && dp <= len)
			{

				r_type np = (xac * (-yf) / sqlen) + (yac * xf / sqlen);
				r_type vx = np * yf / sqlen;
				r_type vy = - np * xf / sqlen;
				r_type d = vx * vx + vy * vy;

				if(r * r >= d)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool
	coll2d::coll_test (CircleCollider2D *c,
			   RectangleCollider2D *r)
	{
		r_type cx = c->x_get ();
		r_type cy = c->y_get ();
		r_type cr = c->r_get ();
		r_type rx = r->x0_get ();
		r_type ry = r->y0_get ();
		r_type rw = r->w_get ();
		r_type rh = r->h_get ();

	    if(cx - cr > rx + rw || cx + cr < rx
		   || cy - cr > ry + rh || cy + cr < ry)
		{
			return false;
		}

		r_type dx = ry < cx ? cx - rx - rw : rx - cx;
		r_type dy = ry < cy ? cy - ry - rh : ry - cy;
		if (dx < 0 || dy < 0)
		{
			return true;
		}

		return dx * dx + dy * dy <= cr * cr;
	}

	bool
	coll2d::coll_test (PolygonCollider2D *pl,
			   PixelCollider2D *px)
	{
		return coll2d::coll_test (px, pl);
	}

	bool
	coll2d::coll_test (PolygonCollider2D *p,
			   LineCollider2D *l)
	{
		return coll2d::coll_test (l, p);
	}

	bool
	coll2d::coll_test (PolygonCollider2D *p,
			   CircleCollider2D *c)
	{
	    return coll2d::coll_test (c, p);
	}

	bool
	coll2d::coll_test (PolygonCollider2D *p1,
			   PolygonCollider2D *p2)
	{
		std::vector<r_type> vert1 = p1->vertices_get ();
		std::vector<r_type> vert2 = p2->vertices_get ();
		size_t c1 = vert1.size ();
		size_t c2 = vert2.size ();
		size_t v1 = c1 / 2;
		size_t v2 = c2 / 2;
		size_t v = v1 + v2;

		for(size_t i = 0; i < v; ++i)
		{

			r_type x1;
			r_type x2;
			r_type y1;
			r_type y2;

			if (i < v1)
			{
				x1 = vert1[i * 2];
				y1 = vert1[i * 2 + 1];
				x2 = vert1[(i + 1) % v1 * 2];
				y2 = vert1[(i + 1) % v1 * 2 + 1];
			}
			else
			{
				size_t j = i - v1;
				x1 = vert2[j * 2];
				y1 = vert2[j * 2 + 1];
				x2 = vert2[(j + 1) % v2 * 2];
				y2 = vert2[(j + 1) % v2 * 2 +1];
			}

			r_type normal_x = y1 - y2;
			r_type normal_y = x2 - x1;

			r_type val = vert1[0] * normal_x + vert1[1] * normal_y;
			r_type min1 = val;
			r_type max1 = val;
			for (size_t j = 2; j < c1; j += 2)
			{
				r_type val =  vert1[j] * normal_x + vert1[j + 1] * normal_y;
				if (val < min1)
				{
					min1 = val;
				}
				else if (val > max1)
				{
					max1 = val;
				}
			}

			val =  vert2[0] * normal_x + vert2[1] * normal_y;
			r_type min2 = val;
			r_type max2 = val;
			for (size_t j = 2; j < c2; j+= 2)
			{
				val =  vert2[j] * normal_x + vert2[j + 1] * normal_y;
				if (val < min2)
				{
					min2 = val;
				}
				else if (val > max2)
				{
					max2 = val;
				}
			}

			if( (min1 < min2 && min2 - max1 > 0) || (min1 - max2 > 0) )
			{
				return false;
			}


		}

		return true;
	}

	bool
	coll2d::coll_test (PolygonCollider2D *p,
			   RectangleCollider2D *r)
	{
		r_type x = r->x0_get ();
		r_type y = r->y0_get ();
		r_type w = r->w_get ();
		r_type h = r->h_get ();
		std::vector<r_type> rvert {
			x, y,
			x + w, y,
			x + w, y + h,
			x, y + h
		};

		PolygonCollider2D *rp = new PolygonCollider2D (x + w / 2, y + h / 2,
													   rvert);
		bool res = coll2d::coll_test (p, rp);
		delete rp;
		return res;
	}


	bool
	coll2d::coll_test (RectangleCollider2D *r,
			   PixelCollider2D *p)
	{
		return coll2d::coll_test (p, r);
	}

	bool
	coll2d::coll_test (RectangleCollider2D *r,
			   LineCollider2D *l)
	{
		return coll2d::coll_test (l, r);
	}

	bool
	coll2d::coll_test (RectangleCollider2D *r,
			   CircleCollider2D *c)
	{
		return coll2d::coll_test (c, r);
	}

	bool
	coll2d::coll_test (RectangleCollider2D *r,
			   PolygonCollider2D *p)
	{
		return coll2d::coll_test (p, r);
	}

	bool
	coll2d::coll_test (RectangleCollider2D *a,
			   RectangleCollider2D *b)
	{
	    r_type ax = a->x0_get ();
		r_type ay = a->x0_get ();
		r_type aw = a->w_get ();
		r_type ah = a->h_get ();
		r_type bx = b->x0_get ();
		r_type by = b->y0_get ();
		r_type bw = b->w_get ();
		r_type bh = b->h_get ();

		return ax <= bx + bw && ax + aw >= bx
			&& ay<= by + bh && ay + ah >= by;
	}


	bool
	coll2d::coll_test_px_px (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PixelCollider2D*> (a),
						  static_cast<PixelCollider2D*> (b));
	}


	bool
	coll2d::coll_test_px_l (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PixelCollider2D*> (a),
						  static_cast<LineCollider2D*> (b));
	}

	bool
	coll2d::coll_test_px_c (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PixelCollider2D*> (a),
						  static_cast<CircleCollider2D*> (b));
	}

	bool
	coll2d::coll_test_px_pl (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PixelCollider2D*> (a),
						  static_cast<PolygonCollider2D*> (b));
	}

	bool
	coll2d::coll_test_px_r (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PixelCollider2D*> (a),
						  static_cast<RectangleCollider2D*> (b));
	}





	bool
	coll2d::coll_test_l_px (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<LineCollider2D*> (a),
						  static_cast<PixelCollider2D*> (b));
	}

	bool
	coll2d::coll_test_l_l (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<LineCollider2D*> (a),
						  static_cast<LineCollider2D*> (b));
	}

	bool
	coll2d::coll_test_l_c (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<LineCollider2D*> (a),
						  static_cast<CircleCollider2D*> (b));
	}

	bool
	coll2d::coll_test_l_pl (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<LineCollider2D*> (a),
						  static_cast<PolygonCollider2D*> (b));
	}

	bool
	coll2d::coll_test_l_r (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<LineCollider2D*> (a),
						  static_cast<RectangleCollider2D*> (b));
	}



	bool
	coll2d::coll_test_c_px (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<CircleCollider2D*> (a),
						  static_cast<PixelCollider2D*> (b));
	}

	bool
	coll2d::coll_test_c_l (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<CircleCollider2D*> (a),
						  static_cast<LineCollider2D*> (b));
	}

	bool
	coll2d::coll_test_c_c (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<CircleCollider2D*> (a),
						  static_cast<CircleCollider2D*> (b));
	}

	bool
	coll2d::coll_test_c_pl (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<CircleCollider2D*> (a),
						  static_cast<PolygonCollider2D*> (b));
	}

	bool
	coll2d::coll_test_c_r (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<CircleCollider2D*> (a),
						  static_cast<RectangleCollider2D*> (b));
	}




	bool
	coll2d::coll_test_pl_px (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PolygonCollider2D*> (a),
						  static_cast<PixelCollider2D*> (b));
	}

	bool
	coll2d::coll_test_pl_l (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PolygonCollider2D*> (a),
						  static_cast<LineCollider2D*> (b));
	}

	bool
	coll2d::coll_test_pl_c (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PolygonCollider2D*> (a),
						  static_cast<CircleCollider2D*> (b));
	}

	bool
	coll2d::coll_test_pl_pl (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PolygonCollider2D*> (a),
						  static_cast<PolygonCollider2D*> (b));
	}

	bool
	coll2d::coll_test_pl_r (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<PolygonCollider2D*> (a),
						  static_cast<RectangleCollider2D*> (b));
	}



	bool
	coll2d::coll_test_r_px (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<RectangleCollider2D*> (a),
						  static_cast<PixelCollider2D*> (b));
	}

	bool
	coll2d::coll_test_r_l (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<RectangleCollider2D*> (a),
						  static_cast<LineCollider2D*> (b));
	}

	bool
	coll2d::coll_test_r_c (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<RectangleCollider2D*> (a),
						  static_cast<CircleCollider2D*> (b));
	}

	bool
	coll2d::coll_test_r_pl (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<RectangleCollider2D*> (a),
						  static_cast<PolygonCollider2D*> (b));
	}

	bool
	coll2d::coll_test_r_r (Collider2D* a, Collider2D* b)
	{
		return coll_test (static_cast<RectangleCollider2D*> (a),
						  static_cast<RectangleCollider2D*> (b));
	}


}