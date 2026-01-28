#include "CPngHeader.h"

/*
*/
CPngHeader::CPngHeader()
{
	memset(this, 0x00, sizeof(CPngHeader));
}

/*
*/
CPngHeader::~CPngHeader()
{

}

/*
*/
void CPngHeader::Read(FILE* file)
{
	memset(this, 0x00, sizeof(CPngHeader));

	fread_s(&m_transmissionSupport, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(m_signature, sizeof(BYTE) * 3, sizeof(BYTE), 3, file);
	fread_s(m_dosLineEnding, sizeof(BYTE) * 2, sizeof(BYTE), 2, file);
	fread_s(&m_eof, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(&m_unixLineEnding, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(m_swizzle, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);

	m_length = SwizzleInt32(m_swizzle);

	fread_s(m_chunkName, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);

	fread_s(m_swizzle, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);

	m_width = SwizzleInt32(m_swizzle);

	fread_s(m_swizzle, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);

	m_height = SwizzleInt32(m_swizzle);

	fread_s(&m_bitsPerChannel, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(&m_colorType, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(&m_compressionMethod, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(&m_filterMethod, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(&m_interlaced, sizeof(BYTE), sizeof(BYTE), 1, file);
	fread_s(&m_CRC, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);

	switch (m_colorType)
	{
	// grayscale
	case 0x00:
	{
		m_bpp = 1;

		break;
	}
	// red, green and blue
	case 0x02:
	{
		m_bpp = 3;

		break;
	}
	// indexed
	case 0x03:
	{
		m_bpp = 1;

		break;
	}
	// grayscale and alpha
	case 0x04:
	{
		m_bpp = 2;

		break;
	}
	// red, green, blue and alpha
	case 0x06:
	{
		m_bpp = 4;

		break;
	}
	}

	m_imageStride = m_width * m_bpp;

	m_imageSize = m_imageStride * m_height;
}