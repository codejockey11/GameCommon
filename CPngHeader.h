#pragma once

#include "framework.h"

class CPngHeader
{
public:

	BYTE m_bitsPerChannel;
	BYTE m_chunkName[4];
	BYTE m_colorType;
	BYTE m_compressionMethod;
	BYTE m_CRC[4];
	BYTE m_dosLineEnding[2];
	BYTE m_eof;
	BYTE m_filterMethod;
	BYTE m_interlaced;
	BYTE m_signature[3];
	BYTE m_transmissionSupport;
	BYTE m_unixLineEnding;

	char m_swizzle[4];

	int32_t m_bpp;
	int32_t m_height;
	int32_t m_imageSize;
	int32_t m_imageStride;
	int32_t m_length;
	int32_t m_width;

	CPngHeader();
	~CPngHeader();

	void Read(FILE* file);
};