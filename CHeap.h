#pragma once

#include "framework.h"

#include "CVec3f.h"

class CHeap
{
public:

	int32_t m_length;
	int32_t m_size;

	unsigned char* m_heap;
	unsigned char* m_offset;

	CHeap();
	CHeap(int32_t size);
	~CHeap();

	bool Append(CVec3f* value);
	bool Append(float value);
	bool Append(int16_t value);
	bool Append(int32_t value);
	bool Append(void* byte, int32_t size);
	bool Append(XMFLOAT3 value);
	bool Append(XMFLOAT4 value);
	bool Append(XMFLOAT4X4 value);
	bool Append(XMMATRIX value);
	bool CheckBoundary(int32_t size);
	void Reset();
};