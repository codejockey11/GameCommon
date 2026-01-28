#pragma once

#include "framework.h"

#include "CHeapAllocator.h"

class CHeapArray
{
public:

	BYTE* m_heap;
	BYTE* m_heapIterator;

	CHeapAllocator* m_allocator;

	int32_t m_size;
	int32_t m_totalSize;

	CHeapArray();
	CHeapArray(bool allocateHeap, int32_t size, int32_t count, ...);
	~CHeapArray();

	BYTE* GetElement(int32_t count, ...);
	int32_t GetOffset(int32_t count, ...);
};