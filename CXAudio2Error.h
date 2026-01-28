#pragma once

#include "framework.h"

#include "CList.h"
#include "CXAudio2ErrorItem.h"

class CXAudio2Error
{
public:

	CList* m_errors;
	CListNode* m_node;
	CXAudio2ErrorItem* m_defaultError;
	CXAudio2ErrorItem* m_XAudio2ErrorItem;

	CXAudio2Error();
	~CXAudio2Error();

	void AddItem(int32_t number, const char* code, const char* message);
	CXAudio2ErrorItem* GetError(int32_t error);
};