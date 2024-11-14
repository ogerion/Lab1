cmake_minimum_required (VERSION 3.14)



project ("First")

add_executable (First "First.cpp" "MemorySpan.h" "MsPtr.h" "Ptr.h" "ShrdPtr.h" "UnqPtr.h" "WeakPtr.h" "tests/MemorySpanTest.h" "tests/MsPtrTest.h" "tests/ShrdPtrTest.h" "tests/UnqPtrTest.h" "tests/WeakPtrTest.h" "tests/PerfomanceTest.h" "Sequence.h" "LinkedListSequence.h" "tests/LinkedListSequenceTest.h")
add_subdirectory(matplotplusplus)
target_link_libraries(First PUBLIC matplot)
