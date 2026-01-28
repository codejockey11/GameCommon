#pragma once

#include "framework.h"

#include "CShaderMaterial.h"
#include "CVertexNT.h"

class CMesh
{
public:

	BYTE* m_vertices;

	CShaderMaterial m_material;

	int32_t m_bufferSize;
	int32_t m_vertexCount;

	CMesh();
	~CMesh();

	void SetBuffer(BYTE* vertices, int32_t count);
	void SetMaterial(CShaderMaterial* shaderMaterial);
};