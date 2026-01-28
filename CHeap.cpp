#include "CHeap.h"

/*
*/
CHeap::CHeap()
{
	memset(this, 0x00, sizeof(CHeap));
}

/*
*/
CHeap::CHeap(int32_t size)
{
	memset(this, 0x00, sizeof(CHeap));

	m_size = size;

	m_heap = new unsigned char[m_size]();

	m_offset = m_heap;
}

/*
*/
CHeap::~CHeap()
{
	SAFE_DELETE_ARRAY(m_heap);
}

/*
*/
bool CHeap::Append(CVec3f* value)
{
	if (!CHeap::CheckBoundary(sizeof(CVec3f)))
	{
		return false;
	}

	memcpy(m_offset, value, sizeof(CVec3f));

	m_offset += sizeof(CVec3f);

	return true;
}

/*
*/
bool CHeap::Append(float value)
{
	if (!CHeap::CheckBoundary(sizeof(float)))
	{
		return false;
	}

	memcpy(m_offset, &value, sizeof(float));

	m_offset += sizeof(float);

	return true;
}

/*
*/
bool CHeap::Append(int16_t value)
{
	if (!CHeap::CheckBoundary(sizeof(int16_t)))
	{
		return false;
	}

	memcpy(m_offset, &value, sizeof(int16_t));

	m_offset += sizeof(int16_t);

	return true;
}

/*
*/
bool CHeap::Append(int32_t value)
{
	if (!CHeap::CheckBoundary(sizeof(int32_t)))
	{
		return false;
	}

	memcpy(m_offset, &value, sizeof(int32_t));

	m_offset += sizeof(int32_t);

	return true;
}

/*
*/
bool CHeap::Append(void* byte, int32_t count)
{
	if (!CHeap::CheckBoundary(count))
	{
		return false;
	}

	memcpy(m_offset, byte, count);

	m_offset += count;

	return true;
}

/*
*/
bool CHeap::Append(XMFLOAT3 value)
{
	if (!CHeap::CheckBoundary(sizeof(XMFLOAT3)))
	{
		return false;
	}

	memcpy(m_offset, &value, sizeof(XMFLOAT3));

	m_offset += sizeof(XMFLOAT3);

	return true;
}

/*
*/
bool CHeap::Append(XMFLOAT4 value)
{
	if (!CHeap::CheckBoundary(sizeof(XMFLOAT4)))
	{
		return false;
	}

	memcpy(m_offset, &value, sizeof(XMFLOAT4));

	m_offset += sizeof(XMFLOAT4);

	return true;
}

/*
*/
bool CHeap::Append(XMFLOAT4X4 value)
{
	if (!CHeap::CheckBoundary(sizeof(XMFLOAT4X4)))
	{
		return false;
	}

	memcpy(m_offset, &value, sizeof(XMFLOAT4X4));

	m_offset += sizeof(XMFLOAT4X4);

	return true;
}

/*
*/
bool CHeap::Append(XMMATRIX value)
{
	if (!CHeap::CheckBoundary(sizeof(XMMATRIX)))
	{
		return false;
	}

	memcpy(m_offset, &value, sizeof(XMMATRIX));

	m_offset += sizeof(XMMATRIX);

	return true;
}

/*
*/
bool CHeap::CheckBoundary(int32_t size)
{
	m_length += size;

	if (m_length > m_size)
	{
		return false;
	}

	return true;
}

/*
*/
void CHeap::Reset()
{
	memset(m_heap, 0x00, m_size);

	m_offset = m_heap;

	m_length = 0;
}