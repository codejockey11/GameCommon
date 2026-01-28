#include "CMesh.h"

/*
*/
CMesh::CMesh()
{
	memset(this, 0x00, sizeof(CMesh));
}

/*
*/
CMesh::~CMesh()
{
	SAFE_DELETE_ARRAY(m_vertices);
}

/*
*/
void CMesh::SetBuffer(BYTE* vertices, int32_t count)
{
	SAFE_DELETE_ARRAY(m_vertices);

	m_vertexCount = count;

	m_bufferSize = sizeof(CVertexNT) * m_vertexCount;

	m_vertices = new BYTE[m_bufferSize]();

	memcpy(m_vertices, vertices, m_bufferSize);
}

/*
*/
void CMesh::SetMaterial(CShaderMaterial* shaderMaterial)
{
	m_material.SetShaderMaterial(shaderMaterial);
}