#include "CDirectoryList.h"
#include "CList.h"
#include "CString.h"

CDirectoryList* m_directoryList;

CListNode* m_node;

CString* m_shader;

CString* m_shaderFilename;

FILE* m_fShader = {};
FILE* m_fShaderList = {};

char prevShaderShortName[128] = {};
char shaderName[128] = {};
char shaderShortName[128] = {};
char shaderSurfaceName[128] = {};
char fileBuffer[128] = {};

int32_t textureNameStart = 0;

void MakeShaderName()
{
	memset(shaderName, 0x00, 128);
	memset(shaderShortName, 0x00, 128);
	memset(shaderSurfaceName, 0x00, 128);

	textureNameStart = 0;
	
	int32_t j = 0;
	int32_t k = 0;
	int32_t slashCount = 0;

	while (strncmp(&m_shader->m_text[textureNameStart], "textures", 8) != 0)
	{
		textureNameStart++;
	}

	for (int32_t x = 0; x < strlen(&m_shader->m_text[textureNameStart]) - 4; x++)
	{
		shaderName[x] = m_shader->m_text[textureNameStart + x];

		if (slashCount == 1)
		{
			if (m_shader->m_text[textureNameStart + x] != '/')
			{
				shaderSurfaceName[j] = m_shader->m_text[textureNameStart + x];

				j++;
			}
		}

		if (slashCount == 2)
		{
			if (m_shader->m_text[textureNameStart + x] != '/')
			{
				shaderShortName[k] = m_shader->m_text[textureNameStart + x];

				k++;
			}
		}

		if (shaderName[x] == '/')
		{
			slashCount++;
		}
	}
}

void MakeShaders()
{
	m_directoryList = new CDirectoryList();

	m_directoryList->LoadFromDirectory("C:/Users/junk_/source/repos/Game/main/textures/", "tga");

	m_node = m_directoryList->m_paths->m_list;

	m_shader = (CString*)m_node->m_object;

	MakeShaderName();

	strcpy_s(prevShaderShortName, 128, shaderSurfaceName);

	m_shaderFilename = new CString("./scripts/");
	m_shaderFilename->Append(shaderSurfaceName);
	m_shaderFilename->Append(".shader");

	printf("%s\n", m_shaderFilename->m_text);

	fopen_s(&m_fShader, m_shaderFilename->m_text, "wb");
	fopen_s(&m_fShaderList, "./scripts/shaderlist.txt", "wb");

	while ((m_node) && (m_node->m_object))
	{
		m_shader = (CString*)m_node->m_object;

		MakeShaderName();

		if (strcmp(shaderSurfaceName, prevShaderShortName) != 0)
		{
			printf("================================================================================\n");

			if (m_fShader)
			{
				fclose(m_fShader);
			}

			SAFE_DELETE(m_shaderFilename);

			m_shaderFilename = new CString("./scripts/");
			m_shaderFilename->Append(shaderSurfaceName);
			m_shaderFilename->Append(".shader");

			printf("%s\n", m_shaderFilename->m_text);

			fopen_s(&m_fShader, m_shaderFilename->m_text, "wb");

			if (m_fShaderList != 0)
			{
				memset(fileBuffer, 0x00, 128);
				sprintf_s(fileBuffer, 128, "%s\n", prevShaderShortName);
				fwrite(fileBuffer, strlen(fileBuffer), 1, m_fShaderList);
			}

			memset(prevShaderShortName, 0x00, 128);

			strcpy_s(prevShaderShortName, 128, shaderSurfaceName);
		}

		printf("%s\n", shaderName);
		printf("{\n");
		printf("\tsurface %s\n", shaderSurfaceName);
		printf("\timplicitMap %s\n", &m_shader->m_text[textureNameStart]);
		printf("}\n\n");

		if (m_fShader != 0)
		{
			memset(fileBuffer, 0x00, 128);
			sprintf_s(fileBuffer, 128, "%s\n", shaderName);
			fwrite(fileBuffer, strlen(fileBuffer), 1, m_fShader);

			memset(fileBuffer, 0x00, 128);
			sprintf_s(fileBuffer, 128, "{\n");
			fwrite(fileBuffer, strlen(fileBuffer), 1, m_fShader);

			memset(fileBuffer, 0x00, 128);
			sprintf_s(fileBuffer, 128, "\tsurface %s\n", shaderSurfaceName);
			fwrite(fileBuffer, strlen(fileBuffer), 1, m_fShader);

			memset(fileBuffer, 0x00, 128);
			sprintf_s(fileBuffer, 128, "\timplicitMap %s\n", &m_shader->m_text[textureNameStart]);
			fwrite(fileBuffer, strlen(fileBuffer), 1, m_fShader);

			memset(fileBuffer, 0x00, 128);
			sprintf_s(fileBuffer, 128, "}\n\n");
			fwrite(fileBuffer, strlen(fileBuffer), 1, m_fShader);
		}

		m_node = m_node->m_next;
	}

	if (m_fShaderList != 0)
	{
		memset(fileBuffer, 0x00, 128);
		sprintf_s(fileBuffer, 128, "%s\n", prevShaderShortName);
		fwrite(fileBuffer, strlen(fileBuffer), 1, m_fShaderList);
	}

	if (m_fShader)
	{
		fclose(m_fShader);
	}

	if (m_fShaderList)
	{
		fclose(m_fShaderList);
	}

	SAFE_DELETE(m_directoryList);
}

int32_t main()
{

	return 0;
}