#include "CBmpImage.h"

/*
*/
CBmpImage::CBmpImage()
{
	memset(this, 0x00, sizeof(CBmpImage));
}

/*
*/
CBmpImage::CBmpImage(const char* filename)
{
	memset(this, 0x00, sizeof(CBmpImage));

	m_err = fopen_s(&m_file, filename, "rb");

	if (m_err != 0)
	{
		return;
	}

	fread_s(&m_bmapHeader.bfType, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_bmapHeader.bfSize, sizeof(DWORD), sizeof(DWORD), 1, m_file);
	fread_s(&m_bmapHeader.bfReserved1, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_bmapHeader.bfReserved2, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_bmapHeader.bfOffBits, sizeof(DWORD), sizeof(DWORD), 1, m_file);

	fread_s(&m_bmapInfo.bmiHeader.biSize, sizeof(DWORD), sizeof(DWORD), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biWidth, sizeof(LONG), sizeof(LONG), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biHeight, sizeof(LONG), sizeof(LONG), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biPlanes, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biBitCount, sizeof(WORD), sizeof(WORD), 1, m_file);

	m_bytesPerPixel = m_bmapInfo.bmiHeader.biBitCount / 8;

	fread_s(&m_bmapInfo.bmiHeader.biCompression, sizeof(DWORD), sizeof(DWORD), 1, m_file);

	if (m_bmapInfo.bmiHeader.biCompression != BI_RGB)
	{
		fclose(m_file);

		return;
	}

	fread_s(&m_bmapInfo.bmiHeader.biSizeImage, sizeof(DWORD), sizeof(DWORD), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biXPelsPerMeter, sizeof(LONG), sizeof(LONG), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biYPelsPerMeter, sizeof(LONG), sizeof(LONG), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biClrUsed, sizeof(DWORD), sizeof(DWORD), 1, m_file);
	fread_s(&m_bmapInfo.bmiHeader.biClrImportant, sizeof(DWORD), sizeof(DWORD), 1, m_file);

	if (m_bmapInfo.bmiHeader.biBitCount == 8)
	{
		fread_s(&m_paletteEntries, sizeof(PALETTEENTRY) * CBmpImage::PALETTE_ENTRY_SIZE, sizeof(PALETTEENTRY), CBmpImage::PALETTE_ENTRY_SIZE, m_file);
	}

	m_size8 = (size_t)m_bmapInfo.bmiHeader.biWidth * m_bmapInfo.bmiHeader.biHeight * m_bytesPerPixel;

	m_pixels8 = new BYTE[m_size8]();

	m_pixels8 += (m_size8 - ((size_t)m_bmapInfo.bmiHeader.biWidth * m_bytesPerPixel));

	fseek(m_file, 0, SEEK_SET);
	fseek(m_file, m_bmapHeader.bfOffBits, SEEK_SET);

	fread_s(m_pixels8, m_size8, ((size_t)m_bmapInfo.bmiHeader.biWidth * m_bytesPerPixel), 1, m_file);

	while (!feof(m_file))
	{
		m_pixels8 -= ((size_t)m_bmapInfo.bmiHeader.biWidth * m_bytesPerPixel);

		fread_s(m_pixels8, m_size8, ((size_t)m_bmapInfo.bmiHeader.biWidth * m_bytesPerPixel), 1, m_file);
	}

	m_pixels8 += ((size_t)m_bmapInfo.bmiHeader.biWidth * m_bytesPerPixel);

	fclose(m_file);

	m_size32 = (size_t)m_bmapInfo.bmiHeader.biWidth * m_bmapInfo.bmiHeader.biHeight * 4;

	m_pixels32 = new BYTE[m_size32]();

	m_p8 = m_pixels8;
	m_p32 = m_pixels32;

	for (int32_t i = 0; i < m_bmapInfo.bmiHeader.biWidth * m_bmapInfo.bmiHeader.biHeight; i++)
	{
		*m_p32 = m_paletteEntries[*m_p8].peRed;
		m_p32++;

		*m_p32 = m_paletteEntries[*m_p8].peGreen;
		m_p32++;

		*m_p32 = m_paletteEntries[*m_p8].peBlue;
		m_p32++;

		*m_p32 = 255;
		m_p32++;

		m_p8++;
	}

	m_isInitialized = true;
}

/*
*/
CBmpImage::~CBmpImage()
{
	SAFE_DELETE_ARRAY(m_pixels8);
	SAFE_DELETE_ARRAY(m_pixels32);
}

