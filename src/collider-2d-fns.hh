/** @file set of function for testing 2D collisions
 */

#ifndef COLLIDER_2D_FNS_HH_
# define COLLIDER_2D_FNS_HH_

# include "collider-2d.hh"
# include "pixel-collider-2d.hh"
# include "line-collider-2d.hh"
# include "circle-collider-2d.hh"
# include "polygon-collider-2d.hh"
# include "rectangle-collider-2d.hh"

namespace opl
{

	namespace coll2d
	{

		bool
		coll_test (PixelCollider2D *a, PixelCollider2D *b);
		bool
		coll_test (PixelCollider2D *p, LineCollider2D *l);
		bool
		coll_test (PixelCollider2D *p, CircleCollider2D *c);
		bool
		coll_test (PixelCollider2D *px, PolygonCollider2D *pl);
		bool
		coll_test (PixelCollider2D *p, RectangleCollider2D *r);

		bool
		coll_test (LineCollider2D *l, PixelCollider2D *p);
		bool
		coll_test (LineCollider2D *l1, LineCollider2D *l2);
		bool
		coll_test (LineCollider2D *l, CircleCollider2D *c);
		bool
		coll_test (LineCollider2D *l, PolygonCollider2D *p);
		bool
		coll_test (LineCollider2D *l, RectangleCollider2D *r);

		bool
		coll_test (CircleCollider2D *c, PixelCollider2D *p);
		bool
		coll_test (CircleCollider2D *c, LineCollider2D *l);
		bool
		coll_test (CircleCollider2D *c1, CircleCollider2D *c2);
		bool
		coll_test (CircleCollider2D *c, PolygonCollider2D *p);
		bool
		coll_test (CircleCollider2D *c, RectangleCollider2D *r);

		bool
		coll_test (PolygonCollider2D *pl, PixelCollider2D *px);
		bool
		coll_test (PolygonCollider2D *p, LineCollider2D *l);
		bool
		coll_test (PolygonCollider2D *p, CircleCollider2D *c);
		bool
		coll_test (PolygonCollider2D *p1, PolygonCollider2D *p2);
		bool
		coll_test (PolygonCollider2D *p, RectangleCollider2D *r);


		bool
		coll_test (RectangleCollider2D *r, PixelCollider2D *p);
		bool
		coll_test (RectangleCollider2D *r, LineCollider2D *l);
		bool
		coll_test (RectangleCollider2D *r, CircleCollider2D *c);
		bool
		coll_test (RectangleCollider2D *r, PolygonCollider2D *p);
		bool
		coll_test (RectangleCollider2D *a, RectangleCollider2D *b);


		bool
		coll_test_px_px (Collider2D* a, Collider2D* b);
		bool
		coll_test_px_l (Collider2D* a, Collider2D* b);
		bool
		coll_test_px_c (Collider2D* a, Collider2D* b);
		bool
		coll_test_px_pl (Collider2D* a, Collider2D* b);
		bool
		coll_test_px_r (Collider2D* a, Collider2D* b);

	    bool
		coll_test_l_px (Collider2D* a, Collider2D* b);
		bool
		coll_test_l_l (Collider2D* a, Collider2D* b);
		bool
		coll_test_l_c (Collider2D* a, Collider2D* b);
		bool
		coll_test_l_pl (Collider2D* a, Collider2D* b);
		bool
		coll_test_l_r (Collider2D* a, Collider2D* b);

		bool
		coll_test_c_px (Collider2D* a, Collider2D* b);
		bool
		coll_test_c_l (Collider2D* a, Collider2D* b);
		bool
		coll_test_c_c (Collider2D* a, Collider2D* b);
		bool
		coll_test_c_pl (Collider2D* a, Collider2D* b);
		bool
		coll_test_c_r (Collider2D* a, Collider2D* b);

		bool
		coll_test_pl_px (Collider2D* a, Collider2D* b);
		bool
		coll_test_pl_l (Collider2D* a, Collider2D* b);
		bool
		coll_test_pl_c (Collider2D* a, Collider2D* b);
		bool
		coll_test_pl_pl (Collider2D* a, Collider2D* b);
		bool
		coll_test_pl_r (Collider2D* a, Collider2D* b);

		bool
		coll_test_r_px (Collider2D* a, Collider2D* b);
		bool
		coll_test_r_l (Collider2D* a, Collider2D* b);
		bool
		coll_test_r_c (Collider2D* a, Collider2D* b);
		bool
		coll_test_r_pl (Collider2D* a, Collider2D* b);
		bool
		coll_test_r_r (Collider2D* a, Collider2D* b);

	}

}

# endif //!COLLIDER_2D_FN_HH