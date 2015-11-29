#include <map>
#include <pthread.h>
#include "utils/HttpString.h"

using namespace std;

class Cache
{
private:
	pthread_mutex_t _mutex;
	map<HttpString, HttpString> _cache;

	Cache():_mutex(PTHREAD_MUTEX_INITIALIZER)
	{
	}
	Cache(const Cache&):_mutex(PTHREAD_MUTEX_INITIALIZER)
	{
	}

	void lock();
	void unlock();

public:
	static Cache* getInstance();
	void put(const HttpString& key, const HttpString& value);
	HttpString get(const HttpString& key);
};
