#include "../ShrdPtr.h"
#include "../WeakPtr.h"
#include <cassert>
void testShrdPtrBasic()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);

	assert(ptr);
	assert(*ptr == 10);

	ShrdPtr<int> ptr1(ptr);

	assert(ptr);
	assert(*ptr1 == 10);

	ShrdPtr<int> ptr2 = ptr1;

	assert(ptr1);
	assert(*ptr2 == 10);
}

void testShrdPtrMove()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);

	assert(ptr);
	assert(*ptr = 10);

	ShrdPtr<int> ptr1(std::move(ptr));

	assert(ptr);
	assert(*ptr1 == 10);

	ShrdPtr<int> ptr2 = std::move(ptr1);

	assert(ptr1);
	assert(*ptr2 == 10);
}

void testShrdPtrReset()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);

	ptr.reset();

	assert(!ptr);
}

void testShrdPtrCounter()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);
	ShrdPtr<int> ptr1(std::move(ptr));
	ShrdPtr<int> ptr2(std::move(ptr));
	ShrdPtr<int> ptr3(std::move(ptr));
	ShrdPtr<int> ptr4(std::move(ptr));
	ShrdPtr<int> ptr5(std::move(ptr));
	ShrdPtr<int> ptr6(std::move(ptr));
	assert(ptr.countS() == 7);
}

void testShrdPtrTypeCast()
{
	class A{};
	class B : public A{};
	B* p = new B();
	ShrdPtr<B> ptr(p);
	ShrdPtr<A> ptr1(ptr);
}

void testShrdPtrCompatibilityWeak()
{
	int* a = new int(10);
	ShrdPtr<int> ptr(a);
	WeakPtr<int> wptr(ptr);
	ShrdPtr<int> ptr1(wptr);
	WeakPtr<int> wptr1(std::move(ptr1));
	ShrdPtr<int> ptr2(std::move(wptr1));
	WeakPtr<int> wptr2 = std::move(ptr2);
	ShrdPtr<int> ptr3 = std::move(wptr2);
	WeakPtr<int> wptr3 = std::move(ptr3);
	ShrdPtr<int> ptr4 = std::move(wptr3);
	
	assert(ptr.countS() == 5);
	assert(ptr.countW() == 4);
}