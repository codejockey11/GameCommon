#include "CHeapArray.h"

/*
*/
CHeapArray::CHeapArray()
{
	memset(this, 0x00, sizeof(CHeapArray));
}

/*
*/
CHeapArray::CHeapArray(bool allocateHeap, int32_t size, int32_t numberOfIndices, ...)
{
	memset(this, 0x00, sizeof(CHeapArray));

	m_allocator = new CHeapAllocator[numberOfIndices]();

	m_size = size;

	va_list argptr;

	int32_t count;

	va_start(argptr, numberOfIndices);

	count = va_arg(argptr, int32_t);

	m_allocator[0].m_count = count;
	m_allocator[0].m_entrySize = size * count;

	for (int32_t i = 1; i < numberOfIndices; i++)
	{
		count = va_arg(argptr, int32_t);

		m_allocator[i].m_count = count;
		m_allocator[i].m_entrySize = m_allocator[i - 1].m_entrySize * count;
	}

	va_end(argptr);

	m_totalSize = m_allocator[numberOfIndices - 1].m_entrySize;

	if (allocateHeap)
	{
		m_heap = new BYTE[m_totalSize]();
	}
}

/*
*/
CHeapArray::~CHeapArray()
{
	SAFE_DELETE_ARRAY(m_heap);
	SAFE_DELETE_ARRAY(m_allocator);
}

/*
*/
BYTE* CHeapArray::GetElement(int32_t numberOfIndices, ...)
{
	va_list argptr;

	int32_t count;
	int32_t displacement;

	va_start(argptr, numberOfIndices);

	count = va_arg(argptr, int32_t);

	if ((count < 0) || (count >= m_allocator[0].m_count))
	{
		return nullptr;
	}

	displacement = m_size * count;

	for (int32_t i = 1; i < numberOfIndices; i++)
	{
		count = va_arg(argptr, int32_t);

		if ((count < 0) || (count >= m_allocator[i].m_count))
		{
			return nullptr;
		}

		displacement += m_allocator[i - 1].m_entrySize * count;
	}

	va_end(argptr);

	return (m_heap + displacement);
}

/*
*/
int32_t  CHeapArray::GetOffset(int32_t numberOfIndices, ...)
{
	va_list argptr;

	int32_t count;
	int32_t displacement;

	va_start(argptr, numberOfIndices);

	count = va_arg(argptr, int32_t);

	if ((count < 0) || (count >= m_allocator[0].m_count))
	{
		return 0;
	}

	displacement = m_size * count;

	for (int32_t i = 1; i < numberOfIndices; i++)
	{
		count = va_arg(argptr, int32_t);

		if ((count < 0) || (count >= m_allocator[i].m_count))
		{
			return 0;
		}

		displacement += m_allocator[i - 1].m_entrySize * count;
	}

	va_end(argptr);

	return displacement;
}