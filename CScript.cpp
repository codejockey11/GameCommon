#include "CScript.h"

/*
*/
CScript::CScript()
{
	memset(this, 0x00, sizeof(CScript));
}

/*
*/
CScript::~CScript()
{
	SAFE_DELETE_ARRAY(m_startOfBuffer);
}

/*
*/
bool CScript::CheckEndOfBuffer()
{
	if (m_buffer >= m_endOfBuffer)
	{
		return true;
	}

	return false;
}

/*
*/
char* CScript::GetToken()
{
	m_tokenFound = false;
	m_tokenCount = 0;

	memset(m_token, 0x00, CScript::MAX_TOKEN);

	while (true)
	{
		if (CScript::CheckEndOfBuffer())
		{
			break;
		}

		if ((m_buffer[0] > ' ') && (m_buffer[0] < 127))
		{
			if (m_tokenCount == CScript::MAX_TOKEN)
			{
				printf_s("Token %s exceeded max token size\n", m_token);

				m_token[CScript::MAX_TOKEN - 1] = 0x00;

				break;
			}

			m_token[m_tokenCount] = m_buffer[0];

			m_tokenCount++;

			m_tokenFound = true;
		}
		else
		{
			if (m_tokenFound)
			{
				break;
			}
		}

		m_buffer++;
	}

	return m_token;
}

/*
*/
char* CScript::GetQuotedToken()
{
	m_tokenFound = false;
	m_tokenCount = 0;

	memset(m_token, 0x00, CScript::MAX_TOKEN);

	while (true)
	{
		if (CScript::CheckEndOfBuffer())
		{
			break;
		}

		if ((m_buffer[0] > 31) && (m_buffer[0] < 127))
		{
			if (m_buffer[0] == 34)
			{
				m_token[m_tokenCount] = m_buffer[0];

				m_tokenCount++;

				m_buffer++;

				while (m_buffer[0] != 34)
				{
					if (m_tokenCount == CScript::MAX_TOKEN)
					{
						m_token[CScript::MAX_TOKEN - 1] = 0x00;

						break;
					}

					m_token[m_tokenCount] = m_buffer[0];

					m_tokenCount++;

					m_buffer++;
				}

				m_token[m_tokenCount] = m_buffer[0];

				m_tokenCount++;

				m_buffer++;

				break;
			}
		}
	}

	return m_token;
}

/*
*/
void CScript::InitBuffer(const char* filename)
{
	m_err = fopen_s(&m_file, filename, "rb");

	if (m_err != 0)
	{
		return;
	}

	m_filePosition = ftell(m_file);
	
	fseek(m_file, 0, SEEK_END);
	
	m_fileSize = ftell(m_file);
	
	fseek(m_file, m_filePosition, SEEK_SET);

	SAFE_DELETE_ARRAY(m_startOfBuffer);

	m_buffer = new char[m_fileSize]();

	fread_s(m_buffer, m_fileSize, 1, m_fileSize, m_file);

	fclose(m_file);

	m_startOfBuffer = m_buffer;

	m_bufferLength = m_fileSize;

	m_endOfBuffer = m_startOfBuffer + m_bufferLength;
}

/*
*/
void CScript::Move(int32_t i)
{
	m_buffer += i;
}

/*
*/
void CScript::MoveToToken(const char* token)
{
	while (true)
	{
		if (CScript::CheckEndOfBuffer())
		{
			break;
		}

		m_result = strncmp(&m_buffer[0], token, strlen(token));
		
		if (m_result == 0)
		{
			break;
		}

		m_buffer++;
	}
}

/*
*/
void CScript::SkipEndOfLine()
{
	if (CScript::CheckEndOfBuffer())
	{
		return;
	}

	while (m_buffer[0] != '\r' && m_buffer[0] != '\n')
	{
		m_buffer++;
	}

	if (m_buffer[0] == '\r')
	{
		m_buffer++;
		m_buffer++;

		return;
	}

	if (m_buffer[0] == '\n')
	{
		m_buffer++;
	}
}

/*
*/
void CScript::SkipTabs()
{
	while (m_buffer[0] == '\t')
	{
		m_buffer++;
	}
}