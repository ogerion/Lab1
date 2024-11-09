#include "../MemorySpan.h"
#include <cassert>

void testMemorySpanBasic()
{
	int* a = new int(1);
	MemorySpan<int> span(a);
	UnqPtr<int>&& f = span.getFirst();
	assert(*(f) == 1);
	delete &f;
}

void testMemorySpanConcat()
{
	int* a = new int(1);
	MemorySpan<int> span1(a);
	span1.append(new int(2));
	span1.append(new int(3));
	span1.append(new int(4));
	span1.append(new int(5));
	span1.append(new int(6));
	span1.append(new int(7));

	int* b = new int(8);
	MemorySpan<int> span2(b);
	span2.append(new int(9));
	span2.append(new int(10));
	span2.append(new int(11));
	span2.append(new int(12));
	span2.append(new int(13));
	span2.append(new int(14));

	span1.concat(span2);
	
	assert(span1.getLenght() == 14);
}

void testMemorySpanGet()
{
	int* a = new int(1);
	MemorySpan<int> span(a);
	span.append(new int(2));
	span.append(new int(3));
	span.append(new int(4));
	span.append(new int(5));
	span.append(new int(6));
	UnqPtr<int> && f = span.getFirst();
	assert(*(f) == 1);
	delete &f;
	UnqPtr<int>&& s = span.getFirst();
	assert(*(s) == 2);
	delete &s; 
	UnqPtr<int>&& t = span.getFirst();
	assert(*(t) == 3);
	delete &t; 
	UnqPtr<int>&& fo = span.getFirst();
	assert(*(fo) == 4);
	delete &fo; 
	UnqPtr<int>&& fi = span.getLast();
	assert(*(fi) == 6);
	delete& fi;
	assert(span.getLenght() == 1);
}

void testMemorySpanCopy()
{
	int* a = new int(1);
	MemorySpan<int> span(a);
	span.append(new int(2));
	span.append(new int(3));
	span.append(new int(4));
	span.append(new int(5));
	span.append(new int(6));
	WeakPtr<int>&& f = span.copyFirst();
	assert(*(f) == 1);
	WeakPtr<int>&& s = span.copyFirst();
	assert(*(s) == 1);
	WeakPtr<int>&& t = span.copyFirst();
	assert(*(t) == 1);
	WeakPtr<int>&& fo = span.copyFirst();
	assert(*(fo) == 1);
	WeakPtr<int>&& fi = span.copyLast();
	assert(*(fi) == 6);
	assert(span.getLenght() == 6);
	delete& f;
	delete& s;
	delete& t;
	delete& fo;
	delete& fi;
}