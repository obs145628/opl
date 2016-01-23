

/** @file Matrix class definition
 */

#ifndef MATRIX_HH_
#define MATRIX_HH_

# include <cstddef>
# include <cassert>
# include <algorithm>
# include <iterator>
# include <stdexcept>
# include <iostream>
# include <vector>
# include "algo.hh"
# include "vector.hh"
# include "math.hh"
# include "serialization.hh"

namespace opl
{

	template<class T>
	class Matrix
	{

	public:
		typedef T value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;

		using varr_type = std::vector<Vector<T>>;

		static Matrix
		id (size_type size);

		static Matrix
		null (size_type rows, size_type cols);

		static Matrix
		from_row_vector (const Vector<T>& v);

		static Matrix
		from_col_vector (const Vector<T>& v);

		static Matrix
		from_rows_vectors (const varr_type& rows);

		static Matrix
		from_cols_vectors (const varr_type& cols);

		template <class It>
		static Matrix
		from_row (It begin, It end);

		template <class It>
		static Matrix
		from_col (It begin, It end);


		Matrix (size_type rows = 0, size_type cols = 0);
		Matrix (size_type rows, size_type cols, const T& x);

		template <class It>
		Matrix (size_type rows, size_type cols, It begin);

		Matrix (size_type rows, size_type cols,
				std::initializer_list<T> list);

		Matrix (const Matrix& v);

		~Matrix ();

		Matrix&
		operator= (const T& x);

		Matrix&
		operator= (const Matrix& v);

		Matrix&
		operator= (std::initializer_list<T> list);

		void
		assign (const T& x);

		void
		assign (size_type rows, size_type cols, const T& x);

		void
		assign (const Matrix& v);

		void
		assign (std::initializer_list<T> list);

		void
		assign (size_type rows, size_type cols,
				std::initializer_list<T> list);

		template <class It>
		void
		assign (It begin, It end);

		template <class It>
		void
		assign (size_type rows, size_type cols, It begin);

		///Resize the matrix and let it unintialized
		void
		resize (size_type rows, size_type cols);

		///Resize the matrix and fill it with x
		void
		resize (size_type rows, size_type cols, const T& x);

		size_type
		rows () const;

		size_type
		cols () const;

		size_type
		size () const;

		bool
		empty () const;

		reference
		at (size_type i, size_type j);

		const_reference
		at (size_type i, size_type j) const;

		T*
		data ();

		const T*
		data () const;

		void
		swap (Matrix& v);

		Vector<T>
		vector_get () const;

		Vector<T>
		row_vector_get (size_type row) const;

		Vector<T>
		col_vector_get (size_type col) const;

		varr_type
		rows_vectors_get () const;

		varr_type
		cols_vectors_get () const;

		Matrix
		transpose () const;

		bool
		is_symmetric () const;

		template<class U>
		friend std::ostream&
		operator<< (std::ostream& os, const Matrix<U>& v);



		template <class U>
		friend bool
		operator== (const Matrix<U>& a, const Matrix<U>& b)
		{
			if (a.rows_ != b.rows_ || a.cols_ != b.cols_)
				return false;
			for (size_t i = 0; i < a.size_; ++i)
				if (a.data_[i] != b.data_[i])
					return false;
			return true;
		}

		template <class U>
		friend bool
		operator!= (const Matrix<U>& a, const Matrix<U>& b)
		{
			if (a.rows_ != b.rows_ || a.cols_ != b.cols_)
				return true;
			for (size_t i = 0; i < a.size_; ++i)
				if (a.data_[i] != b.data_[i])
					return true;
			return false;
		}


		Matrix&
		operator++ ();

		Matrix
		operator++ (int);

		Matrix&
		operator-- ();

		Matrix
		operator-- (int);

		Matrix
		operator- () const;

		Matrix&
		operator+= (const T& x);

		Matrix&
		operator+= (const Matrix& v);

		Matrix&
		operator-= (const T& x);

		Matrix&
		operator-= (const Matrix& v);

		Matrix&
		operator*= (const T& x);

		Matrix&
		operator/= (const T& x);

		Matrix&
		operator%= (const T& x);

		Matrix&
		operator*= (const Matrix& v);



		template<class U>
		friend Matrix
		operator+ (const Matrix<U>& a, const Matrix<U>& b)
		{
			assert (a.rows_ == b.rows_ && a.cols_ == b.cols_);
			Matrix<U> v (a.rows_, a.cols_);
			for (size_t i = 0; i < a.size_; ++i)
				v.data_[i] = a.data_[i] + b.data_[i];
			return v;
		}

