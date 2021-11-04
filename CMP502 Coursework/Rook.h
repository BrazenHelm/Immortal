#pragma once
#include "DrawableBase.h"
#include "Material.h"

class Rook : public DrawableBase<Rook>
{
public:
	Rook(Graphics& gfx, const Material& material, float x, float z);
};

