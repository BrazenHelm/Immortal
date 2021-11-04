#include "Knight.h"
#include "Bindables.h"
#include "OBJ_Loader.h"


Knight::Knight(Graphics& gfx, const Material& material, float x, float z, float angle)
{
	if (!IsStaticInitialized())
	{
		LoadStaticMesh(gfx, "Assets/knight.obj");
		LoadStaticTexture(gfx, "Assets/plain_white.png");
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<MatrixBuffer>(gfx, *this, 0));
	AddBind(std::make_unique<PixelConstantBuffer<Material>>(gfx, material, 1));

	transform.SetPos(x, 0.f, z);
	transform.SetRot(0.f, angle, 0.f);
	transform.SetScale(18.18f, 18.18f, 18.18f);
}
