#include "HQHEASTLAllocator.h"

void* operator new(size_t size, const char*, int, unsigned, const char*, int)
{
	return ::operator new(size);
}

void operator delete(void* p, char const*, int, unsigned, char const*, int)
{
	if (p)
		::operator delete(p);
}
