#pragma once

#include "framework.h"

#include "CString.h"

class CCommandLine
{
public:

	enum
	{
		MAX_IP_LENGTH = 17,
		MAX_MODEL_LENGTH = 32,
		MAX_NAME_LENGTH = 32,
		MAX_PORT_LENGTH = 6
	};

	char m_ip[CCommandLine::MAX_IP_LENGTH];
	char m_modelName[CCommandLine::MAX_MODEL_LENGTH];
	char m_name[CCommandLine::MAX_NAME_LENGTH];
	char m_port[CCommandLine::MAX_PORT_LENGTH];
	char m_port2[CCommandLine::MAX_PORT_LENGTH];

	CString* m_arguments;

	CCommandLine();
	~CCommandLine();

	void ClientConstructor(LPWSTR commandLine);
	void ServerConstructor(LPWSTR commandLine);
};