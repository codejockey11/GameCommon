#include "CCollisionPrimitive.h"

/*
*/
CCollisionPrimitive::CCollisionPrimitive()
{
	memset(this, 0x00, sizeof(CCollisionPrimitive));
}

/*
*/
CCollisionPrimitive::~CCollisionPrimitive()
{

}

/*
*/
void CCollisionPrimitive::ReadPrimitive(FILE* file)
{
	fread_s(&m_surface, sizeof(int32_t), sizeof(int32_t), 1, file);
	
	fread_s(&m_a, sizeof(CVec3f), sizeof(CVec3f), 1, file);
	fread_s(&m_b, sizeof(CVec3f), sizeof(CVec3f), 1, file);
	fread_s(&m_c, sizeof(CVec3f), sizeof(CVec3f), 1, file);
	fread_s(&m_n, sizeof(CVec3f), sizeof(CVec3f), 1, file);
}

/*
*/
void CCollisionPrimitive::WritePrimitive(FILE* file)
{
	fwrite(&m_surface, sizeof(int32_t), 1, file);

	fwrite(&m_a, sizeof(CVec3f), 1, file);
	fwrite(&m_b, sizeof(CVec3f), 1, file);
	fwrite(&m_c, sizeof(CVec3f), 1, file);
	fwrite(&m_n, sizeof(CVec3f), 1, file);
}