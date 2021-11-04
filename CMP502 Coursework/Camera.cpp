#include "Camera.h"

namespace dx = DirectX;

Camera::Camera() :
	m_up(0.f, 1.f, 0.f)
{}


dx::XMMATRIX Camera::GetView() const
{
	return m_view;
}


void Camera::SetPosition(float x, float y, float z)
{
	m_pos = { x, y, z };
	Update();
}


void Camera::LookAt(float x, float y, float z)
{
	m_focus = { x, y, z };
	Update();
}


void Camera::Control(Inputs inputs, float dt)
{
	float dx = (m_forward.x * inputs.xPan + m_right.x * inputs.zPan) * dt * m_moveSpeed;
	float dz = (m_forward.z * inputs.xPan + m_right.z * inputs.zPan) * dt * m_moveSpeed;
	m_pos.x += dx;
	m_pos.z += dz;
	m_focus.x += dx;
	m_focus.z += dz;

	dx::XMMATRIX rotMatrix =
		dx::XMMatrixTranslation(-m_focus.x, -m_focus.y, -m_focus.z) *
		dx::XMMatrixRotationY(inputs.yawRot * dt * m_turnSpeed) *
		dx::XMMatrixTranslation(m_focus.x, m_focus.y, m_focus.z);
	auto pos = dx::XMLoadFloat3(&m_pos);
	dx::XMStoreFloat3(&m_pos, dx::XMVector3Transform(pos, rotMatrix));

	Update();
}


void Camera::Update()
{
	dx::XMVECTOR pos = dx::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.f);
	dx::XMVECTOR focus = dx::XMVectorSet(m_focus.x, m_focus.y, m_focus.z, 0.f);
	dx::XMVECTOR up = dx::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.f);
	m_view = dx::XMMatrixLookAtLH(pos, focus, up);

	const dx::XMVECTOR forward = dx::XMVector4Normalize(
		dx::XMVectorSet(m_focus.x - m_pos.x, 0.f, m_focus.z - m_pos.z, 0.f));
	dx::XMStoreFloat3(&m_forward, forward);

	const dx::XMVECTOR right = dx::XMVector3Cross(up, forward);
	dx::XMStoreFloat3(&m_right, right);
}

