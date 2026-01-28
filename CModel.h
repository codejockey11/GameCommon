#pragma once

#include "framework.h"

#include "CList.h"
#include "CMesh.h"
#include "CString.h"
#include "CVec3f.h"
#include "CVertexNT.h"

class CModel
{
public:

	enum
	{
		E_MATERIAL_NAME_LENGTH = 256
	};

	bool m_isInitialized;

	char* m_buffer;

	CList* m_meshs;
	CListNode* m_node;
	CMesh* m_mesh;
	CString* m_name;

	errno_t m_err;

	FILE* m_file;

	float m_skipfloat;

	short m_length;
	short m_materialCount;

	size_t m_bufferSize;

	int32_t m_skipUINT;

	XMFLOAT3 m_skipXMFLOAT3;

	CModel();
	CModel(const char* filename);
	~CModel();
};