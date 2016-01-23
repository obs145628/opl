/** @file RedBlackTree class definition
 **/

#ifndef RED_BLACK_TREE_HH_
#define RED_BLACK_TREE_HH_

# include <cassert>
# include <iostream>
# include <algorithm>
# include <iterator>
# include <functional>

namespace opl
{


	///Dynamic RedBlackTree with prefix iterators
	template<class T, class Compare = std::less<T>>
	class RedBlackTree
	{

	public:
		typedef T value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;

		RedBlackTree ();
		RedBlackTree (const RedBlackTree& tree);
		~RedBlackTree ();

		bool
		insert (const T& key);

		bool
		contains (const T& key) const;

		bool
		remove (const T& key);

		T
		min_get ();

		T
		max_get ();

		bool
		empty () const;

		template<class U, class V>
		friend std::ostream&
			operator<<(std::ostream& os, const RedBlackTree<U, V>& tree);




	private:

		static const Compare cmp_;

		struct Node
		{
			T key;
			Node* left;
			Node* right;
			Node* parent;
			bool is_black;
		};

		Node *root_;
		Node *leaf_;

		void
		delete_node_ (Node* node);

		Node*
		clone_node_ (const Node* node, const Node* leaf);

		void
		replace_node_ (Node* n1, Node* n2);

		void
		remove_node_ (Node* z);

		void
		remove_fixup_ (Node* x);

		void
		rotate_left_ (Node* x);

		void
		rotate_right_ (Node* x);

		void
		insert_fixup_ (Node* z);

		Node*
		min_node_get_ (Node* node);

		Node*
		max_node_get_ (Node* node);

		Node*
		node_predecessor(Node* node);

		Node*
		node_successor(Node* node);

		void
		print_node_ (std::ostream& os, const Node *node) const;

	public:

		class iterator
		{

		public:
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::random_access_iterator_tag iterator_category;

			iterator ()
				: tree_ (nullptr), node_ (nullptr)
			{

			}

			iterator (RedBlackTree* tree, Node* node)
				: tree_ (tree), node_ (node)
			{

			}

			iterator (const iterator& it)
				: tree_ (it.tree_), node_ (it.node_)
			{

			}

			~iterator ()
		    {

			}

			iterator&
			operator= (const iterator& it)
			{
				tree_ = it.tree_;
				node_ = it.node_;
				return *this;
			}

			bool
			operator== (const iterator& it) const
			{
				return node_ == it.node_;
			}

			bool
			operator!= (const iterator& it) const
			{
				return node_ != it.node_;
			}

			iterator&
			operator++ ()
		    {
				assert (node_ != tree_->leaf_);
				node_ = tree_->node_successor (node_);
				return *this;
			}

			iterator
			operator++ (int)
			{
				assert (node_ != tree_->leaf_);
				iterator it = *this;
				node_ = tree_->node_successor (node_);
				return it;
			}

			iterator&
			operator-- ()
			{
				if (node_ != tree_->leaf_)
					node_ = tree_->node_predecessor (node_);
				else
					node_ =  tree_->max_node_get_ (tree_->root_);
				return *this;
			}

			iterator
			operator-- (int)
			{
				iterator it = *this;
				if (node_ != tree_->leaf_)
					node_ = tree_->node_predecessor (node_);
				else
					node_ = tree_->max_node_get_ (tree_->root_);
				return it;
			}

			reference
			operator* () const
			{
				return node_->key;
			}

			pointer
			operator-> () const
			{
				return &(node_->key);
			}

		private:
			RedBlackTree* tree_;
			Node* node_;


		};

		typedef std::reverse_iterator<iterator> reverse_iterator;


		iterator
		begin ()
		{
			return iterator (this, min_node_get_ (root_));
		}

		iterator
		end ()
		{
			return iterator (this, leaf_);
		}

		reverse_iterator
		rbegin ()
	    {
			return reverse_iterator( iterator (this, leaf_));
		}

		reverse_iterator
		rend ()
	    {
			return reverse_iterator( iterator (this,
			    min_node_get_ (root_)));
		}


	};

	template <class T, class Compare>
	RedBlackTree<T, Compare>::RedBlackTree ()
		: root_ (nullptr), leaf_(nullptr)
	{
	    leaf_ = new Node;
		leaf_->is_black = true;
		leaf_->left = nullptr;
		leaf_->right = nullptr;
		root_ = leaf_;
	}

	template <class T, class Compare>
	RedBlackTree<T, Compare>
	::RedBlackTree (const RedBlackTree& tree)
		: RedBlackTree ()
	{
		if (tree.root_)
		{
			root_ = clone_node_ (tree.root_, tree.leaf_);
			root_->parent = leaf_;
		}
	}

	template <class T, class Compare>
	RedBlackTree<T, Compare>::~RedBlackTree ()
	{
		if(root_ != leaf_)
			delete_node_ (root_);
		delete leaf_;
	}

