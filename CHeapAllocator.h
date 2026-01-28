#pragma once

#include "framework.h"

class CHeapAllocator
{
public:

	int32_t m_count;
	int32_t m_entrySize;

	CHeapAllocator();
	~CHeapAllocator();
};