#include <algorithm>
#include "graph-list.hh"
#include "queue.hh"
#include "stack.hh"
#include "min-heap.hh"
#include "disjoint-set.hh"

namespace opl
{

	GraphList::GraphList (size_t nb_vertices)
		: nb_vertices_ (nb_vertices), edges_ (nb_vertices, nullptr)
	{

	}

	GraphList::~GraphList ()
	{
		for (size_t i = 0; i < nb_vertices_; ++i)
		{
			Node* edge = edges_[i];
			while (edge)
			{
				Node* next = edge->next;
				delete edge;
				edge = next;
			}
		}
	}

	size_t
	GraphList::size_get () const
	{
		return nb_vertices_;
	}

	bool
	GraphList::add_egde (size_t v1, size_t v2, int weight)
	{
		Node** edge = &(edges_[v1]);
		while (*edge && v2 >= (*edge)->v)
		{
			if ((*edge)->v == v2)
				return false;
			edge = &((*edge)->next);
		}

		Node* temp = *edge;
		*edge = new Node;
		(*edge)->next = temp;
		(*edge)->v = v2;
		(*edge)->weight = weight;

		return true;
	}

	bool
	GraphList::remove_edge (size_t v1, size_t v2)
	{
		Node** edge = &(edges_[v1]);
		while (*edge && v2 >= (*edge)->v)
		{
			if( (*edge)->v == v2)
			{
				Node* temp = *edge;
				*edge = temp->next;
				delete temp;
				return true;
			}
			edge = &((*edge)->next);
		}

		return false;
	}

	bool
	GraphList::has_edge (size_t v1, size_t v2) const
	{
		Node* edge = edges_[v1];
		while (edge && v2 > edge->v)
			edge = edge->next;
		return edge && edge->v == v2;
	}

	int
	GraphList::edge_weight_get (size_t v1, size_t v2) const
	{
		Node* edge = edges_[v1];
		while (edge->v != v2)
			edge = edge->next;
		return edge->weight;
	}

	std::ostream&
	operator<< (std::ostream& os, const GraphList& g)
	{
		os << "     ";
		for (size_t i = 0; i < g.nb_vertices_; ++i)
			os << i << "    ";
		os << "\n";

		for (size_t i = 0; i < g.nb_vertices_; ++i)
		{
			os << i << "   ";
			for (size_t j = 0; j < g.nb_vertices_; ++j)
			{
				if (g.has_edge (i, j))
					os << "|" << g.edge_weight_get (i, j) << "   ";
				else
					os << "|    ";
			}
			os << "|\n";
		}
		return os;
	}

	void
	GraphList::topological_sort_rec_ (std::vector<size_t>& res,
									 std::vector<bool> marked,
									 size_t& pos, size_t v) const
	{
		marked[v] = true;
		Node* edge = edges_[v];
		while (edge)
		{
			if(!marked[edge->v])
				topological_sort_rec_ (res, marked, pos, edge->v);
			edge = edge->next;
		}

		res[--pos] = v;
	}

	std::vector <size_t>
	GraphList::topological_sort () const
	{
		size_t pos = nb_vertices_;
		std::vector <size_t> res (pos);
		std::vector<bool> marked (pos, false);

		for (size_t i = 0; i < nb_vertices_; ++i)
			if (!marked[i])
				topological_sort_rec_ (res, marked, pos, i);

		return res;
	}

	std::vector <int>
	GraphList::usp_from (size_t v) const
	{
		std::vector <int> usp (nb_vertices_, -1);
		std::vector <bool> marked (nb_vertices_, false);
		int level = 0;
		Queue<size_t> q;
		q.push (v);
		q.push (-1);
		marked[v] = true;

		while (true)
		{
			v = q.pop ();
			if (v == static_cast<size_t> (-1))
			{
				if (q.empty ())
					break;
				++level;
				q.push (-1);
				continue;
			}

			usp[v] = level;

			Node* edge = edges_[v];
			while (edge)
			{
				if (!marked[edge->v])
				{
					q.push (edge->v);
					marked[edge->v] = true;
				}
			}
		}

		return usp;
	}

	void
	GraphList::scc_rec_ (std::vector<std::vector<size_t>>& scc, size_t& i,
						 std::vector<size_t>& marks,
						 std::vector<size_t>& low,
						 std::vector<bool>& in_stack, Stack<size_t>& s,
						 size_t v) const

