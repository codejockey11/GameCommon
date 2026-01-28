#include "CBrushSide.h"

/*
*/
CBrushSide::CBrushSide()
{
	memset(this, 0x00, sizeof(CBrushSide));
}

/*
*/
CBrushSide::~CBrushSide()
{

}

/*
*/
void CBrushSide::CenterUVCoordinate()
{
	m_center.m_v.m_p.x /= (float)m_vertexCount;
	m_center.m_v.m_p.y /= (float)m_vertexCount;
	m_center.m_v.m_p.z /= (float)m_vertexCount;

	m_center.m_v.m_n.x = m_normal.m_p.x;
	m_center.m_v.m_n.y = m_normal.m_p.y;
	m_center.m_v.m_n.z = m_normal.m_p.z;

	m_position = CVec3f(m_center.m_v.m_p);

	m_u = 0.0f;
	m_v = 0.0f;

	CBrushSide::MakeUVForVertex(&m_normal, &m_position, &m_u, &m_v, m_rotation);

	m_center.m_v.m_uv.x = m_u;
	m_center.m_v.m_uv.y = m_v;
}

/*
*/
void CBrushSide::FinalizeUVCoordinates()
{
	m_textureWidthScaled = m_horizontalScale * m_shaderImage->m_header->m_width;
	m_textureHeightScaled = m_verticalScale * m_shaderImage->m_header->m_height;
	
	if ((m_min.m_p.x < 0.0f) && (m_max.m_p.x < 0.0f))
	{
		m_width = (float)fabs(m_max.m_p.x) - (float)fabs(m_min.m_p.x);
	}
	else if ((m_min.m_p.x < 0.0f) || (m_max.m_p.x < 0.0f))
	{
		m_width = (float)fabs(m_max.m_p.x) + (float)fabs(m_min.m_p.x);
	}
	else
	{
		m_width = m_max.m_p.x - m_min.m_p.x;
	}

	if ((m_min.m_p.y < 0.0f) && (m_max.m_p.y < 0.0f))
	{
		m_height = (float)fabs(m_max.m_p.y) - (float)fabs(m_min.m_p.y);
	}
	else if ((m_min.m_p.y < 0.0f) || (m_max.m_p.y < 0.0f))
	{
		m_height = (float)fabs(m_max.m_p.y) + (float)fabs(m_min.m_p.y);
	}
	else
	{
		m_height = m_max.m_p.y - m_min.m_p.y;
	}
	
	m_tileX = m_width / m_textureWidthScaled;
	m_tileY = m_height / m_textureHeightScaled;
	
	m_widthShifted = m_horizontalShift / m_shaderImage->m_header->m_width;
	m_heightShifted = m_verticalShift / m_shaderImage->m_header->m_height;

	m_center.m_v.m_uv.x /= m_width;
	m_center.m_v.m_uv.y /= m_height;

	m_center.m_v.m_uv.x += m_widthShifted;
	m_center.m_v.m_uv.y -= m_heightShifted;

	m_center.m_v.m_uv.x *= m_tileX;
	m_center.m_v.m_uv.y *= m_tileY;

	for (int32_t i = 0; i < m_vertexCount; i++)
	{
		m_vertex[i].m_v.m_uv.x /= m_width;
		m_vertex[i].m_v.m_uv.y /= m_height;

		m_vertex[i].m_v.m_uv.x += m_widthShifted;
		m_vertex[i].m_v.m_uv.y -= m_heightShifted;

		m_vertex[i].m_v.m_uv.x *= m_tileX;
		m_vertex[i].m_v.m_uv.y *= m_tileY;
	}
}

/*
*/
void CBrushSide::MakeUVForVertex(CVec3f* normal, CVec3f* vertex, float* u, float* v, float rotation)
{
	m_up = CVec3f(0.0f, 1.0f, 0.0f);

	m_inormal = *normal * -1.0f;

	m_ndu = normal->Dot(&m_up);

	if ((m_ndu > 0.0f) && (m_ndu < 1.0f))
	{
	}
	else if ((m_ndu < 0.0f) && (m_ndu > -1.0f))
	{
		m_up = CVec3f(0.0f, -1.0f, 0.0f);
	}
	else if (m_ndu == 1.0f)
	{
		m_up = CVec3f(0.0f, 0.0f, 1.0f);
	}
	else if (m_ndu == -1.0f)
	{
		m_up = CVec3f(0.0f, 0.0f, -1.0f);
	}
	else if (m_ndu == 0.0f)
	{
	}

	m_vpos = *vertex + (m_up * 10000.0f);

	m_collision.IntersectPlane(normal, vertex, &m_vpos, &m_inormal);

	m_pop = m_vpos + (m_inormal * m_collision.m_length);

	m_y = m_pop - *vertex;

	m_y.Normalize();

	m_y = m_y.RotateAngleByAxis(rotation * DEG2RAD, normal);

	m_x = normal->Cross(&m_y);

	m_x.Normalize();

	*u = m_x.Dot(vertex);
	*v = m_y.Dot(vertex);
}

