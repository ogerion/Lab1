#include "tests/UnqPtrTest.h"
#include "tests/ShrdPtrTest.h"
#include "tests/WeakPtrTest.h"
#include "tests/MsPtrTest.h"
#include "tests/MemorySpanTest.h"
#include <matplot/matplot.h>
#include "tests/PerfomanceTest.h"
#include "LinkedListSequence.h"
#include "tests/LinkedListSequenceTest.h"
using namespace std;
using namespace matplot;



int main()
{
	testUnqPtrBasic();
	testUnqPtrMove();
	testUnqPtrRelease();

	testShrdPtrBasic();
	testShrdPtrMove();
	testShrdPtrReset();
	testShrdPtrCounter();
	testShrdPtrTypeCast();
	testShrdPtrCompatibilityWeak();

	testWeakPtrBasic();
	testWeakPtrMove();
	testWeakPtrReset();
	testWeakPtrCounter();
	testWeakPtrTypeCast();

	testMsPtrBasic();
	testMsPtrCopy();
	testMsPtrGet();
	testMsPtrSet();

	testMemorySpanBasic();
	testMemorySpanConcat();
	testMemorySpanGet();
	testMemorySpanCopy();

	testLinkedListSequenceBasic();
	testLinkedListSequenceInsert();
	testLinkedListSequenceGet();
	testLinkedListSequenceGetSubSequence();
	testLinkedListSequenceConcat();

	//vizualize();
	return 0;
}
