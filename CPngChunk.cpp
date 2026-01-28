#include "CPngChunk.h"

/*
*/
CPngChunk::CPngChunk()
{
	memset(this, 0x00, sizeof(CPngChunk));
}

/*
*/
void CPngChunk::FreeResources()
{
	SAFE_DELETE_ARRAY(m_data);
}

/*
*/
void CPngChunk::Read(FILE* file)
{
	fread_s(m_swizzle, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);

	m_length = SwizzleInt32(m_swizzle);

	fread_s(m_id, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);

	m_chunkId = MYMAKEFOURCC(m_id);

	m_data = new BYTE[m_length]();

	if (m_data)
	{
		fread_s(m_data, (size_t)m_length, sizeof(BYTE), (size_t)m_length, file);
	}

	fread_s(m_CRC, sizeof(BYTE) * 4, sizeof(BYTE), 4, file);
}