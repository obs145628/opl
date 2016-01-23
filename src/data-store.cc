#include "data-store.hh"

#include <cassert>
#include <fstream>
#include "serialization.hh"

namespace opl
{

	DataStore::DataStore ()
		: map_ ()
	{

	}

	size_t
	DataStore::size () const
	{
		return map_.size ();
	}

	bool
	DataStore::empty () const
	{
		return map_.empty ();
	}

	bool
	DataStore::has_item (const std::string& key) const
	{
		return map_.find (key) != map_.end ();
	}

	DataStore::binarr_type
	DataStore::bin_get (const std::string& key) const
	{
		return map_.find (key)->second;
	}

	void
	DataStore::bin_set (const std::string& key, const binarr_type& value)
	{
		map_[key] = value;
	}

}