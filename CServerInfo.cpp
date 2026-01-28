#include "CServerInfo.h"

/*
*/
CServerInfo::CServerInfo()
{
	memset(this, 0x00, sizeof(CServerInfo));
}

/*
*/
CServerInfo::~CServerInfo()
{
	SAFE_DELETE(m_timerIdle);
	SAFE_DELETE(m_timerReload);
	SAFE_DELETE(m_socket);
}

/*
*/
void CServerInfo::Clear()
{
	if (m_socket)
	{
		m_socket->Shutdown();
	}

	CServerInfo::~CServerInfo();

	CServerInfo::Constructor();
}

/*
*/
void CServerInfo::Constructor()
{
	memset(this, 0x00, sizeof(CServerInfo));

	m_acceleration = 512.0f;

	m_isFreefall = true;
	m_isAvailable = true;

	m_socket = new CSocket();

	m_timerReload = new CTimer(1000);
	m_timerIdle = new CTimer(1000);
}

/*
*/
void CServerInfo::Initialize(int32_t clientNumber, SOCKET socket, bool isBot, bool isAvailable, bool isReconnect, bool isRunning,
	const char* name, const char* modelName, const char* currentMap)
{
	m_clientNumber = clientNumber;

	m_isBot = isBot;

	m_isAvailable = isAvailable;
	m_isReconnect = isReconnect;
	m_isRunning = isRunning;

	SetPlayerName(name);
	SetModelName(modelName);

	if (strcmp(m_lastMap, currentMap) != 0)
	{
		m_isReconnect = false;
	}
	
	SetLastMapName(currentMap);

	m_socket->m_socket = socket;
}

/*
*/
void CServerInfo::Reset()
{
	m_clientNumber = 0;

	//memset(m_playerName, 0x00, CServerInfo::E_PLAYER_NAME_SIZE);
	memset(m_activity, 0x00, CServerInfo::E_MAX_ACTIVITY);
	memset(m_modelName, 0x00, CServerInfo::E_MODEL_NAME_SIZE);

	m_direction = CVec3f(0.0f, 0.0f, 1.0f);
	m_right = CVec3f(1.0f, 0.0f, 0.0f);

	m_isAvailable = true;
	m_isRunning = false;
	m_isFreefall = true;
	m_isReconnect = false;
	m_isConnected = false;

	if (m_isBot)
	{
		m_lastDirection = CVec3f(0.0f, 0.0f, 1.0f);
		
		m_position = CVec3f(0.0f, 0.0f, 0.0f);
		
		m_team = 0;

		memset(m_lastMap, 0x00, CServerInfo::E_MAP_NAME_SIZE);
		memset(m_playerName, 0x00, CServerInfo::E_PLAYER_NAME_SIZE);
	}

	m_isBot = false;

	//m_position = CVec3f(0.0f, 0.0f, 0.0f);
	//m_lastDirection = CVec3f(0.0f, 0.0f, 0.0f);
	//memset(m_lastMap, 0x00, CServerInfo::E_MAP_NAME_SIZE);

	m_state = 0;
	//m_team = 0;

	m_countdown = 0;
	m_matchTimeSeconds = 0;
	m_idleTime = 0;
	m_reloadTime = 0;

	m_acceleration = 512.0f;
	m_freefallVelocity = 0.0f;
	m_velocity = 0.0f;

	m_px = 0;
	m_py = 0;
	m_pz = 0;
}

/*
*/
void CServerInfo::SetActivity(const char* activity)
{
	memset((void*)m_activity, 0x00, CServerInfo::E_MAX_ACTIVITY);

	if (strlen(activity) <= 0)
	{
		return;
	}

	strcpy_s(m_activity, CServerInfo::E_MAX_ACTIVITY, activity);
}

/*
*/
void CServerInfo::SetClient(CServerInfo* serverInfo)
{
	if (serverInfo == nullptr)
	{
		return;
	}

	m_clientNumber = serverInfo->m_clientNumber;

	CServerInfo::SetPlayerName(serverInfo->m_playerName);
	CServerInfo::SetModelName(serverInfo->m_modelName);
	CServerInfo::SetLastMapName(serverInfo->m_lastMap);

	m_direction = serverInfo->m_direction;
	m_right = serverInfo->m_right;

	m_isAvailable = serverInfo->m_isAvailable;
	m_isBot = serverInfo->m_isBot;
	m_isConnected = serverInfo->m_isConnected;
	m_isFreefall = serverInfo->m_isFreefall;
	m_isReconnect = serverInfo->m_isReconnect;
	m_isRunning = serverInfo->m_isRunning;

	m_position = serverInfo->m_position;
	m_lastDirection = serverInfo->m_lastDirection;

	m_state = serverInfo->m_state;
	m_team = serverInfo->m_team;

	m_countdown = serverInfo->m_countdown;
	m_matchTimeSeconds = serverInfo->m_matchTimeSeconds;
	m_idleTime = serverInfo->m_idleTime;
	m_reloadTime = serverInfo->m_reloadTime;

	m_acceleration = serverInfo->m_acceleration;
	m_freefallVelocity = serverInfo->m_freefallVelocity;
	m_velocity = serverInfo->m_velocity;

	m_px = serverInfo->m_px;
	m_py = serverInfo->m_py;
	m_pz = serverInfo->m_pz;

	m_surface = serverInfo->m_surface;
}

/*
*/
void CServerInfo::SetDirection(XMFLOAT3* direction)
{
	m_direction.m_p = *direction;
}

/*
*/
void CServerInfo::SetLastMapName(const char* mapName)
{
	memset((void*)m_lastMap, 0x00, CServerInfo::E_MAP_NAME_SIZE);

	if (strlen(mapName) <= 0)
	{
		return;
	}

	strcpy_s(m_lastMap, CServerInfo::E_MAP_NAME_SIZE, mapName);
}

/*
*/
void CServerInfo::SetModelName(const char* modelName)
{
	memset((void*)m_modelName, 0x00, CServerInfo::E_MODEL_NAME_SIZE);

	if (strlen(modelName) <= 0)
	{
		return;
	}

	strcpy_s(m_modelName, CServerInfo::E_MODEL_NAME_SIZE, modelName);
}

/*
*/
void CServerInfo::SetPlayerName(const char* playerName)
{
	memset((void*)m_playerName, 0x00, CServerInfo::E_PLAYER_NAME_SIZE);

	if (strlen(playerName) <= 0)
	{
		return;
	}

	strcpy_s(m_playerName, CServerInfo::E_PLAYER_NAME_SIZE, playerName);
}

/*
*/
void CServerInfo::SetRight(XMFLOAT3* right)
{
	m_right.m_p = *right;
}

/*
*/
void CServerInfo::SetServer(CServerInfo* serverInfo)
{
	if (serverInfo == nullptr)
	{
		return;
	}

	m_clientNumber = serverInfo->m_clientNumber;

	CServerInfo::SetPlayerName(serverInfo->m_playerName);
	CServerInfo::SetActivity(serverInfo->m_activity);

	m_direction = serverInfo->m_direction;
	m_right = serverInfo->m_right;
}