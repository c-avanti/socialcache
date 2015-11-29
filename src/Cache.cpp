#include "Cache.h"

Cache* Cache::getInstance()
{
	static Cache cache;
	return &cache;
}

void Cache::lock()
{
	pthread_mutex_lock(&_mutex);
}

void Cache::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

void Cache::put(const HttpString& key, const HttpString& value)
{
	lock();
	_cache[key] = value;
	unlock();
}

HttpString Cache::get(const HttpString& key)
{
	lock();
	map<HttpString, HttpString>::iterator iter = _cache.find(key);
	if (iter == _cache.end())
	{
		return "";
	}
	else
	{
		return iter->second;
	}
	unlock();
}
