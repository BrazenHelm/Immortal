#pragma once
#include <DirectXMath.h>
#include "Inputs.h"

class Camera
{
public:
	Camera();
	~Camera() = default;

	DirectX::XMMATRIX GetView() const;

	void SetPosition(float x, float y, float z);
	void LookAt(float x, float y, float z);

	void Control(Inputs inputs, float dt);

private:
	void Update();

private:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_focus;
	DirectX::XMFLOAT3 m_up;

	DirectX::XMFLOAT3 m_forward;
	DirectX::XMFLOAT3 m_right;

	DirectX::XMMATRIX m_view;

	float m_moveSpeed = 3.f;
	float m_turnSpeed = 0.7f;
};

