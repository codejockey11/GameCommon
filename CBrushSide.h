#pragma once

#include "framework.h"

#include "CCollision.h"
#include "CLocal.h"
#include "CPlane.h"
#include "CShaderMaterial.h"
#include "CTgaImage.h"
#include "CVec3f.h"
#include "CVertex.h"

class CBrushSide
{
public:

	enum
	{
		MAX_VERTICES = 32,
		MAX_TEXTURE_NAME_LENGTH = 128
	};

	bool m_wasFirstSide;

	CCollision m_collision;

	char m_texture[CBrushSide::MAX_TEXTURE_NAME_LENGTH];
	char m_textureBuildName[CBrushSide::MAX_TEXTURE_NAME_LENGTH];
	char m_textureName[CBrushSide::MAX_TEXTURE_NAME_LENGTH];

	CLocal* m_local;;
	CPlane m_plane;
	CShaderMaterial* m_masterMaterials;
	CShaderMaterial* m_materials;
	CShaderMaterial* m_shaderMaterial;
	CTgaImage* m_images;
	CTgaImage* m_shaderImage;
	CVec3f m_inormal;
	CVec3f m_max;
	CVec3f m_min;
	CVec3f m_normal;
	CVec3f m_pop;
	CVec3f m_position;
	CVec3f m_up;
	CVec3f m_v1;
	CVec3f m_v2;
	CVec3f m_v3;
	CVec3f m_vpos;
	CVec3f m_x;
	CVec3f m_y;
	CVertex m_center;
	CVertex m_vertex[CBrushSide::MAX_VERTICES];

	float m_height;
	float m_heightShifted;
	float m_horizontalScale;
	float m_horizontalShift;
	float m_ndu;
	float m_rotation;
	float m_textureHeightScaled;
	float m_textureWidthScaled;
	float m_tileX;
	float m_tileY;
	float m_u;
	float m_v;
	float m_verticalScale;
	float m_verticalShift;
	float m_vf;
	float m_width;
	float m_widthShifted;

	int32_t m_imageNumber;
	int32_t m_number;
	int32_t m_surface1;
	int32_t m_surface2;
	int32_t m_surface3;
	int32_t m_vertexCount;
	int32_t m_vi;

	int32_t* m_masterMaterialsCount;
	int32_t* m_materialsCount;

	CBrushSide();
	~CBrushSide();

	void CenterUVCoordinate();
	void FinalizeUVCoordinates();
	void MakeUVForVertex(CVec3f* normal, CVec3f* vertex, float* u, float* v, float rotation);
	void MakeVertex(CVec3f pop);
	void ParseScript(char* buffer);
	void Plane();
	void PrintInfo() const;
	void ProcessShader();
};