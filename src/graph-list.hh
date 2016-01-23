/** @file GraphList class definition
 */

#ifndef GRAPH_LIST_HH_
# define GRAPH_LIST_HH_

# include <cstddef>
# include <vector>
# include <iostream>
# include "stack.hh"

namespace opl
{

	class GraphList
	{

	public:

		struct Edge
		{
			size_t u;
			size_t v;
			int weight;
		};



		GraphList (size_t nb_vertices);
		~GraphList ();

		size_t
		size_get () const;

		bool
		add_egde (size_t v1, size_t v2, int weight);

		bool
		remove_edge (size_t v1, size_t v2);

		bool
		has_edge (size_t v1, size_t v2) const;

		int
		edge_weight_get (size_t v1, size_t v2) const;

		friend std::ostream&
		operator<< (std::ostream& os, const GraphList& g);

		std::vector <size_t>
		topological_sort () const;

		std::vector <int>
		usp_from (size_t v) const;

	    std::vector<std::vector<size_t>>
		scc () const;

		bool
		wsp_bellman_ford (size_t source, std::vector<int>& distances,
						  std::vector<int>& predecessors) const;

		void
		wsp_dijkstra (size_t source, std::vector<int>& distances,
					  std::vector<int>& predecessors) const;


		std::vector<Edge>
		weight_sort () const;

		std::vector<Edge>
		mst_kruskal () const;

	private:

		struct Node
		{
			size_t v;
			int weight;
			Node* next;
		};

		size_t nb_vertices_;
		std::vector<Node*> edges_;

		struct WSPDHeapItem
		{
			size_t v;
			int predecessor;
			int distance;
		};


		class EdgeComp
		{
		public:
			bool
			operator() (Edge a, Edge b) const
			{
				return a.weight < b.weight;
			}
		};

		class WSPDComp
		{
		public:
			bool
			operator() (WSPDHeapItem a, WSPDHeapItem b) const
			{
				return a.distance < b.distance;
			}
		};



		void
		topological_sort_rec_ (std::vector<size_t>& res,
							   std::vector<bool> marked,
							   size_t& pos, size_t v) const;

	    void
		scc_rec_ (std::vector<std::vector<size_t>>& scc, size_t& i,
				  std::vector<size_t>& marks,
				  std::vector<size_t>& low,
				  std::vector<bool>& in_stack, Stack<size_t>& s,
				  size_t v) const;


	};


}

#endif //!GRAPH_LIST_HH_