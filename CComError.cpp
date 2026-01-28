#include "CComError.h"

/*
*/
CComError::CComError()
{
	memset(this, 0x00, sizeof(CComError));
}

/*
*/
CComError::~CComError()
{

}

/*
*/
wchar_t* CComError::GetComErrorMessage(HRESULT hr)
{
	_com_error err(hr);

	return (wchar_t*)err.ErrorMessage();
}