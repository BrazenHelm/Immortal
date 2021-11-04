#include "Queen.h"
#include "Bindables.h"


Queen::Queen(Graphics& gfx, const Material& material, float x, float z)
{
	if (!IsStaticInitialized())
	{
		LoadStaticMesh(gfx, "Assets/queen.obj");
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

