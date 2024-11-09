#include "../MsPtr.h"
#include <cassert>

void testMsPtrBasic()
{
	int* a = new int(10);
	MsPtr<int> ptr(a);
	WeakPtr<int>&& f(ptr.copy());
	assert(*(f) == 10);
	WeakPtr<int>&& f1 = ptr.copy();
	WeakPtr<int>&& f2 = ptr.copy();
	assert(f1.countS() == 1);
	assert(f2.countW() == 3);
	delete& f;
	delete& f1;
	delete& f2;
}

void testMsPtrCopy()
{
	int* a = new int(10);
	MsPtr<int> ptr(a);
	WeakPtr<int>&& f1 = ptr.copy();
	WeakPtr<int>&& f2 = ptr.copy();
	WeakPtr<int>&& f3 = ptr.copy();
	WeakPtr<int>&& f4 = ptr.copy();
	WeakPtr<int>&& f5 = ptr.copy();
	WeakPtr<int>&& f6 = ptr.copy();
	WeakPtr<int>&& f7 = ptr.copy();
	assert(f7.countW() == 7);
	delete& f1;
	delete& f2;
	delete& f3;
	delete& f4;
	delete& f5;
	delete& f6;
	delete& f7;
}

void testMsPtrGet()
{
	int* a = new int(10);
	MsPtr<int> ptr(a);
	WeakPtr<int>&& wptr = ptr.copy();
	UnqPtr<int>&& p = ptr.get();
	UnqPtr<int> uptr = p;
	delete &p;
	delete &wptr;

	assert(*uptr == 10);
}

void testMsPtrSet()
{
	int* a = new int(1);
	int* b = new int(2);
	int* c = new int(3);

	MsPtr<int> ptr1(a);
	MsPtr<int> ptr2(b);
	MsPtr<int> ptr3(c);

	ptr1.setNext(&ptr2);
	ptr2.setNext(&ptr3);
	ptr3.setNext(&ptr1);

	ptr1.setPrev(&ptr3);
	ptr3.setPrev(&ptr2);
	ptr2.setPrev(&ptr1);
	
	WeakPtr<int>&& f1 = ptr1.copy(-2);
	WeakPtr<int>&& f2 = ptr1.copy(-1);
	WeakPtr<int>&& f3 = ptr1.copy(0);
	WeakPtr<int>&& f4 = ptr1.copy(1);
	WeakPtr<int>&& f5 = ptr1.copy(2);
	assert(*(f1) == 2);
	assert(*(f2) == 3);
	assert(*(f3) == 1);
	assert(*(f4) == 2);
	assert(*(f5) == 3);
	delete& f1;
	delete& f2;
	delete& f3;
	delete& f4;
	delete& f5;
	assert(ptr1.getNext() == &ptr2);
}