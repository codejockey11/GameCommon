#include "CNetwork.h"

/*
*/
CNetwork::CNetwork()
{
	memset(this, 0x00, sizeof(CNetwork));
}

/*
*/
CNetwork::CNetwork(BYTE audience, BYTE type, void* serverInfo, int32_t slength, void* data, int32_t dlength)
{
	memset(this, 0x00, sizeof(CNetwork));

	m_audience = audience;
	m_type = type;

	CNetwork::SetData(data, dlength);
	CNetwork::SetServerInfo(serverInfo, slength);
}

/*
*/
CNetwork::~CNetwork()
{

}

/*
*/
void CNetwork::SetData(void* data, int32_t length)
{
	memset((void*)m_data, 0x00, CNetwork::E_DATA_SIZE);

	if (data == nullptr)
	{
		return;
	}

	if (length > CNetwork::E_DATA_SIZE)
	{
		length = CNetwork::E_DATA_SIZE;
	}

	memcpy_s((void*)m_data, CNetwork::E_DATA_SIZE, data, length);
}

/*
*/
void CNetwork::SetServerInfo(void* serverInfo, int32_t length)
{
	if (serverInfo == nullptr)
	{
		return;
	}

	if (length > CNetwork::E_SERVER_INFO_SIZE)
	{
		length = CNetwork::E_SERVER_INFO_SIZE;
	}

	memset((void*)m_serverInfo, 0x00, CNetwork::E_SERVER_INFO_SIZE);

	memcpy_s((void*)m_serverInfo, CNetwork::E_SERVER_INFO_SIZE, serverInfo, length);
}