/** @file DisjointSet class definition
 */

#ifndef DISJOINT_SET_HH_
#define DISJOINT_SET_HH_

# include <cstddef>
# include <vector>

struct DisjointSet
{
	size_t size;
	size_t *parents;
	size_t *ranks;
};
typedef struct DisjointSet DisjointSet;

namespace opl
{

	///Helper Disjoint Set for graph manipulations
	class DisjointSet
	{

	public:

		DisjointSet (size_t size);

		size_t
		find (size_t x);

		void
		set_union (size_t x, size_t y);

	private:
		size_t size_;
		std::vector<size_t> parents_;
		std::vector<size_t> ranks_;

	};

}

#endif //!DISJOINT_SET_HH_