	template <class T, class Compare>
    bool
	RedBlackTree<T, Compare>::insert (const T& key)
	{
	    Node* parent = leaf_;
		Node** node = &root_;

		while (*node != leaf_)
		{
			Node* current_node = *node;
			if (cmp_ (key, current_node->key))
				node = &(current_node->left);
			else if (cmp_ (current_node->key, key))
				node = &(current_node->right);
			else
				return false;
			parent = current_node;
		}

		*node = new Node;
		Node* new_node = *node;
		new_node->key = key;
		new_node->left = leaf_;
		new_node->right = leaf_;
		new_node->parent = parent;
		new_node->is_black = false;
		insert_fixup_ (new_node);
		return true;
	}

	template <class T, class Compare>
	bool
	RedBlackTree<T, Compare>::contains (const T& key) const
	{
		Node* node = root_;
		while(node != leaf_)
		{
			if(cmp_ (key, node->key))
				node = node->left;
			else if(cmp_ (node->key, key))
				node = node->right;
			else
				return true;
		}

		return false;
	}

	template <class T, class Compare>
	bool
	RedBlackTree<T, Compare>::remove (const T& key)
	{
		Node* node = root_;

		while(node != leaf_)
		{
			if (cmp_ (key, node->key))
				node = node->left;
			else if (cmp_ (node->key, key))
				node = node->right;
			else
			{
				remove_node_ (node);
				return true;
			}
		}

		return false;
	}

	template<class T, class Compare>
	T
	RedBlackTree<T, Compare>::min_get ()
	{
		assert (root_);
		return min_node_get_ (root_)->key;
	}

	template<class T, class Compare>
	T
	RedBlackTree<T, Compare>::max_get ()
	{
		assert (root_);
		return max_node_get_ (root_)->key;
	}

	template <class T, class Compare>
	bool
	RedBlackTree<T, Compare>::empty () const
	{
		return root_ == leaf_;
	}

	template <class T, class Compare>
	std::ostream&
	operator<<(std::ostream& os, const RedBlackTree<T, Compare>& tree)
	{
	    tree.print_node_ (os, tree.root_);
		return os;
	}


	template <class T, class Compare>
	Compare const RedBlackTree<T, Compare>::cmp_ {};

	template <class T, class Compare>
	void
	RedBlackTree<T, Compare>::delete_node_ (Node* node)
	{
		if (node->left != leaf_)
			delete_node_ (node->left);
		if (node->right != leaf_)
			delete_node_ (node->right);
		delete node;
	}

	template <class T, class Compare>
	typename RedBlackTree<T, Compare>::Node*
	RedBlackTree<T, Compare>::clone_node_ (const Node* node, const Node* leaf)
	{
		Node *clone = new Node;

		if (node->left != leaf)
		{
			clone->left = clone_node_ (node->left);
			clone->left->parent = clone;
		}
		else
			clone->left = leaf_;

		if (node->right != leaf)
		{
			clone->right = clone_node_ (node->right);
			clone->right->parent = clone;
		}
		else
			clone->right = leaf_;

		clone->key = node->key;
		clone->is_black = node->is_black;
		return clone;
	}

	template <class T, class Compare>
	void
	RedBlackTree<T, Compare>::replace_node_ (Node* n1, Node* n2)
	{
		if (n1->parent == leaf_)
			root_ = n2;
		else if (n1 == n1->parent->left)
			n1->parent->left = n2;
		else
			n1->parent->right = n2;

		n2->parent = n1->parent;
	}

