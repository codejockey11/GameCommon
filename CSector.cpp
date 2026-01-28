#include "CSector.h"

/*
*/
CSector::CSector()
{
	memset(this, 0x00, sizeof(CSector));
}

/*
*/
CSector::CSector(int32_t width, int32_t depth, int32_t height, int32_t sectorSize)
{
	memset(this, 0x00, sizeof(CSector));

	m_width = width;
	m_depth = depth;
	m_height = height;

	m_sectorSize = sectorSize;

	m_gridWidth = (m_width / m_sectorSize);
	m_gridDepth = (m_depth / m_sectorSize);
	m_gridHeight = (m_height / m_sectorSize);

	m_xdot = CVec3f(1.0f, 0.0f, 0.0f);
	m_ydot = CVec3f(0.0f, 1.0f, 0.0f);
	m_zdot = CVec3f(0.0f, 0.0f, 1.0f);

	m_startWidth = (float)(m_width / 2) - m_width;
	m_startDepth = (float)(m_depth / 2) - m_depth;
	m_startHeight = (float)(m_height / 2) - m_height;

	m_dir[0] = CVec3f(0.0f, 0.0f, 1.0f);
	m_dir[1] = CVec3f(1.0f, 0.0f, 0.0f);
	m_dir[2] = CVec3f(0.0f, 0.0f, -1.0f);
	m_dir[3] = CVec3f(-1.0f, 0.0f, 0.0f);
	m_dir[4] = CVec3f(0.0f, -1.0f, 0.0f);
}

/*
*/
CSector::~CSector()
{

}

/*
*/
bool CSector::CheckPointsInside(int32_t x, int32_t y, int32_t z, CCollisionPrimitive* collisionPrimitive)
{
	CVec3f* position = &collisionPrimitive->m_a;

	for (int32_t i = 0; i < 3; i++)
	{
		CVec3i sector = CSector::GetSector(&position[i].m_p);

		if ((sector.m_p.x == x) && (sector.m_p.y == y) && (sector.m_p.z == z))
		{
			return true;
		}

		if (position[i].m_p.x >= m_volume[0].m_p.x)
			if (position[i].m_p.y >= m_volume[0].m_p.y)
				if (position[i].m_p.z >= m_volume[0].m_p.z)
					if (position[i].m_p.x <= m_volume[6].m_p.x)
						if (position[i].m_p.y <= m_volume[6].m_p.y)
							if (position[i].m_p.z <= m_volume[6].m_p.z)
							{
								return true;
							}
	}

	return false;
}

/*
*/
bool CSector::CheckSectorRayTrace(CCollisionPrimitive* collisionPrimitive)
{
	CVec3f* position = &collisionPrimitive->m_a;

	CVec3f pop = {};

	for (int32_t i = 0; i < 4; i++)
	{
		if (m_dir[i].Dot(&collisionPrimitive->m_n) > 0.0f)
		{
			continue;
		}

		m_collision.IntersectPlane(&collisionPrimitive->m_n, &position[0], &m_volume[i], &m_dir[i]);

		if (m_collision.m_length < 0.0f)
		{
			continue;
		}

		if (m_collision.m_length > m_sectorSize)
		{
			continue;
		}

		pop = m_volume[i] + (m_dir[i] * m_collision.m_length);

		if (m_collision.PointInTriangle(pop, position[0], position[1], position[2]))
		{
			return true;
		}
	}

	int32_t d = 0;

	for (int32_t i = 4; i < 8; i++)
	{
		if (m_dir[d].Dot(&collisionPrimitive->m_n) > 0.0f)
		{
			continue;
		}

		m_collision.IntersectPlane(&collisionPrimitive->m_n, &position[0], &m_volume[i], &m_dir[d]);

		if (m_collision.m_length < 0.0f)
		{
			continue;
		}

		if (m_collision.m_length > m_sectorSize)
		{
			continue;
		}

		pop = m_volume[i] + (m_dir[d] * m_collision.m_length);

		if (m_collision.PointInTriangle(pop, position[0], position[1], position[2]))
		{
			return true;
		}

		d++;
	}

	for (int32_t i = 4; i < 8; i++)
	{
		if (m_dir[4].Dot(&collisionPrimitive->m_n) > 0.0f)
		{
			continue;
		}

		m_collision.IntersectPlane(&collisionPrimitive->m_n, &position[0], &m_volume[i], &m_dir[4]);

		if (m_collision.m_length < 0.0f)
		{
			continue;
		}

		if (m_collision.m_length > m_sectorSize)
		{
			continue;
		}

		pop = m_volume[i] + (m_dir[4] * m_collision.m_length);

		if (m_collision.PointInTriangle(pop, position[0], position[1], position[2]))
		{
			return true;
		}
	}

	return false;
}

