#pragma once

#include "framework.h"

class CNetwork
{
public:

	enum ClientEvent
	{
		E_CE_ACCEPTED = 0,
		E_CE_ACCEPTED_LOBBY,
		E_CE_ACCOUNT_INFO,
		E_CE_ACCOUNT_INFO_END,
		E_CE_BROWSER,
		E_CE_CLOSE_BROWSER,
		E_CE_COMPLETE_LOBBY_CONNECT,
		E_CE_CONNECT,
		E_CE_CONNECT_LOBBY,
		E_CE_CONSOLE,
		E_CE_CONSOLE_MESSAGE,
		E_CE_DISCONNECT,
		E_CE_DRAW_FRAME,
		E_CE_ENTER,
		E_CE_EXIT,
		E_CE_EXIT_GAME,
		E_CE_LOADING,
		E_CE_LOAD_ENVIRONMENT,
		E_CE_LOAD_PLAYER,
		E_CE_QUE_SOUND,
		E_CE_READY_CHECK,
		E_CE_REQUEST_ACCOUNT_INFO,
		E_CE_SEND_ACTIVITY,
		E_CE_SEND_NULL_ACTIVITY,
		E_CE_SERVER_FULL,
		E_CE_SERVER_SHUTDOWN,
		E_CE_SET_LOCAL_LOBBY,
		E_CE_LOBBY_SERVER_FULL,
		E_CE_TO_LOCAL,
		E_CE_TO_SERVER,
		E_CE_UPDATE,
		E_CE_UPDATE_COLLECTABLE,
		E_CE_WINDOW_MODE,

		E_CE_MAX
	};

	enum ServerEvent
	{
		E_SE_ACTIVITY = 0,
		E_SE_DISCONNECT,
		E_SE_EXIT,
		E_SE_NULL_ACTIVITY,
		E_SE_READY,
		E_SE_READY_CHECK,
		E_SE_TO_CLIENT,

		E_SE_MAX
	};

	enum LobbyEvent
	{
		E_LE_ACCOUNT_INFO = 0,
		E_LE_DISCONNECT,
		E_LE_MESSAGE,

		E_LE_MAX
	};

	enum ClientActivity
	{
		E_CA_ATTACK = 1,
		E_CA_BACKWARD,
		E_CA_FORWARD,
		E_CA_STEP_LEFT,
		E_CA_STEP_RIGHT,

		E_CA_MAX
	};

	enum
	{
		E_MAX_ACTIVITY = 2,
		E_DATA_SIZE = 256,
		E_SERVER_INFO_SIZE = 1024
	};

	BYTE m_audience;
	BYTE m_data[CNetwork::E_DATA_SIZE];
	BYTE m_serverInfo[CNetwork::E_SERVER_INFO_SIZE];
	BYTE m_type;

	int32_t m_length;

	CNetwork();
	CNetwork(BYTE audience, BYTE type, void* serverInfo, int32_t slength, void* data, int32_t dlength);
	~CNetwork();

	void SetData(void* data, int32_t length);
	void SetServerInfo(void* serverInfo, int32_t length);
};