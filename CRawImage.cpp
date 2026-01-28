#include "CRawImage.h"

/*
*/
CRawImage::CRawImage()
{
	memset(this, 0x00, sizeof(CRawImage));
}

/*
*/
CRawImage::CRawImage(const char* name)
{
	memset(this, 0x00, sizeof(CRawImage));

	m_name = new CString(name);

	m_err = fopen_s(&m_file, m_name->m_text, "rb");

	if (m_err)
	{
		return;
	}

	m_bytesRead = fread_s(&m_width, sizeof(int32_t), sizeof(int32_t), 1, m_file);
	m_bytesRead = fread_s(&m_height, sizeof(int32_t), sizeof(int32_t), 1, m_file);

	m_imageSize = m_width * m_height * 4;

	m_pixels32 = new BYTE[m_imageSize]();

	m_bytesRead = fread_s(m_pixels32, m_imageSize, sizeof(BYTE), m_imageSize, m_file);

	fclose(m_file);

	m_isInitialized = true;
}

/*
*/
CRawImage::~CRawImage()
{
	SAFE_DELETE_ARRAY(m_pixels32);

	SAFE_DELETE(m_name);
}