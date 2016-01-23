/* @file FiboMinHeap class definition
 */

#ifndef FIBO_MINHEAP_HH_
# define FIBO_MINHEAP_HH_

# include <cassert>
# include <cstddef>
# include <cmath>
# include <algorithm>
# include <functional>
# include <vector>

namespace opl
{

	///Dynamic fibonacci min heap
	template <class T, class Compare = std::less<T>>
	class FiboMinHeap
	{

	public:

	    FiboMinHeap ();
		~FiboMinHeap ();

		///Break the two heaps and create the union of them
		FiboMinHeap (FiboMinHeap& h1, FiboMinHeap& h2);

		void
		push (const T& item);

		T
		get () const;

		T
		pop ();

		bool
		empty () const;


	private:

		static const Compare cmp_;

	    struct Node
		{
			T key;
			Node* parent;
			Node* child;
			Node* left;
			Node* right;
			size_t degree;
			int mark;
		};

		Node* root_;
		size_t n_;

		void
		decrease_key_ (Node* node, const T& key);

		static void
		delete_node_ (Node* node);

		void
		remove_node_ (Node* node);

		static void
		insert_brother_ (Node* node, Node* brother);

		static void
		link_ (Node* child, Node* parent);

		void
		cut_ (Node* child, Node* parent);

		void
		cascading_cut_ (Node* node);

		void
		consolidate_ ();



	};



	template <class T, class Compare>
	FiboMinHeap<T, Compare>::FiboMinHeap ()
		: root_ (nullptr), n_ (0)
	{

	}

	template <class T, class Compare>
	FiboMinHeap<T, Compare>::~FiboMinHeap ()
	{
		if(root_)
			delete_node_ (root_);
	}

	template <class T, class Compare>
	FiboMinHeap<T, Compare>::FiboMinHeap (FiboMinHeap& h1, FiboMinHeap& h2)
	{
		if (!h1->root)
		{
			h1->root = h2->root;
			h2->root = 0;
		}

		root_ = h1->root;
		n_ = h1->n + h2->n;

		if (h2->root)
		{

			Node* node = h2->root;
			do
			{
				Node* next = node->left;
				insert_brother_ (root_, node);
				node = next;
			} while(node != h2->root);

			if (cmp_ (h2->root->key, h1->root->key))
				root_ = h2->root;
		};
	}


	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::push (const T &item)
	{
	    Node* node = new Node;
		node->degree = 0;
		node->parent = nullptr;
		node->child = nullptr;
		node->mark = 0;
		node->key = item;

		if (!root_)
		{
			root_ = node;
			node->left = node;
			node->right = node;
		}
		else
		{
			insert_brother_ (root_, node);
			if (cmp_ (item, root_->key))
				root_ = node;
		}

		++n_;
	}

	template <class T, class Compare>
	T
	FiboMinHeap<T, Compare>::get () const
	{
		assert (root_);
		return root_->key;
	}

	template <class T, class Compare>
	T
	FiboMinHeap<T, Compare>::pop ()
	{
	    assert (root_);
	    Node* root = root_;
		T min = root->key;

		Node *node = root->child;
		for (size_t i = 0; i < root->degree; ++i)
		{
			Node *next = node->left;
			insert_brother_ (root, node);
			node = next;
		}

		if (root == root->left)
			root_ = nullptr;
		else
		{
			root->left->right = root->right;
			root->right->left = root->left;
			root_ = root->left;
			consolidate_ ();
		}

		delete root;
		--n_;;
		return min;
	}

	template <class T, class Compare>
	bool
	FiboMinHeap<T, Compare>::empty () const
	{
		return !root_;
	}

	template <class T, class Compare>
	const Compare FiboMinHeap<T, Compare>::cmp_ {};


	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::decrease_key_ (Node* node, const T& key)
	{
		node->key = key;
		Node* parent = node->parent;

		if(parent && cmp_ (key, parent->key) < 0)
		{
			cut_ (node, parent);
			cascading_cut_ (parent);
		}

		if (_cmp (key, root_->key))
			root_ = node;
	}

	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::delete_node_ (Node* node)
	{
	    Node* bro = node;
		do
		{
			if(bro->child)
				delete_node_ (bro->child);

			bro = bro->left;
			delete bro->right;
		}
		while (bro != node);
	}

	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::remove_node_ (Node* node)
	{
		decrease_key_ (node, root_->key);
		pop ();
	}

	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::insert_brother_ (Node* node, Node* brother)
	{
		Node* temp = node->left;
		node->left = brother;
		brother->right = node;
		brother->left = temp;
		temp->right = brother;
		brother->parent = node->parent;
	}

	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::link_ (Node* child, Node* parent)
	{
		if (!parent->child)
		{
			parent->child = child;
			child->left = child;
			child->right = child;
			child->parent = parent;
		}
		else
			insert_brother_ (parent->child, child);

		++parent->degree;
		child->mark = 0;
	}

	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::cut_ (Node* child, Node* parent)
	{
		if (child->left == child)
			parent->child = 0;
		else
		{
			child->left->right = child->right;
			child->right->left = child->left;
			if(parent->child == child)
				parent->child = parent->child->left;
		}

		--parent->degree;
		insert_brother (root_, child);
		child->mark = 0;
	}

	template <class T, class Compare>
	void
	FiboMinHeap<T, Compare>::cascading_cut_ (Node* node)
	{
	    Node* parent = node->parent;
		if (parent)
		{
			if (node->mark)
			{
				cut_ (node, parent);
				cascading_cut_ (parent);
			}
			else
				node->mark = 1;
		}
	}

	template<class T, class Compare>
	void
	FiboMinHeap<T, Compare>::consolidate_ ()
	{
		size_t max = log(n_) / 0.481211825;

		std::vector<Node *> arr (max);

		Node* root = root_;
		Node *x = root;

		do
		{
			size_t d = x->degree;
			Node* next = x->left;

			while (arr[d])
			{
				Node* y = arr[d];
				if ( cmp_ (y->key, x->key))
				{
					Node *temp = x;
					x = y;
					y = temp;
				}

				link_ (y, x);
				arr[d] = nullptr;
				++d;
			}

			arr[d] = x;
			x = next;

		} while(x != root);

		root_ = nullptr;

		for(size_t i = 0; i < max; ++i)
		{
			if(arr[i])
			{
				if(root_)
				{
					insert_brother_ (root_, arr[i]);
					if (cmp_ (arr[i]->key, root_->key))
						root_ = arr[i];
				}
				else
				{
					root_ = arr[i];
					root_->left = root_;
					root_->right = root_;
					root_->parent = nullptr;
				}
			}
		}
	}

}

#endif //!FIBO_MIN_HEAP_HH_