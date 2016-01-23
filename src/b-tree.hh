/** @file BTree class definition
 **/

#ifndef B_TREE_HH_
#define B_TREE_HH_

# include <cassert>
# include <iostream>
# include <algorithm>
# include <iterator>
# include <functional>
# include <array>

namespace opl
{


	///Dynamic BTree with template order
	template<class T, size_t N = 1024, class Compare = std::less<T>>
	class BTree
	{

	public:

		BTree ();
		BTree (const BTree& tree);
		~BTree ();

		bool
		insert (const T& key);

		bool
		contains (const T& key) const;

		bool
		remove (const T& key);

		T
		min_get () const;

		T
		max_get () const;

		bool
		empty () const;

	private:

		static const Compare cmp_;

		struct Node
		{
			size_t keys_size;
			std::array<T, 2 * N - 1> keys;
			std::array<Node*, 2 * N> children;
		};

		Node* root_;

		static void
		delete_node_ (Node* node);

		static Node*
		clone_node_ (const Node* node);

		static bool
		remove_rec_ (Node* node, const T& key);

		static T
		min_key_get_ (const Node* node);

		static T
		max_key_get_ (const Node* node);

		static size_t
		pos_get_ (const Node* node, const T& key);

		static void
		rotate_left_ (Node* node, size_t i);

		static void
		rotate_right_ (Node* node, size_t i);

		static void
		split_ (Node* node, size_t i);

		static void
		fusion_ (Node* node, size_t i);

	};

	template <class T, size_t N, class Compare>
	BTree<T, N, Compare>::BTree ()
		: root_ (nullptr)
	{

	}

	template <class T, size_t N, class Compare>
	BTree<T, N, Compare>
	::BTree (const BTree& tree)
		: BTree ()
	{
		if (tree.root_)
			root_ = clone_node_ (tree.root_);
	}

	template <class T, size_t N, class Compare>
	BTree<T, N, Compare>::~BTree ()
	{
		if(root_)
			delete_node_ (root_);
	}

	template <class T, size_t N, class Compare>
    bool
	BTree<T, N, Compare>::insert (const T& key)
	{
	    if(!root_)
		{
			root_ = new Node;
			root_->keys[0] = key;
			root_->children[0] = nullptr;
			root_->children[1] = nullptr;
			root_->keys_size = 1;
			return true;
		}

		if(root_->keys_size == 2 * N - 1)
		{
			Node *root = new Node;
			root->children[0] = root_;
			root->keys_size = 0;
			split_ (root, 0);
			root_ = root;
		}

		Node *node = root_;

		while(true)
		{
			size_t pos = pos_get_ (node, key);

			if(pos < node->keys_size && !cmp_ (key, node->keys[pos])
			   && !cmp_ (node->keys[pos], key))
				return false;

			if (!node->children[0])
			{
				std::move (node->keys.begin () + pos,
						   node->keys.begin () + node->keys_size,
						   node->keys.begin () + pos + 1);

				node->keys[pos] = key;
				++node->keys_size;
				node->children[node->keys_size] = nullptr;
				return true;
			}

			if(node->children[pos]->keys_size == 2 * N - 1)
			{
				if (!cmp_ (key, node->keys[N - 1])
				   && !cmp_ (node->keys[N - 1], key))
					return false;

				split_ (node, pos);
				if (cmp_ (node->keys[pos], key))
					++pos;
			}

			node = node->children[pos];
		}
	}

	template <class T, size_t N, class Compare>
	bool
	BTree<T, N, Compare>::contains (const T& key) const
	{
	    Node *node = root_;
		while (node)
		{
			size_t pos = pos_get_ (node, key);
			if (pos < node->keys_size && !cmp_ (key, node->keys[pos])
				&& !cmp_ (node->keys[pos], key))
				return true;
			else
				node = node->children[pos];
		}

		return false;
	}

	template <class T, size_t N, class Compare>
	bool
	BTree<T, N, Compare>::remove (const T& key)
	{
	    if (!root_)
			return false;
		bool removed = remove_rec_ (root_, key);

		if (!root_->keys_size)
		{
			Node *temp = root_;
			root_ = temp->children[0];
			delete temp;
		}

		return removed;
	}

	template<class T, size_t N, class Compare>
	T
	BTree<T, N, Compare>::min_get () const
	{
		assert (root_);
		return min_key_get_ (root_);
	}

	template<class T, size_t N, class Compare>
	T
	BTree<T, N, Compare>::max_get () const
	{
		assert (root_);
		return max_key_get_ (root_);
	}

	template <class T, size_t N, class Compare>
	bool
	BTree<T, N, Compare>::empty () const
	{
		return root_ == nullptr;
	}


	template <class T, size_t N, class Compare>
	Compare const BTree<T, N, Compare>::cmp_ {};

	template <class T, size_t N, class Compare>
	void
	BTree<T, N, Compare>::delete_node_ (Node* node)
	{
	    if (node->children[0])
			for(size_t i = 0; i <= node->keys_size; ++i)
				delete_node_ (node->children[i]);
		delete node;
	}

	template <class T, size_t N, class Compare>
	typename BTree<T, N, Compare>::Node*
	BTree<T, N, Compare>::clone_node_ (const Node* node)
	{
		Node *clone = new Node;

		for (size_t i = 0; i < node->keys_size; ++i)
			clone->keys[i] = node->keys[i];

		for (size_t i = 0; i <= node->keys_size; ++i)
			if (node->children[i])
				clone->children[i] = clone_node_ (node->children[i]);

		clone->keys_size = node->keys_size;
		return clone;
	}


