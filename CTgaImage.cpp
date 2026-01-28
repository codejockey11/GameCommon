#include "CTgaImage.h"

/*
*/
CTgaImage::CTgaImage()
{
	memset(this, 0x00, sizeof(CTgaImage));
}

/*
*/
CTgaImage::CTgaImage(const char* filename)
{
	memset(this, 0x00, sizeof(CTgaImage));

	m_err = fopen_s(&m_file, filename, "rb");

	if (m_err != 0)
	{
		return;
	}

	m_header = new CTgaHeader();

	m_footer = new CTgaFooter();

	m_extension = new CTgaExtension();

	CTgaImage::Load();

	m_isInitialized = true;

	fclose(m_file);
}

/*
*/
CTgaImage::~CTgaImage()
{
	SAFE_DELETE(m_header);
	SAFE_DELETE(m_footer);
	SAFE_DELETE(m_extension);

	if (m_pixels8)
	{
		free(m_pixels8);
	}

	if (m_pixels24)
	{
		free(m_pixels24);
	}

	if (m_pixels32)
	{
		free(m_pixels32);
	}

	SAFE_DELETE_ARRAY(m_filename);
}

/*
*/
void CTgaImage::DumpColorMap()
{
	FILE* file;

	m_err = fopen_s(&file, "colorMap.txt", "wb");

	if (m_err != 0)
	{
		return;
	}

	int32_t i = sizeof(BGR);

	fwrite(m_colorTable, i, m_header->m_cMapLength, file);

	fclose(file);
}

/*
*/
void CTgaImage::DumpFooter()
{
	FILE* file;

	m_err = fopen_s(&file, "footer.txt", "w");

	if (m_err != 0)
	{
		return;
	}

	fwrite(m_footer->m_signature, sizeof(char), strlen(m_footer->m_signature), file);

	fclose(file);
}

/*
*/
void CTgaImage::DumpHeader()
{
	FILE* file;

	m_err = fopen_s(&file, "header.txt", "w");

	if (m_err != 0)
	{
		return;
	}

	memset((void*)m_text, 0x00, CTgaImage::E_MAX_TEXT);
	sprintf_s(m_text, CTgaImage::E_MAX_TEXT, "%05d", m_header->m_width);

	fwrite(m_text, sizeof(char), strlen(m_text), file);

	memset((void*)m_text, 0x00, CTgaImage::E_MAX_TEXT);
	sprintf_s(m_text, CTgaImage::E_MAX_TEXT, "%05d", m_header->m_height);

	fwrite(m_text, sizeof(char), strlen(m_text), file);

	fclose(file);
}

/*
*/
void CTgaImage::DumpRawPixels8()
{
	FILE* file;

	m_err = fopen_s(&file, "pixels8.txt", "wb");

	if (m_err != 0)
	{
		return;
	}

	if (m_pixels8)
	{
		fwrite(m_pixels8, sizeof(BYTE), m_size8, file);
	}

	fclose(file);
}

/*
*/
void CTgaImage::DumpRawPixels24()
{
	FILE* file;

	m_err = fopen_s(&file, "pixels24.txt", "wb");

	if (m_err != 0)
	{
		return;
	}

	if (m_pixels24)
	{
		fwrite(m_pixels24, sizeof(RGB), m_size24, file);
	}

	fclose(file);
}

/*
*/
void CTgaImage::DumpRawPixels32()
{
	FILE* file;

	m_err = fopen_s(&file, "pixels32.txt", "wb");

	if (m_err != 0)
	{
		return;
	}

	if (m_pixels32)
	{
		fwrite(m_pixels32, sizeof(RGBA), m_size32, file);
	}

	fclose(file);
}

