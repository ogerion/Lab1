#include <chrono>
#include <iostream>
#include "../MemorySpan.h"
#include "../UnqPtr.h"
#include "../MsPtr.h"
#include "../ShrdPtr.h"
#include <vector>
#include <cmath>
#include <matplot/matplot.h>
#include <stdio.h>
using namespace std::chrono;
using namespace matplot;
long long MeasureSpan(long long x)
{
	auto start = high_resolution_clock::now();
	MemorySpan<long> span(new long(1));
	for (long i = 0; i < x; i++)
	{
		span.append(new long(i));
	}
	span.destroy();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return long long(duration.count());
}

long long MeasureUnq(long long x)
{
	auto start = high_resolution_clock::now();
	UnqPtr<long> ptr = (new long(1));
	for (long i = 0; i < x; i++)
	{
		delete new UnqPtr<long>(new long(i));
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return long long(duration.count());
}

long long MeasureShrd(long long x)
{
	auto start = high_resolution_clock::now();
	ShrdPtr<long> ptr = (new long(1));
	for (long i = 0; i < x; i++)
	{
		delete new ShrdPtr<long>(ptr);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return long long(duration.count());
}

long long MeasureMs(long long x)
{
	auto start = high_resolution_clock::now();
	MsPtr<long> ptr = (new long(1));
	for (int i = 0; i < x; i++)
	{
		delete new MsPtr<long>(new long(i));
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return long long(duration.count());
}

long long MeasurePtr(long long x)
{
	auto start = high_resolution_clock::now();
	long* ptr = new long(1);
	delete ptr;
	for (long i = 0; i < x; i++)
	{
		delete new long(i);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	return long long(duration.count());
}

void vizualize()
{
	std::vector<long long> x = { 1,10,100,1000,10000,100000,1000000,10000000 };
	std::vector<long long> span = {};
	std::vector<long long> Unq = {};
	std::vector<long long> Ms = {};
	std::vector<long long> Shrd = {};
	std::vector<long long> ptr = {};

	for (int i = 0; i < 8; i++)
	{
		span.push_back(MeasureSpan(x[i]));
		Unq.push_back(MeasureUnq(x[i]));
		Ms.push_back(MeasureMs(x[i]));
		Shrd.push_back(MeasureShrd(x[i]));
		ptr.push_back(MeasurePtr(x[i]));
	}
	loglog(x, span, "-o", x, Unq, "-o", x, Shrd, "-o", x, Ms, "-o", x, ptr, "-o");
	std::cout << "------------------------------------------------------------------------------\n";
	std::cout << "--- count ------ Mspan ------ UnqPt ------ MsPtr ------ ShrdP ------ RaPtr ---\n";
	std::cout << "------------------------------------------------------------------------------\n";
	for (int i = 0; i < 8; i++)
	{
		printf("---  10^%d ------%7d------%7d------%7d------%7d------%7d---\n",int(i), span[i], Unq[i], Ms[i], Shrd[i], ptr[i]);
		std::cout << "------------------------------------------------------------------------------\n";
	}	
	show();
} 