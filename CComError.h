#pragma once

#include "framework.h"

class CComError
{
public:

	CComError();
	~CComError();

	wchar_t* GetComErrorMessage(HRESULT hr);
};