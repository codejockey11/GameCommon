#pragma once

#include "framework.h"

#include "CErrorLog.h"

class CSocket
{
public:

	enum
	{
		E_IP_LENGTH = 15,
		E_PORT_LENGTH = 6,
		E_HOSTNAME_LENGTH = 64
	};

	enum State
	{
		E_NOT_CONNECTED = 0,
		E_CONNECTED,
		E_FAILED
	};

	ADDRINFO  m_addrHints;
	ADDRINFO* m_addrPtr;
	ADDRINFO* m_addrResult;

	CErrorLog* m_errorLog;

	char m_hostname[CSocket::E_HOSTNAME_LENGTH];
	char m_ip[CSocket::E_IP_LENGTH];
	char m_port[CSocket::E_PORT_LENGTH];

	int32_t m_optval;
	int32_t m_result;
	int32_t m_state;
	int32_t m_totalBytes;

	SOCKET m_assignedSocket;
	SOCKET m_socket;

	CSocket();
	CSocket(CErrorLog* errorLog);
	~CSocket();

	SOCKET Accept();
	bool CreateConnectSocket(const char* address, const char* port);
	bool CreateListenSocket(const char* port);
	bool Listen();
	int32_t Receive(char* data, int32_t length);
	bool Send(char* data, int32_t length);
	void SetErrorLog(CErrorLog* errorLog) { m_errorLog = errorLog; }
	void SetReceiveTimeout(int32_t optval);
	bool Shutdown();
	bool ShutdownListen();
};