/*
*/
bool CSector::CheckTriangleOutside(CCollisionPrimitive* collisionPrimitive)
{
	if (collisionPrimitive->m_a.m_p.y < m_volume[0].m_p.y)
		if (collisionPrimitive->m_b.m_p.y < m_volume[0].m_p.y)
			if (collisionPrimitive->m_c.m_p.y < m_volume[0].m_p.y)
			{
				return true;
			}

	if (collisionPrimitive->m_a.m_p.y > m_volume[6].m_p.y)
		if (collisionPrimitive->m_b.m_p.y > m_volume[6].m_p.y)
			if (collisionPrimitive->m_c.m_p.y > m_volume[6].m_p.y)
			{
				return true;
			}

	if (collisionPrimitive->m_a.m_p.x < m_volume[0].m_p.x)
		if (collisionPrimitive->m_b.m_p.x < m_volume[0].m_p.x)
			if (collisionPrimitive->m_c.m_p.x < m_volume[0].m_p.x)
				if (collisionPrimitive->m_a.m_p.z < m_volume[0].m_p.z)
					if (collisionPrimitive->m_b.m_p.z < m_volume[0].m_p.z)
						if (collisionPrimitive->m_c.m_p.z < m_volume[0].m_p.z)
						{
							return true;
						}

	if (collisionPrimitive->m_a.m_p.x > m_volume[6].m_p.x)
		if (collisionPrimitive->m_b.m_p.x > m_volume[6].m_p.x)
			if (collisionPrimitive->m_c.m_p.x > m_volume[6].m_p.x)
				if (collisionPrimitive->m_a.m_p.z > m_volume[6].m_p.z)
					if (collisionPrimitive->m_b.m_p.z > m_volume[6].m_p.z)
						if (collisionPrimitive->m_c.m_p.z > m_volume[6].m_p.z)
						{
							return true;
						}

	return false;
}