/*
*/
void CTgaImage::Flip()
{
	size_t pitch = (size_t)m_header->m_width * 4;
	size_t height = (size_t)m_header->m_height;

	BYTE* flip = (BYTE*)malloc(height * pitch);

	if (flip == nullptr)
	{
		return;
	}


	BYTE* fliph = flip;

	BYTE* start = m_pixels32 + (height * pitch) - pitch;

	for (int32_t i = 0; i < height; i++)
	{
		memcpy((void*)fliph, (void*)start, pitch);

		start -= pitch;
		fliph += pitch;
	}

	memcpy((void*)m_pixels32, (void*)flip, height * pitch);

	free(flip);
}

/*
*/
bool CTgaImage::Load()
{
	CTgaImage::LoadHeader();

	CTgaImage::LoadImageDescription();

	CTgaImage::LoadColorTable();

	CTgaImage::LoadPixelData();

	CTgaImage::LoadExtensions();

	if (m_header->m_imageDescriptor & 8)
	{
		CTgaImage::Flip();
	}

	return true;
}

/*
*/
void CTgaImage::Load(const char* filename)
{
	memset(this, 0x00, sizeof(CTgaImage));

	m_err = fopen_s(&m_file, filename, "rb");

	if (m_err != 0)
	{
		return;
	}

	m_header = new CTgaHeader();

	m_footer = new CTgaFooter();

	m_extension = new CTgaExtension();

	CTgaImage::Load();

	m_isInitialized = true;

	fclose(m_file);
}

/*
*/
void CTgaImage::LoadColorTable()
{
	if (m_header->m_cMapLength > 0)
	{
		fread_s(&m_colorTable, sizeof(BGR) * CTgaImage::E_COLORTABLE_SIZE, sizeof(BGR), m_header->m_cMapLength, m_file);
	}
}

/*
*/
void CTgaImage::LoadHeader()
{
	fread_s(&m_header->m_idLength, sizeof(BYTE), sizeof(BYTE), 1, m_file);
	fread_s(&m_header->m_colorMapType, sizeof(BYTE), sizeof(BYTE), 1, m_file);
	fread_s(&m_header->m_imageType, sizeof(BYTE), sizeof(BYTE), 1, m_file);
	fread_s(&m_header->m_cMapStart, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_header->m_cMapLength, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_header->m_cMapDepth, sizeof(BYTE), sizeof(BYTE), 1, m_file);
	fread_s(&m_header->m_xOffset, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_header->m_yOffset, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_header->m_width, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_header->m_height, sizeof(WORD), sizeof(WORD), 1, m_file);
	fread_s(&m_header->m_pixelDepth, sizeof(BYTE), sizeof(BYTE), 1, m_file);
	fread_s(&m_header->m_imageDescriptor, sizeof(BYTE), sizeof(BYTE), 1, m_file);

	m_size8  = (int32_t)m_header->m_width * m_header->m_height;
	m_size24 = (int32_t)m_header->m_width * m_header->m_height * (WORD)sizeof(RGB);
	m_size32 = (int32_t)m_header->m_width * m_header->m_height * (WORD)sizeof(RGBA);
}

/*
*/
void CTgaImage::LoadImageDescription()
{
	if (m_header->m_idLength > 0)
	{
		fread_s(&m_imageDescription, sizeof(BYTE) * CTgaImage::E_IMAGEDESCRIPTION_SIZE, sizeof(BYTE), m_header->m_idLength, m_file);
	}
}

/*
*/
void CTgaImage::LoadPixelData()
{
	switch (m_header->m_imageType)
	{
	// Colormapped image data
	case 1:
	{
		if (m_header->m_pixelDepth == 8)
		{
			CTgaImage::Load8BitUncompressed();
		}

		break;
	}

	// Truecolor image data
	case 2:
	{
		if (m_header->m_pixelDepth == 24)
		{
			CTgaImage::Load24BitUncompressed();
		}

		if (m_header->m_pixelDepth == 32)
		{
			CTgaImage::Load32BitUncompressed();
		}

		break;
	}

	// Colormap with RLE Compression
	case 9:
	{
		if (m_header->m_pixelDepth == 8)
		{
			CTgaImage::Load8BitCompressed();
		}

		if (m_header->m_pixelDepth == 24)
		{
			CTgaImage::Load24BitCompressed();
		}

		if (m_header->m_pixelDepth == 32)
		{
			CTgaImage::Load32BitCompressed();
		}

		break;
	}

	// BGR with RLE Compression
	case 10:
	{
		if (m_header->m_pixelDepth == 8)
		{
			CTgaImage::Load8BitCompressed();
		}

		if (m_header->m_pixelDepth == 24)
		{
			CTgaImage::Load24BitCompressed();
		}

		if (m_header->m_pixelDepth == 32)
		{
			CTgaImage::Load32BitCompressed();
		}

		break;
	}

	default:
	{
		break;
	}
	}
}

