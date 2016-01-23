/** @file Vector class definition
 */

#ifndef VECTOR_HH_
#define VECTOR_HH_

# include <cstddef>
# include <cassert>
# include <algorithm>
# include <iterator>
# include <stdexcept>
# include <iostream>
# include <vector>
# include "algo.hh"
# include "serialization.hh"

namespace opl
{

	template<class T>
	class Matrix;

	template<class T>
	class Vector
	{

	public:
		typedef T value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;


		Vector (size_type count = 0);
		Vector (size_type count, const T& x);

		template <class It>
		Vector (It begin, It end);

		Vector (std::initializer_list<T> list);
		Vector (const Vector& v);
		~Vector ();

		Vector&
		operator= (const T& x);

		Vector&
		operator= (const Vector& v);

		Vector&
		operator= (std::initializer_list<T> list);

		void
		assign (const T& x);

		void
		assign (const Vector& v);

		void
		assign (std::initializer_list<T> list);

		template <class It>
		void
		assign (It begin, It end);

		///Resize and recopy the vector, new values are unitialized
		void
		resize (size_type n);

		///Resizes and recopy the vector, new values are set to x
		void
		resize (size_type n, const T& x);

		size_type
		size () const;

		bool
		empty () const;

		reference
		at (size_type n);

		const_reference
		at (size_type n) const;

		reference
		operator[] (size_type n);

		const_reference
		operator[] (size_type n) const;

		T*
		data ();

		const T*
		data () const;


		void
		swap (Vector& v);

		template<class U>
		friend std::ostream&
		operator<< (std::ostream& os, const Vector<U>& v);



		template <class U>
		friend bool
		operator== (const Vector<U>& a, const Vector<U>& b)
		{
			if (a.size_ != b.size_)
				return false;
			for (size_t i = 0; i < a.size_; ++i)
				if (a.data_[i] != b.data_[i])
					return false;
			return true;
		}

		template <class U>
		friend bool
		operator!= (const Vector<U>& a, const Vector<U>& b)
		{
			if (a.size_ != b.size_)
				return true;
			for (size_t i = 0; i < a.size_; ++i)
				if (a.data_[i] != b.data_[i])
					return true;
			return false;
		}


		Vector&
		operator++ ();

		Vector
		operator++ (int);

		Vector&
		operator-- ();

		Vector
		operator-- (int);

		Vector
		operator- () const;

		Vector&
		operator+= (const T& x);

		Vector&
		operator+= (const Vector& v);

		Vector&
		operator-= (const T& x);

		Vector&
		operator-= (const Vector& v);

		Vector&
		operator*= (const T& x);

		Vector&
		operator/= (const T& x);

		Vector&
		operator%= (const T& x);



		template<class U>
		friend Vector
		operator+ (const Vector<U>& a, const Vector<U>& b)
		{
			assert (a.size_ == b.size_);
			Vector<U> v (a.size_);
			for (size_t i = 0; i < a.size_; ++i)
				v.data_[i] = a.data_[i] + b.data_[i];
			return v;
		}

