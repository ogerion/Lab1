
# First lab by Bredihin Vladimir B23-554
## Getting started

 1. Make sure you have have installed C++ complier and CMake(3.8 or higher)
 2. To visualize charts, the [matplot++](https://alandefreitas.github.io/matplotplusplus/) is used in this project
 ## Project sructure
 

```mermaid
classDiagram
	MemorySpan<|-- MsPtr
      UnqPtr<|-- Ptr
      ShrdPtr<|-- Ptr
      WeakPtr<|-- Ptr
      ShrdPtr <|-- WeakPtr
      WeakPtr <|-- ShrdPtr
      MsPtr <|-- UnqPtr
      MsPtr <|-- WeakPtr
      MsPtr <|-- ShrdPtr
      LinkedListSequence <|-- Sequence
      LinkedListSequence <|-- Node
      Node <|-- ShrdPtr
      Ptr : T * ptr
      Ptr: T * get()
      Ptr: *(ptr)()
      Ptr: (ptr->)()
      Ptr: bool (ptr)()
      Ptr: bool (!ptr)()
      class UnqPtr{
	      T * ptr
          T * release()
      }
      class ShrdPtr{
	      size_t * counterS
	      size_t * counterW
          T * ptr
          size_t countS()
          size_t countW()
          size_t * getSCounter()
          size_t * getWCounter()
          T * destroy()
          reset()
          release()
      }
      class WeakPtr{
          size_t * counterS
	      size_t * counterW
          T * ptr
          size_t countS()
          size_t countW()
          size_t * getSCounter()
          size_t * getWCounter()
          T * destroy()
          reset()
          release()
      }
      class MsPtr{
	      ShrdPtr<T> * ptr
	      MsPtr<T> * next
	      MsPtr<T> * prev
	      UnqPtr<T> get()
	      WeakPtr<T> copy()
	      MsPtr<T> * getPrev()
	      MsPtr<T> * getNext()
	      setNext(MsPtr<T> *)
	      setPrev(MsPtr<T> *)
		  
      }
      class MemorySpan{
	      MsPtr<T> * base
	      size_t size
	      size_t getLenght()
	      append(T *)
	      prepend(T *)
	      insertAt(T *,size_t)
	      UnqPtr<T> getFirst()
	      UnqPtr<T> getLast()
	      UnqPtr<T> getByIndex(size_t)
	      WeakPtr<T> copyFirst()
	      WeakPtr<T> copyLast()
	      WeakPtr<T> copyByIndex(size_t)
	      concat(MemorySpan<T>)
	      destroy()
      }
	class Sequence{
		size_t size
		size_t GetLenght()
		Append(T&)
		Prepend(T&)
		InsertAt(T&, size_t)
		GetFirst()
		GetLast()
		Get(size_T)
		Concat(Sequence &)
		GetSubSequence(size_t,size_t)
	}
	class Node{
		T & val;
		ShrdPtr<Node<T>> & next
		ShrdPtr<Node<T>> & prev
		T & getVal()
		setNext(ShrdPtr<Node<T>> &)
		setPrev(ShrdPtr<Node<T>> &)
		ShrdPtr<Node<T>> & getNext()
		ShrdPtr<Node<T>> & getPrev()
	}
	class LinkedListSequence{
		Shrdptr<Node<T>> base
		
	}
	class Sequence{
		size_t size
		Append(T&)
		Prepend(T&)
		InsertAt(T&, size_t)
		GetFirst()
		GetLast()
		Get(size_T)
		Concat(Sequence &)
		GetSubSequence(size_t,size_t)
	}
```
