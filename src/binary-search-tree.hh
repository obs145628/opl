/** @file BinarySearchTree class definition
 **/

#ifndef BINARY_SEARCH_TREE_HH_
#define BINARY_SEARCH_TREE_HH_

# include <cassert>
# include <iostream>
# include <algorithm>
# include <iterator>
# include <functional>

namespace opl
{


	///Dynamic BST with prefix iterators
	template<class T, class Compare = std::less<T>>
	class BinarySearchTree
	{

	public:
		typedef T value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;

		BinarySearchTree ();
		BinarySearchTree (const BinarySearchTree& tree);
		~BinarySearchTree ();

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

		template<class U, class V>
		friend std::ostream&
			operator<<(std::ostream& os, const BinarySearchTree<U, V>& tree);




	private:

		static const Compare cmp_;

		struct Node
		{
			T key;
			Node* left;
			Node* right;
			Node* parent;
		};

		Node *root_;

		static void
		delete_node_ (Node* node);

		static Node*
		clone_node_ (const Node* node);

		void
		replace_node_ (Node* n1, Node* n2);

		void
		remove_node_ (Node* node);

		static Node*
		min_node_get_ (Node* node);

		static Node*
		max_node_get_ (Node* node);

		static Node*
		node_predecessor(Node* node);

		static Node*
		node_successor(Node* node);

		static void
		print_node_ (std::ostream& os, const Node *node);

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

			iterator (BinarySearchTree* tree, Node* node)
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
				assert (node_);
				node_ = node_successor (node_);
				return *this;
			}

			iterator
			operator++ (int)
			{
				assert (node_);
				iterator it = *this;
				node_ = node_successor (node_);
				return it;
			}

			iterator&
			operator-- ()
			{
				if (node_)
					node_ = node_predecessor (node_);
				else
					node_ =  tree_->max_node_get_ (tree_->root_);
				return *this;
			}

			iterator
			operator-- (int)
			{
				iterator it = *this;
				if (node_)
					node_ = node_predecessor (node_);
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
			BinarySearchTree* tree_;
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
			return iterator (this, nullptr);
		}

		reverse_iterator
		rbegin ()
	    {
			return reverse_iterator( iterator (this, nullptr));
		}

