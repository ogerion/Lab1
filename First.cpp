#include "tests/UnqPtrTest.h"
#include "tests/ShrdPtrTest.h"
#include "tests/WeakPtrTest.h"
#include "tests/MsPtrTest.h"
#include "tests/MemorySpanTest.h"
#include <matplot/matplot.h>
#include "tests/PerfomanceTest.h"

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
	testShrdPtrDestroy();
	testShrdPtrTypeCast();
	testShrdPtrCompatibilityWeak();

	testWeakPtrBasic();
	testWeakPtrMove();
	testWeakPtrReset();
	testWeakPtrCounter();
	testWeakPtrDestroy();
	testWeakPtrTypeCast();

	testMsPtrBasic();
	testMsPtrCopy();
	testMsPtrGet();
	testMsPtrSet();

	testMemorySpanBasic();
	testMemorySpanConcat();
	testMemorySpanGet();
	testMemorySpanCopy();

	vizualize();
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}
