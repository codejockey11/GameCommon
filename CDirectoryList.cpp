#include "CDirectoryList.h"

/*
*/
CDirectoryList::CDirectoryList()
{
	memset(this, 0x00, sizeof(CDirectoryList));

    m_paths = new CList();
    
    m_filenames = new CList();
}

/*
*/
CDirectoryList::~CDirectoryList()
{
    CDirectoryList::Clear();
    
    SAFE_DELETE(m_filenames);
    SAFE_DELETE(m_paths);
}

/*
*/
void CDirectoryList::Clear()
{
    m_node = m_paths->m_list;

    while ((m_node) && (m_node->m_object))
    {
        m_path = (CString*)m_node->m_object;

        SAFE_DELETE(m_path);

        m_node = m_paths->Delete(m_node);
    }

    m_node = m_filenames->m_list;

    while ((m_node) && (m_node->m_object))
    {
        m_filename = (CString*)m_node->m_object;

        SAFE_DELETE(m_filename);

        m_node = m_filenames->Delete(m_node);
    }
}

/*
*/
void CDirectoryList::LoadFromDirectory(const char* directory, const char* fileExtension)
{
    WIN32_FIND_DATAA fdFile = {};
    
    HANDLE hFind = NULL;

    char path[MAX_PATH] = {};

    sprintf_s(path, MAX_PATH, "%s*.*", directory);

    if ((hFind = FindFirstFileA(path, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        return;
    }

    while (FindNextFileA(hFind, &fdFile))
    {
        if (strncmp(fdFile.cFileName, ".", 1) != 0 && strncmp(fdFile.cFileName, "..", 2) != 0)
        {
            if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                sprintf_s(path, MAX_PATH, "%s%s/", directory, fdFile.cFileName);

                CDirectoryList::LoadFromDirectory(path, fileExtension);
            }
            else
            {
                sprintf_s(path, MAX_PATH, "%s%s", directory, fdFile.cFileName);

                CString* pathname = new CString(path);
                CString* filename = new CString(fdFile.cFileName);

                if (strlen(fileExtension) > 0)
                {
                    char* r = strstr(path, fileExtension);

                    if (r != 0)
                    {
                        m_paths->Add(pathname, pathname->m_text);
                        
                        m_filenames->Add(filename, filename->m_text);
                    }
                }
                else
                {
                    m_paths->Add(pathname, pathname->m_text);

                    m_filenames->Add(filename, filename->m_text);
                }
            }
        }
    }

    FindClose(hFind);
}

/*
*/
void CDirectoryList::Reset()
{
    if (m_paths)
    {
        CDirectoryList::Clear();
    }
}