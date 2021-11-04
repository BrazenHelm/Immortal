#pragma once

#include "WindowsInclude.h"
#include "Camera.h"
#include "Inputs.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

class Graphics
{
	friend class Bindable;

public:
	Graphics(HWND hWnd, int width, int height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;

	void EndFrame();
	void ClearBuffer(float r, float g, float b);

	void DrawIndexed(UINT count);

	DirectX::XMMATRIX GetCamera();
	DirectX::XMMATRIX GetProjection() const;

	//void DrawTestCube(float angle, float x, float y);

	void SetDrawModeDepth();
	void SetDrawModeLight();

	//void SaveDepthMap();

	void ControlCamera(Inputs inputs, float dt);

private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_pContext;
	Microsoft::WRL::ComPtr<ID3D11Device>			m_pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			m_pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pDSV;

	// Render to texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pRenderTargetTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		m_pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pShaderResourceView;

	Camera m_camera;
};

