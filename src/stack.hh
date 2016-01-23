/* @file Stack class definition
 */

#ifndef STACK_HH_
# define STACK_HH_

# include <cassert>

namespace opl
{

	///Dynamic stack
	template <class T>
	class Stack
	{

	public:

		Stack ();
		Stack (const Stack& stack);
		~Stack ();

		void
		push(const T& item);

		T
		get () const;

		T
		pop ();

		bool
		empty () const;

	private:

		struct Node
		{
			T item;
			Node* next;
		};

		Node* head_;

		static void
		delete_node_ (Node* node);

		static Node*
		clone_node_ (const Node* node);


	};

	template <class T>
	Stack<T>::Stack ()
		: head_ (nullptr)
	{

	}

	template <class T>
	Stack<T>::Stack (const Stack& stack)
		: Stack ()
	{
		head_ = stack.head_ ? clone_node_ (stack.head_) : nullptr;
	}

	template <class T>
	Stack<T>::~Stack ()
	{
		if (head_)
			delete_node_ (head_);
	}

	template <class T>
	void
	Stack<T>::push (const T &item)
	{
		Node* node = new Node ();
		node->item = item;
		node->next = head_;
		head_ = node;
	}

	template <class T>
	T
	Stack<T>::get () const
	{
		assert (head_);
		return head_->item;
	}

	template <class T>
	T
	Stack<T>::pop ()
	{
		assert (head_);
	    T item = head_->item;
		Node* next = head_->next;
		delete head_;
		head_ = next;
		return item;
	}

	template <class T>
	bool
	Stack<T>::empty () const
	{
		return head_ == nullptr;
	}

	template <class T>
	void
	Stack<T>::delete_node_ (Node* node)
	{
		if (node->next)
			delete_node_ (node->next);
		delete node;
	}

	template <class T>
	typename Stack<T>::Node*
	Stack<T>::clone_node_ (const Node* node)
	{
		Node *clone = new Node ();
		clone->item = node->item;
		clone->next = node->next ? clone_node_ (node->next) : nullptr;
		return clone;
	}



}

#endif //!STACK_HH_