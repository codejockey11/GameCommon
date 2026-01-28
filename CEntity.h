#pragma once

#include "framework.h"

#include "CBrush.h"
#include "CKeyValue.h"
#include "CList.h"
#include "CVec3f.h"
#include "CVec3i.h"

class CEntity
{
public:

	enum
	{
		MAX_KEY_VALUE = 32
	};

	enum Type
	{
		WORLDSPAWN = 0,
		INFOPLAYERSTART,
		COLLECTABLE,
		STATICMODEL,
		TERRAIN,
		LIGHT,
		PROJECTOR,
		MAX_TYPE
	};

	CKeyValue* m_keyValue;
	CList* m_brushes;
	CListNode* m_node;
	CBrush* m_brush;
	CVec3f m_vec3f;
	CVec3i m_vec3i;

	int32_t m_keyValueCount;
	int32_t m_number;

	unsigned char m_type;

	CEntity();
	~CEntity();

	void AddKeyValue(const char* key, const char* value);
	bool Constructor(int32_t keyValueCount);
	void GetKeyValue(const char* key, char** value);
	void GetKeyValue(const char* key, CVec3f* v);
	void GetKeyValue(const char* key, CVec3i* v);
	void GetKeyValue(const char* key, float* value);
	void GetKeyValue(const char* key, int32_t* value);
	void WriteKeyValues(FILE* map);
};