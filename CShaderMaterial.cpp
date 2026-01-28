#include "CShaderMaterial.h"

/*
*/
CShaderMaterial::CShaderMaterial()
{
	memset(this, 0x00, sizeof(CShaderMaterial));
}

/*
*/
CShaderMaterial::~CShaderMaterial()
{

}

/*
*/
void CShaderMaterial::Setd(float i)
{
	m_opticalDensity = i;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetIllum(int32_t i)
{
	m_illum = i;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetKa(float r, float g, float b, float a)
{
	m_ambient.x = r;
	m_ambient.y = g;
	m_ambient.z = b;
	m_ambient.w = a;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetKd(float r, float g, float b, float a)
{
	m_diffuse.x = r;
	m_diffuse.y = g;
	m_diffuse.z = b;
	m_diffuse.w = a;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetKe(float r, float g, float b, float a)
{
	m_emissive.x = r;
	m_emissive.y = g;
	m_emissive.z = b;
	m_emissive.w = a;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetKs(float r, float g, float b, float a)
{
	m_specular.x = r;
	m_specular.y = g;
	m_specular.z = b;
	m_specular.w = a;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetMapBump(char* s)
{
	strcpy_s(m_map_bump, E_TEXTURE_NAME, s);

	m_hasmap_bump = 1;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetMapD(char* s)
{
	strcpy_s(m_map_d, E_TEXTURE_NAME, s);

	m_hasmap_d = 1;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetMapKa(char* s)
{
	strcpy_s(m_map_Ka, E_TEXTURE_NAME, s);

	m_hasmap_Ka = 1;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetMapKd(char* s)
{
	strcpy_s(m_map_Kd, E_TEXTURE_NAME, s);

	m_hasmap_Kd = 1;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetMapKs(char* s)
{
	strcpy_s(m_map_Ks, E_TEXTURE_NAME, s);

	m_hasmap_Ks = 1;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetMapNs(char* s)
{
	strcpy_s(m_map_Ns, E_TEXTURE_NAME, s);

	m_hasmap_Ns = 1;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetName(char* s)
{
	strcpy_s(m_name, E_TEXTURE_NAME, s);
}

/*
*/
void CShaderMaterial::SetNi(float i)
{
	m_opacity = i;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetNs(float i)
{
	m_specularExponent = i;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetNumber(int32_t i)
{
	m_number = i;

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetShaderMaterial(CShaderMaterial* shaderMaterial)
{
	m_number = shaderMaterial->m_number;

	m_ambient = shaderMaterial->m_ambient;
	m_diffuse = shaderMaterial->m_diffuse;
	m_emissive = shaderMaterial->m_emissive;
	m_specular = shaderMaterial->m_specular;
	m_illum = shaderMaterial->m_illum;
	m_opacity = shaderMaterial->m_opacity;
	m_opticalDensity = shaderMaterial->m_opticalDensity;
	m_specularExponent = shaderMaterial->m_specularExponent;

	CShaderMaterial::SetMapBump(shaderMaterial->m_map_bump);
	CShaderMaterial::SetMapD(shaderMaterial->m_map_d);
	CShaderMaterial::SetMapKa(shaderMaterial->m_map_Ka);
	CShaderMaterial::SetMapKd(shaderMaterial->m_map_Kd);
	CShaderMaterial::SetMapKs(shaderMaterial->m_map_Ks);
	CShaderMaterial::SetMapNs(shaderMaterial->m_map_Ns);
	CShaderMaterial::SetName(shaderMaterial->m_name);

	m_needsUpload = true;
}

/*
*/
void CShaderMaterial::SetSurface(char* surface, int32_t v)
{
	if (strncmp(surface, "alpha", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_ALPHA;
	}
	else if (strncmp(surface, "block", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_BLOCK;
	}
	else if (strncmp(surface, "brick", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_BRICK;
	}
	else if (strncmp(surface, "common", 6) == 0)
	{
		m_surface ^= v << E_SURFACE_COMMON;
	}
	else if (strncmp(surface, "concrete", 8) == 0)
	{
		m_surface ^= v << E_SURFACE_CONCRETE;
	}
	else if (strncmp(surface, "dirt", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_DIRT;
	}
	else if (strncmp(surface, "door", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_DOOR;
	}
	else if (strncmp(surface, "effect", 6) == 0)
	{
		m_surface ^= v << E_SURFACE_EFFECT;
	}
	else if (strncmp(surface, "environment", 11) == 0)
	{
		m_surface ^= v << E_SURFACE_ENVIRONMENT;
	}
	else if (strncmp(surface, "fire", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_FIRE;
	}
	else if (strncmp(surface, "floor", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_FLOOR;
	}
	else if (strncmp(surface, "grass", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_GRASS;
	}
	else if (strncmp(surface, "grate", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_GRATE;
	}
	else if (strncmp(surface, "house", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_HOUSE;
	}
	else if (strncmp(surface, "light", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_LIGHT;
	}
	else if (strncmp(surface, "metal", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_METAL;
	}
	else if (strncmp(surface, "misc", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_MISC;
	}
	else if (strncmp(surface, "props", 5) == 0)
	{
		m_surface ^= v << E_SURFACE_PROPS;
	}
	else if (strncmp(surface, "radiant", 7) == 0)
	{
		m_surface ^= v << E_SURFACE_RADIANT;
	}
	else if (strncmp(surface, "road", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_ROAD;
	}
	else if (strncmp(surface, "rock", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_ROCK;
	}
	else if (strncmp(surface, "sand", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_SAND;
	}
	else if (strncmp(surface, "snow", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_SNOW;
	}
	else if (strncmp(surface, "trim", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_TRIM;
	}
	else if (strncmp(surface, "wall", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_WALL;
	}
	else if (strncmp(surface, "window", 6) == 0)
	{
		m_surface ^= v << E_SURFACE_WINDOW;
	}
	else if (strncmp(surface, "wood", 4) == 0)
	{
		m_surface ^= v << E_SURFACE_WOOD;
	}
}