	template<class T, class Compare>
	void
	RedBlackTree<T, Compare>::remove_node_ (Node* z)
	{
		Node* x;
		Node* y = z;
		bool y_is_black = y->is_black;

		if (z->left == leaf_)
		{
			x = z->right;
			replace_node_ (z, z->right);
		}
		else if (z->right == leaf_)
		{
			x = z->left;
			replace_node_ (z, z->left);
		}

		else
		{
			y = min_node_get_ (z->right);
			y_is_black = y->is_black;
			x = y->right;

			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				replace_node_ (y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			replace_node_ (z, y);
			y->left = z->left;
			y->left->parent = y;
			y->is_black = z->is_black;
		}

		if (y_is_black)
			remove_fixup_(x);

		delete z;
	}


	template <class T, class Compare>
	void
	RedBlackTree<T, Compare>::remove_fixup_ (Node* x)
	{
	    while (x != root_ && x->is_black)
		{
			if (x == x->parent->left)
			{
				Node *w = x->parent->right;
				if (!w->is_black)
				{
					w->is_black = true;
					x->parent->is_black = false;
					rotate_left_ (x->parent);
					w = x->parent->right;
				}
				if (w->left->is_black && w->right->is_black)
				{
					w->is_black = false;
					x = x->parent;
				}
				else
				{
					if (w->right->is_black)
					{
						w->left->is_black = true;
						w->is_black = false;
						rotate_right_ (w);
						w = x->parent->right;
					}
					w->is_black = x->parent->is_black;
					x->parent->is_black = true;
					w->right->is_black = true;
					rotate_left_ (x->parent);
					x = root_;
				}
			}

			else
			{
				Node *w = x->parent->left;
				if (!w->is_black)
				{
					w->is_black = true;
					x->parent->is_black = false;
					rotate_right_ (x->parent);
					w = x->parent->left;
				}
				if (w->left->is_black && w->right->is_black)
				{
					w->is_black = false;
					x = x->parent;
				}
				else
				{
					if (w->left->is_black)
					{
						w->right->is_black = true;
						w->is_black = false;
						rotate_left_ (w);
						w = x->parent->left;
					}

					w->is_black = x->parent->is_black;
					x->parent->is_black = true;
					w->left->is_black = true;
					rotate_right_ (x->parent);
					x = root_;
				}
			}
		}
		x->is_black = true;
	}


	template<class T, class Compare>
	void
	RedBlackTree<T, Compare>::rotate_left_ (Node* x)
	{
		Node *y = x->right;

		x->right = y->left;
		if (y->left != leaf_)
			y->left->parent = x;

		y->parent = x->parent;
		if (x->parent == leaf_)
			root_ = y;
		else if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->left = x;
		x->parent = y;
	}

	template<class T, class Compare>
	void
	RedBlackTree<T, Compare>::rotate_right_ (Node* x)
	{
		Node *y = x->left;

		x->left = y->right;
		if (y->right != leaf_)
			y->right->parent = x;

		y->parent = x->parent;
		if (x->parent == leaf_)
			root_ = y;
		else if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->right = x;
		x->parent = y;
	}

	template<class T, class Compare>
	void
	RedBlackTree<T, Compare>::insert_fixup_ (Node *z)
	{
		while (!z->parent->is_black)
		{
			if (z->parent == z->parent->parent->left)
			{
				Node *y = z->parent->parent->right;
				if (!y->is_black)
				{
					z->parent->is_black = true;
					y->is_black = true;
					z->parent->parent->is_black = false;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						rotate_left_ (z);
					}
					z->parent->is_black = true;
					z->parent->parent->is_black = false;
					rotate_right_ (z->parent->parent);
				}
			}

			else
			{
				Node *y = z->parent->parent->left;
				if (!y->is_black)
				{
					z->parent->is_black = true;
					y->is_black = true;
					z->parent->parent->is_black = false;
					z = z->parent->parent;
				}
				else
				{
					if(z == z->parent->left)
					{
						z = z->parent;
						rotate_right_ (z);
					}
					z->parent->is_black = true;
					z->parent->parent->is_black = false;
					rotate_left_ (z->parent->parent);
				}
			}
		}

		root_->is_black = true;
	}


	template <class T, class Compare>
	typename RedBlackTree<T, Compare>::Node*
	RedBlackTree<T, Compare>::min_node_get_ (Node* node)
	{
		while (node->left != leaf_)
			node = node->left;
		return node;
	}

    template <class T, class Compare>
	typename RedBlackTree<T, Compare>::Node*
	RedBlackTree<T, Compare>::max_node_get_ (Node* node)
	{
		while (node->right != leaf_)
			node = node->right;
		return node;
	}

	template<class T, class Compare>
	typename RedBlackTree<T, Compare>::Node*
	RedBlackTree<T, Compare>::node_predecessor(Node* node)
	{
		assert (node != leaf_);

		if (node->left != leaf_)
		{
			node = node->left;
			while (node->right != leaf_)
				node = node->right;
			return node;
		}
		else
		{
			Node *parent = node->parent;
			while (parent != leaf_ && node == parent->left)
			{
				node = parent;
				parent = node->parent;
			}
		    return parent;
		}
	}

    template<class T, class Compare>
	typename RedBlackTree<T, Compare>::Node*
	RedBlackTree<T, Compare>::node_successor(Node* node)
	{
		assert (node != leaf_);

		if (node->right != leaf_)
		{
			node = node->right;
			while (node->left != leaf_)
				node = node->left;
			return node;
		}
		else
		{
			Node *parent = node->parent;
			while (parent != leaf_ && node == parent->right)
			{
				node = parent;
				parent = node->parent;
			}
			return parent;
		}
	}

	template <class T, class Compare>
	void
	RedBlackTree<T, Compare>::print_node_ (std::ostream& os,
										   const Node *node) const
	{
	    if (node == leaf_)
		{
			os << ".";
			return;
		}

		os << "<" << node->key << ",";
		print_node_ (os, node->left);
		os << ",";
		print_node_ (os, node->right);
		os << ">";
	}



}

#endif //!RED_BLACK_TREE_HH_