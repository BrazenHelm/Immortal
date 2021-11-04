#include "App.h"
#include "GDIPlusManager.h"
#include <memory>
#include <random>

#include "Board.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"


GDIPlusManager gdpim;


App::App(int width) :
	m_window(width, width / 16 * 9, "CMP502 Coursework"),
	m_light(m_window.Gfx(), 0.f, 0.f, 3.5f)
{
	SetUpScene();
	Drawable::InitializeSharedBindables(m_window.Gfx());
	m_window.PlayAudio();
	//dist = std::uniform_real_distribution<float>(-0.1f, 0.1f);
}


int App::Run()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())	// if (msg == WM_QUIT)
		{
			return *ecode;
		}

		DoFrame();
	}
}


void App::DoFrame()
{
	float dt = m_timer.Split();
	m_window.Gfx().ControlCamera(m_window.input.GetInputs(), dt);

	DoCandleFlicker();
	m_light.Bind(m_window.Gfx(), m_window.Gfx().GetCamera());

	// Render pass for depth map
	m_window.Gfx().SetDrawModeDepth();
	Drawable::SetDrawModeDepth(m_window.Gfx());
	for (auto& object : m_pDrawables)
	{
		object->Draw(m_window.Gfx());
	}

	// Main render pass
	m_window.Gfx().SetDrawModeLight();
	Drawable::SetDrawModeLight(m_window.Gfx());
	for (auto& object : m_pDrawables)
	{
		object->Draw(m_window.Gfx());
	}

	m_window.Gfx().EndFrame();
}


void App::DoCandleFlicker()
{
	static std::mt19937 rng;
	static std::uniform_real_distribution<float> dist(-1.f, 1.f);

	const DirectX::XMFLOAT3 centre = { -5.f, 8.f, -2.5f };
	const float regressionFactor = 0.95f;
	const float distanceMultiplier = 0.1f;

	static DirectX::XMFLOAT3 offset = { 0.f, 0.f, 0.f };

	offset.x *= regressionFactor;
	offset.y *= regressionFactor;
	offset.z *= regressionFactor;
	offset.x += dist(rng) * distanceMultiplier;
	offset.y += dist(rng) * distanceMultiplier;
	offset.z += dist(rng) * distanceMultiplier;

	const DirectX::XMFLOAT3 attCentre = { 1.f, 0.025f, 0.001f };
	const float attRegressionFactor = 0.9f;
	const float attMultiplier = 0.07f;

	static DirectX::XMFLOAT3 attOffset = { 0.f, 0.f, 0.f };

	attOffset.x *= attRegressionFactor;
	attOffset.y *= attRegressionFactor;
	attOffset.z *= attRegressionFactor;
	attOffset.x += dist(rng) * attCentre.x * attMultiplier;
	attOffset.y += dist(rng) * attCentre.y * attMultiplier;
	attOffset.z += dist(rng) * attCentre.z * attMultiplier;

	m_light.SetPos(centre.x + offset.x, centre.y + offset.y, centre.z + offset.z);
	m_light.SetAttenuation(attCentre.x + attOffset.x, attCentre.y + attOffset.y,
		attCentre.z + attOffset.z);
}


void App::SetUpScene()
{
	Material board = { {1.f, 1.f, 1.f}, 0.8f, 30.f };
	m_pDrawables.push_back(std::make_unique<Board>(m_window.Gfx(), board, 3.5f, 3.5f));

	MakePiece(QUEEN, BLACK, "a1");
	MakePiece(BISHOP, BLACK, "g1");

	MakePiece(PAWN, WHITE, "a2");
	MakePiece(PAWN, WHITE, "c2");
	MakePiece(KING, WHITE, "e2");

	MakePiece(PAWN, WHITE, "d3");

	MakePiece(PAWN, WHITE, "g4");

	MakePiece(PAWN, BLACK, "b5");
	MakePiece(KNIGHT, WHITE, "d5");
	MakePiece(PAWN, WHITE, "e5");
	MakePiece(PAWN, WHITE, "h5");

	MakePiece(KNIGHT, BLACK, "a6");
	MakePiece(KNIGHT, BLACK, "f6");

	MakePiece(PAWN, BLACK, "a7");
	MakePiece(PAWN, BLACK, "d7");
	MakePiece(BISHOP, WHITE, "e7");
	MakePiece(PAWN, BLACK, "f7");
	MakePiece(KNIGHT, WHITE, "g7");
	MakePiece(PAWN, BLACK, "h7");

	MakePiece(ROOK, BLACK, "a8");
	MakePiece(BISHOP, BLACK, "c8");
	MakePiece(KING, BLACK, "d8");
	MakePiece(ROOK, BLACK, "h8");
}


void App::MakePiece(App::PieceType type, App::PieceColor color, const std::string& square)
{
	float x, z;
	char file = square[0];
	char rank = square[1];

	switch (file)
	{
		case 'a': x = 0.f; break;
		case 'b': x = 1.f; break;
		case 'c': x = 2.f; break;
		case 'd': x = 3.f; break;
		case 'e': x = 4.f; break;
		case 'f': x = 5.f; break;
		case 'g': x = 6.f; break;
		case 'h': x = 7.f; break;
		default: assert(false); break;
	}
	switch (rank)
	{
		case '1': z = 0.f; break;
		case '2': z = 1.f; break;
		case '3': z = 2.f; break;
		case '4': z = 3.f; break;
		case '5': z = 4.f; break;
		case '6': z = 5.f; break;
		case '7': z = 6.f; break;
		case '8': z = 7.f; break;
		default: assert(false); break;
	}

	Material mat;
	float angle;	// only used for knights
	switch (color)
	{
		case WHITE:
			mat = { {1.f, 1.f, 0.90f}, 0.5f, 10.f };
			angle = 0.f;
			break;
		case BLACK:
			mat = { {0.25f, 0.30f, 0.30f}, 100.f, 50.f };
			angle = DirectX::XM_PI;
			break;
		default: assert(false); break;
	}

	switch (type)
	{
		case BISHOP: m_pDrawables.push_back(std::make_unique<Bishop>(
				m_window.Gfx(), mat, x, z)); break;
		case KING: m_pDrawables.push_back(std::make_unique<King>(
				m_window.Gfx(), mat, x, z)); break;
		case KNIGHT: m_pDrawables.push_back(std::make_unique<Knight>(
				m_window.Gfx(), mat, x, z, angle)); break;
		case PAWN: m_pDrawables.push_back(std::make_unique<Pawn>(
				m_window.Gfx(), mat, x, z)); break;
		case QUEEN: m_pDrawables.push_back(std::make_unique<Queen>(
				m_window.Gfx(), mat, x, z)); break;
		case ROOK: m_pDrawables.push_back(std::make_unique<Rook>(
				m_window.Gfx(), mat, x, z)); break;
		default: assert(false); break;
	}
}

