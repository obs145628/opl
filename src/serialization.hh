/** @file Set of serialization funcitons
 */

#ifndef SERIALIZATION_HH_
# define SERIALIZATION_HH_

# include <iostream>
# include <vector>
# include <map>
# include <fstream>

namespace opl
{

	template <class T>
	class SerialManager
	{

	public:
		static void
		pack (std::ostream& os, const T& data)
		{
			os.write (reinterpret_cast<const char *> (&data), sizeof (data));
		}

		static T
		unpack (std::istream& is)
		{
			T val;
			is.read (reinterpret_cast<char *> (&val), sizeof (val));
			return val;
		}
	};

	template <class T>
	void
	serialize (std::ostream& os, const T& data)
	{
		SerialManager<T>::pack (os, data);
	}

	template <class T>
	T
	unserialize (std::istream& is)
	{
		return SerialManager<T>::unpack (is);
	}


	template<>
	class SerialManager<std::string>
	{

	public:
		static void
		pack (std::ostream& os, const std::string& data)
		{
			serialize(os, data.size());
			os.write(&(data[0]), data.size());
		}

		static std::string
		unpack (std::istream& is)
		{
			std::string data;
			size_t size = unserialize<size_t> (is);
			data.resize (size);
			is.read (&(data[0]), size);
			return data;
		}
	};

	template <class T>
	class SerialManager<std::vector<T>>
	{

	public:
		static void
		pack (std::ostream& os,
			  const std::vector<T>& data)
		{
			serialize (os, data.size ());
			os.write (&(data[0]), data.size ());
		}

		static std::vector<T>
		unpack (std::istream& is)
		{
			size_t size = unserialize<size_t> (is);
			std::vector<T> data (size);
			is.read (&(data[0]), size);
			return data;
		}

	};

	template <class U, class V>
	class SerialManager<std::map<U, V>>
	{

	public:
		static void
		pack (std::ostream& os,
			  const std::map<U, V>& data)
		{
			serialize(os, data.size ());
			for (auto it = data.begin (); it != data.end (); ++it)
			{
				serialize(os, it->first);
				serialize(os, it->second);
			}
		}

		static std::map<U, V>
		unpack (std::istream& is)
		{
			std::map<U, V> data;
			size_t size = unserialize<size_t> (is);
			for (size_t i = 0; i < size; ++i)
			{
				U key = unserialize<U> (is);
				V value = unserialize<V> (is);
				data[key] = value;
			}
			return data;
		}

	};

	template <class T>
	void serialize_to_file (const std::string& path, const T& data)
	{
		std::ofstream fs (path, std::ios::out | std::ios::binary);
		serialize(fs, data);
	}

	template <class T>
	T unserialize_from_file (const std::string& path)
	{
		std::ifstream fs (path, std::ios::binary);
		return unserialize<T> (fs);
	}



}


#endif //!SERIALIZATION_HH_