/*
*/
bool CSector::CheckTriangleRayTrace(CCollisionPrimitive* collisionPrimitive)
{
	// bottom
	m_sectorTriangle[0][0] = m_volume[0];
	m_sectorTriangle[0][1] = m_volume[1];
	m_sectorTriangle[0][2] = m_volume[2];
	m_sectorNormal[0] = CVec3f::Normal(&m_volume[0], &m_volume[1], &m_volume[2]);

	m_sectorTriangle[1][0] = m_volume[2];
	m_sectorTriangle[1][1] = m_volume[3];
	m_sectorTriangle[1][2] = m_volume[0];
	m_sectorNormal[1] = m_sectorNormal[0];

	// top
	m_sectorTriangle[2][0] = m_volume[6];
	m_sectorTriangle[2][1] = m_volume[5];
	m_sectorTriangle[2][2] = m_volume[4];
	m_sectorNormal[2] = CVec3f::Normal(&m_volume[6], &m_volume[5], &m_volume[4]);

	m_sectorTriangle[3][0] = m_volume[4];
	m_sectorTriangle[3][1] = m_volume[7];
	m_sectorTriangle[3][2] = m_volume[6];
	m_sectorNormal[3] = m_sectorNormal[2];

	// front
	m_sectorTriangle[4][0] = m_volume[7];
	m_sectorTriangle[4][1] = m_volume[4];
	m_sectorTriangle[4][2] = m_volume[0];
	m_sectorNormal[4] = CVec3f::Normal(&m_volume[7], &m_volume[4], &m_volume[0]);

	m_sectorTriangle[5][0] = m_volume[0];
	m_sectorTriangle[5][1] = m_volume[3];
	m_sectorTriangle[5][2] = m_volume[7];
	m_sectorNormal[5] = m_sectorNormal[4];

	// right
	m_sectorTriangle[6][0] = m_volume[6];
	m_sectorTriangle[6][1] = m_volume[7];
	m_sectorTriangle[6][2] = m_volume[3];
	m_sectorNormal[6] = CVec3f::Normal(&m_volume[6], &m_volume[7], &m_volume[3]);

	m_sectorTriangle[7][0] = m_volume[3];
	m_sectorTriangle[7][1] = m_volume[2];
	m_sectorTriangle[7][2] = m_volume[6];
	m_sectorNormal[7] = m_sectorNormal[6];

	// back
	m_sectorTriangle[8][0] = m_volume[0];
	m_sectorTriangle[8][1] = m_volume[4];
	m_sectorTriangle[8][2] = m_volume[7];
	m_sectorNormal[8] = CVec3f::Normal(&m_volume[0], &m_volume[4], &m_volume[7]);

	m_sectorTriangle[9][0] = m_volume[7];
	m_sectorTriangle[9][1] = m_volume[3];
	m_sectorTriangle[9][2] = m_volume[0];
	m_sectorNormal[9] = m_sectorNormal[8];

	// left
	m_sectorTriangle[10][0] = m_volume[0];
	m_sectorTriangle[10][1] = m_volume[4];
	m_sectorTriangle[10][2] = m_volume[5];
	m_sectorNormal[10] = CVec3f::Normal(&m_volume[0], &m_volume[4], &m_volume[5]);

	m_sectorTriangle[11][0] = m_volume[5];
	m_sectorTriangle[11][1] = m_volume[1];
	m_sectorTriangle[11][2] = m_volume[0];
	m_sectorNormal[11] = m_sectorNormal[10];

	CVec3f* position = &collisionPrimitive->m_a;

	CVec3f pop = {};

	for (int32_t t = 0; t < 3; t++)
	{
		for (int32_t i = 0; i < 12; i++)
		{
			int32_t p = t + 1;

			if (p == 3) p = 0;

			m_dir[5] = position[p] - position[t];

			m_dir[5].Normalize();

			if (m_dir[5].Dot(&m_sectorNormal[i]) > 0.0f)
			{
				continue;
			}

			m_collision.IntersectPlane(&m_sectorNormal[i], &m_sectorTriangle[i][0], &position[t], &m_dir[5]);

			if (m_collision.m_length < 0.0f)
			{
				continue;
			}

			if (m_collision.m_length > m_sectorSize)
			{
				continue;
			}

			pop = position[t] + (m_dir[5] * m_collision.m_length);

			if (m_collision.PointInTriangle(pop, m_sectorTriangle[i][0], m_sectorTriangle[i][1], m_sectorTriangle[i][2]))
			{
				return true;
			}
		}
	}

	return false;
}

/*
*/
CVec3i CSector::GetSector(CVec3f* position)
{
	m_sector.m_p.x = (int32_t)((m_xdot.Dot(position) / m_sectorSize) + (m_gridWidth / 2.0f));
	m_sector.m_p.z = (int32_t)((m_zdot.Dot(position) / m_sectorSize) + (m_gridDepth / 2.0f));
	m_sector.m_p.y = (int32_t)((m_ydot.Dot(position) / m_sectorSize) + (m_gridHeight / 2.0f));

	return m_sector;
}

/*
*/
CVec3i CSector::GetSector(XMFLOAT3* position)
{
	m_vec3f = CVec3f(position->x, position->y, position->z);

	return CSector::GetSector(&m_vec3f);
}