/*
*/
void CBrushSide::MakeVertex(CVec3f pop)
{
	// point-on-plane found earlier is a vertex that might need some adjusting

	// stash the integer value
	m_vi = (int32_t)pop.m_p.x;

	// get the decimal value
	m_vf = pop.m_p.x - m_vi;

	// rounding up
	if (fabs(m_vf) >= 0.5f)
	{
		if (m_vi >= 0.0f)
		{
			m_vi += 1;
		}
		else
		{
			m_vi -= 1;
		}

		pop.m_p.x = (float)m_vi;
	}
	else if (fabs(m_vf) <= EPSILON)
	{
		pop.m_p.x = (float)m_vi;
	}

	// doing it for y
	m_vi = (int32_t)pop.m_p.y;
	m_vf = pop.m_p.y - m_vi;

	if (fabs(m_vf) >= 0.5f)
	{
		if (m_vi >= 0.0f)
		{
			m_vi += 1;
		}
		else
		{
			m_vi -= 1;
		}

		pop.m_p.y = (float)m_vi;
	}
	else if (fabs(m_vf) <= EPSILON)
	{
		pop.m_p.y = (float)m_vi;
	}

	// doing it for z
	m_vi = (int32_t)pop.m_p.z;
	m_vf = pop.m_p.z - m_vi;

	if (fabs(m_vf) >= 0.5f)
	{
		if (m_vi >= 0.0f)
		{
			m_vi += 1;
		}
		else
		{
			m_vi -= 1;
		}

		pop.m_p.z = (float)m_vi;
	}
	else if (fabs(m_vf) <= EPSILON)
	{
		pop.m_p.z = (float)m_vi;
	}

	m_vertex[m_vertexCount].m_number = m_vertexCount;

	m_vertex[m_vertexCount].m_v.m_p = pop.m_p;

	m_vertex[m_vertexCount].m_v.m_n.x = m_normal.m_p.x;
	m_vertex[m_vertexCount].m_v.m_n.y = m_normal.m_p.y;
	m_vertex[m_vertexCount].m_v.m_n.z = m_normal.m_p.z;

	m_position = CVec3f(m_vertex[m_vertexCount].m_v.m_p);

	m_center.m_v.m_p.x += m_vertex[m_vertexCount].m_v.m_p.x;
	m_center.m_v.m_p.y += m_vertex[m_vertexCount].m_v.m_p.y;
	m_center.m_v.m_p.z += m_vertex[m_vertexCount].m_v.m_p.z;

	m_u = 0.0f;
	m_v = 0.0f;

	CBrushSide::MakeUVForVertex(&m_normal, &m_position, &m_u, &m_v, m_rotation);

	if (m_u < m_min.m_p.x)
	{
		m_min.m_p.x = m_u;
	}

	if (m_u > m_max.m_p.x)
	{
		m_max.m_p.x = m_u;
	}

	if (m_v < m_min.m_p.y)
	{
		m_min.m_p.y = m_v;
	}

	if (m_v > m_max.m_p.y)
	{
		m_max.m_p.y = m_v;
	}

	m_vertex[m_vertexCount].m_v.m_uv.x = m_u;
	m_vertex[m_vertexCount].m_v.m_uv.y = m_v;

	m_vertexCount++;
}

