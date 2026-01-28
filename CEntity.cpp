#include "CEntity.h"

/*
*/
CEntity::CEntity()
{
	memset(this, 0x00, sizeof(CEntity));
}

/*
*/
CEntity::~CEntity()
{
	if (m_brushes)
	{
		m_node = m_brushes->m_list;

		while ((m_node) && (m_node->m_object))
		{
			m_brush = (CBrush*)m_node->m_object;

			SAFE_DELETE(m_brush);

			m_node = m_brushes->Delete(m_node);
		}

		SAFE_DELETE(m_brushes);
	}

	SAFE_DELETE_ARRAY(m_keyValue);
}

/*
*/
void CEntity::AddKeyValue(const char* key, const char* value)
{
	m_keyValue[m_keyValueCount].SetKey(key);
	m_keyValue[m_keyValueCount].SetValue(value);

	if (strncmp(m_keyValue[m_keyValueCount].m_key, "classname", 9) == 0)
	{
		if (strncmp(m_keyValue[m_keyValueCount].m_value, "worldspawn", 10) == 0)
		{
			m_type = CEntity::Type::WORLDSPAWN;

			m_brushes = new CList();
		}
		else if (strncmp(m_keyValue[m_keyValueCount].m_value, "infoPlayerStart", 10) == 0)
		{
			m_type = CEntity::Type::INFOPLAYERSTART;
		}
		else if (strncmp(m_keyValue[m_keyValueCount].m_value, "collectable", 11) == 0)
		{
			m_type = CEntity::Type::COLLECTABLE;
		}
		else if (strncmp(m_keyValue[m_keyValueCount].m_value, "staticModel", 11) == 0)
		{
			m_type = CEntity::Type::STATICMODEL;
		}
		else if (strncmp(m_keyValue[m_keyValueCount].m_value, "terrain", 7) == 0)
		{
			m_type = CEntity::Type::TERRAIN;
		}
		else if (strncmp(m_keyValue[m_keyValueCount].m_value, "light", 5) == 0)
		{
			m_type = CEntity::Type::LIGHT;
		}
		else if (strncmp(m_keyValue[m_keyValueCount].m_value, "projector", 9) == 0)
		{
			m_type = CEntity::Type::PROJECTOR;
		}
	}

	m_keyValueCount++;
}

/*
*/
bool CEntity::Constructor(int32_t keyValueCount)
{
	if (keyValueCount > 0)
	{
		m_keyValue = new CKeyValue[keyValueCount]();
	}
	else
	{
		m_keyValue = new CKeyValue[CEntity::MAX_KEY_VALUE]();
	}

	return true;
}

/*
*/
void CEntity::GetKeyValue(const char* key, char** value)
{
	for (int32_t i = 0; i < m_keyValueCount; i++)
	{
		if (strncmp(m_keyValue[i].m_key, key, strlen(key)) == 0)
		{
			*value = m_keyValue[i].m_value;

			break;
		}
	}
}

/*
*/
void CEntity::GetKeyValue(const char* key, int32_t* value)
{
	for (int32_t i = 0; i < m_keyValueCount; i++)
	{
		if (strncmp(m_keyValue[i].m_key, key, strlen(key)) == 0)
		{
			*value = atoi(m_keyValue[i].m_value);

			break;
		}
	}
}

/*
*/
void CEntity::GetKeyValue(const char* key, float* value)
{
	for (int32_t i = 0; i < m_keyValueCount; i++)
	{
		if (strncmp(m_keyValue[i].m_key, key, strlen(key)) == 0)
		{
			*value = (float)atof(m_keyValue[i].m_value);

			break;
		}
	}
}

/*
*/
void CEntity::GetKeyValue(const char* key, CVec3f* vec3f)
{
	for (int32_t i = 0; i < m_keyValueCount; i++)
	{
		if (strncmp(m_keyValue[i].m_key, key, strlen(key)) == 0)
		{
			sscanf_s(m_keyValue[i].m_value, "%f %f %f", &m_vec3f.m_p.x, &m_vec3f.m_p.y, &m_vec3f.m_p.z);

			memcpy(vec3f, &m_vec3f, sizeof(CVec3f));

			break;
		}
	}
}

/*
*/
void CEntity::GetKeyValue(const char* key, CVec3i* vec3i)
{
	for (int32_t i = 0; i < m_keyValueCount; i++)
	{
		if (strncmp(m_keyValue[i].m_key, key, strlen(key)) == 0)
		{
			sscanf_s(m_keyValue[i].m_value, "%i %i %i", &m_vec3i.m_p.x, &m_vec3i.m_p.y, &m_vec3i.m_p.z);

			memcpy(vec3i, &m_vec3i, sizeof(CVec3i));

			break;
		}
	}
}

/*
*/
void CEntity::WriteKeyValues(FILE* file)
{
	fwrite(&m_number, sizeof(int32_t), 1, file);
	fwrite(&m_type, sizeof(unsigned char), 1, file);
	fwrite(&m_keyValueCount, sizeof(int32_t), 1, file);

	for (int32_t i = 0; i < m_keyValueCount; i++)
	{
		fwrite(m_keyValue[i].m_key, 1, CKeyValue::MAX_KEY, file);
		fwrite(m_keyValue[i].m_value, 1, CKeyValue::MAX_VALUE, file);
	}
}