/*
*/
CVec3i CSector::GetSector(XMFLOAT4* position)
{
	m_vec3f = CVec3f(position->x, position->y, position->z);

	return CSector::GetSector(&m_vec3f);
}

/*
*/
void CSector::NextDepth()
{
	m_volume[0].m_p.z += m_sectorSize;
	m_volume[1].m_p.z += m_sectorSize;
	m_volume[2].m_p.z += m_sectorSize;
	m_volume[3].m_p.z += m_sectorSize;

	m_volume[4].m_p.z += m_sectorSize;
	m_volume[5].m_p.z += m_sectorSize;
	m_volume[6].m_p.z += m_sectorSize;
	m_volume[7].m_p.z += m_sectorSize;
}

/*
*/
void CSector::NextHeight()
{
	m_volume[0].m_p.y += m_sectorSize;
	m_volume[1].m_p.y += m_sectorSize;
	m_volume[2].m_p.y += m_sectorSize;
	m_volume[3].m_p.y += m_sectorSize;

	m_volume[4].m_p.y += m_sectorSize;
	m_volume[5].m_p.y += m_sectorSize;
	m_volume[6].m_p.y += m_sectorSize;
	m_volume[7].m_p.y += m_sectorSize;
}

/*
*/
void CSector::NextWidth()
{
	m_volume[0].m_p.x += m_sectorSize;
	m_volume[1].m_p.x += m_sectorSize;
	m_volume[2].m_p.x += m_sectorSize;
	m_volume[3].m_p.x += m_sectorSize;

	m_volume[4].m_p.x += m_sectorSize;
	m_volume[5].m_p.x += m_sectorSize;
	m_volume[6].m_p.x += m_sectorSize;
	m_volume[7].m_p.x += m_sectorSize;
}

/*
5---6
|\   \
| \   \
|  4---7
|
1---2
 \   \
  \   \
   0---3
*/
void CSector::Reset()
{
	m_volume[0] = CVec3f(m_startWidth, m_startHeight, m_startDepth);
	m_volume[1] = CVec3f(m_startWidth, m_startHeight, m_startDepth + m_sectorSize);
	m_volume[2] = CVec3f(m_startWidth + m_sectorSize, m_startHeight, m_startDepth + m_sectorSize);
	m_volume[3] = CVec3f(m_startWidth + m_sectorSize, m_startHeight, m_startDepth);

	m_volume[4] = CVec3f(m_startWidth, m_startHeight + m_sectorSize, m_startDepth);
	m_volume[5] = CVec3f(m_startWidth, m_startHeight + m_sectorSize, m_startDepth + m_sectorSize);
	m_volume[6] = CVec3f(m_startWidth + m_sectorSize, m_startHeight + m_sectorSize, m_startDepth + m_sectorSize);
	m_volume[7] = CVec3f(m_startWidth + m_sectorSize, m_startHeight + m_sectorSize, m_startDepth);
}

/*
*/
void CSector::ResetDepth()
{
	m_volume[0].m_p.z = m_startDepth;
	m_volume[1].m_p.z = m_startDepth + m_sectorSize;
	m_volume[2].m_p.z = m_startDepth + m_sectorSize;
	m_volume[3].m_p.z = m_startDepth;

	m_volume[4].m_p.z = m_startDepth;
	m_volume[5].m_p.z = m_startDepth + m_sectorSize;
	m_volume[6].m_p.z = m_startDepth + m_sectorSize;
	m_volume[7].m_p.z = m_startDepth;
}

/*
*/
void CSector::ResetWidth()
{
	m_volume[0].m_p.x = m_startWidth;
	m_volume[1].m_p.x = m_startWidth;
	m_volume[2].m_p.x = m_startWidth + m_sectorSize;
	m_volume[3].m_p.x = m_startWidth + m_sectorSize;

	m_volume[4].m_p.x = m_startWidth;
	m_volume[5].m_p.x = m_startWidth;
	m_volume[6].m_p.x = m_startWidth + m_sectorSize;
	m_volume[7].m_p.x = m_startWidth + m_sectorSize;
}