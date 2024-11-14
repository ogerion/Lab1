#include "../ShrdPtr.h"
#include "../WeakPtr.h"
#include <cassert>
void testWeakPtrBasic()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);

	assert(ptr);
	assert(*ptr == 10);

	WeakPtr<int> ptr1(ptr);

	assert(ptr);
	assert(*ptr1 == 10);

	WeakPtr<int> ptr2 = ptr1;

	assert(ptr1);
	assert(*ptr2 == 10);
}

void testWeakPtrMove()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);

	assert(ptr);
	assert(*ptr = 10);

	WeakPtr<int> ptr1(std::move(ptr));

	assert(ptr);
	assert(*ptr1 == 10);

	WeakPtr<int> ptr2 = std::move(ptr1);

	assert(ptr1);
	assert(*ptr2 == 10);
}

void testWeakPtrReset()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);
	WeakPtr<int> wptr(ptr);
	wptr.reset();

	assert(!wptr);
}

void testWeakPtrCounter()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);
	WeakPtr<int> ptr1(ptr);
	WeakPtr<int> ptr2(ptr);
	WeakPtr<int> ptr3(ptr);
	WeakPtr<int> ptr4(ptr);
	WeakPtr<int> ptr5(ptr);
	WeakPtr<int> ptr6(ptr);

	assert(ptr.countS() == 1);
	assert(ptr.countW() == 6);
}

void testWeakPtrTypeCast()
{
	class A {};
	class B : public A {};
	B* p = new B();
	ShrdPtr<B> ptr(p);
	WeakPtr<A> ptr1(ptr);
}
