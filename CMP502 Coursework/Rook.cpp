#include "Rook.h"
#include "Bindables.h"


Rook::Rook(Graphics& gfx, const Material& material, float x, float z)
{
	if (!IsStaticInitialized())
	{
		LoadStaticMesh(gfx, "Assets/rook.obj");
		LoadStaticTexture(gfx, "Assets/plain_white.png");
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<MatrixBuffer>(gfx, *this));
	AddBind(std::make_unique<PixelConstantBuffer<Material>>(gfx, material, 1));

	transform.SetPos(x, 0.f, z);
	transform.SetScale(18.18f, 18.18f, 18.18f);
}

