#include "CXAudio2Error.h"

/*
*/
CXAudio2Error::CXAudio2Error()
{
	memset(this, 0x00, sizeof(CXAudio2Error));

	m_errors = new CList();

	m_defaultError = new CXAudio2ErrorItem(0x00000000, "XUDIO2_UKNOWN_ERROR", "There is something wrong with the parameters of the call.");

	CXAudio2Error::AddItem(0x88960001, "XAUDIO2_E_INVALID_CALL", "Returned by XAudio2 for certain API usage errors (invalid calls and so on) that are hard to avoid completely and should be handled by a title at runtime. (API usage errors that are completely avoidable, such as invalid parameters, cause an ASSERT in debug builds and undefined behavior in retail builds, so no error code is defined for them.)");
	CXAudio2Error::AddItem(0x88960002, "XAUDIO2_E_XMA_DECODER_ERROR", "The Xbox 360 XMA hardware suffered an unrecoverable error.");
	CXAudio2Error::AddItem(0x88960003, "XAUDIO2_E_XAPO_CREATION_FAILED", "An effect failed to instantiate.");
	CXAudio2Error::AddItem(0x88960004, "XAUDIO2_E_DEVICE_INVALIDATED", "An audio device became unusable through being unplugged or some other event.");
}

/*
*/
CXAudio2Error::~CXAudio2Error()
{
	m_node = m_errors->m_list;

	while ((m_node) && (m_node->m_object))
	{
		m_XAudio2ErrorItem = (CXAudio2ErrorItem*)m_node->m_object;

		SAFE_DELETE(m_XAudio2ErrorItem);

		m_node = m_errors->Delete(m_node);
	}

	SAFE_DELETE(m_errors);

	SAFE_DELETE(m_defaultError);
}

/*
*/
void CXAudio2Error::AddItem(int32_t number, const char* code, const char* message)
{
	m_XAudio2ErrorItem = new CXAudio2ErrorItem(number, code, message);

	m_errors->Append(m_XAudio2ErrorItem, m_XAudio2ErrorItem->m_nbr);
}

/*
*/
CXAudio2ErrorItem* CXAudio2Error::GetError(int32_t error)
{
	m_node = m_errors->Search(error);

	if (m_node)
	{
		return (CXAudio2ErrorItem*)m_node->m_object;
	}

	return m_defaultError;
}