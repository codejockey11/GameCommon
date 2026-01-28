#include "CModel.h"

/*
*/
CModel::CModel()
{
	memset(this, 0x00, sizeof(CModel));
}

/*
*/
CModel::CModel(const char* filename)
{
	memset(this, 0x00, sizeof(CModel));

	m_name = new CString(filename);

	m_err = fopen_s(&m_file, filename, "rb");

	if (m_err != 0)
	{
		return;
	}

	m_meshs = new CList();

	fread_s(&m_materialCount, sizeof(int32_t), sizeof(int32_t), 1, m_file);

	for (int32_t i = 0; i < m_materialCount; i++)
	{
		m_mesh = new CMesh();

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		m_buffer = new char[m_length + 1]();

		fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

		SAFE_DELETE_ARRAY(m_buffer);

		fread_s(&m_skipXMFLOAT3, sizeof(XMFLOAT3), sizeof(XMFLOAT3), 1, m_file);
		fread_s(&m_skipXMFLOAT3, sizeof(XMFLOAT3), sizeof(XMFLOAT3), 1, m_file);
		fread_s(&m_skipXMFLOAT3, sizeof(XMFLOAT3), sizeof(XMFLOAT3), 1, m_file);
		fread_s(&m_skipXMFLOAT3, sizeof(XMFLOAT3), sizeof(XMFLOAT3), 1, m_file);
		fread_s(&m_skipfloat, sizeof(float), sizeof(float), 1, m_file);
		fread_s(&m_skipfloat, sizeof(float), sizeof(float), 1, m_file);
		fread_s(&m_skipUINT, sizeof(int32_t), sizeof(int32_t), 1, m_file);
		fread_s(&m_skipfloat, sizeof(float), sizeof(float), 1, m_file);

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		if (m_length > 0)
		{
			m_buffer = new char[m_length + 1]();

			fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

			SAFE_DELETE_ARRAY(m_buffer);
		}

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		if (m_length > 0)
		{
			m_buffer = new char[m_length + 1]();

			fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

			SAFE_DELETE_ARRAY(m_buffer);
		}

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		if (m_length > 0)
		{
			m_buffer = new char[m_length + 1]();

			fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

			SAFE_DELETE_ARRAY(m_buffer);
		}

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		if (m_length > 0)
		{
			m_buffer = new char[m_length + 1]();

			fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

			SAFE_DELETE_ARRAY(m_buffer);
		}

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		if (m_length > 0)
		{
			m_buffer = new char[m_length + 1]();

			fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

			SAFE_DELETE_ARRAY(m_buffer);
		}

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		if (m_length > 0)
		{
			m_buffer = new char[m_length + 1]();

			fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

			SAFE_DELETE_ARRAY(m_buffer);
		}

		fread_s(&m_length, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		if (m_length > 0)
		{
			m_buffer = new char[m_length + 1]();

			fread_s(m_buffer, sizeof(char) * m_length, sizeof(char), m_length, m_file);

			SAFE_DELETE_ARRAY(m_buffer);
		}

		fread_s(&m_mesh->m_vertexCount, sizeof(int32_t), sizeof(int32_t), 1, m_file);

		m_bufferSize = m_mesh->m_vertexCount * sizeof(CVertexNT);

		m_mesh->m_vertices = new BYTE[m_bufferSize];

		fread_s(m_mesh->m_vertices, sizeof(BYTE) * m_bufferSize, sizeof(BYTE), m_bufferSize, m_file);

		m_meshs->Add(m_mesh, nullptr);
	}
	
	fclose(m_file);

	m_isInitialized = true;
}

/*
*/
CModel::~CModel()
{
	m_node = m_meshs->m_list;

	while ((m_node) && (m_node->m_object))
	{
		m_mesh = (CMesh*)m_node->m_object;

		SAFE_DELETE(m_mesh);

		m_node = m_meshs->Delete(m_node);
	}

	SAFE_DELETE(m_meshs);

	SAFE_DELETE(m_name);
}