#pragma once

#include "framework.h"

#include "CBrushSide.h"
#include "CBrushSideIntersection.h"
#include "CCollision.h"
#include "CLocal.h"
#include "CScript.h"
#include "CShaderMaterial.h"
#include "CTgaImage.h"

class CBrush
{
public:

	CBrushSide m_brushSide[MAX_SIDES];
	CBrushSideIntersection m_brushSideIntersection;
	CBrushSideIntersection m_returnSide;
	CCollision m_collision;
	CLine3D m_line;
	CLocal* m_local;
	CScript* m_mapScript;
	CShaderMaterial* m_masterMaterials;
	CShaderMaterial* m_materials;
	CTgaImage* m_images;
	CVec3f m_startPoint;

	FILE* m_fCollision;
	FILE* m_fMap;

	float m_minLength;
	float m_ndn;
	float m_nearest;

	int32_t m_nextSide;
	int32_t m_number;
	int32_t m_sideCount;
	int32_t m_sideIndex;

	int32_t* m_masterMaterialsCount;
	int32_t* m_materialsCount;

	CBrush();
	~CBrush();

	void BuildSides();
	CBrushSideIntersection FindNearestIntersection(CBrushSide* brushSide);
	void FindStartingSide(CBrushSide* brushSide);
	void ParseScript();
	void PrintInfo() const;
};