		template<class U>
		friend Vector
		operator+ (const Vector<U>& v, const U& x)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] + x;
			return u;
		}


		template<class U>
		friend Vector
		operator+ (const U& x, const Vector<U>& v)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x + v.data_[i];
			return u;
		}



		template<class U>
		friend Vector
		operator- (const Vector<U>& a, const Vector<U>& b)
		{
			assert (a.size_ == b.size_);
			Vector<U> v (a.size_);
			for (size_t i = 0; i < a.size_; ++i)
				v.data_[i] = a.data_[i] - b.data_[i];
			return v;
		}

		template<class U>
		friend Vector
		operator- (const Vector<U>& v, const U& x)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] - x;
			return u;
		}

		template<class U>
		friend Vector
		operator- (const U& x, const Vector<U>& v)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x - v.data_[i];
			return u;
		}

		template<class U>
		friend Vector
		operator* (const Vector<U>& v, const U& x)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] * x;
			return u;
		}

		template<class U>
		friend Vector
		operator* (const U& x, const Vector<U>& v)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x * v.data_[i];
			return u;
		}

		template<class U>
		friend Vector
		operator/ (const Vector<U>& v, const U& x)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] / x;
			return u;
		}

		template<class U>
		friend Vector
		operator/ (const U& x, const Vector<U>& v)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x / v.data_[i];
			return u;
		}

		template<class U>
		friend Vector
		operator% (const Vector<U>& v, const U& x)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] % x;
			return u;
		}

		template<class U>
		friend Vector
		operator% (const U& x, const Vector<U>& v)
		{
			Vector<U> u (v.size_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x % v.data_[i];
			return u;
		}

		void
		increment()
		{
			algo::increment (data_, data_ + size_);
		}

		void
		decrement()
		{
			algo::decrement (data_, data_ + size_);
		}

		Vector
		pre_increment ()
		{
			Vector v (size_);
			algo::pre_increment (data_, data_ + size_, v.data_);
			return v;
		}

		Vector
		pre_decrement ()
		{
			Vector v (size_);
			algo::pre_decrement (data_, data_ + size_, v.data_);
			return v;
		}

		Vector
		post_increment ()
		{
			Vector v (size_);
			algo::post_increment (data_, data_ + size_, v.data_);
			return v;
		}

		Vector
		post_decrement ()
		{
			Vector v (size_);
			algo::post_decrement (data_, data_ + size_, v.data_);
			return v;
		}

		void
		plus (const Vector& v)
		{
			assert (size_ == v.size_);
			algo::plus (data_, data_ + size_, v.data_);
	   	}

		Vector
		plus_get (const Vector& v) const
		{
			assert (size_ == v.size_);
			Vector res (size_);
			algo::plus (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		minus (const Vector& v)
		{
			assert (size_ == v.size_);
			algo::minus (data_, data_ + size_, v.data_);
	   	}

		Vector
		minus_get (const Vector& v) const
		{
			assert (size_ == v.size_);
			Vector res (size_);
			algo::minus (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		multiplies (const Vector& v)
		{
			assert (size_ == v.size_);
			algo::multiplies (data_, data_ + size_, v.data_);
	   	}

		Vector
		multiplies_get (const Vector& v) const
		{
			assert (size_ == v.size_);
			Vector res (size_);
			algo::multiplies (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		divides (const Vector& v)
		{
			assert (size_ == v.size_);
			algo::divides (data_, data_ + size_, v.data_);
	   	}

		Vector
		divides_get (const Vector& v) const
		{
			assert (size_ == v.size_);
			Vector res (size_);
			algo::divides (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		modulus (const Vector& v)
		{
			assert (size_ == v.size_);
			algo::modulus (data_, data_ + size_, v.data_);
	   	}

		Vector
		modulus_get (const Vector& v) const
		{
			assert (size_ == v.size_);
			Vector res (size_);
			algo::modulus (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		plus_x (const T& x)
		{
			algo::plus_x (data_, data_ + size_, x);
	   	}

		Vector
		plus_x_get (const T& x) const
		{
			Vector res (size_);
			algo::plus_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		minus_x (const T& x)
		{
			algo::minus_x (data_, data_ + size_, x);
	   	}

		Vector
		minus_x_get (const T& x) const
		{
			Vector res (size_);
			algo::minus_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		multiplies_x (const T& x)
		{
			algo::multiplies_x (data_, data_ + size_, x);
	   	}

		Vector
		muliplies_x_get (const T& x) const
		{
			Vector res (size_);
			algo::multiplies_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		divides_x (const T& x)
		{
			algo::divides_x (data_, data_ + size_, x);
	   	}

		Vector
		divides_x_get (const T& x) const
		{
			Vector res (size_);
			algo::divides_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		modulus_x (const T& x)
		{
			algo::modulus_x (data_, data_ + size_, x);
	   	}

		Vector
		modulus_x_get (const T& x) const
		{
			Vector res (size_);
			algo::modulus_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		x_plus (const T& x)
		{
			algo::x_plus (x, data_, data_ + size_);
	   	}

		Vector
		x_plus_get (const T& x) const
		{
			Vector res (size_);
			algo::x_plus (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_minus (const T& x)
		{
			algo::x_minus (x, data_, data_ + size_);
	   	}

		Vector
		x_minus_get (const T& x) const
		{
			Vector res (size_);
			algo::x_minus (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_multiplies (const T& x)
		{
			algo::x_multiplies (x, data_, data_ + size_);
	   	}

		Vector
		x_multiplies_get (const T& x) const
		{
			Vector res (size_);
			algo::x_multiplies (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_divides (const T& x)
		{
			algo::x_divides (x, data_, data_ + size_);
	   	}

		Vector
		x_divides_get (const T& x) const
		{
			Vector res (size_);
			algo::x_divides (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_modulus (const T& x)
		{
			algo::x_modulus (x, data_, data_ + size_);
	   	}

		Vector
		x_modulus_get (const T& x) const
		{
			Vector res (size_);
			algo::x_modulus (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		negate ()
		{
			algo::negate (data_, data_ + size_);
	   	}

		Vector
		negate_get () const
		{
			Vector res (size_);
			algo::negate (data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		abs ()
		{
			algo::abs (data_, data_ + size_);
	   	}

		Vector
		abs_get () const
		{
			Vector res (size_);
			algo::abs (data_, data_ + size_, res.data_);
			return res;
	   	}

		T
		min () const
		{
		    return algo::min (data_, data_ + size_);
	   	}

		T
		max () const
		{
		    return algo::max (data_, data_ + size_);
	   	}

		T
		min_abs () const
		{
		    return algo::min_abs (data_, data_ + size_);
	   	}

		T
		max_abs () const
		{
		    return algo::max_abs (data_, data_ + size_);
	   	}

		T
		norm_square () const
		{
		    return algo::norm_square (data_, data_ + size_);
	   	}

		T
		norm () const
		{
		    return algo::norm (data_, data_ + size_);
	   	}

		T
		p_norm (size_t p) const
		{
		    return algo::p_norm (data_, data_ + size_, p);
	   	}

		T
		sum () const
		{
		    return algo::sum (data_, data_ + size_);
	   	}

		T
		sum_abs () const
		{
		    return algo::sum_abs (data_, data_ + size_);
	   	}

		T
		product () const
		{
		    return algo::product (data_, data_ + size_);
	   	}

		T
		product_abs () const
		{
		    return algo::product_abs (data_, data_ + size_);
	   	}

		void
		normalize ()
		{
			algo::normalize (data_, data_ + size_);
	   	}

		Vector
		normalize_get () const
		{
			Vector res (size_);
			algo::normalize (data_, data_ + size_, res.data_);
			return res;
	   	}

		bool
		is_unit () const
		{
		    return algo::is_unit (data_, data_ + size_);
	   	}

		T
		dot_product (const Vector& v) const
		{
			assert (size_ == v.size_);
			return algo::dot_product (data_, data_ + size_, v.data_);
	   	}

		T
		distance_square (const Vector& v) const
		{
			assert (size_ == v.size_);
			return algo::distance_square (data_, data_ + size_, v.data_);
	   	}

		T
		distance (const Vector& v) const
		{
			assert (size_ == v.size_);
			return algo::distance (data_, data_ + size_, v.data_);
	   	}

		bool
		is_orthogonal (const Vector& v) const
		{
			assert (size_ == v.size_);
			return algo::is_orthogonal (data_, data_ + size_, v.data_);
	   	}

		bool
		is_orthonormal (const Vector& v) const
		{
			assert (size_ == v.size_);
			return algo::is_orthonormal (data_, data_ + size_, v.data_);
	   	}

		bool
		is_null () const
		{
			return algo::is_null (data_, data_ + size_);
	   	}

		bool
		equals (const Vector& v) const
		{
			if (size_ != v.size_)
				return false;
			return algo::equals (data_, data_ + size_, v.data_);
	   	}

		void
		project_along (const Vector& v)
		{
			assert (size_ == v.size_);
			algo::project_along (data_, data_ + size_, v.data_);
	   	}

		Vector
		project_along_get (const Vector& v) const
		{
			assert (size_ == v.size_);
			Vector res (size_);
			algo::project_along (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		project_orthogonal (const Vector& v)
		{
			assert (size_ == v.size_);
			algo::project_orthogonal (data_, data_ + size_, v.data_);
	   	}

		Vector
		project_orthogonal_get (const Vector& v) const
		{
			assert (size_ == v.size_);
			Vector res (size_);
			algo::project_orthogonal (data_, data_ + size_, v.data_,
									  res.data_);
			return res;
	   	}

		T
		average () const
		{
			return algo::average (data_, data_ + size_);
		}

		std::vector<Vector>
		line_segment (const Vector& v, size_t size) const;

		static bool
		is_orthogonal_set (const std::vector<Vector>& set);

		static bool
		is_orthonormal_set (const std::vector<Vector>& set);

		Vector
		project_orthogonal_get (const std::vector<Vector>& set,
								Vector& coeffs) const;

		static std::vector<Vector>
		orthogonalize (const std::vector<Vector>& set,
					   std::vector<Vector>& coeffs);

		static std::vector<Vector>
		basis_get (const std::vector<Vector>& set);

		static std::vector<Vector>
		subset_basis_get (const std::vector<Vector>& set);

		static size_t
		rank (const std::vector<Vector>& set);

		static bool
		is_independant_set (const std::vector<Vector>& set);

		static std::vector<Vector>
		orthogonal_complement_get (const std::vector<Vector>& u_basis,
								   const std::vector<Vector>& v_basis);



		class iterator
		{

		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef const T& const_reference;
			typedef const T* const_pointer;
			typedef std::random_access_iterator_tag iterator_category;

			iterator ()
				: ptr_ (nullptr)
			{

			}

			iterator (T *ptr)
				: ptr_ (ptr)
			{

		  	}

			iterator (const iterator& it)
				: ptr_ (it.ptr_)
			{

			}

			~iterator ()
			{

			}

			iterator&
			operator= (const iterator& it)
			{
				ptr_ = it.ptr_;
				return *this;
			}

			bool
			operator== (const iterator& it) const
			{
				return ptr_ == it.ptr_;
			}

			bool
			operator!= (const iterator& it) const
			{
				return ptr_ != it.ptr_;
			}

			bool
			operator> (const iterator& it) const
		    {
				return ptr_ > it.ptr_;
			}

			bool
			operator>= (const iterator& it) const
			{
				return ptr_ >= it.ptr_;
			}

			bool
			operator< (const iterator& it) const
			{
				return ptr_ < it.ptr_;
			}

			bool
			operator<= (const iterator& it) const
			{
				return ptr_ <= it.ptr_;
			}

			iterator&
			operator++ ()
			{
				++ptr_;
				return *this;
			}

			iterator
			operator++ (int)
			{
				iterator it = *this;
				++ptr_;
				return it;
			}

			iterator&
			operator-- ()
			{
				--ptr_;
				return *this;
			}

			iterator
			operator-- (int)
			{
				iterator it = *this;
				--ptr_;
				return it;
			}

			iterator&
			operator+= (size_type n)
			{
				ptr_ += n;
				return *this;
			}

			iterator
			operator+ (size_type n) const
			{
				return ptr_ + n;
			}

			friend iterator
			operator+ (size_type n, const iterator& it)
			{
				return it.ptr_ + n;
			}

			iterator&
			operator-= (size_type n)
			{
				ptr_ -= n;
				return *this;
			}

			iterator
			operator- (size_type n) const
			{
				return ptr_ - n;
			}

			difference_type
			operator- (iterator it) const
			{
				return ptr_ - it.ptr_;
			}

			reference
			operator* () const
			{
				return *ptr_;
			}

			pointer
			operator-> () const
			{
				return ptr_;
			}

			reference
			operator[] (size_type n) const
			{
				return ptr_[n];
			}

		private:
			T *ptr_;

		};

		class const_iterator
		{

		public:
		    typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef const T& const_reference;
			typedef const T* const_pointer;
		    typedef std::random_access_iterator_tag iterator_category;


			const_iterator ()
				: ptr_ (nullptr)
			{

			}

			const_iterator (T* ptr)
				: ptr_ (ptr)
			{

			}

			const_iterator (const const_iterator& it)
				: ptr_ (it.ptr_)
			{

			}

			const_iterator (const iterator& it)
				: ptr_ (it.ptr_)
			{

			}

			~const_iterator ()
		   	{

	   		}

			const_iterator&
			operator= (const const_iterator& it)
			{
				ptr_ = it.ptr_;
				return *this;
			}

			bool
			operator== (const const_iterator& it) const
			{
				return ptr_ == it.ptr_;
			}

			bool
			operator!= (const const_iterator& it) const
			{
					return ptr_ != it.ptr_;
			}

			bool
			operator> (const const_iterator& it) const
			{
				return ptr_ > it.ptr_;
			}

			bool
			operator>= (const const_iterator& it) const
			{
				return ptr_ >= it.ptr_;
			}

			bool operator< (const const_iterator& it) const
			{
				return ptr_ < it.ptr_;
			}

			bool operator<= (const const_iterator& it) const
			{
				return ptr_ <= it.ptr_;
			}

			const_iterator&
			operator++ ()
			{
				++ptr_;
				return *this;
			}

			const_iterator
			operator++ (int)
			{
				const_iterator it = *this;
				++ptr_;
				return it;
			}

			const_iterator&
			operator-- ()
			{
				--ptr_;
				return *this;
			}

			const_iterator
			operator-- (int)
			{
				const_iterator it = *this;
				--ptr_;
				return it;
			}

			const_iterator&
			operator+= (size_type n)
			{
				ptr_ += n;
				return *this;
			}

			const_iterator
			operator+ (size_type n) const
			{
				return ptr_ + n;
			}

			friend const_iterator
			operator+ (size_type n, const const_iterator& it)
			{
				return it.ptr_ + n;
			}

			const_iterator&
			operator-= (size_type n)
			{
				ptr_ -= n;
				return *this;
			}

			const_iterator
			operator- (size_type n) const
			{
				return ptr_ - n;
			}

			difference_type
			operator- (const_iterator it) const
			{
				return ptr_ - it.ptr_;
			}

			const_reference
			operator* () const
			{
				return *ptr_;
			}

			const_pointer
			operator-> () const
			{
				return ptr_;
			}

			const_reference
			operator[] (size_type n) const
			{
				return ptr_[n];
			}

		private:
			const T* ptr_;

		};

		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator
		begin ()
		{
			return iterator (data_);
		}

		const_iterator
		begin () const
		{
			return const_iterator (data_);
		}

		const_iterator
		cbegin () const
		{
			return const_iterator (data_);
		}

		iterator
		end ()
		{
			return iterator (data_ + size_);
		}

		const_iterator
		end () const
		{
			return const_iterator (data_ + size_);
		}

		const_iterator
		cend () const
		{
			return const_iterator (data_ + size_);
		}

		reverse_iterator
		rbegin ()
		{
			return reverse_iterator (data_ + size_);
		}

		const_reverse_iterator
		rbegin () const
		{
			return const_reverse_iterator (data_ + size_);
		}

		const_reverse_iterator
		crbegin () const
		{
			return const_reverse_iterator (data_ + size_);
		}

		reverse_iterator
		rend ()
		{
			return reverse_iterator (data_);
		}

		const_reverse_iterator
		rend () const
		{
			return const_reverse_iterator (data_);
		}

		const_reverse_iterator
		crend () const
		{
			return const_reverse_iterator (data_);
		}


	private:
		T* data_;
		size_type size_;

		///Resize the vector without copying the old values
		void
		resize_mem_ (size_type n);

		friend class Matrix<T>;

		friend class SerialManager<Vector>;



	};

	using vect_type = Vector<double>;

	template <class T>
	class SerialManager<Vector<T>>
	{
	public:
		static void
		pack (std::ostream& os, const Vector<T>& data)
		{
			serialize (os, data.size_);
			os.write (reinterpret_cast <const char *> (data.data_),
					  data.size_ * sizeof (T));
		}

		static Vector<T>
		unpack (std::istream& is)
		{
			size_t size = unserialize <size_t> (is);
			Vector<T> v (size);
			is.read (reinterpret_cast<char *> ( v.data_),
					 v.size_ * sizeof (T));
			return v;
		}
	};

	template <class T>
	Vector<T>::Vector (size_type count)
		: size_ (count)
	{
		data_ = new T[count];
	}

	template <class T>
	Vector<T>::Vector (size_type count, const T& x)
		: Vector (count)
	{
		std::fill (data_, data_ + count, x);
	}

	template <class T>
	template <class It>
	Vector<T>::Vector (It begin, It end)
		: Vector (end - begin)
	{
		std::copy (begin, end, data_);
	}

	template <class T>
	Vector<T>::Vector (std::initializer_list<T> list)
		: Vector (list.begin (), list.end ())
	{

	}

	template <class T>
	Vector<T>::Vector (const Vector& v)
		: Vector (v.size_)
	{
		std::copy_n (v.data_, v.size_, data_);
	}

	template <class T>
	Vector<T>::~Vector ()
	{
		delete data_;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator= (const T& x)
	{
		assign (x);
		return *this;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator= (const Vector& v)
	{
		assign (v);
		return *this;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator= (std::initializer_list<T> list)
	{
		assign (list);
		return *this;
	}

	template <class T>
	void
	Vector<T>::assign (const T& x)
	{
		std::fill (data_, data_ + size_, x);
	}

	template <class T>
	void
	Vector<T>::assign (const Vector& v)
	{
		resize_mem_ (v.size_);
		std::copy_n (v.data_, v.size_, data_);
	}

	template <class T>
	void
	Vector<T>::assign (std::initializer_list<T> list)
	{
		assign (list.begin (), list.end ());
	}

	template <class T>
	template <class It>
	void
	Vector<T>::assign (It begin, It end)
	{
		resize_mem_ (end - begin);
		std::copy (begin, end, data_);
	}

	template <class T>
	void
	Vector<T>::resize (size_type n)
	{
		if(n == size_)
			return;
		T* new_data = new T[n];
		std::copy_n (data_, std::min (n, size_), new_data);
		delete data_;
		data_ = new_data;
		size_ = n;
	}

	template <class T>
	void
	Vector<T>::resize (size_type n, const T& x)
	{
		if(n == size_)
			return;
		T* new_data = new T[n];
		std::copy_n (data_, std::min (n, size_), new_data);
		delete data_;
		data_ = new_data;

		if (n > size_)
			std::fill (data_ + size_, data_ + n, x);
		size_ = n;
	}


	template <class T>
	typename Vector<T>::size_type
	Vector<T>::size () const
	{
		return size_;
	}

	template <class T>
	bool
	Vector<T>::empty () const
	{
		return !size_;
	}


	template <class T>
	typename Vector<T>::reference
	Vector<T>::at (size_type n)
	{
		if (n < 0 || n >= size_)
			throw std::out_of_range ("Vector out of range index");
		return data_[n];
	}

	template <class T>
	typename Vector<T>::const_reference
	Vector<T>::at (size_type n) const
	{
		if (n < 0 || n >= size_)
			throw std::out_of_range ("Vector out of range index");
		return data_[n];
	}

	template <class T>
	typename Vector<T>::reference
	Vector<T>::operator[] (size_type n)
	{
		assert (n >= 0 && n < size_);
		return data_[n];
	}

	template <class T>
	typename Vector<T>::const_reference
	Vector<T>::operator[] (size_type n) const
	{
		assert (n >= 0 && n < size_);
		return data_[n];
	}

	template <class T>
	T*
	Vector<T>::data ()
	{
		return data_;
	}

	template <class T>
	const T*
	Vector<T>::data () const
	{
		return data_;
	}

	template <class T>
	void
	Vector<T>::swap (Vector& v)
	{
		if (v.size_ != size_)
		{
			Vector temp = v;
			v.assign (*this);
			assign (temp);
		}
		else
			std::swap_ranges (data_, data_ + size_, v.data_);
	}

	template <class T>
	std::ostream&
	operator<< (std::ostream& os, const Vector<T>& v)
	{
		os << "[";
		for (size_t i = 0; i < v.size_; ++i)
		{
			if (i)
				os << ", ";
			os << v.data_[i];
		}
		os << "]";
		return os;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator++ ()
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] += 1;
		return *this;
	}

	template <class T>
	Vector<T>
	Vector<T>::operator++ (int)
	{
		Vector temp (*this);
		for (size_t i = 0; i < size_; ++i)
			data_[i] += 1;
		return temp;
	}

    template <class T>
	Vector<T>&
	Vector<T>::operator-- ()
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= 1;
		return *this;
	}

	template <class T>
	Vector<T>
	Vector<T>::operator-- (int)
	{
		Vector temp (*this);
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= 1;
		return temp;
	}

	template <class T>
	Vector<T>
	Vector<T>::operator- () const
	{
		Vector neg (size_);
		for (size_t i = 0; i < size_; ++i)
			neg.data_[i] = - data_[i];
		return neg;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator+= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] += x;
		return *this;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator+= (const Vector& v)
	{
		assert (size_ == v.size_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] += v.data_[i];
		return *this;
	}

    template <class T>
	Vector<T>&
	Vector<T>::operator-= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= x;
		return *this;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator-= (const Vector& v)
	{
		assert (size_ == v.size_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= v.data_[i];
		return *this;
	}

    template <class T>
	Vector<T>&
	Vector<T>::operator*= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] *= x;
		return *this;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator/= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] /= x;
		return *this;
	}

	template <class T>
	Vector<T>&
	Vector<T>::operator%= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] %= x;
		return *this;
	}


	template <class T>
	void
	Vector<T>::resize_mem_ (size_type n)
	{
		if(n != size_)
		{
			delete data_;
			data_ = new T[n];
			size_ = n;
		}
	}

	template <class T>
	std::vector<Vector<T>>
	Vector<T>::line_segment (const Vector& v, size_t size) const
	{
		assert(size_ == v.size_);

		std::vector<Vector> line (size);
		T range = 1 / static_cast<T> (size - 1);
	    T alpha = 0;

		for (size_t i = 0; i < size; ++i)
		{
			T beta = 1 - alpha;
			Vector point (size_);
			for (size_t j = 0; j < size_; ++j)
				point[j] = alpha * v[j] + beta * data_[j];
			line[i] = point;
			alpha += range;
		}

		return line;
	}

	template <class T>
	bool
	Vector<T>::is_orthogonal_set (const std::vector<Vector>& set)
	{
		size_t n = set.size ();
		for (size_t i = 0; i < n; ++i)
			for (size_t j = i + 1; j < n; ++j)
				if(!set[i].is_orthogonal (set[j]))
					return false;
		return true;
	}

	template <class T>
	bool
	Vector<T>::is_orthonormal_set (const std::vector<Vector>& set)
	{
		for(size_t i = 0; i < set.size (); ++i)
			if(!set[i].is_unit ())
				return false;
		return is_orthogonal_set (set);
	}

	template <class T>
	Vector <T>
	Vector<T>::project_orthogonal_get (const std::vector<Vector>& set,
							Vector& coeffs) const
	{
		size_t n = set.size ();
		coeffs.resize_mem_ (n+1);
		coeffs.data_[n] = 1;

		Vector v (*this);

		for (size_t i = 0; i < n; ++i)
		{
			Vector vi = set[i];
			T den = vi.norm_square ();
			T coeff = den < 1e-10 ? 0 : v.dot_product (vi) / den;
			coeffs.data_[i] = coeff;

			for(size_t k = 0; k < size_; ++k)
				v.data_[k] -= coeff * vi.data_[k];
		}

		return v;
	}

	template <class T>
	std::vector<Vector<T>>
	Vector<T>::orthogonalize (const std::vector<Vector>& set,
							  std::vector<Vector>& coeffs)
	{
		size_t n = set.size ();
		std::vector<Vector> res (n);
		coeffs.resize (n);

		for (size_t i = 0; i < n; ++i)
		{
			std::vector<Vector> subset (res.begin (), res.begin () + i);
			res[i] = set[i].project_orthogonal_get (subset, coeffs[i]);
		}

		return res;
	}

	template <class T>
	std::vector<Vector<T>>
	Vector<T>::basis_get (const std::vector<Vector>& set)
	{
		size_t n = set.size ();
		std::vector<Vector> coeffs;
		std::vector<Vector> orth = orthogonalize (set, coeffs);
		std::vector<Vector> base;

		for(size_t i = 0; i < n; ++i)
		{
			Vector v = orth[i];
			if(!v.is_null ())
				base.push_back (v);
		}
		return base;
	}

	template <class T>
	std::vector<Vector<T>>
	Vector<T>::subset_basis_get (const std::vector<Vector>& set)
	{
		size_t n = set.size ();
		std::vector<Vector> coeffs;
		std::vector<Vector> orth = orthogonalize (set, coeffs);
		std::vector<Vector> base;

		for(size_t i = 0; i < n; ++i)
		{
			Vector v = orth[i];
			if(!v.is_null ())
				base.push_back (set[i]);
		}
		return base;
	}

	template <class T>
	size_t
	Vector<T>::rank (const std::vector<Vector>& set)
	{
		return basis_get (set).size ();
	}

	template <class T>
	bool
	Vector<T>::is_independant_set (const std::vector<Vector>& set)
	{
		return rank (set) == set.size ();
	}

	template <class T>
	std::vector<Vector<T>>
	Vector<T>::orthogonal_complement_get (const std::vector<Vector>& u_basis,
										  const std::vector<Vector>& v_basis)
	{
		size_t dim_u = u_basis.size ();
		size_t dim_v = v_basis.size ();
		assert(dim_u <= dim_v);

		std::vector<Vector> uv (u_basis);
		uv.insert (uv.end (), v_basis.begin (), v_basis.end ());

		std::vector<Vector> coeffs;
		std::vector<Vector> uv_orth = orthogonalize (uv, coeffs);

		size_t n = dim_v-dim_u;
		std::vector<Vector> basis;

		for(size_t i = dim_u; i < dim_u + dim_v; ++i)
		{
			Vector v = uv_orth[i];
			if (basis.size () < n && !v.is_null ())
				basis.push_back (v);
		}
		return basis;
	}

}

#endif //!VECTOR_HH_