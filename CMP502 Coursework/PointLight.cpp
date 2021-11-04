#include "PointLight.h"


PointLight::PointLight(Graphics& gfx, float x, float y, float z) :
	m_lightBuffer(gfx),
	m_matrixBuffer(gfx, 1)
{
	m_data.pos = { x, y, z };
	m_data.ambient = { 0.15f, 0.15f, 0.35f };
	m_data.diffuseColor = { 1.f, 0.8f, 0.2f };
	m_data.diffuseIntensity = 1.f;
	m_data.attConst = 1.f;
	m_data.attLin = 0.35f;
	m_data.attQuad = 0.1f;

	m_camera.SetPosition(x, y, z);
	m_camera.LookAt(2.f, 0.f, 3.f);
}


void PointLight::Bind(Graphics& gfx, DirectX::XMMATRIX view) const
{
	auto dataCopy = m_data;
	auto pos = DirectX::XMLoadFloat3(&m_data.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	m_lightBuffer.Update(gfx, dataCopy);
	m_lightBuffer.Bind(gfx);

	LightMatrixBuffer lmb =
	{
		DirectX::XMMatrixTranspose(m_camera.GetView()),
		DirectX::XMMatrixTranspose(gfx.GetProjection())
	};
	m_matrixBuffer.Update(gfx, lmb);
	m_matrixBuffer.Bind(gfx);
}

