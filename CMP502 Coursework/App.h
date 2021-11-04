#pragma once
#include "Drawable.h"
#include "PointLight.h"
#include "Timer.h"
#include "Window.h"
#include <random>
#include <vector>


class App
{
public:
	App(int width);
	
	int Run();

private:
	void DoFrame();

	void DoCandleFlicker();

	void SetUpScene();

	enum PieceType { BISHOP, KING, KNIGHT, PAWN, QUEEN, ROOK };
	enum PieceColor { BLACK, WHITE };
	void MakePiece(PieceType type, PieceColor color, const std::string& square);

private:
	Window		m_window;
	Timer		m_timer;
	PointLight	m_light;
	std::vector<std::unique_ptr<Drawable>> m_pDrawables;
};

