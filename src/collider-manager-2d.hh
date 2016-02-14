/** @file ColliderManager2D ckass definition
 */

#ifndef COLLIDER_MANAGER_2D_HH_
# define COLLIDER_MANAGER_2D_HH_

# include <cstddef>
# include <map>
# include "object-2d.hh"
# include "collider-2d.hh"

namespace opl
{

	class ColliderManager2D
	{
	public:

		static ColliderManager2D*
		instance ();

		bool
		are_colliding (Object2D* a, Object2D* b);

		bool
		are_colliding (Collider2D* a, Collider2D* b);



	private:
		using coll_fn_type = bool (*) (Collider2D*, Collider2D*);
		static ColliderManager2D* instance_;

		std::map<size_t, coll_fn_type> fns_;



		ColliderManager2D ();
		ColliderManager2D(const ColliderManager2D&) = delete;

		static size_t
		fn_id_get_ (size_t id1, size_t id2);



	};

}

#endif //!COLLIDER_MANAGER_HH_