/*
*/
void CTgaImage::Load8BitCompressed()
{
	m_pixels8 = (BYTE*)malloc(m_size8);

	if (m_pixels8 == nullptr)
	{
		return;
	}

	m_pixels24 = (BYTE*)malloc(m_size24);

	if (m_pixels24 == nullptr)
	{
		return;
	}

	m_pixels32 = (BYTE*)malloc(m_size32);

	if (m_pixels32 == nullptr)
	{
		return;
	}

	BYTE* pIterator8 = m_pixels8;
	BYTE* pIterator24 = m_pixels24;
	BYTE* pIterator32 = m_pixels32;

	int32_t pcount = 0;

	RLEPacket8* p8 = new RLEPacket8();

	while (m_size32 > pcount)
	{
		p8->ReadCount(m_file);

		int32_t count = (int32_t)p8->GetCount();

		// encoded or raw
		if (p8->IsEncoded())
		{
			p8->ReadValue(m_file);

			BGR bgr = m_colorTable[p8->m_value];

			for (int32_t c = 0; c < count; c++)
			{
				*pIterator8 = p8->m_value;
				pIterator8 += 1;


				*pIterator24 = bgr.m_R;
				pIterator24 += 1;

				*pIterator24 = bgr.m_G;
				pIterator24 += 1;

				*pIterator24 = bgr.m_B;
				pIterator24 += 1;


				*pIterator32 = bgr.m_R;
				pIterator32 += 1;

				*pIterator32 = bgr.m_G;
				pIterator32 += 1;

				*pIterator32 = bgr.m_B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
		else
		{
			for (int32_t c = 0; c < count; c++)
			{
				fread_s(&p8->m_value, sizeof(BYTE), sizeof(BYTE), 1, m_file);

				BGR bgr = m_colorTable[p8->m_value];

				*pIterator8 = p8->m_value;
				pIterator8 += 1;


				*pIterator24 = bgr.m_R;
				pIterator24 += 1;

				*pIterator24 = bgr.m_G;
				pIterator24 += 1;

				*pIterator24 = bgr.m_B;
				pIterator24 += 1;


				*pIterator32 = bgr.m_R;
				pIterator32 += 1;

				*pIterator32 = bgr.m_G;
				pIterator32 += 1;

				*pIterator32 = bgr.m_B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
	}

	SAFE_DELETE(p8);
}

/*
*/
void CTgaImage::Load8BitUncompressed()
{
	m_pixels8 = (BYTE*)malloc(m_size8);

	if (m_pixels8 == nullptr)
	{
		return;
	}

	m_pixels24 = (BYTE*)malloc(m_size24);

	if (m_pixels24 == nullptr)
	{
		return;
	}

	m_pixels32 = (BYTE*)malloc(m_size32);

	if (m_pixels32 == nullptr)
	{
		return;
	}

	BYTE* pIterator8  = m_pixels8;
	BYTE* pIterator24 = m_pixels24;
	BYTE* pIterator32 = m_pixels32;

	BYTE value;

	int32_t pcount = 0;

	while (m_size32 > pcount)
	{
		fread_s(&value, sizeof(BYTE), sizeof(BYTE), 1, m_file);

		BGR bgr = m_colorTable[value];

		*pIterator8 = value;
		pIterator8 += 1;


		*pIterator24 = bgr.m_R;
		pIterator24 += 1;

		*pIterator24 = bgr.m_G;
		pIterator24 += 1;

		*pIterator24 = bgr.m_B;
		pIterator24 += 1;


		*pIterator32 = bgr.m_R;
		pIterator32 += 1;

		*pIterator32 = bgr.m_G;
		pIterator32 += 1;

		*pIterator32 = bgr.m_B;
		pIterator32 += 1;

		*pIterator32 = 255;
		pIterator32 += 1;

		pcount += 4;
	}
}

/*
*/
void CTgaImage::Load24BitCompressed()
{
	m_pixels24 = (BYTE*)malloc(m_size24);

	if (m_pixels24 == nullptr)
	{
		return;
	}

	m_pixels32 = (BYTE*)malloc(m_size32);

	if (m_pixels32 == nullptr)
	{
		return;
	}

	BYTE* pIterator24 = m_pixels24;
	BYTE* pIterator32 = m_pixels32;

	int32_t pcount = 0;

	RLEPacket24* p24 = new RLEPacket24();

	while (m_size32 > pcount)
	{
		p24->ReadCount(m_file);

		int32_t count = (int32_t)p24->GetCount();

		// encoded or raw
		if (p24->IsEncoded())
		{
			p24->ReadValue(m_file);

			for (int32_t c = 0; c < count; c++)
			{
				*pIterator24 = p24->m_value.m_R;
				pIterator24 += 1;

				*pIterator24 = p24->m_value.m_G;
				pIterator24 += 1;

				*pIterator24 = p24->m_value.m_B;
				pIterator24 += 1;


				*pIterator32 = p24->m_value.m_R;
				pIterator32 += 1;

				*pIterator32 = p24->m_value.m_G;
				pIterator32 += 1;

				*pIterator32 = p24->m_value.m_B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
		else
		{
			for (int32_t c = 0; c < count; c++)
			{
				p24->ReadValue(m_file);

				*pIterator24 = p24->m_value.m_R;
				pIterator24 += 1;

				*pIterator24 = p24->m_value.m_G;
				pIterator24 += 1;

				*pIterator24 = p24->m_value.m_B;
				pIterator24 += 1;


				*pIterator32 = p24->m_value.m_R;
				pIterator32 += 1;

				*pIterator32 = p24->m_value.m_G;
				pIterator32 += 1;

				*pIterator32 = p24->m_value.m_B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
	}

	SAFE_DELETE(p24);
}

/*
*/
void CTgaImage::Load24BitUncompressed()
{
	m_pixels24 = (BYTE*)malloc(m_size24);

	if (m_pixels24 == nullptr)
	{
		return;
	}

	m_pixels32 = (BYTE*)malloc(m_size32);

	if (m_pixels32 == nullptr)
	{
		return;
	}

	BYTE* pIterator24 = m_pixels24;
	BYTE* pIterator32 = m_pixels32;

	BGR bgr;

	int32_t pcount = 0;

	while (m_size32 > pcount)
	{
		fread_s(&bgr, sizeof(BGR), sizeof(BGR), 1, m_file);

		*pIterator24 = bgr.m_R;
		pIterator24 += 1;

		*pIterator24 = bgr.m_G;
		pIterator24 += 1;

		*pIterator24 = bgr.m_B;
		pIterator24 += 1;


		*pIterator32 = bgr.m_R;
		pIterator32 += 1;

		*pIterator32 = bgr.m_G;
		pIterator32 += 1;

		*pIterator32 = bgr.m_B;
		pIterator32 += 1;

		*pIterator32 = 255;
		pIterator32 += 1;

		pcount += 4;
	}
}

/*
*/
void CTgaImage::Load32BitCompressed()
{
	m_pixels24 = (BYTE*)malloc(m_size24);

	if (m_pixels24 == nullptr)
	{
		return;
	}

	m_pixels32 = (BYTE*)malloc(m_size32);

	if (m_pixels32 == nullptr)
	{
		return;
	}

	BYTE* pIterator24 = m_pixels24;

	BYTE* pIterator32 = m_pixels32;

	int32_t pcount = 0;

	RLEPacket32* p32 = new RLEPacket32();

	while (m_size32 > pcount)
	{
		p32->ReadCount(m_file);

		int32_t count = (int32_t)p32->GetCount();

		// encoded or raw
		if (p32->IsEncoded())
		{
			p32->ReadValue(m_file);

			for (int32_t c = 0; c < count; c++)
			{
				*pIterator24 = p32->m_value.m_R;
				pIterator24 += 1;

				*pIterator24 = p32->m_value.m_G;
				pIterator24 += 1;

				*pIterator24 = p32->m_value.m_B;
				pIterator24 += 1;


				*pIterator32 = p32->m_value.m_R;
				pIterator32 += 1;

				*pIterator32 = p32->m_value.m_G;
				pIterator32 += 1;

				*pIterator32 = p32->m_value.m_B;
				pIterator32 += 1;

				*pIterator32 = p32->m_value.m_A;
				pIterator32 += 1;

				pcount += 4;
			}
		}
		else
		{
			for (int32_t c = 0; c < count; c++)
			{
				p32->ReadValue(m_file);

				*pIterator24 = p32->m_value.m_R;
				pIterator24 += 1;

				*pIterator24 = p32->m_value.m_G;
				pIterator24 += 1;

				*pIterator24 = p32->m_value.m_B;
				pIterator24 += 1;


				*pIterator32 = p32->m_value.m_R;
				pIterator32 += 1;

				*pIterator32 = p32->m_value.m_G;
				pIterator32 += 1;

				*pIterator32 = p32->m_value.m_B;
				pIterator32 += 1;

				*pIterator32 = p32->m_value.m_A;
				pIterator32 += 1;

				pcount += 4;
			}
		}
	}

	SAFE_DELETE(p32);
}

/*
*/
void CTgaImage::Load32BitUncompressed()
{
	m_pixels24 = (BYTE*)malloc(m_size24);

	if (m_pixels24 == nullptr)
	{
		return;
	}

	m_pixels32 = (BYTE*)malloc(m_size32);

	if (m_pixels32 == nullptr)
	{
		return;
	}

	BYTE* pIterator24 = m_pixels24;
	BYTE* pIterator32 = m_pixels32;

	BGRA bgra;

	int32_t pcount = 0;

	while (m_size32 > pcount)
	{
		fread_s(&bgra, sizeof(BGRA), sizeof(BGRA), 1, m_file);

		*pIterator24 = bgra.m_R;
		pIterator24 += 1;

		*pIterator24 = bgra.m_G;
		pIterator24 += 1;

		*pIterator24 = bgra.m_B;
		pIterator24 += 1;


		*pIterator32 = bgra.m_R;
		pIterator32 += 1;

		*pIterator32 = bgra.m_G;
		pIterator32 += 1;

		*pIterator32 = bgra.m_B;
		pIterator32 += 1;

		*pIterator32 = bgra.m_A;
		pIterator32 += 1;

		pcount += 4;
	}
}

/*
*/
void CTgaImage::LoadExtensions()
{
	if (!feof(m_file))
	{
		m_footer->ReadValues(m_file);
	}

	if (m_footer->m_extensionOffset > 0)
	{
	}

	if (m_footer->m_developerOffset > 0)
	{
	}
}

/*
*/
void CTgaImage::OnlyHeader(const char* filename)
{
	memset(this, 0x00, sizeof(CTgaImage));

	m_filename = new char[strlen(filename) + 1]();

	strcpy_s(m_filename, strlen(filename) + 1, filename);

	m_err = fopen_s(&m_file, filename, "rb");

	if (m_err != 0)
	{
		return;
	}

	m_header = new CTgaHeader();

	CTgaImage::LoadHeader();

	m_isInitialized = true;

	fclose(m_file);
}