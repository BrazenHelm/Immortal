#include "Board.h"
#include "Bindables.h"
#include "OBJ_Loader.h"


Board::Board(Graphics& gfx, const Material& material, float x, float z)
{
	if (!IsStaticInitialized())
	{
		LoadStaticMesh(gfx, "Assets/board_no_underside.obj");
		LoadStaticTexture(gfx, "Assets/board_texture.png");
	}
	else
	{
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<MatrixBuffer>(gfx, *this, 0));
	AddBind(std::make_unique<PixelConstantBuffer<Material>>(gfx, material, 1));

	transform.SetPos(x, 0.f, z);
	transform.SetScale(18.18f, 18.18f, 18.18f);
}

