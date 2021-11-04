#pragma once
#include "DrawableBase.h"
#include "Material.h"

class Board : public DrawableBase<Board>
{
public:
	Board(Graphics& gfx, const Material& material, float x, float z);
};