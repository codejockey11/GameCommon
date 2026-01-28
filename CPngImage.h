#pragma once

#include "framework.h"

#include "CPngChunk.h"
#include "CPngHeader.h"

class CPngImage
{
public:

	enum
	{
		MAX_FILENAME = 256
	};

	bool m_isInitialized;

	BYTE m_filter;

	BYTE* m_out;
	BYTE* m_pixels32;
	BYTE* m_pOut;
	BYTE* m_pPixels;
	BYTE* m_prevRow;

	char m_name[CPngImage::MAX_FILENAME];

	CPngChunk m_pngChunk;
	CPngHeader m_header;

	errno_t m_err;

	FILE* m_file;

	int32_t m_predict;
	int32_t m_predicta;
	int32_t m_predictb;
	int32_t m_predictc;

	int32_t m_count;
	int32_t m_outSize;
	int32_t m_ret;

	z_stream m_zStream;

	CPngImage();
	CPngImage(const char* name);
	~CPngImage();

	void ApplyFiltering();
	uint8_t PaethPredict(uint8_t a, uint8_t b, uint8_t c);
};