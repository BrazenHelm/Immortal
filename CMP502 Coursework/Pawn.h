#pragma once
#include "DrawableBase.h"
#include "Material.h"

class Pawn : public DrawableBase<Pawn>
{
public:
	Pawn(Graphics& gfx, const Material& material, float x, float z);
};

