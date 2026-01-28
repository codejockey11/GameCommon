#pragma once

#include "framework.h"

class CPngChunk
{
public:

	BYTE m_CRC[4];
	BYTE m_id[4];
	
	BYTE* m_data;

	char m_swizzle[4];

	DWORD m_chunkId;

	int32_t m_length;

	CPngChunk();

	void FreeResources();
	void Read(FILE* file);
};