		template<class U>
		friend Matrix
		operator+ (const Matrix<U>& v, const U& x)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] + x;
			return u;
		}


		template<class U>
		friend Matrix
		operator+ (const U& x, const Matrix<U>& v)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x + v.data_[i];
			return u;
		}



		template<class U>
		friend Matrix
		operator- (const Matrix<U>& a, const Matrix<U>& b)
		{
		    assert (a.rows_ == b.rows_ && a.cols_ == b.cols_);
			Matrix<U> v (a.rows_, a.cols_);
			for (size_t i = 0; i < a.size_; ++i)
				v.data_[i] = a.data_[i] - b.data_[i];
			return v;
		}

		template<class U>
		friend Matrix
		operator- (const Matrix<U>& v, const U& x)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] - x;
			return u;
		}

		template<class U>
		friend Matrix
		operator- (const U& x, const Matrix<U>& v)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x - v.data_[i];
			return u;
		}

		template<class U>
		friend Matrix
		operator* (const Matrix<U>& v, const U& x)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] * x;
			return u;
		}

		template<class U>
		friend Matrix
		operator* (const U& x, const Matrix<U>& v)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x * v.data_[i];
			return u;
		}

		template<class U>
		friend Matrix
		operator/ (const Matrix<U>& v, const U& x)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] / x;
			return u;
		}

		template<class U>
		friend Matrix
		operator/ (const U& x, const Matrix<U>& v)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x / v.data_[i];
			return u;
		}

		template<class U>
		friend Matrix
		operator% (const Matrix<U>& v, const U& x)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = v.data_[i] % x;
			return u;
		}

		template<class U>
		friend Matrix
		operator% (const U& x, const Matrix<U>& v)
		{
			Matrix<U> u (v.rows_, v.cols_);
			for (size_t i = 0; i < v.size_; ++i)
				u.data_[i] = x % v.data_[i];
			return u;
		}

		template <class U>
		friend Matrix
		operator* (const Matrix<U>& a, const Matrix<U>& b)
		{
			assert (a.cols_ == b.rows_);
			Matrix m (a.rows_, b.cols_);

			for (size_type i = 0; i < m.rows_; ++i)
			{
				for (size_type j = 0; j < m.cols_; ++j)
				{
					T val = 0;
					for (size_type k = 0; k < a.cols_; ++k)
						val += a.at (i, k) * b.at (k, j);
					m.at (i ,j) = val;
				}
			}
			return m;
		}

		template <class U>
		friend Vector<U>
		operator* (const Matrix<U>& a, const Vector<U>& b)
		{
			assert(a.cols_ == b.size ());
			Vector<U> v (a.rows_);

			for (size_type i = 0; i < a.rows_; ++i)
			{
				T val = 0;
				for (size_type k = 0; k < a.cols_; ++k)
					val += a.at (i, k) * b[k];
				v[i] = val;
			}

			return v;
		}

		template <class U>
		friend Vector<U>
		operator* (const Vector<U>& a, const Matrix<U>& b)
		{
			assert(a.size () == b.rows_);
			Vector<U> v (b.cols_);

			for (size_type j = 0; j < b.cols_; ++j)
			{
				T val = 0;
				for (size_type k = 0; k < b.rows_; ++k)
					val += a[k] * b.at (k, j);
				v[j] = val;
			}

			return v;
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

		Matrix
		pre_increment ()
		{
			Matrix v (rows_,  cols_);
			algo::pre_increment (data_, data_ + size_, v.data_);
			return v;
		}

		Matrix
		pre_decrement ()
		{
			Matrix v (rows_, cols_);
			algo::pre_decrement (data_, data_ + size_, v.data_);
			return v;
		}

		Matrix
		post_increment ()
		{
			Matrix v (rows_, cols_);
			algo::post_increment (data_, data_ + size_, v.data_);
			return v;
		}

		Matrix
		post_decrement ()
		{
			Matrix v (rows_, cols_);
			algo::post_decrement (data_, data_ + size_, v.data_);
			return v;
		}

		void
		plus (const Matrix& v)
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			algo::plus (data_, data_ + size_, v.data_);
	   	}

		Matrix
		plus_get (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			Matrix res (rows_, cols_);
			algo::plus (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		minus (const Matrix& v)
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			algo::minus (data_, data_ + size_, v.data_);
	   	}

		Matrix
		minus_get (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			Matrix res (rows_, cols_);
			algo::minus (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		multiplies (const Matrix& v)
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			algo::multiplies (data_, data_ + size_, v.data_);
	   	}

		Matrix
		multiplies_get (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			Matrix res (rows_, cols_);
			algo::multiplies (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		divides (const Matrix& v)
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			algo::divides (data_, data_ + size_, v.data_);
	   	}

		Matrix
		divides_get (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			Matrix res (rows_, cols_);
			algo::divides (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		modulus (const Matrix& v)
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			algo::modulus (data_, data_ + size_, v.data_);
	   	}

		Matrix
		modulus_get (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			Matrix res (rows_, cols_);
			algo::modulus (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		plus_x (const T& x)
		{
			algo::plus_x (data_, data_ + size_, x);
	   	}

		Matrix
		plus_x_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::plus_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		minus_x (const T& x)
		{
			algo::minus_x (data_, data_ + size_, x);
	   	}

		Matrix
		minus_x_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::minus_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		multiplies_x (const T& x)
		{
			algo::multiplies_x (data_, data_ + size_, x);
	   	}

		Matrix
		muliplies_x_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::multiplies_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		divides_x (const T& x)
		{
			algo::divides_x (data_, data_ + size_, x);
	   	}

		Matrix
		divides_x_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::divides_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		modulus_x (const T& x)
		{
			algo::modulus_x (data_, data_ + size_, x);
	   	}

		Matrix
		modulus_x_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::modulus_x (data_, data_ + size_, x, res.data_);
			return res;
	   	}

		void
		x_plus (const T& x)
		{
			algo::x_plus (x, data_, data_ + size_);
	   	}

		Matrix
		x_plus_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::x_plus (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_minus (const T& x)
		{
			algo::x_minus (x, data_, data_ + size_);
	   	}

		Matrix
		x_minus_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::x_minus (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_multiplies (const T& x)
		{
			algo::x_multiplies (x, data_, data_ + size_);
	   	}

		Matrix
		x_multiplies_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::x_multiplies (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_divides (const T& x)
		{
			algo::x_divides (x, data_, data_ + size_);
	   	}

		Matrix
		x_divides_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::x_divides (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		x_modulus (const T& x)
		{
			algo::x_modulus (x, data_, data_ + size_);
	   	}

		Matrix
		x_modulus_get (const T& x) const
		{
			Matrix res (rows_, cols_);
			algo::x_modulus (x, data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		negate ()
		{
			algo::negate (data_, data_ + size_);
	   	}

		Matrix
		negate_get () const
		{
			Matrix res (rows_, cols_);
			algo::negate (data_, data_ + size_, res.data_);
			return res;
	   	}

		void
		abs ()
		{
			algo::abs (data_, data_ + size_);
	   	}

		Matrix
		abs_get () const
		{
			Matrix res (rows_, cols_);
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

		Matrix
		normalize_get () const
		{
			Matrix res (rows_, cols_);
			algo::normalize (data_, data_ + size_, res.data_);
			return res;
	   	}

		bool
		is_unit () const
		{
		    return algo::is_unit (data_, data_ + size_);
	   	}

		T
		dot_product (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			return algo::dot_product (data_, data_ + size_, v.data_);
	   	}

		T
		distance_square (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			return algo::distance_square (data_, data_ + size_, v.data_);
	   	}

		T
		distance (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			return algo::distance (data_, data_ + size_, v.data_);
	   	}

		bool
		is_orthogonal (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			return algo::is_orthogonal (data_, data_ + size_, v.data_);
	   	}

		bool
		is_orthonormal (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			return algo::is_orthonormal (data_, data_ + size_, v.data_);
	   	}

		bool
		is_null () const
		{
			return algo::is_null (data_, data_ + size_);
	   	}

		bool
		equals (const Matrix& v) const
		{
			if (rows_ != v.rows_ || cols_ != v.cols_)
				return false;
			return algo::equals (data_, data_ + size_, v.data_);
	   	}

		void
		project_along (const Matrix& v)
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			algo::project_along (data_, data_ + size_, v.data_);
	   	}

		Matrix
		project_along_get (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			Matrix res (size_);
			algo::project_along (data_, data_ + size_, v.data_, res.data_);
			return res;
	   	}

		void
		project_orthogonal (const Matrix& v)
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			algo::project_orthogonal (data_, data_ + size_, v.data_);
	   	}

		Matrix
		project_orthogonal_get (const Matrix& v) const
		{
		    assert (rows_ == v.rows_ && cols_ == v.cols_);
			Matrix res (rows_, cols_);
			algo::project_orthogonal (data_, data_ + size_, v.data_,
									  res.data_);
			return res;
	   	}

		T
		average () const
		{
			return algo::average (data_, data_ + size_);
		}



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

		class range_iterator
		{

		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef const T& const_reference;
			typedef const T* const_pointer;
			typedef std::random_access_iterator_tag iterator_category;

			range_iterator ()
				: ptr_ (nullptr), d_(0)
			{

			}

			range_iterator (T *ptr, size_type d)
				: ptr_ (ptr), d_ (d)
			{

		  	}

			range_iterator (const iterator& it)
				: ptr_ (it.ptr_), d_ (it.d_)
			{

			}

			~range_iterator ()
			{

			}

			range_iterator&
			operator= (const range_iterator& it)
			{
				ptr_ = it.ptr_;
				d_ = it.d_;
				return *this;
			}

			bool
			operator== (const range_iterator& it) const
			{
				return ptr_ == it.ptr_;
			}

			bool
			operator!= (const range_iterator& it) const
			{
				return ptr_ != it.ptr_;
			}

			bool
			operator> (const range_iterator& it) const
		    {
				return ptr_ > it.ptr_;
			}

			bool
			operator>= (const range_iterator& it) const
			{
				return ptr_ >= it.ptr_;
			}

			bool
			operator< (const range_iterator& it) const
			{
				return ptr_ < it.ptr_;
			}

			bool
			operator<= (const range_iterator& it) const
			{
				return ptr_ <= it.ptr_;
			}

			range_iterator&
			operator++ ()
			{
				ptr_ += d_;
				return *this;
			}

			range_iterator
			operator++ (int)
			{
				range_iterator it = *this;
				ptr_ += d_;
				return it;
			}

			range_iterator&
			operator-- ()
			{
				ptr_ -= d_;
				return *this;
			}

			range_iterator
			operator-- (int)
			{
				range_iterator it = *this;
				ptr_ += d_;
				return it;
			}

			range_iterator&
			operator+= (size_type n)
			{
				ptr_ += n * d_;
				return *this;
			}

			range_iterator
			operator+ (size_type n) const
			{
				return range_iterator (ptr_ + n * d_, d_);
			}

			friend range_iterator
			operator+ (size_type n, const range_iterator& it)
			{
				return range_iterator (it.ptr_ + n * it.d_, it.d_);
			}

			range_iterator&
			operator-= (size_type n)
			{
				ptr_ -= n * d_;
				return *this;
			}

			range_iterator
			operator- (size_type n) const
			{
				return range_iterator (ptr_ - n * d_, d_);
			}

			difference_type
			operator- (range_iterator it) const
			{
				return (ptr_ - it.ptr_) / d_;
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
				return ptr_[n * d_];
			}

		private:
			T *ptr_;
			size_type d_;

		};

		class const_range_iterator
		{

		public:
		    typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef const T& const_reference;
			typedef const T* const_pointer;
		    typedef std::random_access_iterator_tag iterator_category;


			const_range_iterator ()
				: ptr_ (nullptr), d_ (0)
			{

			}

			const_range_iterator (T* ptr, size_type d)
				: ptr_ (ptr), d_ (d)
			{

			}

			const_range_iterator (const const_range_iterator& it)
				: ptr_ (it.ptr_), d_ (it.d_)
			{

			}

			const_range_iterator (const range_iterator& it)
				: ptr_ (it.ptr_), d_ (it.d_)
			{

			}

			~const_range_iterator ()
		   	{

	   		}

			const_range_iterator&
			operator= (const const_range_iterator& it)
			{
				ptr_ = it.ptr_;
				d_ = it.d_;
				return *this;
			}

			bool
			operator== (const const_range_iterator& it) const
			{
				return ptr_ == it.ptr_;
			}

			bool
			operator!= (const const_range_iterator& it) const
			{
					return ptr_ != it.ptr_;
			}

			bool
			operator> (const const_range_iterator& it) const
			{
				return ptr_ > it.ptr_;
			}

			bool
			operator>= (const const_range_iterator& it) const
			{
				return ptr_ >= it.ptr_;
			}

			bool operator< (const const_range_iterator& it) const
			{
				return ptr_ < it.ptr_;
			}

			bool operator<= (const const_range_iterator& it) const
			{
				return ptr_ <= it.ptr_;
			}

			const_range_iterator&
			operator++ ()
			{
				ptr_ += d_;
				return *this;
			}

			const_range_iterator
			operator++ (int)
			{
				const_range_iterator it = *this;
				ptr_ += d_;
				return it;
			}

			const_range_iterator&
			operator-- ()
			{
				ptr_ -= d_;
				return *this;
			}

			const_range_iterator
			operator-- (int)
			{
				const_range_iterator it = *this;
				ptr_ -= d_;
				return it;
			}

			const_range_iterator&
			operator+= (size_type n)
			{
				ptr_ += n * d_;
				return *this;
			}

			const_range_iterator
			operator+ (size_type n) const
			{
				return const_range_iterator (ptr_ + n * d_, d_);
			}

			friend const_range_iterator
			operator+ (size_type n, const const_range_iterator& it)
			{
				return const_range_iterator (it.ptr_ + n * it.d_, it.d_);
			}

			const_range_iterator&
			operator-= (size_type n)
			{
				ptr_ -= n * d_;
				return *this;
			}

			const_range_iterator
			operator- (size_type n) const
			{
				return const_range_iterator (ptr_ - n * d_, d_);
			}

			difference_type
			operator- (const_range_iterator it) const
			{
				return (ptr_ - it.ptr_) / d_;
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
				return ptr_[n * d_];
			}

		private:
			const T* ptr_;
			size_type d_;

		};

		typedef std::reverse_iterator<range_iterator> reverse_range_iterator;
		typedef std::reverse_iterator<const_range_iterator> const_reverse_range_iterator;


		class region_iterator
		{

		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef const T& const_reference;
			typedef const T* const_pointer;
			typedef std::random_access_iterator_tag iterator_category;

			region_iterator ()
				: m_ (nullptr), p_ (0), i0_(0), j0_(0), c_ (0)
			{

			}

			region_iterator (Matrix *m, size_type p,
							 size_type i0, size_type j0, size_type c)
				: m_ (m), p_ (p), i0_ (i0), j0_ (j0), c_ (c)
			{

		  	}

			region_iterator (const region_iterator& it)
				: m_ (it.m_), p_ (it.p_), i0_ (it.i0_), j0_ (it.j0_),
				  c_ (it.c_)
			{

			}

			~region_iterator ()
			{

			}

			iterator&
			operator= (const region_iterator& it)
			{
				m_ = it.m_;
				p_ = it.p_;
				i0_ = it.i0_;
				j0_ = it.j0_;
				c_ = it.c_;
				return *this;
			}

			bool
			operator== (const region_iterator& it) const
			{
				return p_ == it.p_;
			}

			bool
			operator!= (const region_iterator& it) const
			{
				return p_ != it.p_;
			}

			bool
			operator> (const region_iterator& it) const
		    {
				return p_ > it.p_;
			}

			bool
			operator>= (const region_iterator& it) const
			{
				return p_ >= it.p_;
			}

			bool
			operator< (const region_iterator& it) const
			{
				return p_ < it.p_;
			}

			bool
			operator<= (const region_iterator& it) const
			{
				return p_ <= it.p_;
			}

			region_iterator&
			operator++ ()
			{
				++p_;
				return *this;
			}

			region_iterator
			operator++ (int)
			{
				iterator it = *this;
				++p_;
				return it;
			}

			region_iterator&
			operator-- ()
			{
				--p_;
				return *this;
			}

			region_iterator
			operator-- (int)
			{
				iterator it = *this;
				--p_;
				return it;
			}

			region_iterator&
			operator+= (size_type n)
			{
				p_ += n;
				return *this;
			}

			region_iterator
			operator+ (size_type n) const
			{
				return region_iterator (m_, p_ + n, i0_, j0_, c_);
			}

			friend region_iterator
			operator+ (size_type n, const region_iterator& it)
			{
				return region_iterator (it.m_, it.p_ + n, it.i0_, it.j0_,
										it.c_);
			}

			region_iterator&
			operator-= (size_type n)
			{
				p_ -= n;
				return *this;
			}

			region_iterator
			operator- (size_type n) const
			{
				return region_iterator (m_, p_ - n, i0_, j0_, c_);
			}

			difference_type
			operator- (region_iterator it) const
			{
				return p_ - it.p_;
			}

			reference
			operator* () const
			{
				size_type p = p_;
				return m_->at (i0_ + p / c_, j0_ + p % c_);
			}

			pointer
			operator-> () const
			{
				size_type p = p_;
				return &(m_->at (i0_ + p / c_, j0_ + p % c_));
			}

			reference
			operator[] (size_type n) const
			{
				size_type p = p_ + n;
				return m_->at (i0_ + p / c_, j0_ + p % c_);
			}

		private:
			Matrix* m_;
			size_type p_;
			size_type i0_;
			size_type j0_;
			size_type c_;

		};

		class const_region_iterator
		{

		public:
		    typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef const T& const_reference;
			typedef const T* const_pointer;
		    typedef std::random_access_iterator_tag iterator_category;


			const_region_iterator ()
				: m_ (nullptr), p_ (0), i0_ (0), j0_ (0), c_ (0)
		   	{

			}

			const_region_iterator (const Matrix *m, size_type p,
								   size_type i0, size_type j0, size_type c)
				: m_ (m), p_ (p), i0_ (i0), j0_ (j0), c_ (c)
			{

			}

			const_region_iterator (const const_region_iterator& it)
				: m_ (it.m_), p_ (it.p_), i0_ (it.i0_), j0_ (it.j0_),
				  c_ (it.c_)
			{

			}

			const_region_iterator (const region_iterator& it)
				: m_ (it.m_), p_ (it.p_), i0_ (it.i0_), j0_ (it.j0_),
				  c_ (it.c_)
			{

			}

			~const_region_iterator ()
		   	{

	   		}

			const_region_iterator&
			operator= (const const_region_iterator& it)
			{
				m_ = it.m_;
				p_ = it.p_;
				i0_ = it.i0_;
				j0_ = it.j0_;
				c_ = it.c_;
				return *this;
			}

			bool
			operator== (const const_region_iterator& it) const
			{
				return p_ == it.p_;
			}

			bool
			operator!= (const const_region_iterator& it) const
			{
				return p_ != it.p_;
			}

			bool
			operator> (const const_region_iterator& it) const
			{
				return p_ > it.p_;
			}

			bool
			operator>= (const const_region_iterator& it) const
			{
				return p_ >= it.p_;
			}

			bool operator< (const const_region_iterator& it) const
			{
				return p_ < it.p_;
			}

			bool operator<= (const const_region_iterator& it) const
			{
				return p_ <= it.p_;
			}

			const_region_iterator&
			operator++ ()
			{
				++p_;
				return *this;
			}

			const_region_iterator
			operator++ (int)
			{
				const_region_iterator it = *this;
				++p_;
				return it;
			}

			const_region_iterator&
			operator-- ()
			{
				--p_;
				return *this;
			}

			const_region_iterator
			operator-- (int)
			{
				const_region_iterator it = *this;
				--p_;
				return it;
			}

			const_region_iterator&
			operator+= (size_type n)
			{
				p_ += n;
				return *this;
			}

			const_region_iterator
			operator+ (size_type n) const
			{
				return const_region_iterator (m_, p_ + n, i0_, j0_, c_);
			}

			friend const_region_iterator
			operator+ (size_type n, const const_region_iterator& it)
			{
				return const_region_iterator (it.m_, it.p_ + n,
											  it.i0_, it.j0_, it.c_);
			}

			const_region_iterator&
			operator-= (size_type n)
			{
				p_ -= n;
				return *this;
			}

			const_region_iterator
			operator- (size_type n) const
			{
				return const_region_iterator (m_, p_ - n, i0_, j0_, c_);
			}

			difference_type
			operator- (const_region_iterator it) const
			{
				return p_ - it.p_;
			}

			const_reference
			operator* () const
			{
				size_type p = p_;
				return m_->at (i0_ + p / c_, j0_ + p % c_);
			}

			const_pointer
			operator-> () const
			{
				size_type p = p_;
				return & (m_->at (i0_ + p / c_, j0_ + p % c_));
			}

			const_reference
			operator[] (size_type n) const
			{
				size_type p = p_ + n;
				return m_->at (i0_ + p / c_, j0_ + p % c_);
			}

		private:
			const Matrix* m_;
			size_type p_;
			size_type i0_;
			size_type j0_;
			size_type c_;

		};

		typedef std::reverse_iterator<region_iterator> reverse_region_iterator;
		typedef std::reverse_iterator<const_region_iterator> const_reverse_region_iterator;

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


		iterator
		begin_row (size_type row)
		{
			assert (row < rows_);
			return iterator (data_ + row * cols_);
		}

		const_iterator
		begin_row (size_type row) const
		{
			assert(row < rows_);
			return const_iterator (data_ + row * cols_);
		}

		const_iterator
		cbegin_row (size_type row) const
		{
			assert(row < rows_);
			return const_iterator (data_ + row * cols_);
		}

		iterator
		end_row (size_type row)
		{
			assert(row < rows_);
			return iterator (data_ + (row + 1) * cols_);
		}

		const_iterator
		end_row (size_type row) const
		{
			assert(row < rows_);
			return const_iterator (data_ + (row + 1) * cols_);
		}

		const_iterator
		cend_row (size_type row) const
		{
			assert(row < rows_);
			return const_iterator (data_ + (row + 1) * cols_);
		}

		reverse_iterator
		rbegin_row (size_type row)
		{
			assert(row < rows_);
			return reverse_iterator (data_ + (row + 1) * cols_);
		}

		const_reverse_iterator
		rbegin_row (size_type row) const
		{
			assert(row < rows_);
			return const_reverse_iterator (data_ + (row + 1) * cols_);
		}

		const_reverse_iterator
		crbegin_row (size_type row) const
		{
			assert(row < rows_);
			return const_reverse_iterator (data_ + (row + 1) * cols_);
		}

		reverse_iterator
		rend_row (size_type row)
		{
			assert(row < rows_);
			return reverse_iterator (data_ + row * cols_);
		}

		const_reverse_iterator
		rend_row (size_type row) const
		{
			assert(row < rows_);
			return const_reverse_iterator (data_ + row * cols_);
		}

		const_reverse_iterator
		crend_row (size_type row) const
		{
			assert(row < rows_);
			return const_reverse_iterator (data_ + row * cols_);
		}



		range_iterator
		begin_col (size_type col)
		{
			assert (col < cols_);
			return range_iterator (data_ + col, cols_);
		}

		const_range_iterator
		begin_col (size_type col) const
		{
			assert (col < cols_);
			return const_range_iterator (data_ + col, cols_);
		}

		const_range_iterator
		cbegin_col (size_type col) const
		{
			assert (col < cols_);
			return const_range_iterator (data_ + col, cols_);
		}

		range_iterator
		end_col (size_type col)
		{
			assert (col < cols_);
			return range_iterator (data_ + col + size_, cols_);
		}

		const_range_iterator
		end_col (size_type col) const
		{
			assert (col < cols_);
			return const_range_iterator (data_ + col + size_, cols_);
		}

		const_range_iterator
		cend_col (size_type col) const
		{
			assert (col < cols_);
			return const_range_iterator (data_ + col + size_, cols_);
		}

		reverse_range_iterator
		rbegin_col (size_type col)
		{
			assert (col < cols_);
			return reverse_range_iterator (end_col (col));
		}

		const_reverse_range_iterator
		rbegin_col (size_type col) const
		{
			assert (col < cols_);
			return const_reverse_range_iterator (cend_col (col));
		}

		const_reverse_range_iterator
		crbegin_col (size_type col) const
		{
			assert (col < cols_);
			return const_reverse_range_iterator (cend_col (col));
		}

		reverse_range_iterator
		rend_col (size_type col)
		{
			assert (col < cols_);
			return reverse_range_iterator (begin_col(col));
		}

		const_reverse_range_iterator
		rend_col (size_type col) const
		{
			assert (col < cols_);
			return const_reverse_range_iterator (cbegin_col (col));
		}

		const_reverse_range_iterator
		crend_col (size_type col) const
		{
			assert (col < cols_);
			return const_reverse_range_iterator (cbegin_col (col));
		}




		range_iterator
		begin_diag ()
		{
			assert (rows_ == cols_);
			return range_iterator (data_, cols_ + 1);
		}

		const_range_iterator
		begin_diag () const
		{
		    assert (rows_ == cols_);
			return const_range_iterator (data_, cols_ + 1);
		}

		const_range_iterator
		cbegin_diag () const
		{
		    assert (rows_ == cols_);
			return const_range_iterator (data_, cols_ + 1);
		}

		range_iterator
		end_diag ()
		{
		    assert (rows_ == cols_);
			return range_iterator (data_ + size_ + cols_, cols_ + 1);
		}

		const_range_iterator
		end_diag () const
		{
		    assert (rows_ == cols_);
			return const_range_iterator (data_ + size_ + cols_ , cols_ + 1);
		}

		const_range_iterator
		cend_diag () const
		{
		    assert (rows_ == cols_);
			return const_range_iterator (data_ + size_ + cols_, cols_ + 1);
		}

		reverse_range_iterator
		rbegin_diag ()
		{
		    assert (rows_ == cols_);
			return reverse_range_iterator (end_diag ());
		}

		const_reverse_range_iterator
		rbegin_diag () const
		{
		    assert (rows_ == cols_);
			return const_reverse_range_iterator (cend_diag ());
		}

		const_reverse_range_iterator
		crbegin_diag () const
		{
		    assert (rows_ == cols_);
			return const_reverse_range_iterator (cend_diag ());
		}

		reverse_range_iterator
		rend_diag ()
		{
		    assert (rows_ == cols_);
			return reverse_range_iterator (begin_diag ());
		}

		const_reverse_range_iterator
		rend_diag () const
		{
		    assert (rows_ == cols_);
			return const_reverse_range_iterator (cbegin_diag ());
		}

		const_reverse_range_iterator
		crend_diag () const
		{
		    assert (rows_ == cols_);
			return const_reverse_range_iterator (cbegin_diag ());
		}




		region_iterator
		begin_region (size_type i0, size_type j0,
					  size_type rows, size_type cols)
		{
			assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return region_iterator (this, 0, i0, j0, cols);
		}

		const_region_iterator
		begin_region (size_type i0, size_type j0,
					  size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_region_iterator (this, 0, i0, j0, cols);
		}

		const_region_iterator
		cbegin_region (size_type i0, size_type j0,
					   size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_region_iterator (this, 0, i0, j0, cols);
		}

		region_iterator
		end_region (size_type i0, size_type j0,
					size_type rows, size_type cols)
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return region_iterator (this, rows * cols, i0, j0, cols);
		}

		const_region_iterator
		end_region (size_type i0, size_type j0,
					size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_region_iterator (this, rows * cols, i0, j0, cols);
		}

		const_region_iterator
		cend_region (size_type i0, size_type j0,
					 size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_region_iterator (this, rows * cols, i0, j0, cols);
		}

		reverse_region_iterator
		rbegin_region (size_type i0, size_type j0,
					   size_type rows, size_type cols)
		{
			assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return reverse_region_iterator (end_region (i0, j0, rows, cols));
		}

		const_reverse_region_iterator
		rbegin_region (size_type i0, size_type j0,
					   size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_reverse_region_iterator (cend_region (i0, j0,
															   rows, cols));
		}

		const_reverse_region_iterator
		crbegin_region (size_type i0, size_type j0,
						size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_reverse_range_iterator (cend_region (i0, j0,
															   rows, cols));
		}

		reverse_region_iterator
		rend_region (size_type i0, size_type j0,
					 size_type rows, size_type cols)
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return reverse_region_iterator (begin_region (i0, j0,
														  rows, cols));
		}

		const_reverse_region_iterator
		rend_region (size_type i0, size_type j0,
				   size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_reverse_region_iterator (cbegin_region (i0, j0,
																 rows, cols));
		}

		const_reverse_region_iterator
		crend_region (size_type i0, size_type j0,
					  size_type rows, size_type cols) const
		{
		    assert (i0 < rows_);
			assert (j0 < cols_);
			assert (i0 + rows <= rows_);
			assert (j0 + cols <= cols_);
			return const_reverse_region_iterator (cbegin_region (i0, j0,
																 rows, cols));
		}


		bool
		is_id () const;

		bool
		is_inverse_of (const Matrix& m) const;


		//Traingular matrices

		bool
		is_lower_triangular () const;

		bool
		is_upper_triangular () const;

		varr_type
		lower_triangular_rows_get () const;

		varr_type
		lower_triangular_cols_get () const;

		varr_type
		upper_triangular_rows_get () const;

		varr_type
		upper_triangular_cols_get () const;

		static Matrix
		lower_triangular_from_rows (const varr_type& vals);

		static Matrix
		lower_triangular_from_cols (const varr_type& vals);

		static Matrix
		upper_triangular_from_rows (const varr_type& vals);

		static Matrix
		upper_triangular_from_cols (const varr_type& vals);

		Vector<T>
		lower_triangular_solve_system (const Vector<T>& b) const;

		Matrix
		lower_triangular_solve_systems (const Matrix& b) const;

		Vector<T>
		upper_triangular_solve_system (const Vector<T>& b) const;

		Matrix
		upper_triangular_solve_systems (const Matrix& b) const;

		Matrix
		lower_triangular_inverse () const;

		Matrix
		upper_triangular_inverse () const;

		T
		triangular_determinant () const;

		bool
		triangular_is_inversible () const;



		//Diagonal matrices

		bool
		is_diagonal () const;

		Vector<T>
		diagonal_to_vector () const;

		static Matrix
		diagonal_from_vector (const Vector<T>& it);

		template <class It>
		static Matrix
		diagonal_from_it (It begin, It end);

		//Gauss manipulations

		Matrix
		gauss_to_echelon_form () const;

		Matrix
		gauss_to_echelon_form (Matrix& p) const;

		///Returns rank using gauss method
		size_type
		gauss_rank () const;

		///Returns a base for Row(M) using gauss method
		varr_type
		gauss_row_base () const;

		///Returns a base for Col(M) using gauss method
		varr_type
		gauss_col_base () const;

		///Returns a base for Null(M) using gauss method
		varr_type
		gauss_null_base () const;

		///Returns the matrix inverse using gauss method
		Matrix
		gauss_inverse () const;


		///Orthogonalisation

		bool
		is_orthogonal () const;

		static Matrix
		outter_product (const Vector<T>& a, const Vector<T>& b);

		varr_type
		row_basis () const;

		varr_type
		col_basis () const;

		size_type
		rank () const;

		varr_type
		null_basis () const;

		void
		gram_schmidt_qr_decomposition (Matrix &q, Matrix &r) const;

		Vector <T>
		qr_solver (const Vector<T>& b) const;


		//QR Decompositon

		///Computes the QR decomposition using Householder projectors
		void
		householder_qr_decomposition(Matrix &q, Matrix &r) const;

		///Calculate det(M) using Householder QR decomposition
		T
		qr_determinant () const;

		///Returns x: Mx = b using Householder QR decomposition
		Vector<T>
		qr_solve_system (const Vector<T>& b) const;

		///Returns X: MX = B using Householder QR decompositon
		Matrix<T>
		qr_solve_systems (const Matrix<T>& b) const;

		///Computes the inverse of M using Householder QR decomposition
		Matrix<T>
		qr_inverse () const;





        //Cholesky decomposition

		Matrix
		cholesky_decomposition () const;

		void
		cholesky_ldl_decomposition (Matrix &l, Matrix &d) const;

		///Returns x : Mx = b using cholesky decomposition
		Vector<T>
		cholesky_solve_system (const Vector<T>& b) const;

		///Returns X: MX = B using cholesky decomposition
		Matrix<T>
		cholesky_solve_systems (const Matrix<T>& b) const;

		///Computes the inverse of M using cholesky decomposition
		Matrix<T>
		cholesky_inverse () const;

		///Returns det(M) using cholesky decomposition
		T
		cholesky_determinant () const;



		//LU Decomposition

		void
		lu_decomposition (Matrix& l, Matrix &u) const;


		///Returns the number of rows permutations
		size_type
		plu_decomposition (Matrix& p, Matrix &l, Matrix& u) const;

		///Returns det(M) using the PLU decomposition
		T
		plu_determinant () const;

		///Returns x: Mx = b using the PLU decomposition
		Vector<T>
		plu_solve_system (const Vector<T>& b) const;

		///Returns X: MX = B using the PLU decomposition
		Matrix<T>
		plu_solve_systems (const Matrix<T>& b) const;

		///Comptes the inverse of M using the PLU decomposition
		Matrix<T>
		plu_inverse () const;







	private:
		T* data_;
		size_type rows_;
		size_type cols_;
		size_type size_;

		size_type
		gauss_count_rank () const;

		void
		householder_update_q (const Vector<T>& v, size_type n, size_type col);

		void
		householder_update_r (const Vector<T>& v, size_type n, size_type p,
							  size_type col);

		static T
		plu_get_determinant (const Matrix& u, size_type parity);


		friend class SerialManager<Matrix>;


	};

	using mat_type = Matrix<double>;

	template <class T>
	class SerialManager<Matrix<T>>
	{
	public:
		static void
		pack (std::ostream& os, const Matrix<T>& data)
		{
			serialize (os, data.rows_);
			serialize (os, data.cols_);
			os.write (reinterpret_cast <const char *> (data.data_),
					  data.size_ * sizeof (T));
		}

		static Matrix<T>
		unpack (std::istream& is)
		{
			size_t rows = unserialize <size_t> (is);
			size_t cols = unserialize <size_t> (is);
			Matrix<T> m (rows, cols);
			is.read (reinterpret_cast<char *> ( m.data_),
					 m.size_ * sizeof (T));
			return m;
		}
	};

	template <class T>
	Matrix<T>
	Matrix<T>::id (size_type size)
	{
		Matrix m (size, size, static_cast<T> (0));
		for (size_type i = 0; i < size; ++i)
			m.at (i, i) = 1;
		return m;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::null (size_type rows, size_type cols)
	{
		return Matrix (rows, cols, static_cast<T> (0));
	}

	template <class T>
	Matrix<T>
	Matrix<T>::from_row_vector (const Vector<T>& v)
	{
		return Matrix (1, v.size_, v.data_);
	}

	template <class T>
	Matrix<T>
    Matrix<T>::from_col_vector (const Vector<T>& v)
	{
		return Matrix (v.size_, 1, v.data_);
	}

	template <class T>
    Matrix<T>
	Matrix<T>::from_rows_vectors (const varr_type& rows)
	{
		if (rows.empty())
			return Matrix {};

		size_type r = rows.size ();
		size_type c = rows[0].size_;
		Matrix m (r, c);
		for (size_type i = 0; i < r; ++i)
			for (size_type j = 0; j < c; ++j)
				m.at (i, j) = rows[i].data_[j];
		return m;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::from_cols_vectors (const varr_type& cols)
	{
		if (cols.empty())
			return Matrix {};

		size_type c = cols.size ();
		size_type r = cols[0].size_;
		Matrix m (r, c);
		for (size_type i = 0; i < r; ++i)
			for (size_type j = 0; j < c; ++j)
				m.at (i, j) = cols[j].data_[i];
		return m;
	}

	template <class T>
	template <class It>
	Matrix<T>
	Matrix<T>::from_row (It begin, It end)
	{
		return Matrix (1, end - begin, begin);
	}

	template <class T>
	template <class It>
	Matrix<T>
	Matrix<T>::from_col (It begin, It end)
	{
		return Matrix (end - begin, 1, begin);
	}

	template <class T>
	Matrix<T>::Matrix (size_type rows, size_type cols)
		: rows_ (rows), cols_ (cols), size_ (rows * cols)
	{
		data_ = new T[size_];
	}

	template <class T>
	Matrix<T>::Matrix (size_type rows, size_type cols, const T& x)
		: Matrix (rows, cols)
	{
		std::fill (data_, data_ + size_, x);
	}

	template <class T>
	template <class It>
	Matrix<T>::Matrix (size_type rows, size_type cols, It begin)
		: Matrix (rows, cols)
	{
		std::copy_n (begin, size_, data_);
	}

	template <class T>
	Matrix<T>::Matrix (size_type rows, size_type cols,
					   std::initializer_list<T> list)
		: Matrix (rows, cols, list.begin ())
	{

	}

	template <class T>
	Matrix<T>::Matrix (const Matrix& v)
		: Matrix(v.rows_, v.cols_, v.data_)
	{

	}

	template <class T>
	Matrix<T>::~Matrix ()
	{
		delete data_;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator= (const T& x)
	{
		assign (x);
		return *this;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator= (const Matrix& v)
	{
		assign (v);
		return *this;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator= (std::initializer_list<T> list)
	{
		assign (list);
		return *this;
	}

	template <class T>
	void
	Matrix<T>::assign (const T& x)
	{
		std::fill (data_, data_ + size_, x);
	}

	template <class T>
	void
	Matrix<T>::assign (size_type rows, size_type cols, const T& x)
	{
		resize (rows, cols, x);
	}

	template <class T>
	void
	Matrix<T>::assign (const Matrix& v)
	{
		resize (v.rows_, v.cols_);
		std::copy_n (v.data_, size_, data_);
	}

	template <class T>
	void
	Matrix<T>::assign (std::initializer_list<T> list)
	{
		std::copy (list.begin (), list.end (), data_);
	}

	template <class T>
	void
	Matrix<T>::assign (size_type rows, size_type cols,
					   std::initializer_list<T> list)
	{
		resize (rows, cols);
		std::copy (list.begin (), list.end (), data_);
	}

	template <class T>
	template <class It>
	void
	Matrix<T>::assign (It begin, It end)
	{
		std::copy (begin, end, data_);
	}

	template <class T>
	template <class It>
	void
	Matrix<T>::assign (size_type rows, size_type cols, It begin)
	{
		resize (rows, cols);
		std::copy_n (begin, size_, data_);
	}

    template <class T>
	void
	Matrix<T>::resize (size_type rows, size_type cols)
	{
		size_type n = rows * cols;
		if(n != size_)
		{
			delete data_;
			data_ = new T[n];
			size_ = n;
		}
		rows_ = rows;
		cols_ = cols;
	}

	template <class T>
	void
	Matrix<T>::resize (size_type rows, size_type cols, const T& x)
	{
		resize (rows, cols);
		std::fill (data_, data_ + size_, x);
	}

	template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::rows () const
	{
		return rows_;
	}

	template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::cols () const
	{
		return cols_;
	}

	template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::size () const
	{
		return size_;
	}


	template <class T>
	bool
	Matrix<T>::empty () const
	{
		return !size_;
	}

	template <class T>
	typename Matrix<T>::reference
	Matrix<T>::at (size_type i, size_type j)
	{
		assert(i < rows_);
		assert(j < cols_);
		return data_[i * cols_ + j];
	}

	template <class T>
	typename Matrix<T>::const_reference
	Matrix<T>::at (size_type i, size_type j) const
	{
		assert(i < rows_);
		assert(j < cols_);
		return data_[i * cols_ + j];
	}

	template <class T>
	T*
	Matrix<T>::data ()
	{
		return data_;
	}

	template <class T>
	const T*
	Matrix<T>::data () const
	{
		return data_;
	}

	template <class T>
	void
	Matrix<T>::swap (Matrix& v)
	{
		if (v.rows_ != rows_ || v.cols_ != cols_)
		{
			Matrix temp = v;
			v.assign (*this);
			assign (temp);
		}
		else
			std::swap_ranges (data_, data_ + size_, v.data_);
	}

	template <class T>
	Vector<T>
	Matrix<T>::vector_get () const
	{
		return Vector<T> (data_, data_ + size_);
	}

	template <class T>
	Vector<T>
	Matrix<T>::row_vector_get (size_type row) const
	{
		Vector<T> v (cols_);
		for (size_type i = 0; i < cols_; ++i)
			v.data_[i] = at (row, i);
		return v;
	}

	template <class T>
	Vector<T>
	Matrix<T>::col_vector_get (size_type col) const
	{
		Vector<T> v (rows_);
		for (size_type i = 0; i < rows_; ++i)
			v.data_[i] = at (i, col);
		return v;
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::rows_vectors_get () const
	{
		varr_type arr (rows_);
		for (size_type i = 0; i < rows_; ++i)
			arr[i] = row_vector_get (i);
		return arr;
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::cols_vectors_get () const
	{
		varr_type arr (cols_);
		for (size_type i = 0; i < cols_; ++i)
			arr[i] = col_vector_get (i);
		return arr;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::transpose () const
	{
		Matrix m (cols_, rows_);
		for (size_type i = 0; i < rows_; ++i)
			for (size_type j = 0; j < cols_; ++j)
				m.at (j, i) = at (i, j);
		return m;
	}

	template <class T>
	bool
	Matrix<T>::is_symmetric () const
	{
		return rows_ == cols_ && equals (transpose ());
	}

	template<class T>
	std::ostream&
	operator<< (std::ostream& os, const Matrix<T>& v)
	{
		os << "[";
		for (size_t i = 0; i < v.rows_; ++i)
		{
			for (size_t j = 0; j < v.cols_; ++j)
			{
				os << v.at (i, j);
				if (i + 1 != v.rows_ || j + 1 != v.cols_)
					os << ", ";
			}
			if(i + 1 != v.rows_)
				os << "\n";
		}
		os << "]\n";
		return os;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator++ ()
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] += 1;
		return *this;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::operator++ (int)
	{
		Matrix temp (*this);
		for (size_t i = 0; i < size_; ++i)
			data_[i] += 1;
		return temp;
	}

    template <class T>
	Matrix<T>&
	Matrix<T>::operator-- ()
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= 1;
		return *this;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::operator-- (int)
	{
		Matrix temp (*this);
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= 1;
		return temp;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::operator- () const
	{
		Matrix neg (rows_, cols_);
		for (size_t i = 0; i < size_; ++i)
			neg.data_[i] = - data_[i];
		return neg;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator+= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] += x;
		return *this;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator+= (const Matrix& v)
	{
		assert (rows_ == v.rows_ && cols_ == v.cols_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] += v.data_[i];
		return *this;
	}

    template <class T>
	Matrix<T>&
	Matrix<T>::operator-= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= x;
		return *this;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator-= (const Matrix& v)
	{
	    assert (rows_ == v.rows_ && cols_ == v.cols_);
		for (size_t i = 0; i < size_; ++i)
			data_[i] -= v.data_[i];
		return *this;
	}

    template <class T>
	Matrix<T>&
	Matrix<T>::operator*= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] *= x;
		return *this;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator/= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] /= x;
		return *this;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator%= (const T& x)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] %= x;
		return *this;
	}

	template <class T>
	Matrix<T>&
	Matrix<T>::operator*= (const Matrix& v)
	{
		assert(cols_ == v.rows_);
	    Matrix res = *this * v;
		assign (res);
		return *this;
	}


	template <class T>
	bool
	Matrix<T>::is_id () const
	{
		return rows_ == cols_ && equals (id (rows_));
	}

	template <class T>
	bool
	Matrix<T>::is_inverse_of (const Matrix& m) const
	{
		return rows_ == cols_ && m.rows_ == m.cols_ && rows_ == m.rows_
			&& (*this * m).is_id ();
	}


	//Traingular matrices

	template <class T>
	bool
	Matrix<T>::is_lower_triangular () const
	{
		if (rows_ != cols_)
			return false;

		T norm = static_cast<T> (0);
		for (size_type i = 0; i < rows_; ++i)
			for (size_type j = i + 1; j < cols_; ++j)
				norm += at (i, j) * at (i, j);

		return norm < static_cast<T> (1e-10);
	}

	template <class T>
	bool
	Matrix<T>::is_upper_triangular () const
	{
		if (rows_ != cols_)
			return false;

		T norm = static_cast<T> (0);
		for (size_type i = 0; i < rows_; ++i)
			for (size_type j = 0; j < i; ++j)
				norm += at (i, j) * at (i, j);

		return norm < static_cast<T> (1e-10);
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::lower_triangular_rows_get () const
	{
		assert (rows_ == cols_);
		varr_type rows (rows_);

		for (size_type i = 0; i < rows_; ++i)
		{
			Vector<T> v (i+1);
			for (size_type j = 0; j < i+1; ++j)
				v[j] = at (i, j);
			rows[i] = v;
		}

		return rows;
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::lower_triangular_cols_get () const
	{
		assert (rows_ == cols_);
		varr_type cols (cols_);

		for (size_type j = 0; j < cols_; ++j)
		{
			Vector<T> v (rows_ - j);
			for (size_type i = j; i < rows_; ++i)
				v[i - j] = at (i, j);
			cols[j] = v;
		}

		return cols;
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::upper_triangular_rows_get () const
	{
		assert (rows_ == cols_);
		varr_type rows (rows_);

		for (size_type i = 0; i < rows_; ++i)
		{
			Vector<T> v (cols_ - i);
			for (size_type j = i; j < cols_; ++j)
				v[j - i] = at (i, j);
			rows[i] = v;
		}

		return rows;
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::upper_triangular_cols_get () const
	{
		assert (rows_ == cols_);
		varr_type cols (cols_);

		for (size_type j = 0; j < cols_; ++j)
		{
			Vector<T> v (j + 1);
			for (size_type i = 0; i < j + 1; ++i)
				v[i] = at (i, j);
			cols[j] = v;
		}

		return cols;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::lower_triangular_from_rows (const varr_type& vals)
	{
		size_type n = vals.size ();
		Matrix m = null (n, n);

		for (size_type i = 0; i < n; ++i)
		{
			assert (vals[i].size_ == i+1);
			for (size_type j = 0; j < i + 1; ++j)
				m.at (i, j) = vals[i].data_[j];
		}

		return m;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::lower_triangular_from_cols (const varr_type& vals)
	{
		size_type n = vals.size ();
		Matrix m = null (n, n);

		for (size_type j = 0; j < n; ++j)
		{
			assert (vals[j].size_ == n - j);
			for (size_type i = j; i < n; ++i)
				m.at (i, j) = vals[j].data_[i - j];
		}

		return m;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::upper_triangular_from_rows (const varr_type& vals)
	{
		size_type n = vals.size ();
		Matrix m = null (n, n);

		for (size_type i = 0; i < n; ++i)
		{
			assert (vals[i].size_ == n - i);
			for (size_type j = i; j < n; ++j)
				m.at (i, j) = vals[i].data_[j - i];
		}

		return m;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::upper_triangular_from_cols (const varr_type& vals)
	{
		size_type n = vals.size ();
		Matrix m = null (n, n);

		for (size_type j = 0; j < n; ++j)
		{
			assert (vals[j].size_ == j + 1);
			for (size_type i = 0; i < j + 1; ++i)
				m.at (i, j) = vals[j].data_[i];
		}

		return m;
	}

	template <class T>
	Vector<T>
	Matrix<T>::lower_triangular_solve_system (const Vector<T>& b) const
	{
		assert (rows_ == cols_);
		assert (rows_ == b.size_);
		size_type n = rows_;
		Vector<T> x (n);

		for(size_type i = 0; i < n; ++i)
		{
			T val = b.data_ [i];
			for(size_t k = 0; k < i; ++k)
				val -= at (i, k) * x.data_[k];
			x.data_[i] = val / at (i, i);
		}

		return x;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::lower_triangular_solve_systems (const Matrix& b) const
	{
		assert (rows_ == cols_);
		assert (rows_ == b.rows_);
		size_type n = rows_;

		Matrix x (rows_, b.cols_);

		for (size_type j = 0; j < b.cols_; ++j)
		{
			for (size_type i = 0; i < n; ++i)
			{
				T val = b.at (i, j);
				for (size_type k = 0; k < i; ++k)
					val -= at (i, k) * x.at (k, j);
				x.at (i, j) = val / at (i, i);
			}
		}

		return x;
	}

	template <class T>
	Vector<T>
	Matrix<T>::upper_triangular_solve_system (const Vector<T>& b) const
	{
		assert (rows_ == cols_);
		assert (rows_ == b.size_);
		size_type n = rows_;
		Vector<T> x (n);

		for(size_type i = n-1; i < n; --i)
		{
			T val = b.data_ [i];
			for(size_t k = i+1; k < n; ++k)
				val -= at (i, k) * x.data_[k];
			x.data_[i] = val / at (i, i);
		}

		return x;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::upper_triangular_solve_systems (const Matrix& b) const
	{
		assert (rows_ == cols_);
		assert (rows_ == b.rows_);
		size_type n = rows_;
		Matrix x (rows_, b.cols_);

		for (size_type j = 0; j < b.cols_; ++j)
		{
			for (size_type i = n - 1; i < n; --i)
			{
				T val = b.at (i, j);
				for (size_type k = i + 1; k < n; ++k)
					val -= at (i, k) * x.at (k, j);
				x.at (i, j) = val / at (i, i);
			}
		}

		return x;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::lower_triangular_inverse () const
	{
		assert (rows_ == cols_);
		return lower_triangular_solve_systems (id (rows_));
	}

	template <class T>
	Matrix<T>
	Matrix<T>::upper_triangular_inverse () const
	{
		assert (rows_ == cols_);
		return upper_triangular_solve_systems (id (rows_));
	}

	template <class T>
	T
	Matrix<T>::triangular_determinant () const
	{
		assert (rows_ == cols_);
		T det = static_cast<T> (1);
		for (size_type i = 0; i < rows_; ++i)
			det *= at (i, i);
		return det;
	}

	template <class T>
	bool
	Matrix<T>::triangular_is_inversible () const
	{
		assert (rows_ == cols_);
		return triangular_determinant() > static_cast<T> (1e-10);
	}





	//Diagonal matrices

	template <class T>
	bool
	Matrix<T>::is_diagonal () const
	{
		assert (rows_ == cols_);
		T val = static_cast<T> (0);
		for (size_type i = 0; i < rows_; ++i)
			for (size_type j = 0; j < cols_; ++j)
				if(i != j)
					val += at (i, j);
		return val < 1e-10;
	}


	template <class T>
	Vector<T>
	Matrix<T>::diagonal_to_vector () const
	{
		assert (rows_ == cols_);
		Vector<T> v (rows_);
		for (size_type i = 0; i < rows_; ++i)
			v.data_[i] = at (i, i);
		return v;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::diagonal_from_vector (const Vector<T>& it)
	{
		size_type n = it.size_;
		Matrix m (null (n, n));
		for (size_type i = 0; i < n; ++i)
			m.at (i, i) = it.data_ [i];
		return m;
	}

	template <class T>
	template <class It>
	Matrix<T>
	Matrix<T>::diagonal_from_it (It begin, It end)
	{
		size_type n = end - begin;
		Matrix m (null (n, n));
		size_type i = 0;
		It it = begin;
		for (; it != end; ++i, ++it)
			m.at (i, i) = *it;;
		return m;
	}


	template <class T>
	Matrix<T>
	Matrix<T>::gauss_to_echelon_form () const
	{
		Matrix m (*this);
		size_type n = rows_;
		size_type p = cols_;

		for (size_type j = 0; j < n-1 && j < p; ++j)
		{
			size_type pivot = j;
			for (size_type i = j + 1; i < n; ++i)
			{
				if (std::abs( m.at (i,j)) > std::abs (m.at (pivot, j)))
					pivot = i;
			}

			if(pivot != j)
				std::swap_ranges(m.begin_row (j), m.end_row (j),
								 m.begin_row (pivot));

			if(m.at (j, j))
			{

				for(size_type i = j + 1; i < n; ++i)
				{
					T multiplier = m.at (i, j) / m.at (j, j);
					m.at (i, j) = 0;
					for(size_type k = j + 1; k < p; ++k)
						m.at (i, k) = m.at (i, k) - multiplier * m.at (j, k);
				}

			}

			else
			{
				for(size_t k = j + 1; k < p; ++k)
					m.at (j, k) = 0;
				std::swap_ranges(m.begin_row (j), m.end_row (j),
								 m.begin_row (n - 1));
			}
		}

		return m;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::gauss_to_echelon_form (Matrix& perm) const
	{
		Matrix m (*this);
		size_type n = rows_;
		size_type p = cols_;
		perm = id (n);

	    for (size_type j = 0; j < n-1 && j < p; ++j)
		{
			size_type pivot = j;
			for (size_type i = j + 1; i < n; ++i)
			{
				if (std::abs( m.at (i,j)) > std::abs (m.at (pivot, j)))
					pivot = i;
			}

			if(pivot != j)
			{
				std::swap_ranges (m.begin_row (j), m.end_row (j),
								 m.begin_row (pivot));
				std::swap_ranges (perm.begin_row (j), perm.end_row (j),
								 perm.begin_row (pivot));
			}

			if(m.at (j, j))
			{

				for(size_type i = j + 1; i < n; ++i)
				{
					T multiplier = m.at (i, j) / m.at (j, j);
					m.at (i, j) = 0;
					for (size_type k = j + 1; k < p; ++k)
						m.at (i, k) = m.at (i, k) - multiplier * m.at (j, k);

					for (size_type k = 0; k < n; ++k)
						perm. at (i, k) = perm.at (i, k) - multiplier
							* perm.at (j, k);
				}

			}

			else
			{
				for(size_type k = j + 1; k < p; ++k)
					m.at (j, k) = 0;
				for (size_type k = 0; k < n; ++k)
					perm.at (j, k) = 0;
				std::swap_ranges(m.begin_row (j), m.end_row (j),
								 m.begin_row (n - 1));
				std::swap_ranges(perm.begin_row (j), perm.end_row (j),
								 perm.begin_row (n - 1));
			}
		}

		return m;
	}

    template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::gauss_rank () const
	{
		return gauss_to_echelon_form ().gauss_count_rank ();
	}

    template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::gauss_row_base () const
	{
		Matrix m = gauss_to_echelon_form ();
		size_type rank = m.gauss_count_rank();
		varr_type base (rank);
		for(size_type i = 0; i < rank; ++i)
			base[i] = Vector<T> (m.begin_row (i), m.end_row (i));

		return base;
	}


	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::gauss_col_base () const
	{
		return transpose ().gauss_row_base ();
	}


	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::gauss_null_base () const
	{
		Matrix m = transpose ();
		Matrix p;
	    Matrix res = m.gauss_to_echelon_form (p);
		size_type rank = res.gauss_count_rank ();
		size_type n = m.rows_ - rank;

		varr_type bs (n);
		for (size_type i = 0; i < n; ++i)
			bs[i] = Vector<T> (p.begin_row (rank + i), p.end_row (rank + i));

		return bs;
	}

    template <class T>
	Matrix<T>
	Matrix<T>::gauss_inverse () const
	{
		assert(rows_ == cols_);
		size_type n = rows_;
		Matrix m (*this);
		Matrix res (id (n));


		for(size_type j = 0; j < n; ++j)
		{
			size_t pivot = j;
			for(size_type i = j + 1; i < n; ++i)
				if (std::abs (m.at (i,j)) > std::abs (m.at (pivot, j)))
					pivot = i;

			if(pivot != j)
			{
				std::swap_ranges(m.begin_row (j), m.end_row (j),
								 m.begin_row (pivot));
				std::swap_ranges(res.begin_row (j), res.end_row (j),
								 res.begin_row (pivot));
			}

			T pivot_value = m.at (j, j);
			algo::divides_x(m.begin_row (j), m.end_row (j), pivot_value);
			algo::divides_x(res.begin_row (j), res.end_row (j), pivot_value);

			for(size_type i = 0; i < n; ++i)
			{
				if(i == j)
					continue;
				T val = m.at (i, j);

				for (size_type k = 0; k < n; ++k)
				{
					m.at (i, k) -= val * m.at (j, k);
					res.at (i, k) -= val * res.at (j, k);
				}
			}

		}

		return res;
	}

	template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::gauss_count_rank () const
	{
		size_type n = rows_;
		size_type p = cols_;

		for(size_type i = n-1; i < n; --i)
			for(size_type j = 0; j < p; ++j)
				if(at (i, j))
				return i + 1;
		return 0;
	}



	///Orthogonalisation


	template <class T>
	bool
	Matrix<T>::is_orthogonal () const
	{
		return rows_ == cols_ && is_inverse_of (transpose ());
	}

	template <class T>
	Matrix<T>
	Matrix<T>::outter_product (const Vector<T>& a, const Vector<T>& b)
	{
		size_type n = a.size_;
		size_type p = b.size_;
		Matrix m (n, p);

		for (size_type i = 0; i < n; ++i)
			for( size_type j = 0; j < p; ++j)
				m.at (i, j) = a.data_[i] * b.data_[j];

		return m;
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::row_basis () const
	{
	    return Vector<T>::basis_get (rows_vectors_get ());
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::col_basis () const
	{
		return Vector<T>::basis_get (cols_vectors_get ());
	}

	template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::rank () const
	{
		if (rows_ > cols_)
			return Vector<T>::rank (rows_vectors_get ());
		else
			return Vector<T>::rank (cols_vectors_get ());
	}

	template <class T>
	typename Matrix<T>::varr_type
	Matrix<T>::null_basis () const
	{
		size_type p = cols_;
		varr_type set = cols_vectors_get ();
		varr_type coeffs;
		varr_type orth = Vector<T>::orthogonalize (set, coeffs);

		Matrix t (p ,p);
		for (size_type j = 0; j < p; ++j)
		{
			size_type i = 0;
			for(; i < j+1; ++i)
				t.at (i, j) = coeffs[j].data_[i];
			for(; i < p; ++i)
				t.at (i, j) = 0;
		}

		Matrix t_inv (t.upper_triangular_inverse ());

		varr_type basis;
		for(size_type i = 0; i < p; ++i)
		{
			if(orth[i].norm_square () < 1e-10)
				basis.push_back (Vector<T> (t_inv.begin_col (i),
											t_inv.end_col (i)));

		}

		return basis;
	}

	template <class T>
	void
	Matrix<T>::gram_schmidt_qr_decomposition (Matrix &q, Matrix &r) const
	{
		size_type p = cols_;
		varr_type set = cols_vectors_get ();
		varr_type coeffs;
		varr_type orth = Vector<T>::orthogonalize (set, coeffs);

		q = from_cols_vectors(orth);
		r = Matrix (p, p);
		for(size_type j = 0; j < p; ++j)
		{
			size_type i = 0;
			for(; i < j+1; ++i)
				r. at (i, j) = coeffs[j].data_[i];
			for(; i < p; ++i)
				r.at (i, j) = 0;
		}

		for(size_type i = 0; i < p; ++i)
		{
			T norm = algo::norm (q.begin_col (i), q.end_col (i));
			algo::divides_x (q.begin_col (i), q.end_col (i), norm);
			algo::multiplies_x (r.begin_row (i), r.end_row(i), norm);
		}
	}

	template <class T>
	Vector <T>
	Matrix<T>::qr_solver (const Vector<T>& b) const
	{
		Matrix q;
		Matrix r;
		gram_schmidt_qr_decomposition (q, r);

		Matrix qt = q.transpose ();
		Vector<T> c = qt * b;
		return r.upper_triangular_solve_system (c);
	}


	//QR Decomposition

	template <class T>
	void
	Matrix<T>::householder_update_q (const Vector<T>& v, size_type n,
									 size_type col)
	{
		Vector<T> x (n);
		for (size_type i = 0; i < n; ++i)
		{
			T val = 0;
			for (size_type j = 0; j < n - col; ++j)
				val += at (i, j + col) * v.data_[j];
			x.data_[i] = val;
		}

		for (size_type i = 0; i < n; ++i)
			for (size_type j = 0; j < n - col; ++j)
				at (i, j + col) -= 2 * x.data_[i] * v.data_[j];
	}

	template <class T>
	void
	Matrix<T>::householder_update_r (const Vector<T>& v, size_type n,
									 size_type p, size_type col)
	{
		Vector<T> x (p - col);
		for (size_type j = 0; j < p - col; ++j)
		{
			T val = 0;
			for (size_type i = 0; i < n - col; ++i)
				val += v.data_[i] * at (i + col, j + col);
			x.data_[j] = val;
		}

		for (size_type i = 0; i < n - col; ++i)
			for (size_type j = 0; j < p - col; ++j)
				at (i + col, j + col) -= 2 * v.data_[i] * x.data_[j];
	}

    template <class T>
	void
	Matrix<T>::householder_qr_decomposition(Matrix &q, Matrix &r) const
	{
		size_type n = rows_;
		size_type p = cols_;
		q = id (n);
		r = *this;

		for (size_type j = 0; j < n && j < p; ++j)
		{
			Vector<T> v (n - j);
			for (size_type i = j; i < n; ++i)
				v.data_ [i - j] = r.at (i, j);

			T s = v.data_[0] > 0 ? static_cast<T> (1) : static_cast<T> (-1);
			T norm = v.norm ();
			v.data_[0] -= s * norm;

			if (!v.is_null ())
			{
				v.normalize ();
				r.householder_update_r (v, n, p, j);
				q.householder_update_q (v, n, j);
			}
		}
	}

    template <class T>
	T
	Matrix<T>::qr_determinant () const
	{
		assert (rows_ == cols_);
		Matrix q;
		Matrix r;
		householder_qr_decomposition (q, r);
		return r.triangular_determinant ();
	}

    template <class T>
	Vector<T>
	Matrix<T>::qr_solve_system (const Vector<T>& b) const
	{
		assert (rows_ == cols_);
		assert (rows_ == b.size_);

		Matrix q;
		Matrix r;
		householder_qr_decomposition (q, r);

		Matrix qt = q.transpose ();
		Vector<T> b0 =qt * b;
		return r.upper_triangular_solve_system (b0);
	}

    template <class T>
	Matrix<T>
	Matrix<T>::qr_solve_systems (const Matrix<T>& b) const
	{
		assert (rows_ == cols_);
		assert (b.rows_ == b.cols_);
		assert (rows_ == b.rows_);

		Matrix q;
		Matrix r;
		householder_qr_decomposition (q, r);

		Matrix qt = q.transpose ();
		Matrix b0 = qt * b;
		return r.upper_triangular_solve_systems(b0);
	}

    template <class T>
	Matrix<T>
	Matrix<T>::qr_inverse () const
	{
		assert (rows_ == cols_);
		return qr_solve_systems (id (rows_));
	}


	//Cholesky decomposition

	template <class T>
	Matrix<T>
	Matrix<T>::cholesky_decomposition () const
	{
		assert(rows_ == cols_);

		size_type n = rows_;
		Matrix l (n, n);

		for(size_type i = 0; i < n; ++i)
		{
			for(size_type j = 0; j <= i; ++j)
			{

				T val = at (i, j);
				for (size_type k = 0; k < j; ++k)
					val -= l.at (i, k) * l.at (j, k);

				if( i == j)
					l.at (i, j) = std::sqrt (val);
				else
					l.at (i, j) = val / l.at (j, j);
			}
		}

		return l;
	}

	template <class T>
	void
	Matrix<T>::cholesky_ldl_decomposition (Matrix &l, Matrix &d) const
	{
		assert (rows_ == cols_);
		size_type n = rows_;
		l = id (n);
		d = null (n, n);

		for (size_type i = 0; i < n; ++i)
		{
			for (size_type j = 0; j < i; ++j)
			{
				T val = at (i, j);
				for (size_type k = 0; k < j; ++k)
					val -= l.at (i, k) * l.at (j, k) * d.at (k, k);
				l.at (i, j) = val / d.at (j, j);
			}

			T val = at (i, i);
			for (size_type k = 0; k < i; ++k)
				val -= l.at (i, k) * l.at (i, k) * d.at (k, k);
			d.at (i, i) = val;
		}
	}

    template <class T>
	Vector<T>
	Matrix<T>::cholesky_solve_system (const Vector<T>& b) const
	{
		assert (rows_ == cols_);

		Matrix l = cholesky_decomposition ();
		Matrix lt = l.transpose ();

		Vector<T> y = l.lower_triangular_solve_system (b);
		return lt.upper_triangular_solve_system (y);
	}

    template <class T>
	Matrix<T>
	Matrix<T>::cholesky_solve_systems (const Matrix<T>& b) const
	{
		assert (rows_ == cols_);

		Matrix l = cholesky_decomposition ();
		Matrix lt = l.transpose ();

		Matrix y = l.lower_triangular_solve_systems (b);
		return lt.upper_triangular_solve_systems (y);
	}

    template <class T>
	Matrix<T>
	Matrix<T>::cholesky_inverse () const
	{
		assert (rows_ == cols_);
		return cholesky_solve_systems (id (rows_));
	}

	template <class T>
	T
	Matrix<T>::cholesky_determinant () const
	{
		T det = cholesky_decomposition().triangular_determinant ();
		return det * det;
	}



	template <class T>
	T
	Matrix<T>::plu_get_determinant (const Matrix& u, size_type parity)
	{
		assert (u.rows_ == u.cols_);
		size_type n = u.rows_;

		T det = static_cast<T> (math::powm1 (static_cast <int> (parity)));

		for (size_type i = 0; i < n; ++i)
			det *= u.at (i, i);
		return det;
	}


	//LU Decomposition

	template <class T>
	void
	Matrix<T>::lu_decomposition (Matrix& l, Matrix &u) const
	{
		assert(rows_ == cols_);
		size_type n = rows_;
		l = id (n);
		u = *this;

		for (size_type j = 0; j < n; ++j)
		{
			for (size_type i = j + 1; i < n; ++i)
			{
				T num = u.at (i, j);
			    T den = u.at (j, j);
				T val = num || den ? num / den : static_cast<T> (0);
				u.at (i, j) = static_cast<T> (0);

				for (size_type k = j + 1; k < n; ++k)
					u.at (i, k) -= val * u.at (j, k);
				l.at (i, j) = val;
			}
		}
	}


    template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::plu_decomposition (Matrix& p, Matrix &l, Matrix& u) const
	{
		assert(rows_ == cols_);
		size_type n = rows_;
		size_type parity = 0;
		p = id (n);
		l = id (n);
		u = *this;

		for (size_type j = 0; j < n; ++j)
		{

			size_type pivot = j;
			for (size_type i = j + 1; i < n; ++i)
				if (std::abs (u.at (i, j)) > std::abs (u.at (pivot, j)))
					pivot = i;

			if (pivot != j)
			{
				++parity;
				std::swap_ranges (p.begin_row (j), p.end_row (j),
								  p.begin_row (pivot));
				std::swap_ranges (l.begin_row (j), l.end_row (j),
								  l.begin_row (pivot));
				std::swap_ranges (u.begin_row (j), u.end_row (j),
								  u.begin_row (pivot));
			}


			for (size_type i = j + 1; i < n; ++i)
			{
				T num = u.at (i, j);
				T den = u.at (j, j);
				T val = num || den ? num / den : static_cast<T> (0);
				u.at (i, j) = 0;
				for (size_type k = j + 1; k < n; ++k)
					u.at (i, k) -= val * u.at (j, k);
				l.at (i, j) = val;
			}
		}

		return parity;
	}

    template <class T>
	T
	Matrix<T>::plu_determinant () const
	{
		assert(rows_ == cols_);
		Matrix p;
		Matrix l;
		Matrix u;
		size_type parity = plu_decomposition (p, l, u);
		return plu_get_determinant (u, parity);
	}

    template <class T>
	Vector<T>
	Matrix<T>::plu_solve_system (const Vector<T>& b) const
	{
		assert(rows_ == cols_);
		assert(rows_ == b.size_);
		size_type n = rows_;
		Matrix p;
		Matrix l;
		Matrix u;
	    plu_decomposition (p, l, u);
		Vector<T> b0 = p * b;
		Vector<T> x (n);
		Vector<T> y (n);

		for (size_type i = 0; i < n; ++i)
		{
			T val = b0.data_[i];
			for (size_type k = 0; k < i; ++k)
				val -= l.at (i, k) * y.data_[k];
			y.data_[i] = val;
		}

		for (size_type i = n - 1; i < n; --i)
		{
			T val = y.data_[i];
			for (size_type k = i + 1; k < n; ++k)
				val -= u.at (i, k) * x.data_[k];
			x.data_[i] = val / u.at (i, i);
		}

		return x;
	}

	template <class T>
	Matrix<T>
	Matrix<T>::plu_solve_systems (const Matrix<T>& b) const
	{
		assert (rows_ == cols_);
		assert (b.rows_ == b.cols_);
		assert (rows_ == b.rows_);
		size_type n = rows_;
		Matrix p;
		Matrix l;
		Matrix u;
		plu_decomposition (p, l, u);
		Matrix b0 = p * b;
		Matrix y (n, n);
		Matrix x (n, n);

		for (size_type j = 0; j < n; ++j)
		{
			for(size_type i = 0; i < n; ++i)
			{
				T val = b0.at (i, j);
				for(size_type k = 0; k < i; ++k)
					val -= l.at(i, k) * y.at (k, j);
				y.at (i, j) = val;
			}
		}

		for (size_type j = 0; j < n; ++j)
		{
			for(size_type i = n - 1; i < n; --i)
			{
				T val = y.at (i, j);
				for (size_type k = i + 1; k < n; ++k)
					val -= u.at (i, k) * x.at (k, j);
				x.at (i, j) = val / u.at (i, i);
			}
		}

		return x;
	}

    template <class T>
	Matrix<T>
	Matrix<T>::plu_inverse () const
	{
		assert (rows_ == cols_);
		return plu_solve_systems (id (rows_));
	}


}

#endif //!MATRIX_HH_