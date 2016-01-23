/* @file Queue class definition
 */

#ifndef QUEUE_HH_
# define QUEUE_HH_

# include <cassert>

namespace opl
{

	///Dynamic queue
	template <class T>
	class Queue
	{

	public:

		Queue ();
		Queue (const Queue& queue);
		~Queue ();

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


	};

	template <class T>
	Queue<T>::Queue ()
		: head_ (nullptr)
	{

	}

	template <class T>
	Queue<T>::Queue (const Queue& queue)
		: Queue ()
	{
	    if(!queue.head_)
			return;

		Node* src_node = queue.head_;
		Node** dst = &head_;

		do
		{
			*dst = new Node;
			(*dst)->item = src_node->item;
			dst = &((*dst)->next);
			src_node = src_node->next;
		}
		while (src_node != queue.head_);

		*dst = head_;
	}

	template <class T>
	Queue<T>::~Queue ()
	{
		if(!head_)
			return;

		Node* node = head_->next;
		while (node != head_)
		{
			Node *temp = node;
			node = node->next;
			delete temp;
		}

		delete head_;
	}

	template <class T>
	void
	Queue<T>::push (const T &item)
	{
	    Node* head = head_;
		Node* node = new Node;
		node->item = item;
	    head_ = node;

		if(!head)
			node->next = node;
		else
		{
			node->next = head->next;
			head->next = node;
		}
	}

	template <class T>
	T
	Queue<T>::get () const
	{
		assert (head_);
		return head_->next->item;
	}

	template <class T>
	T
	Queue<T>::pop ()
	{
		assert (head_);
	    Node* head = head_;
		Node* top = head->next;
		T item = top->item;

		if(head == top)
			head_ = nullptr;
		else
			head->next = top->next;

		delete top;
		return item;
	}

	template <class T>
	bool
	Queue<T>::empty () const
	{
		return head_ == nullptr;
	}



}

#endif //!QUEUE_HH_