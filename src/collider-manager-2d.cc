#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include "collider-manager-2d.hh"
#include "collider-2d-fns.hh"

namespace opl
{

	ColliderManager2D* ColliderManager2D::instance_ = nullptr;

	ColliderManager2D*
	ColliderManager2D::instance ()
	{
		if (!instance_)
			instance_ = new ColliderManager2D;
		return instance_;
	}

	ColliderManager2D::ColliderManager2D ()
		: fns_ ()
	{

		fns_[fn_id_get_(PixelCollider2D::ID, PixelCollider2D::ID)]
			= coll2d::coll_test_px_px;
		fns_[fn_id_get_(PixelCollider2D::ID, LineCollider2D::ID)]
			= coll2d::coll_test_px_l;
		fns_[fn_id_get_(PixelCollider2D::ID, CircleCollider2D::ID)]
			= coll2d::coll_test_px_c;
		fns_[fn_id_get_(PixelCollider2D::ID, PolygonCollider2D::ID)]
			= coll2d::coll_test_px_pl;
		fns_[fn_id_get_(PixelCollider2D::ID, RectangleCollider2D::ID)]
			= coll2d::coll_test_px_r;

		fns_[fn_id_get_(LineCollider2D::ID, PixelCollider2D::ID)]
			= coll2d::coll_test_l_px;
		fns_[fn_id_get_(LineCollider2D::ID, LineCollider2D::ID)]
			= coll2d::coll_test_l_l;
		fns_[fn_id_get_(LineCollider2D::ID, CircleCollider2D::ID)]
			= coll2d::coll_test_l_c;
		fns_[fn_id_get_(LineCollider2D::ID, PolygonCollider2D::ID)]
			= coll2d::coll_test_l_pl;
		fns_[fn_id_get_(LineCollider2D::ID, RectangleCollider2D::ID)]
			= coll2d::coll_test_l_r;

		fns_[fn_id_get_(CircleCollider2D::ID, PixelCollider2D::ID)]
			= coll2d::coll_test_c_px;
		fns_[fn_id_get_(CircleCollider2D::ID, LineCollider2D::ID)]
			= coll2d::coll_test_c_l;
		fns_[fn_id_get_(CircleCollider2D::ID, CircleCollider2D::ID)]
			= coll2d::coll_test_c_c;
		fns_[fn_id_get_(CircleCollider2D::ID, PolygonCollider2D::ID)]
			= coll2d::coll_test_c_pl;
		fns_[fn_id_get_(CircleCollider2D::ID, RectangleCollider2D::ID)]
			= coll2d::coll_test_c_r;

		fns_[fn_id_get_(PolygonCollider2D::ID, PixelCollider2D::ID)]
			= coll2d::coll_test_pl_px;
		fns_[fn_id_get_(PolygonCollider2D::ID, LineCollider2D::ID)]
			= coll2d::coll_test_pl_l;
		fns_[fn_id_get_(PolygonCollider2D::ID, CircleCollider2D::ID)]
			= coll2d::coll_test_pl_c;
		fns_[fn_id_get_(PolygonCollider2D::ID, PolygonCollider2D::ID)]
			= coll2d::coll_test_pl_pl;
		fns_[fn_id_get_(PolygonCollider2D::ID, RectangleCollider2D::ID)]
			= coll2d::coll_test_pl_r;

		fns_[fn_id_get_(RectangleCollider2D::ID, PixelCollider2D::ID)]
			= coll2d::coll_test_r_px;
		fns_[fn_id_get_(RectangleCollider2D::ID, LineCollider2D::ID)]
			= coll2d::coll_test_r_l;
		fns_[fn_id_get_(RectangleCollider2D::ID, CircleCollider2D::ID)]
			= coll2d::coll_test_r_c;
		fns_[fn_id_get_(RectangleCollider2D::ID, PolygonCollider2D::ID)]
			= coll2d::coll_test_r_pl;
		fns_[fn_id_get_(RectangleCollider2D::ID, RectangleCollider2D::ID)]
			= coll2d::coll_test_r_r;

	}


	bool
	ColliderManager2D::are_colliding (Object2D* a, Object2D* b)
	{
		assert (a->collider_get ());
		assert (b->collider_get ());
		return are_colliding (a->collider_get (), b->collider_get ());
	}

	bool
	ColliderManager2D::are_colliding (Collider2D* a, Collider2D* b)
	{
		size_t id1 = a->id_get ();
		size_t id2 = b->id_get ();
		size_t fn_id = fn_id_get_(id1, id2);

		return fns_[fn_id] (a, b);
	}


	size_t
	ColliderManager2D::fn_id_get_ (size_t id1, size_t id2)
	{
		return id1 * 100 + id2;
	}



}