/*
*/
void CBmpImage::WriteBitmapHeader(int32_t width, int32_t height, FILE* file)
{
	memset(&m_bmapHeader, 0x00, sizeof(BITMAPFILEHEADER));
	memset(&m_bmapInfo, 0x00, sizeof(BITMAPINFO));

	m_bmapHeader.bfType = 19778;
	fwrite(&m_bmapHeader.bfType, sizeof(WORD), 1, file);

	m_bmapHeader.bfSize = 0;
	fwrite(&m_bmapHeader.bfSize, sizeof(DWORD), 1, file);

	m_bmapHeader.bfReserved1 = 0;
	fwrite(&m_bmapHeader.bfReserved1, sizeof(WORD), 1, file);

	m_bmapHeader.bfReserved2 = 0;
	fwrite(&m_bmapHeader.bfReserved2, sizeof(WORD), 1, file);

	m_bmapHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (256 * sizeof(PALETTEENTRY));
	fwrite(&m_bmapHeader.bfOffBits, sizeof(DWORD), 1, file);

	m_bmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	fwrite(&m_bmapInfo.bmiHeader.biSize, sizeof(DWORD), 1, file);

	m_bmapInfo.bmiHeader.biWidth = width;
	fwrite(&m_bmapInfo.bmiHeader.biWidth, sizeof(LONG), 1, file);

	m_bmapInfo.bmiHeader.biHeight = height;
	fwrite(&m_bmapInfo.bmiHeader.biHeight, sizeof(LONG), 1, file);

	m_bmapInfo.bmiHeader.biPlanes = 1;
	fwrite(&m_bmapInfo.bmiHeader.biPlanes, sizeof(WORD), 1, file);

	m_bmapInfo.bmiHeader.biBitCount = 8;
	fwrite(&m_bmapInfo.bmiHeader.biBitCount, sizeof(WORD), 1, file);

	m_bmapInfo.bmiHeader.biCompression = BI_RGB;
	fwrite(&m_bmapInfo.bmiHeader.biCompression, sizeof(DWORD), 1, file);

	m_bmapInfo.bmiHeader.biSizeImage = m_bmapInfo.bmiHeader.biWidth * m_bmapInfo.bmiHeader.biHeight;
	fwrite(&m_bmapInfo.bmiHeader.biSizeImage, sizeof(DWORD), 1, file);

	m_bmapInfo.bmiHeader.biXPelsPerMeter = 0;
	fwrite(&m_bmapInfo.bmiHeader.biXPelsPerMeter, sizeof(LONG), 1, file);

	m_bmapInfo.bmiHeader.biYPelsPerMeter = 0;
	fwrite(&m_bmapInfo.bmiHeader.biYPelsPerMeter, sizeof(LONG), 1, file);

	m_bmapInfo.bmiHeader.biClrUsed = 0;
	fwrite(&m_bmapInfo.bmiHeader.biClrUsed, sizeof(DWORD), 1, file);

	m_bmapInfo.bmiHeader.biClrImportant = 0;
	fwrite(&m_bmapInfo.bmiHeader.biClrImportant, sizeof(DWORD), 1, file);
}

/*
*/
void CBmpImage::WriteGreyscalePalette(FILE* file)
{
	for (int32_t i = 0; i < 256; i++)
	{
		m_paletteEntry.peRed = (BYTE)i;
		m_paletteEntry.peGreen = (BYTE)i;
		m_paletteEntry.peBlue = (BYTE)i;
		m_paletteEntry.peFlags = 0;

		fwrite(&m_paletteEntry, sizeof(PALETTEENTRY), 1, file);
	}
}

/*
*/
void CBmpImage::WriteColorPalette(FILE* file)
{
	for (int32_t i = 0; i < 256; i++)
	{
		switch (i)
		{
		case 0:
		{
			m_paletteEntry.peRed = 0;
			m_paletteEntry.peGreen = 0;
			m_paletteEntry.peBlue = 0;

			break;
		}
		case 1:
		{
			m_paletteEntry.peRed = 255;
			m_paletteEntry.peGreen = 0;
			m_paletteEntry.peBlue = 0;

			break;
		}
		case 2:
		{
			m_paletteEntry.peRed = 0;
			m_paletteEntry.peGreen = 255;
			m_paletteEntry.peBlue = 0;

			break;
		}
		case 3:
		{
			m_paletteEntry.peRed = 0;
			m_paletteEntry.peGreen = 0;
			m_paletteEntry.peBlue = 255;

			break;
		}
		case 4:
		{
			m_paletteEntry.peRed = 255;
			m_paletteEntry.peGreen = 255;
			m_paletteEntry.peBlue = 255;

			break;
		}
		default:
		{
			m_paletteEntry.peRed = rand() % 256;
			m_paletteEntry.peGreen = rand() % 256;
			m_paletteEntry.peBlue = rand() % 256;

			break;
		}
		}

		m_paletteEntry.peFlags = 0;

		fwrite(&m_paletteEntry, sizeof(PALETTEENTRY), 1, file);
	}
}