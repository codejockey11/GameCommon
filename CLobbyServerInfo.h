#pragma once

#include "framework.h"

#include "CSocket.h"

class CLobbyServerInfo
{
public:

	enum
	{
		E_MAX_CLIENTS = 4,
		E_NAME_SIZE = 32
	};

	bool m_isAvailable;
	bool m_isConnected;

	BYTE m_state;

	char m_name[CLobbyServerInfo::E_NAME_SIZE];

	CSocket* m_socket;

	int32_t m_clientNumber;

	CLobbyServerInfo();
	~CLobbyServerInfo();

	void Clear();
	void Constructor();
	void Initialize(CLobbyServerInfo* serverInfo);
	void Reset();
	void SetClient(CLobbyServerInfo* serverInfo);
	void SetServer(CLobbyServerInfo* serverInfo);
	void SetName(const char* name);
};