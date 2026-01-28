#include "CBrush.h"

/*
*/
CBrush::CBrush()
{
	memset(this, 0x00, sizeof(CBrush));
}

/*
*/
CBrush::~CBrush()
{

}

/*
// The strategy is to rotate around the side's normal finding a line direction
// and then find the point in the direction of that line with a plane and that plane's normal
// pointing in a similar direction.  The resulting intersection is a vertex for the side.
*/
void CBrush::BuildSides()
{
	for (int32_t s = 0; s < m_sideCount; s++)
	{
		m_brushSide[s].m_min.m_p.x = 100000.0f;
		m_brushSide[s].m_min.m_p.y = 100000.0f;
		m_brushSide[s].m_min.m_p.z = 100000.0f;

		m_brushSide[s].m_max.m_p.x = -100000.0f;
		m_brushSide[s].m_max.m_p.y = -100000.0f;
		m_brushSide[s].m_max.m_p.z = -100000.0f;

		// find the starting line from the side being processed and an adjacent side
		FindStartingSide(&m_brushSide[s]);

		// loop through all sides starting with that line
		for (int32_t as = 0; as < m_sideCount; as++)
		{
			// skip the side being processed
			if (as == s)
			{
				continue;
			}

			// find nearest intersection in the direction of the line
			m_brushSideIntersection = FindNearestIntersection(&m_brushSide[s]);

			// small lengths will be considered a duplicate vertice
			if (m_brushSideIntersection.m_length >= 0.50f)
			{
				m_brushSide[s].MakeVertex(m_brushSideIntersection.m_pop);
			}

			// end process when the first side is intersected
			if (m_brushSideIntersection.m_brushSide.m_wasFirstSide)
			{
				break;
			}

			// set a new start point
			m_startPoint = m_brushSideIntersection.m_pop;

			// find the next line from the side being processed and the intersected side
			m_line = m_brushSide[s].m_plane.PlanePlaneIntersection2(&m_brushSideIntersection.m_brushSide.m_plane);
		}

		// good spot for you to chop the windings and you is not me

		// compute the uv for the vertices

		m_brushSide[s].CenterUVCoordinate();

		m_brushSide[s].FinalizeUVCoordinates();
	}
}

/*
*/
CBrushSideIntersection CBrush::FindNearestIntersection(CBrushSide* brushSide)
{
	memset(&m_returnSide, 0x00, sizeof(CBrushSideIntersection));

	m_minLength = 1000000.0f;

	// process against all sides
	for (int32_t s = 0; s < m_sideCount; s++)
	{
		// skip the side being processed
		if (brushSide->m_number == s)
		{
			continue;
		}

		// only want sides that the line's direction is going towards
		if (m_line.m_D.Dot(&m_brushSide[s].m_normal) <= 0.0f)
		{
			continue;
		}

		// line intersecting plane
		m_collision.IntersectPlane(&m_brushSide[s].m_normal, &m_brushSide[s].m_v1, &m_startPoint, &m_line.m_D);

		// skip the side if the vertice is on it
		if (m_collision.m_length <= 0.0f)
		{
			continue;
		}

		// only want the plane that is near the line's starting point
		if (m_collision.m_length <= m_minLength)
		{
			m_returnSide.m_brushSide = m_brushSide[s];
			m_returnSide.m_pop = m_startPoint + (m_line.m_D * m_collision.m_length);
			m_returnSide.m_length = m_collision.m_length;

			m_minLength = m_collision.m_length;
		}
	}

	return m_returnSide;
}

/*
*/
void CBrush::FindStartingSide(CBrushSide* brushSide)
{
	// initialize for the side

	for (int32_t s = 0; s < m_sideCount; s++)
	{
		m_brushSide[s].m_wasFirstSide = false;
	}

	m_nextSide = brushSide->m_number + 1;

	if (m_nextSide == m_sideCount)
	{
		m_nextSide = 0;
	}

	m_nearest = 0.0f;

	m_sideIndex = m_nextSide;

	// find the nearest side that is perpendicular or closest to but not including dot 1.0

	// process against all sides
	for (int32_t s = 0; s < m_sideCount; s++)
	{
		// skip the side being processed
		if (brushSide->m_number == s)
		{
			continue;
		}

		m_ndn = brushSide->m_normal.Dot(&m_brushSide[s].m_normal);

		// is this one the nearest side 
		if (m_ndn >= m_nearest)
		{
			m_sideIndex = s;

			m_nearest = m_ndn;
		}
	}

	// when the nearest side is found it's the first side that made a line
	m_brushSide[m_sideIndex].m_wasFirstSide = true;

	// the initial line
	m_line = brushSide->m_plane.PlanePlaneIntersection2(&m_brushSide[m_sideIndex].m_plane);

	// the initial starting point
	m_startPoint = m_line.m_P0 - (m_line.m_D * 10000.0f);
}

/*
*/
void CBrush::ParseScript()
{
	while (strncmp(m_mapScript->m_buffer, "}", 1) != 0)
	{
		if (m_sideCount == MAX_SIDES)
		{
			printf("CBrush exceeded maximum sides:%i\n", m_sideCount);
		}
		else
		{
			m_brushSide[m_sideCount].m_masterMaterials = m_masterMaterials;
			m_brushSide[m_sideCount].m_masterMaterialsCount = m_masterMaterialsCount;
			
			m_brushSide[m_sideCount].m_local = m_local;

			m_brushSide[m_sideCount].m_materials = m_materials;
			m_brushSide[m_sideCount].m_materialsCount = m_materialsCount;

			m_brushSide[m_sideCount].m_images = m_images;

			m_brushSide[m_sideCount].ParseScript(m_mapScript->m_buffer);

			m_brushSide[m_sideCount].m_number = m_sideCount;

			m_sideCount++;
		}

		m_mapScript->SkipEndOfLine();
	}
}

/*
*/
void CBrush::PrintInfo() const
{
	for (int32_t i = 0; i < m_sideCount; i++)
	{
		m_brushSide[i].PrintInfo();
	}

	printf("\n");
}