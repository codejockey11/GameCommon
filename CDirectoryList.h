#pragma once

#include "framework.h"

#include "CList.h"
#include "CString.h"

class CDirectoryList
{
public:

	CList* m_filenames;
	CList* m_paths;
	CListNode* m_node;
	CString* m_filename;
	CString* m_path;

	CDirectoryList();
	~CDirectoryList();

	void Clear();
	void LoadFromDirectory(const char* directory, const char* fileExtension);
	void Reset();
};