#pragma once
#include "../LinkedListSequence.h"
#include <cassert>

void testLinkedListSequenceBasic()
{
	LinkedListSequence<int> list = LinkedListSequence<int>();
	int a = 0;
	list.Append(a);
	assert(list.GetLenght() == 1);
	assert(list.GetFirst() == 0);
}

void testLinkedListSequenceInsert()
{
	LinkedListSequence<int> list = LinkedListSequence<int>();
	int a = 0; int b = 1; int c = 2;
	list.Append(b);
	list.InsertAt(c, 1);
	list.Prepend(a);
	assert(list.Get(0) == 0);
	assert(list.Get(1) == 1);
	assert(list.Get(2) == 2);
}

void testLinkedListSequenceGet()
{
	LinkedListSequence<int> list = LinkedListSequence<int>();
	int a = 0; int b = 1; int c = 2;
	list.Append(b);
	list.InsertAt(c, 1);
	list.Prepend(a);
	assert(list.GetFirst() == 0);
	assert(list.Get(1) == 1);
	assert(list.GetLast() == 2);
}

void testLinkedListSequenceGetSubSequence()
{
	LinkedListSequence<int> list = LinkedListSequence<int>();
	int a = 0; int b = 1; int c = 2; int d = 3; int e = 4; int f = 5;
	
	list.Append(a);
	list.Append(b);
	list.Append(c);
	list.Append(d);
	list.Append(e);
	list.Append(f);

	LinkedListSequence<int> res = list.GetSubSequence(1, 4);
	assert(res.Get(0) == list.Get(1));
	assert(res.Get(1) == list.Get(2));
	assert(res.Get(2) == list.Get(3));
}

void testLinkedListSequenceConcat()
{
	LinkedListSequence<int> list1 = LinkedListSequence<int>();
	int a = 0; int b = 1; int c = 2;

	list1.Append(a);
	list1.Append(b);
	list1.Append(c);

	LinkedListSequence<int> list2 = LinkedListSequence<int>();
	int d = 3; int e = 4; int f = 5;

	list2.Append(d);
	list2.Append(e);
	list2.Append(f);

	list1 = list1.Concat(list2);

	assert(list1.Get(0) == 0);
	assert(list1.Get(1) == 1);
	assert(list1.Get(2) == 2);
	assert(list1.Get(3) == 3);
	assert(list1.Get(4) == 4);
}