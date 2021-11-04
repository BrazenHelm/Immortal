#pragma once
#include "DrawableBase.h"
#include "Material.h"

class King : public DrawableBase<King>
{
public:
	King(Graphics& gfx, const Material& material, float x, float z);
};

