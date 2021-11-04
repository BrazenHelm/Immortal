#pragma once
#include "DrawableBase.h"
#include "Material.h"

class Knight : public DrawableBase<Knight>
{
public:
	Knight(Graphics& gfx, const Material& material, float x, float z, float angle);
};

