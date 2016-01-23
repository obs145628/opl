#include <climits>
#include <cassert>
#include "graph-matrix.hh"
#include "queue.hh"

static const int DISTANCE_INF = INT_MAX;

namespace opl
{

	GraphMatrix::GraphMatrix (size_t nb_vertices)
		: nb_vertices_ (nb_vertices), m_ (nb_vertices * nb_vertices)
	{

	}

	size_t
	GraphMatrix::size() const
	{
		return nb_vertices_;
	}

	bool
	GraphMatrix::add_edge (size_t v1, size_t v2, int weight)
	{
		size_t pos = v1 * nb_vertices_ + v2;
		if (m_[pos].exists)
			return false;
		m_[pos].exists = 1;
		m_[pos].weight = weight;
		return true;
	}

	bool
	GraphMatrix::remove_edge (size_t v1, size_t v2)
	{
		size_t pos = v1 * nb_vertices_ + v2;
		if (m_[pos].exists)
			return false;
		m_[pos].exists = false;
		return true;
	}

	bool
	GraphMatrix::has_edge (size_t v1, size_t v2) const
	{
		return m_[v1 * nb_vertices_ + v2].exists;
	}

	int
	GraphMatrix::edge_weight_get (size_t v1, size_t v2) const
	{
		assert (m_[v1 * nb_vertices_ + v2].exists);
		return m_[v1 * nb_vertices_ + v2].weight;
	}

	std::ostream& operator<< (std::ostream& os, const GraphMatrix& g)
	{
		os << "    ";
		for (size_t i = 0; i < g.nb_vertices_; ++i)
			os << i;
		os << "\n";

		for (size_t i = 0; i < g.nb_vertices_; ++i)
		{
			os << i;
			for (size_t j = 0; j < g.nb_vertices_; ++j)
			{
				if (g.has_edge (i, j))
					os << "|" << g.edge_weight_get (i, j);
				else
					os << "|    ";
			}
			os << "|\n";
		}
		return os;
	}

	std::vector<int>
	GraphMatrix::usp_from(size_t v)
	{
		std::vector<int> usp (nb_vertices_, -1);
		std::vector<bool> marked (nb_vertices_, false);

		int level = 0;

		opl::Queue<size_t> q;
		q.push (v);
		q.push (-1);

		marked[v] = true;

		while(true)
		{
			v = q.pop ();
			if(v == (size_t)-1)
			{
				if (q.empty ())
					break;
				++level;
				q.push (-1);
				continue;
			}

			usp[v] = level;

			size_t offset = v * nb_vertices_;
			for (size_t i = 0; i < nb_vertices_; ++i)
			{
				if (!marked[i] && m_[offset + i].exists)
				{
					q.push (i);
					marked[i] = true;
				}
			}
		}

		return usp;
	}

	void
	GraphMatrix::wsp_floyd_wharsall(std::vector<int>& dist,
									std::vector<int>& pred)
	{
		size_t n = nb_vertices_;
		dist.resize(n * n);
		pred.resize(n * n);

		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				dist[i*n + j] = i == j ? 0 :
					(m_[i*n +j].exists ? m_[i*n + j].weight : INT_MAX);
				pred[i*n + j] = i == j || dist[i*n + j] == INT_MAX ? -1 : i;
			}
		}


		for(size_t k = 0; k < n; ++k)
		{
			for(size_t i = 0; i < n; ++i)
			{
				for(size_t j = 0; j < n; ++j)
				{
					int distij = dist[i*n+j];
					int distik = dist[i*n+k];
					int distkj = dist[k*n+j];
					if(distik == INT_MAX || distkj == INT_MAX)
						break;
					int path = distik + distkj;
					if(distij > path)
					{
						dist[i*n + j] = path;
						pred[i*n + j] = pred[k*n + j];
					}
				}
			}
		}
	}

	std::vector<int>
	GraphMatrix::transitive_closure()
	{
		size_t n = nb_vertices_;
		std::vector<int> tc (n * n);


		for(size_t i = 0; i < n; ++i)
			for(size_t j = 0; j < n; ++j)
				tc[i*n + j] = i == j || m_[i*n + j].exists;

		for(size_t k = 0; k < n; ++k)
			for(size_t i = 0; i < n; ++i)
				for(size_t j = 0; j < n; ++j)
					tc[i*n + j] = tc[i*n + j] || (tc[i*n + k] && tc[k*n + j]);

		return tc;
	}

	int
	GraphMatrix::flow_ford_fulkerson (size_t s,
									  size_t t,
									  std::vector<int>& fgraph)
	{
		size_t n = nb_vertices_;

		std::vector<int> rgraph (n*n);
		for (size_t i = 0; i < n * n; ++i)
			rgraph[i] = m_[i].weight;

		fgraph.resize(n * n, 0);

		std::vector<int> parents (n);

		int max_flow = 0;

		while (flow_ford_fulkerson_bfs_ (rgraph, s, t, parents, n))
		{
			int path_flow = INT_MAX;
			size_t v = t;
			while (v != s)
			{
				size_t u = parents[v];
				path_flow = std::min (path_flow, rgraph[u*n+v]);
				v = u;
			}

			v = t;
			while(v != s)
			{
				size_t u = parents[v];
				rgraph[u*n+v] -= path_flow;
				rgraph[v*n+u] += path_flow;

				if(m_[u*n+v].exists)
					fgraph[u*n+v] += path_flow;
				else
					fgraph[v*n+u] -= path_flow;

				v = u;
			}

			max_flow += path_flow;
		}

		return max_flow;

	}

	bool
	GraphMatrix::flow_ford_fulkerson_bfs_ (std::vector<int>& r_graph,
										   size_t s,
										   size_t t,
										   std::vector<int>& parents,
										   size_t n)
	{
		std::vector<bool> marked (n, false);

		opl::Queue<size_t> q;
		q.push (s);
		marked[s] = true;
		parents[s] = -1;




		while (!q.empty())
		{
		    size_t v = q.pop ();

			for(size_t i = 0; i < n; ++i)
			{
				if (!marked[i] && r_graph[v*n+i] > 0)
				{
					q.push (i);
					parents[i] = v;
					marked[i] = true;
				}
			}
		}

		return marked[t];
	}

}