#pragma once

#include "framework.h"

#include "CVec3f.h"

class CCamera
{
public:

	enum
	{
		E_LH = 0,
		E_RH
	};

	bool m_isInitialized;

	BYTE m_type;

	float m_farPlane;
	float m_fov;
	float m_height;
	float m_nearPlane;
	float m_pitch;
	float m_ratio;
	float m_roll;
	float m_width;
	float m_yaw;

	XMFLOAT3 m_look;
	XMFLOAT3 m_position;
	XMFLOAT3 m_right;
	XMFLOAT3 m_rotation;
	XMFLOAT3 m_up;

	XMFLOAT4X4 m_xmfproj;
	XMFLOAT4X4 m_xmfview;
	XMFLOAT4X4 m_xmfworld;

	XMMATRIX m_twvpMat;
	XMMATRIX m_wvpMat;
	XMMATRIX m_xmMatrix;
	XMMATRIX m_xmproj;
	XMMATRIX m_xmview;
	XMMATRIX m_xmworld;

	XMVECTOR m_xmvlook;
	XMVECTOR m_xmvposition;
	XMVECTOR m_xmvup;

	CCamera();
	~CCamera();

	void Constructor(float width, float height, CVec3f* position, float fov, float nearPlane, float farPlane, float ratio);

	void Copy(CCamera* camera);
	void SetPosition(CVec3f* position);
	void UpdateRotation(float x, float y, float z);
	void UpdateView();
};