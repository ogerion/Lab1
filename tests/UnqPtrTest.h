#include "../UnqPtr.h"
#include <cassert>

void testUnqPtrBasic()
{
	int * a = new int(10);
	UnqPtr<int> ptr(a);
	
	assert(ptr);
	assert(*ptr == 10);
	
	UnqPtr<int> ptr1(ptr);
	
	assert(!ptr);
	assert(*ptr1 == 10);
	
	UnqPtr<int> ptr2 = ptr1;
	
	assert(!ptr1);
	assert(*ptr2 == 10);
}

void testUnqPtrMove()
{
	int* a = new int(10);
	UnqPtr<int> ptr(a);

	assert(ptr);
	assert(*ptr = 10);

	UnqPtr<int> ptr1(std::move(ptr));

	assert(!ptr);
	assert(*ptr1 == 10);

	UnqPtr<int> ptr2 = std::move(ptr1);
	
	assert(!ptr1);
	assert(*ptr2 == 10);
}

void testUnqPtrRelease()
{
	int* a = new int(10);
	UnqPtr<int> ptr(a);

	delete (ptr.release());
	assert(!ptr);
}
