#pragma once
#include "DrawableBase.h"
#include "Material.h"

class Queen : public DrawableBase<Queen>
{
public:
	Queen(Graphics& gfx, const Material& material, float x, float z);
};

