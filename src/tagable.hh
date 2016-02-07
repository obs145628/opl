/** @File Tagable class definition
 */

#ifndef TAGABLE_HH_
# define TAGABLE_HH_

# include <vector>
# include <string>

namespace opl
{

	///Mixin for managaging a list of string tags
	class Tagable
	{

	public:

		std::vector<std::string>
		tags_get () const;

		size_t
		tags_size () const;

		std::string
		tag_get (size_t i) const;

		void
		insert_tag (const std::string& tag);

		void
		remove_tag (const std::string& tag);

		bool
		has_tag (const std::string& tag) const;

		void
		clear_tags ();


	private:
		std::vector<std::string> tags_;


	};

}

#endif //!TAGABLE_HH_