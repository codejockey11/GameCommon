#pragma once

#include "framework.h"

#include "CSocket.h"
#include "CTimer.h"
#include "CVec3f.h"

class CServerInfo
{
public:

	enum Team
	{
		E_TEAM_RED = 0,
		E_TEAM_BLUE,
		E_MAX_TEAM
	};

	enum ClientState
	{
		E_LOGIN = 0,
		E_LOBBY,
		E_GAME,
		E_MAX_CLIENT_STATE
	};

	enum
	{
		E_MAX_CLIENTS = 4,
		E_MAX_ACTIVITY = 10,
		E_PLAYER_NAME_SIZE = 32,
		E_MAP_NAME_SIZE = 32,
		E_MODEL_NAME_SIZE = 128,
		E_DATA_SIZE = 256
	};

	bool m_isAvailable;
	bool m_isBot;
	bool m_isConnected;
	bool m_isFreefall;
	bool m_isReconnect;
	bool m_isRunning;

	BYTE m_state;
	BYTE m_team;

	char m_activity[CServerInfo::E_MAX_ACTIVITY];
	char m_lastMap[CServerInfo::E_MAP_NAME_SIZE];
	char m_modelName[CServerInfo::E_MODEL_NAME_SIZE];
	char m_playerName[CServerInfo::E_PLAYER_NAME_SIZE];

	CSocket* m_socket;
	CTimer* m_timerIdle;
	CTimer* m_timerReload;
	CVec3f m_direction;
	CVec3f m_lastDirection;
	CVec3f m_position;
	CVec3f m_right;

	float m_acceleration;
	float m_freefallVelocity;
	float m_velocity;

	int32_t m_clientNumber;
	int32_t m_countdown;
	int32_t m_idleTime;
	int32_t m_matchTimeSeconds;
	int32_t m_px;
	int32_t m_py;
	int32_t m_pz;
	int32_t m_reloadTime;
	int32_t m_surface;

	CServerInfo();
	~CServerInfo();

	void Clear();
	void Constructor();
	void Initialize(int32_t clientNumber, SOCKET socket, bool isBot, bool isAvailable, bool isReconnect, bool isRunning,
		const char* name, const char* modelName, const char* currentMap);
	void Reset();
	void SetActivity(const char* activity);
	void SetClient(CServerInfo* serverInfo);
	void SetDirection(XMFLOAT3* direction);
	void SetLastMapName(const char* mapName);
	void SetModelName(const char* modelName);
	void SetPlayerName(const char* playerName);
	void SetRight(XMFLOAT3* right);
	void SetServer(CServerInfo* serverInfo);
};