	template <class T, size_t N, class Compare>
	bool
	BTree<T, N, Compare>::remove_rec_ (Node* node, const T& key)
	{
	    size_t i = pos_get_ (node, key);

		if (node->children[0])
		{
			if(i < node->keys_size && !cmp_ (key, node->keys[i])
			   && !cmp_ (node->keys[i], key))
			{
				if(node->children[i]->keys_size > node->children[i+1]->keys_size)
				{
					node->keys[i] = max_key_get_ (node->children[i]);
					return remove_rec_ (node->children[i], node->keys[i]);
				}
				else
				{
					if(node->children[i+1]->keys_size > N - 1)
					{
						node->keys[i] = min_key_get_ (node->children[i+1]);
						return remove_rec_ (node->children[i + 1], node->keys[i]);
					}
					else
					{
						fusion_ (node, i);
						return remove_rec_ (node->children[i], key);
					}
				}
			}

			else
			{
				if (node->children[i]->keys_size == N - 1)
				{
					if(i && node->children[i - 1]->keys_size > N - 1)
						rotate_right_ (node, i);
					else
					{
						if(i < node->keys_size && node->children[i+1]->keys_size > N - 1)
							rotate_left_ (node, i);
						else
						{
							if(i)
								--i;
							fusion_ (node, i);
						}
					}
				}
				return remove_rec_ (node->children[i], key);
			}
		}


		else
		{
			if(i < node->keys_size && !cmp_ (key, node->keys[i])
			   && !cmp_ (node->keys[i], key))
			{
				std::move (node->keys.begin () + i + 1,
						   node->keys.begin () + node->keys_size,
						   node->keys.begin () + i);
				--node->keys_size;
				return true;
			}
			else
				return false;
		}
	}


	template <class T, size_t N, class Compare>
	T
	BTree<T, N, Compare>::min_key_get_ (const Node* node)
	{
		while (node->children[0])
			node = node->children[0];
		return node->keys[0];
	}

    template <class T, size_t N, class Compare>
	T
	BTree<T, N, Compare>::max_key_get_ (const Node* node)
	{
		while (node->children[0])
			node = node->children[node->keys_size];
		return node->keys[node->keys_size - 1];
	}

	template<class T, size_t N, class Compare>
	size_t
	BTree<T, N, Compare>::pos_get_ (const Node* node, const T& key)
	{
		size_t l = 0;
		size_t r = node->keys_size - 1;

		while (r + 1 && l <= r)
		{
			size_t m = (l + r) / 2;
			if (cmp_ (key, node->keys[m]))
				r = m - 1;
			else if (cmp_ (node->keys[m], key))
				l = m + 1;
			else
				return m;
		}
		return l;
	}

	template <class T, size_t N, class Compare>
	void
	BTree<T, N, Compare>::rotate_left_ (Node* node, size_t i)
	{
		Node *l = node->children[i];
		Node *r = node->children[i + 1];

		++l->keys_size;
		l->keys[l->keys_size - 1] = node->keys[i];
		l->children[l->keys_size] = r->children[0];
		node->keys[i] = r->keys[0];

		std::move (r->keys.begin () + 1, r->keys.begin() + r->keys_size,
				   r->keys.begin ());

		if (r->children[0])
		{
			std::move(r->children.begin () + 1,
					  r->children.begin () + r->keys_size + 1,
					  r->children.begin ());
		}

		--r->keys_size;
	}

	template <class T, size_t N, class Compare>
	void
	BTree<T, N, Compare>::rotate_right_ (Node* node, size_t i)
	{
		Node *l = node->children[i-1];
		Node *r = node->children[i];

		std::move (r->children.begin () + 1,
				   r->children.begin () + r->keys_size + 1,
				   r->children.begin () + 2);

		std::move (r->keys.begin (), r->keys.begin () + r->keys_size,
				   r->keys.begin () + 1);

		r->children[1] = r->children[0];
		r->keys[0] = node->keys[i-1];
		++r->keys_size;

		node->keys[i-1] = l->keys[l->keys_size-1];
		r->children[0] = l->children[l->keys_size];
		--l->keys_size;
	}

	template <class T, size_t N, class Compare>
	void
	BTree<T, N, Compare>::split_ (Node* node, size_t i)
	{
		Node* l = node->children[i];
		Node* r = new Node;

		std::move (l->children.begin () + N, l->children.begin () + 2 * N - 1,
				   r->children.begin ());

		std::move (l->keys.begin () + N, l->keys.end (),
				   r->keys.begin ());

		r->children[N - 1] = l->children[2 * N - 1];
		r->keys_size = N - 1;
		l->keys_size = N - 1;

		std::move (node->children.begin () + i + 1,
				   node->children.begin () + node->keys_size + 1,
				   node->children.begin () + i + 2);

		std::move (node->keys.begin () + i,
				   node->keys.begin () + node->keys_size,
				   node->keys.begin () + i + 1);

		node->children[i+1] = r;
		node->keys[i] = l->keys[N - 1];
		++node->keys_size;
	}

	template<class T, size_t N, class Compare>
	void
	BTree<T, N, Compare>::fusion_ (Node* node, size_t i)
	{
		Node *l = node->children[i];
		Node *r = node->children[i + 1];

		l->keys[N - 1] = node->keys[i];

		std::move (r->keys.begin (), r->keys.begin () + N - 1,
				   l->keys.begin () + N);

		std::move (r->children.begin (), r->children.begin () + N - 1,
				   l->children.begin () + N);

		l->children[2 * N - 1] = r->children[N - 1];
		l->keys_size = 2 * N - 1;
		delete r;

		std::move (node->keys.begin () + i + 1,
				   node->keys.begin () + node->keys_size,
				   node->keys.begin () + i);
		std::move (node->children.begin () + i + 2,
				   node->children.begin () + node->keys_size + 1,
				   node->children.begin () + i + 1);

		--node->keys_size;
	}

}

#endif //!B_TREE_HH_