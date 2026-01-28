#pragma once

#include "framework.h"

class CBmpImage
{
public:

	enum
	{
		PALETTE_ENTRY_SIZE = 256
	};
	
	BITMAPFILEHEADER m_bmapHeader;

	BITMAPINFO m_bmapInfo;

	bool m_isInitialized;

	BYTE* m_p32;
	BYTE* m_p8;
	BYTE* m_pixels32;
	BYTE* m_pixels8;

	errno_t m_err;

	FILE* m_file;

	int32_t m_bytesPerPixel;

	PALETTEENTRY m_paletteEntries[CBmpImage::PALETTE_ENTRY_SIZE];
	PALETTEENTRY m_paletteEntry;

	size_t m_size32;
	size_t m_size8;

	CBmpImage();
	CBmpImage(const char* filename);
	~CBmpImage();

	void WriteBitmapHeader(int32_t width, int32_t height, FILE* file);
	void WriteGreyscalePalette(FILE* file);
	void WriteColorPalette(FILE* file);
};