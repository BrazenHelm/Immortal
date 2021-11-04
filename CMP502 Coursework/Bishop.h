#pragma once
#include "DrawableBase.h"
#include "Material.h"

class Bishop : public DrawableBase<Bishop>
{
public:
	Bishop(Graphics& gfx, const Material& material, float x, float y);
};

