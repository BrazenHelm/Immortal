#include "Input.h"
#include "Keyboard.h"


Input::Input(Keyboard* pKeyboard) :
	m_pKeyboard(pKeyboard)
{}


Input::~Input()
{
	m_pKeyboard = nullptr;
}


Inputs Input::GetInputs()
{
	Inputs inputs;
	inputs.xPan = GetVerticalPan();
	inputs.zPan = GetHorizontalPan();
	inputs.yawRot = GetRotation();

	if (inputs.xPan != 0 && inputs.zPan != 0)
	{
		inputs.xPan /= sqrtf(2.f);
		inputs.zPan /= sqrtf(2.f);
	}

	return inputs;
}


float Input::GetVerticalPan()
{
	bool goingUp = m_pKeyboard->KeyIsPressed('W');
	bool goingDown = m_pKeyboard->KeyIsPressed('S');
	
	if (goingUp && !goingDown) return 1.f;
	if (goingDown && !goingUp) return -1.f;
	else return 0;
}


float Input::GetHorizontalPan()
{
	bool goingRight = m_pKeyboard->KeyIsPressed('D');
	bool goingLeft = m_pKeyboard->KeyIsPressed('A');

	if (goingRight && !goingLeft) return 1.f;
	if (goingLeft && !goingRight) return -1.f;
	else return 0;
}


int Input::GetRotation()
{
	bool turningLeft = m_pKeyboard->KeyIsPressed('Q');
	bool turningRight = m_pKeyboard->KeyIsPressed('E');

	if (turningLeft && !turningRight) return 1;
	if (turningRight && !turningLeft) return -1;
	else return 0;
}

