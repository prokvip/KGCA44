#pragma once
template<class T>
class TObjectPool
{
public:
	static void* operator new (size_t size)
	{
		return _aligned_malloc(size, );
	}
	static void operator delete (void* obj)
	{
		_aligned_free(obj);
	}
};

