#include "CLobbyServerInfo.h"

/*
*/
CLobbyServerInfo::CLobbyServerInfo()
{
	memset(this, 0x00, sizeof(CLobbyServerInfo));
}

/*
*/
CLobbyServerInfo::~CLobbyServerInfo()
{
	SAFE_DELETE(m_socket);
}

/*
*/
void CLobbyServerInfo::Clear()
{
	SAFE_DELETE(m_socket);

	CLobbyServerInfo::Constructor();

	m_isAvailable = true;
}

/*
*/
void CLobbyServerInfo::Constructor()
{
	memset(this, 0x00, sizeof(CLobbyServerInfo));

	m_socket = new CSocket();

	m_isAvailable = true;
}

/*
*/
void CLobbyServerInfo::Initialize(CLobbyServerInfo* serverInfo)
{
	m_clientNumber = serverInfo->m_clientNumber;

	CLobbyServerInfo::SetName(serverInfo->m_name);

	m_state = serverInfo->m_state;

	m_isAvailable = serverInfo->m_isAvailable;
	m_isConnected = serverInfo->m_isConnected;
}

/*
*/
void CLobbyServerInfo::Reset()
{
	m_socket->Shutdown();

	CLobbyServerInfo::Clear();

	m_isAvailable = true;
}

/*
*/
void CLobbyServerInfo::SetClient(CLobbyServerInfo* serverInfo)
{
	m_clientNumber = serverInfo->m_clientNumber;

	CLobbyServerInfo::SetName(serverInfo->m_name);

	m_isAvailable = serverInfo->m_isAvailable;
	m_isConnected = serverInfo->m_isConnected;

	m_state = serverInfo->m_state;
}

/*
*/
void CLobbyServerInfo::SetName(const char* name)
{
	memset((void*)m_name, 0x00, CLobbyServerInfo::E_NAME_SIZE);

	if (strlen(name) >= CLobbyServerInfo::E_NAME_SIZE)
	{
		memcpy_s((void*)m_name, CLobbyServerInfo::E_NAME_SIZE, (void*)name, (rsize_t)CLobbyServerInfo::E_NAME_SIZE - 1);

		return;
	}

	memcpy_s((void*)m_name, CLobbyServerInfo::E_NAME_SIZE, (void*)name, strlen(name));
}

/*
*/
void CLobbyServerInfo::SetServer(CLobbyServerInfo* serverInfo)
{
	m_clientNumber = serverInfo->m_clientNumber;

	CLobbyServerInfo::SetName(serverInfo->m_name);
}