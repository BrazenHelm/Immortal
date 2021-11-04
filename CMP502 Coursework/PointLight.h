#pragma once
#include "Graphics.h"
#include "ConstantBuffer.h"
#include "MatrixBuffer.h"

class PointLight
{
public:
	PointLight(Graphics& gfx, float x, float y, float z);

	void Bind(Graphics& gfx, DirectX::XMMATRIX view) const;

	void SetPos(float x, float y, float z)
	{
		m_data.pos = { x, y, z };
		m_camera.SetPosition(x, y, z);
	}

	void SetAttenuation(float constant, float linear, float quadratic)
	{
		m_data.attConst = constant;
		m_data.attLin = linear;
		m_data.attQuad = quadratic;
	}

private:
	struct PointLightBuffer
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;	// attenuation
		float attLin;	// attenuation
		float attQuad;	// attenuation
	};

private:
	PointLightBuffer m_data;
	mutable PixelConstantBuffer<PointLightBuffer> m_lightBuffer;

	Camera m_camera;
	struct LightMatrixBuffer
	{
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX proj;
	};
	mutable VertexConstantBuffer<LightMatrixBuffer> m_matrixBuffer;
};

