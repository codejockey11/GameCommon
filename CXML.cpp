#include "CXML.h"

/*
*/
CXML::CXML()
{
	memset(this, 0x00, sizeof(CXML));
}

/*
*/
CXML::~CXML()
{
	SAFE_DELETE_ARRAY(m_startOfBuffer);
}

/*
*/
bool CXML::CheckEndOfBuffer()
{
	if (m_buffer >= m_endOfBuffer)
	{
		return true;
	}

	return false;
}

/*
*/
char* CXML::GetAttributes()
{
	m_index = 0;

	memset(m_attribute, 0x00, CXML::MAX_ATTRIBUTE);

	while (strncmp(m_buffer, ">", 1) != 0)
	{
		memcpy(&m_attribute[m_index], m_buffer, 1);

		m_index++;

		m_buffer++;

		if (m_index == CXML::MAX_ATTRIBUTE)
		{
			m_attribute[m_index - 1] = 0x00;

			break;
		}
	}

	return m_attribute;
}

/*
*/
char* CXML::GetValue()
{
	m_index = 0;

	memset(m_value, 0x00, CXML::MAX_VALUE);
	
	while (strncmp(m_buffer, "<", 1) != 0)
	{
		memcpy(&m_value[m_index], m_buffer, 1);

		m_index++;

		m_buffer++;

		if (m_index == CXML::MAX_VALUE)
		{
			m_value[m_index - 1] = 0x00;

			break;
		}
	}

	return m_value;
}

/*
*/
void CXML::InitBuffer(const char* xml)
{
	SAFE_DELETE_ARRAY(m_startOfBuffer);

	m_bufferLength = (int32_t)strlen(xml);

	m_buffer = new char[m_bufferLength]();

	if (m_buffer)
	{
		memcpy(m_buffer, xml, m_bufferLength);
	}

	m_startOfBuffer = m_buffer;

	m_endOfBuffer = m_buffer + m_bufferLength;
}

/*
*/
void CXML::Move(int32_t i)
{
	m_buffer += i;
}

/*
*/
void CXML::MoveToEnd()
{
	while (strncmp(m_buffer, "</", 2) != 0)
	{
		m_buffer++;
	}

	while (strncmp(m_buffer, ">", 1) != 0)
	{
		m_buffer++;
	}

	m_buffer++;
}

/*
*/
void CXML::MoveToTag(const char* tag)
{
	while (strncmp(m_buffer, tag, strlen(tag)) != 0)
	{
		m_buffer++;

		if (CheckEndOfBuffer())
		{
			break;
		}
	}
}