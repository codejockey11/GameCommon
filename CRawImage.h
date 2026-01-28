#pragma once

#include "framework.h"

#include "CString.h"

class CRawImage
{
public:

	bool m_isInitialized;

	BYTE* m_pixels32;

	CString* m_name;

	errno_t m_err;

	FILE* m_file;

	size_t m_bytesRead;

	int32_t m_height;
	int32_t m_imageSize;
	int32_t m_width;

	CRawImage();
	CRawImage(const char* name);
	~CRawImage();
};