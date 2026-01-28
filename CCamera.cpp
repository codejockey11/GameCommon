#include "CCamera.h"

/*
*/
CCamera::CCamera()
{
	memset(this, 0x00, sizeof(CCamera));
}

/*
*/
void CCamera::Constructor(float width, float height, CVec3f* position, float fov, float nearPlane, float farPlane, float ratio)
{
	memset(this, 0x00, sizeof(CCamera));

	m_width = width;

	m_height = height;

	CCamera::SetPosition(position);

	m_fov = fov;

	m_nearPlane = nearPlane;
	
	m_farPlane = farPlane;

	m_ratio = ratio;

	m_type = CCamera::E_LH;

	m_xmworld = XMMatrixIdentity();

	XMStoreFloat4x4(&m_xmfworld, m_xmworld);

	switch (m_type)
	{
	case CCamera::E_LH:
	{
		m_xmproj = XMMatrixPerspectiveFovLH(fov * (float)M_PI / 180.0f, m_ratio, nearPlane, farPlane);

		break;
	}
	case CCamera::E_RH:
	{
		m_xmproj = XMMatrixPerspectiveFovRH(fov * (float)M_PI / 180.0f, m_ratio, nearPlane, farPlane);

		break;
	}
	}

	XMStoreFloat4x4(&m_xmfproj, m_xmproj);

	CCamera::UpdateView();
	
	m_isInitialized = true;
}

/*
*/
CCamera::~CCamera()
{

}

/*
*/
void CCamera::Copy(CCamera* camera)
{
	m_xmworld = camera->m_xmworld;

	m_xmproj = camera->m_xmproj;

	m_position = camera->m_position;

	m_rotation = camera->m_rotation;

	CCamera::UpdateView();
}

/*
*/
void CCamera::SetPosition(CVec3f* position)
{
	m_position.x = position->m_p.x;
	m_position.y = position->m_p.y;
	m_position.z = position->m_p.z;
}

/*
*/
void CCamera::UpdateRotation(float x, float y, float z)
{
	m_rotation.x += x;

	if (m_rotation.x < 0.0f)
	{
		m_rotation.x = 359.9f;
	}
	else if (m_rotation.x > 359.9f)
	{
		m_rotation.x = 0.0f;
	}

	m_rotation.y += y;

	if (m_rotation.y < 0.0f)
	{
		m_rotation.y = 359.9f;
	}
	else if (m_rotation.y > 359.9f)
	{
		m_rotation.y = 0.0f;
	}

	m_rotation.z += z;

	if (m_rotation.z < 0.0f)
	{
		m_rotation.z = 359.9f;
	}
	else if (m_rotation.z > 359.9f)
	{
		m_rotation.z = 0.0f;
	}
}

/*
*/
void CCamera::UpdateView()
{
	m_pitch = m_rotation.x * (float)M_PI / 180.0f;

	m_yaw = m_rotation.y * (float)M_PI / 180.0f;
	
	m_roll = m_rotation.z * (float)M_PI / 180.0f;

	m_xmMatrix = XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, m_roll);

	switch (m_type)
	{
	case CCamera::E_LH:
	{
		m_look.x = 0.0f;
		m_look.y = 0.0f;
		m_look.z = 1.0f;

		m_xmvlook = XMLoadFloat3(&m_look);

		m_xmvlook = XMVector3TransformCoord(m_xmvlook, m_xmMatrix);

		m_look = XMFLOAT3(XMVectorGetX(m_xmvlook), XMVectorGetY(m_xmvlook), XMVectorGetZ(m_xmvlook));

		m_look.x = m_look.x + m_position.x;
		m_look.y = m_look.y + m_position.y;
		m_look.z = m_look.z + m_position.z;

		m_xmvlook = XMLoadFloat3(&m_look);

		m_up.x = 0.0f;
		m_up.y = 1.0f;
		m_up.z = 0.0f;

		m_xmvup = XMLoadFloat3(&m_up);

		m_xmvup = XMVector3TransformCoord(m_xmvup, m_xmMatrix);

		m_up = XMFLOAT3(XMVectorGetX(m_xmvup), XMVectorGetY(m_xmvup), XMVectorGetZ(m_xmvup));

		m_xmvposition = XMLoadFloat3(&m_position);

		m_xmview = XMMatrixLookAtLH(m_xmvposition, m_xmvlook, m_xmvup);

		XMStoreFloat4x4(&m_xmfview, m_xmview);

		m_right = XMFLOAT3(m_xmfview.m[0][0], m_xmfview.m[1][0], m_xmfview.m[2][0]);
		m_up = XMFLOAT3(m_xmfview.m[0][1], m_xmfview.m[1][1], m_xmfview.m[2][1]);
		m_look = XMFLOAT3(m_xmfview.m[0][2], m_xmfview.m[1][2], m_xmfview.m[2][2]);

		// In order to transform the memory from the format defined on the CPU to the order expected in HLSL,
		// you need to transpose the CPU matrix before sending it to the GPU.
		// See row_major and column_major
		// Default is column_major
		// doing row_major so no transpose
		//twvpMat = xmworld * xmview * xmproj;
		//wvpMat = XMMatrixTranspose(twvpMat);

		break;
	}
	case CCamera::E_RH:
	{
		m_look.x = 0.0f;
		m_look.y = 1.0f;
		m_look.z = 0.0f;

		m_xmvlook = XMLoadFloat3(&m_look);

		m_xmvlook = XMVector3TransformCoord(m_xmvlook, m_xmMatrix);

		m_look = XMFLOAT3(XMVectorGetX(m_xmvlook), XMVectorGetY(m_xmvlook), XMVectorGetZ(m_xmvlook));

		m_look.x = m_look.x + m_position.x;
		m_look.y = m_look.y + m_position.y;
		m_look.z = m_look.z + m_position.z;

		m_xmvlook = XMLoadFloat3(&m_look);

		m_up.x = 0.0f;
		m_up.y = 0.0f;
		m_up.z = 1.0f;

		m_xmvup = XMLoadFloat3(&m_up);

		m_xmvup = XMVector3TransformCoord(m_xmvup, m_xmMatrix);

		m_up = XMFLOAT3(XMVectorGetX(m_xmvup), XMVectorGetY(m_xmvup), XMVectorGetZ(m_xmvup));

		m_xmvposition = XMLoadFloat3(&m_position);

		m_xmview = XMMatrixLookAtRH(m_xmvposition, m_xmvlook, m_xmvup);

		XMStoreFloat4x4(&m_xmfview, m_xmview);

		m_right = XMFLOAT3(m_xmfview.m[0][0], m_xmfview.m[1][0], m_xmfview.m[2][0]);
		m_up = XMFLOAT3(m_xmfview.m[0][1], m_xmfview.m[1][1], m_xmfview.m[2][1]);
		m_look = XMFLOAT3(m_xmfview.m[0][2], m_xmfview.m[1][2], m_xmfview.m[2][2]);

		// In order to transform the memory from the format defined on the CPU to the order expected in HLSL,
		// you need to transpose the CPU matrix before sending it to the GPU.
		// See row_major and column_major
		// Default is column_major
		// doing row_major so no transpose
		//twvpMat = xmworld * xmview * xmproj;
		//wvpMat = XMMatrixTranspose(twvpMat);

		break;
	}
	}
}