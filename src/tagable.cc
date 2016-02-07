#include <algorithm>
#include "tagable.hh"


namespace opl
{

	std::vector<std::string>
	Tagable::tags_get () const
	{
		return tags_;
	}

	size_t
	Tagable::tags_size () const
	{
		return tags_.size ();
	}

	std::string
	Tagable::tag_get (size_t i) const
	{
		return tags_[i];
	}

	void
	Tagable::insert_tag (const std::string& tag)
	{
		auto it = std::find (tags_.begin (), tags_.end (), tag);
		if (it == tags_.end ())
			tags_.push_back (tag);
	}

	void
	Tagable::remove_tag (const std::string& tag)
	{
	    auto it = std::find (tags_.begin (), tags_.end (), tag);
		if (it == tags_.end ())
			tags_.erase (it);
	}

	bool
	Tagable::has_tag (const std::string& tag) const
	{
		return std::find (tags_.begin (), tags_.end (), tag) != tags_.end ();
	}

	void
	Tagable::clear_tags ()
	{
		tags_.clear ();
	}

}