/*
*/
void CBrushSide::ParseScript(char* buffer)
{
	memset(m_texture, 0x00, CBrushSide::MAX_TEXTURE_NAME_LENGTH);

	sscanf_s(buffer, "( %f %f %f ) ( %f %f %f ) ( %f %f %f ) %s  %f %f %f   %f %f   %i %i %i",
		&m_v1.m_p.x,
		&m_v1.m_p.z,
		&m_v1.m_p.y,

		&m_v2.m_p.x,
		&m_v2.m_p.z,
		&m_v2.m_p.y,

		&m_v3.m_p.x,
		&m_v3.m_p.z,
		&m_v3.m_p.y,

		m_texture, CBrushSide::MAX_TEXTURE_NAME_LENGTH,

		&m_horizontalShift,
		& m_verticalShift,
		&m_rotation,

		&m_horizontalScale,
		&m_verticalScale,

		&m_surface1,
		&m_surface2,
		&m_surface3
	);

	memset(m_textureName, 0x00, CBrushSide::MAX_TEXTURE_NAME_LENGTH);

	memcpy(m_textureName, "textures/", 9);

	strncat_s(m_textureName, CBrushSide::MAX_TEXTURE_NAME_LENGTH, m_texture, strlen(m_texture));

	memset(m_texture, 0x00, CBrushSide::MAX_TEXTURE_NAME_LENGTH);

	memcpy(m_texture, m_textureName, strlen(m_textureName));

	m_normal = m_v1.Normal(&m_v3, &m_v2, &m_v1);

	CBrushSide::Plane();

	CBrushSide::ProcessShader();
}

/*
*/
void CBrushSide::Plane()
{
	m_plane.m_origin = m_v1;

	m_plane.m_normal = m_normal;

	m_plane.m_dist = m_plane.m_origin.Dot(&m_plane.m_normal);
}

/*
*/
void CBrushSide::PrintInfo() const
{
	printf("side:%i \n\n", m_number);

	printf("material:%i %s \n\n", m_shaderMaterial->m_number, m_shaderMaterial->m_name);

	printf("%f %f %f|", m_v1.m_p.x, m_v1.m_p.y, m_v1.m_p.z);
	printf("%f %f %f|", m_v2.m_p.x, m_v2.m_p.y, m_v2.m_p.z);
	printf("%f %f %f|", m_v3.m_p.x, m_v3.m_p.y, m_v3.m_p.z);

	printf("%f %f %f|", m_normal.m_p.x, m_normal.m_p.y, m_normal.m_p.z);

	printf("%s %i %i %i \n\n", m_texture, m_imageNumber, m_shaderImage->m_header->m_width, m_shaderImage->m_header->m_height);

	printf("min:\t%f %f \n", m_min.m_p.x, m_min.m_p.y);
	printf("max:\t%f %f \n\n", m_max.m_p.x, m_max.m_p.y);

	printf("center:\t%f %f %f|%f %f \n\n", m_center.m_v.m_p.x, m_center.m_v.m_p.y, m_center.m_v.m_p.z, m_center.m_v.m_uv.x, m_center.m_v.m_uv.y);

	for (int32_t i = 0; i < m_vertexCount; i++)
	{
		m_vertex[i].PrintInfo();
	}

	printf("\n");
}

/*
*/
void CBrushSide::ProcessShader()
{
	for (int32_t i = 0; i < *m_materialsCount; i++)
	{
		if (strcmp(m_materials[i].m_name, m_texture) == 0)
		{
			m_shaderMaterial = &m_materials[i];

			m_shaderImage = &m_images[i];

			m_imageNumber = i;

			return;
		}
	}

	for (int32_t i = 0; i < *m_masterMaterialsCount; i++)
	{
		if (strcmp(m_masterMaterials[i].m_name, m_texture) == 0)
		{
			m_imageNumber = *m_materialsCount;

			memcpy(&m_materials[m_imageNumber], &m_masterMaterials[i], sizeof(CShaderMaterial));

			memset(m_textureBuildName, 0x00, CBrushSide::MAX_TEXTURE_NAME_LENGTH);

			strncat_s(m_textureBuildName, CBrushSide::MAX_TEXTURE_NAME_LENGTH, m_local->m_installPath->m_text, m_local->m_installPath->m_length);
			strncat_s(m_textureBuildName, CBrushSide::MAX_TEXTURE_NAME_LENGTH, "main/", 5);
			strncat_s(m_textureBuildName, CBrushSide::MAX_TEXTURE_NAME_LENGTH, m_masterMaterials[i].m_map_Kd, strlen(m_masterMaterials[i].m_map_Kd));

			m_images[m_imageNumber].OnlyHeader(m_textureBuildName);

			m_shaderMaterial = &m_materials[m_imageNumber];

			m_shaderMaterial->m_number = m_imageNumber;

			m_shaderImage = &m_images[m_imageNumber];

			*m_materialsCount += 1;

			return;
		}
	}
}