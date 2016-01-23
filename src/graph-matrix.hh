/** @file GraphMatrix class definition
 */

#ifndef GRAPH_MATRIX_HH_
#define GRAPH_MATRIX_HH_

#include <cstddef>
#include <vector>
#include <iostream>

namespace opl
{

	class GraphMatrix
	{

	public:

		GraphMatrix (size_t nb_vertices);

		size_t
		size() const;

		bool
		add_edge (size_t v1, size_t v2, int weight);

		bool
		remove_edge (size_t v1, size_t v2);

		bool
		has_edge (size_t v1, size_t v2) const;

		int
		edge_weight_get (size_t v1, size_t v2) const;

		friend std::ostream& operator<< (std::ostream& os,
										 const GraphMatrix& g);

		std::vector<int>
		usp_from(size_t v);

		void
		wsp_floyd_wharsall(std::vector<int>& distances,
						   std::vector<int>& predecessors);

		std::vector<int>
	    transitive_closure();

		int
		flow_ford_fulkerson(size_t s, size_t t, std::vector<int>& flow_graph);



	private:

		struct Edge
		{
			bool exists;
			int weight;
		};

		size_t nb_vertices_;
		std::vector<Edge> m_;

		static bool
		flow_ford_fulkerson_bfs_ (std::vector<int>& r_graph, size_t s,
								  size_t t, std::vector<int>& parents,
								  size_t n);

	};

}



#endif //!GRAPH_MATRIX_HH_