/** @file Observer design pattern
 */

#ifndef OBSERVER_HH_
# define OBSERVER_HH_

#include <cstddef>
#include <vector>
#include <algorithm>

 namespace opl
 {

	 struct Event
	 {
		 size_t sender;
		 size_t type;
		 size_t value;
		 std::vector<char> data;
	 };

	 class Subject;

	 class Observer
	 {
	 public:
		 virtual void
		 notify (const Event& evt) = 0;

	 };


	 class Subject
	 {

	 public:
		 void
		 subscribe (Observer* observer)
		 {
			 obs_.push_back (observer);
		 }

		 void
		 unsubscribe (Observer* observer)
		 {
			 obs_.erase (std::remove (obs_.begin (), obs_.end (), observer));
		 }

		 void
		 send_notify (const Event& evt)
	   	 {
			 for (size_t i = 0; i < obs_.size (); ++i)
				 obs_[i]->notify (evt);
   		 }

		 void
		 send_notify (size_t sender, size_t type, size_t value)
	   	 {
			 Event evt;
			 evt.sender = sender;
			 evt.type = type;
			 evt.value = value;
			 send_notify (evt);
		 }




	 private:
		 std::vector<Observer *> obs_;

	 };

 }


#endif //!OBSERVER_HH_