	{
		marks[v] = i;
		low[v] = i;
		s.push (v);
		in_stack[v] = true;
		++i;

		Node* edge = edges_[v];
		while (edge)
		{
			if (marks[edge->v] == static_cast<size_t> (-1))
			{
				scc_rec_ (scc, i, marks, low, in_stack, s, edge->v);
				low[v] = std::min (low[v], low[edge->v]);
			}
			else if(in_stack[edge->v])
				low[v] = std::min (low[v], marks[edge->v]);
			edge = edge->next;
		}

		if(marks[v] == low[v])
		{
			std::vector<size_t> cc (nb_vertices_ + 1);

			size_t w;
			size_t j = 0;
			do
			{
				w = s.pop ();
				in_stack[w] = false;
				cc[++j] = w;
			}
			while(v != w);
			cc[0] = j;
			scc.push_back (cc);
		}
	}


	std::vector<std::vector<size_t>>
	GraphList::scc () const
	{
		std::vector<std::vector<size_t>> scc;
		std::vector<size_t> marks (nb_vertices_, -1);
		std::vector<size_t> low (nb_vertices_, -1);
		std::vector<bool> in_stack (nb_vertices_, false);
		Stack<size_t> s;
		size_t i = 0;

		for(size_t j = 0; j < nb_vertices_; ++j)
		{
			if(marks[j] == static_cast<size_t> (-1))
				scc_rec_ (scc, i, marks, low, in_stack, s, j);
		}
		return scc;
	}

	bool
	GraphList::wsp_bellman_ford (size_t source, std::vector<int>& dist,
								 std::vector<int>& pre) const
	{
		dist.resize (nb_vertices_);
		pre.resize (nb_vertices_);
		for (size_t i = 0; i < nb_vertices_; ++i)
		{
			dist[i] = -1;
			pre[i] = -1;
		}
		dist[source] = 0;

		for (size_t n = 1; n < nb_vertices_; ++n)
		{
			for (size_t i = 0; i < nb_vertices_; ++i)
			{
				if (dist[i] == -1)
					continue;
				Node* edge = edges_[i];
				while (edge)
				{
					if (dist[i] + edge->weight < dist[edge->v])
					{
						dist[edge->v] = dist[i] + edge->weight;
						pre[edge->v] = i;
					}
					edge = edge->next;
				}
			}
		}

		for (size_t i = 0; i < nb_vertices_; ++i)
		{
			if (dist[i] == -1)
				continue;
			Node* edge = edges_[i];
			while (edge)
			{
				if (dist[i] + edge->weight < dist[edge->v])
					return false;
				edge = edge->next;
			}
		}

		return true;
	}



	void
	GraphList::wsp_dijkstra (size_t source, std::vector<int>& dist,
				  std::vector<int>& pred) const
	{
		MinHeap<WSPDHeapItem, WSPDComp> h;
	    dist.resize (nb_vertices_);
		pred.resize (nb_vertices_);
		for(size_t i = 0; i < nb_vertices_; ++i)
		{
			dist[i] = -1;
			pred[i] = -1;
		}

		WSPDHeapItem item;;
		item.v = source;
		item.predecessor = -1;
		item.distance = 0;
		h.push (item);

		while(!h.empty ())
		{
			item = h.pop ();
			size_t v = item.v;
			if(item.distance < dist[item.v])
			{
				dist[v] = item.distance;
				pred[v] = item.predecessor;
			}
			Node* edge = edges_[v];
			int distance = item.distance;

			while(edge)
			{
				if(dist[edge->v] == -1)
				{
					WSPDHeapItem next;
					next.v = edge->v;
					next.predecessor = v;
					next.distance = distance + edge->weight;
					h.push (next);
				}
				edge = edge->next;
			}
		}
	}

	std::vector<GraphList::Edge>
	GraphList::weight_sort () const
	{
		MinHeap<Edge, EdgeComp> h;

		for (size_t i = 0; i < nb_vertices_; ++i)
		{
			Node* edge = edges_[i];
			while (edge)
			{
				Edge true_edge;
				true_edge.u = i;
				true_edge.v = edge->v;
				true_edge.weight = edge->weight;
				h.push (true_edge);
				edge = edge->next;
			}
		}

		std::vector<Edge> res;
		while (!h.empty())
			res.push_back (h.pop ());
		return res;
	}

	std::vector<GraphList::Edge>
	GraphList::mst_kruskal () const
	{
		std::vector<Edge> edges = weight_sort();
		std::vector<Edge> res;
		DisjointSet ds (nb_vertices_);

		for (size_t i = 0; i < edges.size (); ++i)
		{
			if (ds.find (edges[i].u) != ds.find (edges[i].v))
			{
				res.push_back (edges[i]);
				ds.set_union (edges[i].u, edges[i].v);
			}
		}
		return res;
	}


}