		reverse_iterator
		rend ()
	    {
			return reverse_iterator( iterator (this,
			    min_node_get_ (root_)));
		}


	};

	template <class T, class Compare>
	BinarySearchTree<T, Compare>::BinarySearchTree ()
		: root_ (nullptr)
	{

	}

	template <class T, class Compare>
	BinarySearchTree<T, Compare>
	::BinarySearchTree (const BinarySearchTree& tree)
		: BinarySearchTree ()
	{
		if (tree.root_)
		{
			root_ = clone_node_ (tree.root_);
			root_->parent = nullptr;
		}
	}

	template <class T, class Compare>
	BinarySearchTree<T, Compare>::~BinarySearchTree ()
	{
		if(root_)
			delete_node_ (root_);
	}

	template <class T, class Compare>
    bool
	BinarySearchTree<T, Compare>::insert (const T& key)
	{

		Node* parent = nullptr;
		Node** node = &root_;

		while(*node)
		{

			Node* current_node = *node;
		    if (cmp_ (key, current_node->key))
				node = &(current_node->left);
			else if(cmp_ (current_node->key, key))
				node = &(current_node->right);
			else
				return false;
			parent = current_node;
		}

		*node = new Node;
		Node* new_node = *node;
		new_node->key = key;
		new_node->left = nullptr;
		new_node->right = nullptr;
		new_node->parent = parent;
		return true;
	}

	template <class T, class Compare>
	bool
	BinarySearchTree<T, Compare>::contains (const T& key) const
	{
		Node* node = root_;
		while(node)
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
	BinarySearchTree<T, Compare>::remove (const T& key)
	{
		Node* node = root_;
		while(node)
		{
			if(cmp_ (key, node->key))
				node = node->left;
			else if(cmp_ (node->key, key))
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
	BinarySearchTree<T, Compare>::min_get () const
	{
		assert (root_);
		return min_node_get_ (root_)->key;
	}

	template<class T, class Compare>
	T
	BinarySearchTree<T, Compare>::max_get () const
	{
		assert (root_);
		return max_node_get_ (root_)->key;
	}

	template <class T, class Compare>
	bool
	BinarySearchTree<T, Compare>::empty () const
	{
		return root_ == nullptr;
	}

	template <class T, class Compare>
	std::ostream&
	operator<<(std::ostream& os, const BinarySearchTree<T, Compare>& tree)
	{
		BinarySearchTree<T, Compare>::print_node_ (os, tree.root_);
		return os;
	}


	template <class T, class Compare>
	Compare const BinarySearchTree<T, Compare>::cmp_ {};

	template <class T, class Compare>
	void
	BinarySearchTree<T, Compare>::delete_node_ (Node* node)
	{
		if (node->left)
			delete_node_ (node->left);
		if (node->right)
			delete_node_ (node->right);
		delete node;
	}

	template <class T, class Compare>
	typename BinarySearchTree<T, Compare>::Node*
	BinarySearchTree<T, Compare>::clone_node_ (const Node* node)
	{
		Node *clone = new Node;

		if (node->left)
		{
			clone->left = clone_node_ (node->left);
			clone->left->parent = clone;
		}
		else
			clone->left = nullptr;

		if (node->right)
		{
			clone->right = clone_node_ (node->right);
			clone->right->parent = clone;
		}
		else
			clone->right = nullptr;

		clone->key = node->key;
		return clone;
	}

	template <class T, class Compare>
	void
	BinarySearchTree<T, Compare>::replace_node_ (Node* n1, Node* n2)
	{
		if (!n1->parent)
			root_ = n2;
		else if (n1 == n1->parent->left)
			n1->parent->left = n2;
		else
			n1->parent->right = n2;

		if(n2)
			n2->parent = n1->parent;
	}

	template <class T, class Compare>
	void
	BinarySearchTree<T, Compare>::remove_node_ (Node* node)
	{
		if(!node->left)
			replace_node_(node, node->right);
		else if(!node->right)
			replace_node_(node, node->left);

		else
		{
			Node* next = min_node_get_ (node->right);

			if (next->parent != node)
			{
				replace_node_ (next, next->right);
				next->right = node->right;
				next->right->parent = next;
			}

			replace_node_ (node, next);
			next->left = node->left;
			next->left->parent = next;
		}

		delete node;
	}


	template <class T, class Compare>
	typename BinarySearchTree<T, Compare>::Node*
	BinarySearchTree<T, Compare>::min_node_get_ (Node* node)
	{
		while (node->left)
			node = node->left;
		return node;
	}

    template <class T, class Compare>
	typename BinarySearchTree<T, Compare>::Node*
	BinarySearchTree<T, Compare>::max_node_get_ (Node* node)
	{
		while (node->right)
			node = node->right;
		return node;
	}

	template<class T, class Compare>
	typename BinarySearchTree<T, Compare>::Node*
	BinarySearchTree<T, Compare>::node_predecessor(Node* node)
	{
		assert (node);

		if (node->left)
		{
			node = node->left;
			while (node->right)
				node = node->right;
			return node;
		}
		else
		{
			Node *parent = node->parent;
			while (parent && node == parent->left)
			{
				node = parent;
				parent = node->parent;
			}
		    return parent;
		}
	}

    template<class T, class Compare>
	typename BinarySearchTree<T, Compare>::Node*
	BinarySearchTree<T, Compare>::node_successor(Node* node)
	{
		assert (node);

		if (node->right)
		{
			node = node->right;
			while (node->left)
				node = node->left;
			return node;
		}
		else
		{
			Node *parent = node->parent;
			while (parent && node == parent->right)
			{
				node = parent;
				parent = node->parent;
			}
			return parent;
		}
	}

	template <class T, class Compare>
	void
	BinarySearchTree<T, Compare>::print_node_ (std::ostream& os,
											   const Node *node)
	{
	    if (!node)
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

#endif //!BINARY_SEARCH_TREE_HH_