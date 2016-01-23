/* @file MinHeap class definition
 */

#ifndef MINHEAP_HH_
# define MINHEAP_HH_

# include <cassert>
# include <cstddef>
# include <algorithm>
# include <functional>
# include <vector>
# include <iostream>

namespace opl
{

	///Dynamic min heap
	template <class T, class Compare = std::less<T>>
	class MinHeap
	{

	public:

	    MinHeap ();

		template<class It>
		MinHeap (It begin, It end);

		void
		push(const T& item);

		T
		get () const;

		T
		pop ();

		size_t
		size () const;

		bool
		empty () const;


	private:

		static const Compare cmp_;

		std::vector<T> data_;

		void
		resolve_ (size_t i);



	};



	template <class T, class Compare>
	MinHeap<T, Compare>::MinHeap ()
		: data_ ()
	{

	}

	template <class T, class Compare>
	template <class It>
	MinHeap<T, Compare>::MinHeap (It begin, It end)
	: MinHeap ()
	{
		data_.insert (data_.begin(), begin, end);
		size_t count = data_.size ();
		for (size_t i = count / 2; i < count; --i)
			resolve_ (i);
	}


	template <class T, class Compare>
	void
	MinHeap<T, Compare>::push (const T &item)
	{
		size_t i = data_.size ();
		data_.push_back(item);

		while(i && cmp_ (item, data_[i / 2]))
		{
			std::swap (data_[i], data_[i / 2]);
			i /= 2;
		}
	}

	template <class T, class Compare>
	T
	MinHeap<T, Compare>::get () const
	{
		assert (!data_.empty ());
		return data_[0];
	}

	template <class T, class Compare>
	T
	MinHeap<T, Compare>::pop ()
	{
	    assert (!data_.empty ());
		T min = data_[0];
		data_[0] = data_.back ();
		data_.pop_back ();
		resolve_ (0);
		return min;
	}

	template <class T, class Compare>
	size_t
	MinHeap<T, Compare>::size () const
	{
		return data_.size ();
	}

	template <class T, class Compare>
	bool
	MinHeap<T, Compare>::empty () const
	{
		return data_.empty ();
	}

	template<class T, class Compare>
	void
	MinHeap<T, Compare>::resolve_ (size_t i)
	{
		while(true)
		{
			size_t l = i * 2;
			size_t r = l + 1;
			size_t min = (l < data_.size()
						  && cmp_ (data_[l], data_[i])) ? l : i;
			if (r < data_.size() && cmp_ (data_[r], data_[min]))
				min = r;

			if (min == i)
				return;

			std::swap (data_[i], data_[min]);
			i = min;
		}
	}

	template <class T, class Compare>
	const Compare MinHeap<T, Compare>::cmp_ {};



}

#endif //!MIN_HEAP_HH_