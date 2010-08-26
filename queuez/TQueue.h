#include "TEvent.h"
#include "TMutex.h"

#include <deque>

template <class T>
class TQueue 
{
	TEvent _event;
	TMutex _mutex;
	std::deque<T> _queue;
public:
	T Get()
	{
		_event.Wait();
		{
			TLocker locker(&_mutex);
		
			T t = _queue.front();
			_queue.pop_front();
			if (_queue.size() == 0)
				_event.Reset();		
			return t;
		}
	}

	void Put(T t)
	{
		TLocker locker(&_mutex);
		_queue.push_back(t);
		_event.Set();
	}
};
