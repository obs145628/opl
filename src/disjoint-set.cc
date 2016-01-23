#include "disjoint-set.hh"

namespace opl
{

	DisjointSet::DisjointSet (size_t size)
		: size_ (size), parents_ (size), ranks_ (size, 0)
	{
		for(size_t i = 0; i < size; ++i)
			parents_[i] = i;
	}

	size_t
	DisjointSet::find (size_t x)
	{
		if (parents_[x] == x)
			return x;

		size_t res = find (parents_[x]);
		parents_[x] = res;
		return res;
	}

	void
	DisjointSet::set_union (size_t x, size_t y)
	{
		size_t x_parent = find (x);
		size_t y_parent = find (y);
		if (x_parent == y_parent)
			return;

		size_t x_rank = ranks_[x_parent];
		size_t y_rank = ranks_[y_parent];

		if (x_rank < y_rank)
			parents_[x_parent] = y_parent;
		else if (x_rank > y_rank)
			parents_[y_parent] = x_parent;
		else
		{
			parents_[x_parent] = y_parent;
			++ranks_[y_parent];
		}
	}

}