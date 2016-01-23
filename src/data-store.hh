/** @file DataStore class definition
 */

#ifndef DATA_STORE_HH_
#define DATA_STORE_HH_

# include <cstddef>
# include <string>
# include <map>
# include <vector>
# include <iostream>
# include <sstream>
# include "serialization.hh"

namespace opl
{

	class DataStore
	{

	public:
		using binarr_type = std::vector<char>;

		DataStore ();

		size_t
		size () const;

		bool
		empty () const;

		bool
		has_item (const std::string& key) const;

		binarr_type
		bin_get (const std::string& key) const;

		void
		bin_set (const std::string& key, const binarr_type& value);


		template <class T>
		void
		item_set (const std::string& key, T value)
		{
			std::stringstream ss;
		    serialize(ss, value);
			binarr_type data { std::istreambuf_iterator<char> (ss),
					std::istreambuf_iterator<char> () };
			bin_set (key, data);
		}

		template <class T>
		T
		item_get (const std::string& key) const
		{
			binarr_type data = bin_get (key);
			std::stringstream ss;
			ss.write (&(data[0]), data.size ());
			return unserialize<T> (ss);
		}


	private:

		std::map<std::string, binarr_type> map_;
		friend class SerialManager<DataStore>;

	};

	template <>
	class SerialManager<DataStore>
	{
	public:
		static void
		pack (std::ostream& os, const DataStore& data)
   		{
			serialize (os, data.map_);
		}

		static DataStore
		unpack (std::istream& is)
	 	{
			DataStore data;
			data.map_ = unserialize<std::map<std::string, std::vector<char>>> (is);
			return data;
		}
	};

}


#endif //!DATA_STORE_HH_