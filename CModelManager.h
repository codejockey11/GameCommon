#pragma once

#include "framework.h"

#include "CList.h"
#include "CModel.h"

class CModelManager
{
public:
	
	CList* m_models;
	CListNode* m_node;
	CModel* m_model;

	CModelManager();
	~CModelManager();

	CModel* Create(const char* filename);
	void Delete(const char* filename);
	CModel* Get(const char* filename);
};