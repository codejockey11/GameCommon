#include "CCommandLine.h"

/*
*/
CCommandLine::CCommandLine()
{
	memset(this, 0x00, sizeof(CCommandLine));
}

/*
*/
CCommandLine::~CCommandLine()
{
	SAFE_DELETE(m_arguments);
}

/*
*/
void CCommandLine::ClientConstructor(LPWSTR commandLine)
{
	memset(this, 0x00, sizeof(CCommandLine));

	m_arguments = new CString(commandLine);

	sscanf_s(m_arguments->m_text, "%s %s %s %s %s\n",
		m_ip, CCommandLine::MAX_IP_LENGTH,
		m_port, CCommandLine::MAX_PORT_LENGTH,
		m_port2, CCommandLine::MAX_PORT_LENGTH,
		m_name, CCommandLine::MAX_NAME_LENGTH,
		m_modelName, CCommandLine::MAX_MODEL_LENGTH);
}

/*
*/
void CCommandLine::ServerConstructor(LPWSTR commandLine)
{
	memset(this, 0x00, sizeof(CCommandLine));

	m_arguments = new CString(commandLine);

	sscanf_s(m_arguments->m_text, "%s\n",
		m_port, CCommandLine::MAX_PORT_LENGTH);
}