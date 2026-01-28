#include "CPngImage.h"

/*
*/
CPngImage::CPngImage()
{
	memset(this, 0x00, sizeof(CPngImage));
}

/*
*/
CPngImage::CPngImage(const char* name)
{
	memset(this, 0x00, sizeof(CPngImage));

	strcpy_s(m_name, CPngImage::MAX_FILENAME, name);

	m_err = fopen_s(&m_file, m_name, "rb");

	if (m_err != 0)
	{
		return;
	}

	m_header.Read(m_file);

	m_zStream.zalloc = Z_NULL;
	m_zStream.zfree = Z_NULL;
	m_zStream.opaque = Z_NULL;
	m_zStream.avail_in = 0;
	m_zStream.next_in = Z_NULL;

	m_ret = inflateInit(&m_zStream);

	if (m_ret != Z_OK)
	{
		fclose(m_file);

		return;
	}

	m_pixels32 = new BYTE[m_header.m_imageSize]();

	if (m_pixels32 == 0)
	{
		fclose(m_file);

		return;
	}

	m_pPixels = m_pixels32;

	// + 1 for filter byte returned after inflate
	m_outSize = (m_header.m_imageStride + 1) * m_header.m_height;

	m_zStream.avail_out = m_outSize;

	m_out = new BYTE[m_outSize]();

	m_zStream.next_out = m_out;

	m_pOut = m_out;

	m_pngChunk.Read(m_file);

	while (m_pngChunk.m_chunkId != c_IEND)
	{
		switch (m_pngChunk.m_chunkId)
		{
		case c_IDAT:
		{
			m_zStream.avail_in = m_pngChunk.m_length;
			m_zStream.next_in = m_pngChunk.m_data;

			m_ret = inflate(&m_zStream, Z_NO_FLUSH);

			switch (m_ret)
			{
			case Z_OK:
			{
				break;
			}
			case Z_STREAM_END:
			{
				CPngImage::ApplyFiltering();

				break;
			}
			case Z_NEED_DICT:
			case Z_ERRNO:
			case Z_STREAM_ERROR:
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
			case Z_BUF_ERROR:
			case Z_VERSION_ERROR:
			{
				break;
			}
			}

			m_pngChunk.FreeResources();

			break;
		}
		default:
		{
			m_pngChunk.FreeResources();

			break;
		}
		}

		m_pngChunk.Read(m_file);
	}

	inflateEnd(&m_zStream);

	SAFE_DELETE_ARRAY(m_out);

	fclose(m_file);

	m_isInitialized = true;
}

/*
*/
CPngImage::~CPngImage()
{
	SAFE_DELETE_ARRAY(m_pixels32);
}

/*
*/
void CPngImage::ApplyFiltering()
{
	for (int32_t y = 0;y < m_header.m_height;y++)
	{
		m_filter = m_pOut[0];

		m_pOut += 1;

		m_prevRow = m_pPixels - m_header.m_imageStride;

		switch (m_filter)
		{
		// Filter type 0: None
		case 0x00:
		{
			memcpy(m_pPixels, m_pOut, (size_t)m_header.m_imageStride);

			break;
		}
		// Filter type 1: Sub
		case 0x01:
		{
			for (int32_t x = 0; x < 4; x++)
			{
				m_pPixels[x] = m_pOut[x];
			}

			for (int32_t x = m_header.m_bpp; x < m_header.m_imageStride; x++)
			{
				m_pPixels[x] = m_pOut[x] + m_pPixels[x - m_header.m_bpp];
			}

			break;
		}
		// Filter type 2: Up
		case 0x02:
		{
			for (int32_t x = 0; x < m_header.m_imageStride; x++)
			{
				m_pPixels[x] = m_pOut[x] + m_prevRow[x];
			}

			break;
		}
		// Filter type 3: Average
		case 0x03:
		{
			for (int32_t x = 0; x < 4; x++)
			{
				m_pPixels[x] = m_pOut[x] + (m_prevRow[x] >> 1);
			}

			for (int32_t x = m_header.m_bpp; x < m_header.m_imageStride; x++)
			{
				m_pPixels[x] = m_pOut[x] + ((m_pPixels[x - m_header.m_bpp] + m_prevRow[x]) >> 1);
			}

			break;
		}
		case 0x04:
		{
			for (int32_t x = 0; x < 4; x++)
			{
				m_pPixels[x] = m_pOut[x] + CPngImage::PaethPredict(0, m_prevRow[x], 0);
			}

			for (int32_t x = m_header.m_bpp; x < m_header.m_imageStride; x++)
			{
				m_pPixels[x] = m_pOut[x] + CPngImage::PaethPredict(m_pPixels[x - m_header.m_bpp], m_prevRow[x], m_prevRow[x - m_header.m_bpp]);
			}

			break;
		}
		}

		m_pPixels += m_header.m_imageStride;
		m_pOut += m_header.m_imageStride;
	}
}

