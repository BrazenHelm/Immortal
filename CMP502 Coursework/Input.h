#pragma once
#include "Inputs.h"


class Keyboard;

class Input
{
public:
	Input(Keyboard* pKeyboard);
	~Input();

	Inputs GetInputs();
	float GetVerticalPan();
	float GetHorizontalPan();
	int GetRotation();

private:
	Keyboard* m_pKeyboard;
};

