#ifndef HQHEASTLAllocator_H
#define HQHEASTLAllocator_H

#include "HQH.H"

// Copy From: \HQH7\EASTL-3.21.12\test\packages\EAStdC\test\source\EAStdCTest.cpp
void* operator new(size_t size, const char*, int, unsigned, const char*, int);
void operator delete(void* p, char const*, int, unsigned, char const*, int);

#endif // HQHEASTLAllocator_H