/*
*/
uint8_t CPngImage::PaethPredict(uint8_t a, uint8_t b, uint8_t c)
{
	m_predict = a + b - c;

	m_predicta = abs(m_predict - a);
	m_predictb = abs(m_predict - b);
	m_predictc = abs(m_predict - c);

	if (m_predicta <= m_predictb && m_predicta <= m_predictc)
	{
		return a;
	}
	
	if (m_predictb <= m_predictc)
	{
		return b;
	}

	return c;
}

/*
 
This person seems to be the only one on the internet that has a valid solution for PNG inflate and applying the filters
https://handmade.network/forums/articles/t/2822-tutorial_implementing_a_basic_png_reader_the_handmade_way

void CPngImage::sh_png_defilter()
{
	int32_t x = m_header.m_width;// sh_get_uint32be(ihdr->data);
	int32_t y = m_header.m_height;// sh_get_uint32be(ihdr->data + 4);
	uint8_t bit_depth = m_header.m_bitsPerChannel;// *(ihdr->data + 4 + 4);//count the bytes out
	uint8_t byte_per_pixel = 4;// 1;//this is usually determined by checking color type, the picture I'm using is only greyscale, its only one byte per pixel

	uint8_t* row = m_out;// decompressed_image;
	int32_t stride = x * byte_per_pixel;

	uint8_t* image = m_pixels;// (uint8_t*)malloc((size_t)x * y * byte_per_pixel); //this is even smaller than the filter but just being safe
	uint8_t* working = image;

	for(int32_t i = 0; i < y; ++i) {
		working = image + i*stride;
		uint8_t filter = *row++;

		switch(filter) {
			//case sh_no_filter: {
		case 0: {
				for(int32_t j = 0; j < x * 4; ++j) {
					working[j] = row[j];
				}
			} break;

			//case sh_sub_filter: {
		case 1: {
				for(int32_t j = 0; j < x * 4; ++j) {
					uint8_t a = 0;
					if (j < 4) {
						a = 0;// working[j];
					}
					else {
						a = working[j-4];
					}
					uint8_t value = row[j] + a;
					working[j] = value;
				}
			} break;

			//case sh_up_filter: {
		case 2: {
				uint8_t*prev_row = working - stride;
				for(int32_t j = 0; j < x * 4; ++j) {
					uint8_t b = prev_row[j];
					uint8_t value = row[j] + b;
					working[j] = value;
				}
		   } break;

			//case sh_avg_filter: {
			case 3: {
				uint8_t*prev_row = working - stride;
				for(int32_t j = 0; j < x * 4; ++j) {
					uint8_t a = 0;
					uint8_t b = prev_row[j];
					if (j < 4) {
						a = 0;// working[j];
					}
					else {
						a = working[j - 4];
					}

					uint8_t value = row[j] + ( (a + b) >> 1 );
					working[j] = value;
				}
			} break;

			//case sh_paeth_filter: {
			case 4: {
				uint8_t*prev_row = working - stride;
				for(int32_t j = 0; j < x * 4; ++j) {
					uint8_t a = 0;
					uint8_t b = prev_row[j];
					uint8_t c = 0;
					if (j < 4) {
						a = 0;// working[j];
						c = 0;// prev_row[j];
					}
					else {
						a = working[j - 4];
						c = prev_row[j - 4];
					}

					uint8_t value = row[j] + sh_png_paeth_predict((int32_t) a, (int32_t) b, (int32_t) c);
					working[j] = value;
				}
			} break;

		}

		row += stride;
	}
}
*/