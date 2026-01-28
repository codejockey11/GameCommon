#include "CModelManager.h"

/*
*/
CModelManager::CModelManager()
{
	memset(this, 0x00, sizeof(CModelManager));

	m_models = new CList();
}

/*
*/
CModelManager::~CModelManager()
{
	m_node = m_models->m_list;

	while ((m_node) && (m_node->m_object))
	{
		m_model = (CModel*)m_node->m_object;

		SAFE_DELETE(m_model);

		m_node = m_models->Delete(m_node);
	}

	SAFE_DELETE(m_models);
}

/*
*/
CModel* CModelManager::Create(const char* filename)
{
	m_model = CModelManager::Get(filename);

	if (m_model)
	{
		return m_model;
	}

	m_model = new CModel(filename);

	if (m_model->m_isInitialized)
	{
		m_models->Add(m_model, filename);

		return m_model;
	}

	SAFE_DELETE(m_model);

	return nullptr;
}

/*
*/
void CModelManager::Delete(const char* filename)
{
	m_node = m_models->Search(filename);

	if (m_node)
	{
		m_model = (CModel*)m_node->m_object;

		SAFE_DELETE(m_model);

		m_models->Delete(m_node);
	}
}

/*
*/
CModel* CModelManager::Get(const char* filename)
{
	m_node = m_models->Search(filename);

	if (m_node)
	{
		return (CModel*)m_node->m_object;
	}

	return nullptr;
}