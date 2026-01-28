#pragma once

#include "framework.h"

class CShaderMaterial
{
public:

	enum
	{
		E_MATERIAL_NAME = 128,
		E_TEXTURE_NAME = 128
	};

	enum Surface
	{
		E_SURFACE_ALPHA = 0,
		E_SURFACE_BLOCK,
		E_SURFACE_BRICK,
		E_SURFACE_COMMON,
		E_SURFACE_CONCRETE,
		E_SURFACE_DIRT,
		E_SURFACE_DOOR,
		E_SURFACE_EFFECT,
		E_SURFACE_ENVIRONMENT,
		E_SURFACE_FIRE,
		E_SURFACE_FLOOR,
		E_SURFACE_GRASS,
		E_SURFACE_GRATE,
		E_SURFACE_HOUSE,
		E_SURFACE_LIGHT,
		E_SURFACE_METAL,
		E_SURFACE_MISC,
		E_SURFACE_PROPS,
		E_SURFACE_RADIANT,
		E_SURFACE_ROAD,
		E_SURFACE_ROCK,
		E_SURFACE_SAND,
		E_SURFACE_SNOW,
		E_SURFACE_TRIM,
		E_SURFACE_WALL,
		E_SURFACE_WINDOW,
		E_SURFACE_WOOD
	};

	bool m_needsUpload;

	char m_map_bump[E_TEXTURE_NAME];
	char m_map_d[E_TEXTURE_NAME];
	char m_map_Ka[E_TEXTURE_NAME];
	char m_map_Kd[E_TEXTURE_NAME];
	char m_map_Ks[E_TEXTURE_NAME];
	char m_map_Ns[E_TEXTURE_NAME];
	char m_name[E_MATERIAL_NAME];
	char m_refl[E_TEXTURE_NAME];

	float m_opacity;
	float m_opticalDensity;
	float m_specularExponent;

	int32_t m_hasmap_bump;
	int32_t m_hasmap_d;
	int32_t m_hasmap_Ka;
	int32_t m_hasmap_Kd;
	int32_t m_hasmap_Ks;
	int32_t m_hasmap_Ns;

	int32_t m_illum;
	int32_t m_number;
	int32_t m_surface;

	XMFLOAT4 m_ambient;
	XMFLOAT4 m_diffuse;
	XMFLOAT4 m_emissive;
	XMFLOAT4 m_specular;

	CShaderMaterial();
	~CShaderMaterial();

	void Setd(float i);
	void SetIllum(int32_t i);
	void SetKa(float r, float g, float b, float a);
	void SetKd(float r, float g, float b, float a);
	void SetKe(float r, float g, float b, float a);
	void SetKs(float r, float g, float b, float a);
	void SetMapBump(char* s);
	void SetMapD(char* s);
	void SetMapKa(char* s);
	void SetMapKd(char* s);
	void SetMapKs(char* s);
	void SetMapNs(char* s);
	void SetName(char* s);
	void SetNi(float i);
	void SetNs(float i);
	void SetNumber(int32_t i);
	void SetShaderMaterial(CShaderMaterial* material);
	void SetSurface(char* surface, int32_t v);
};