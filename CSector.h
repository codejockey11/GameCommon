#pragma once

#include "framework.h"

#include "CCollision.h"
#include "CCollisionPrimitive.h"
#include "CVec3f.h"
#include "CVec3i.h"

class CSector
{
public:

	CCollision m_collision;
	
	CVec3f m_dir[6];
	CVec3f m_vec3f;
	CVec3f m_volume[8];
	CVec3f m_xdot;
	CVec3f m_ydot;
	CVec3f m_zdot;
	CVec3i m_sector;
	CVec3f m_sectorNormal[12];
	CVec3f m_sectorTriangle[12][3];

	float m_startWidth;
	float m_startHeight;
	float m_startDepth;

	int32_t m_depth;
	int32_t m_gridDepth;
	int32_t m_gridHeight;
	int32_t m_gridWidth;
	int32_t m_height;
	int32_t m_sectorSize;
	int32_t m_width;

	CSector();
	CSector(int32_t width, int32_t height, int32_t vertical, int32_t sectorSize);
	~CSector();

	bool CheckPointsInside(int32_t x, int32_t y, int32_t z, CCollisionPrimitive* collisionPrimitive);
	bool CheckSectorRayTrace(CCollisionPrimitive* collisionPrimitive);
	bool CheckTriangleOutside(CCollisionPrimitive* collisionPrimitive);
	bool CheckTriangleRayTrace(CCollisionPrimitive* collisionPrimitive);
	CVec3i GetSector(CVec3f* position);
	CVec3i GetSector(XMFLOAT3* position);
	CVec3i GetSector(XMFLOAT4* position);
	void NextDepth();
	void NextHeight();
	void NextWidth();
	void Reset();
	void ResetDepth();
	void ResetWidth();
};