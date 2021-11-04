#pragma once
#include "WindowsInclude.h"
#include "AudioPlayer.h"
#include "Graphics.h"
#include "Input.h"
#include "Keyboard.h"
#include "MyException.h"
#include <memory>
#include <optional>

class Window
{
private:
	// singleton manager
	class WindowClass
	{
	public:
		static const char* GetName() noexcept { return wndClassName; }
		static HINSTANCE GetInstance() noexcept { return wndClass.hInst; }
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "DirectX3D11_Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	static std::optional<int> ProcessMessages();

	Graphics& Gfx() { return *m_pGfx; }
	bool PlayAudio() { return m_pAudio->Play(); }

	void SetTitle(const std::string& newTitle);

private:
	static LRESULT CALLBACK HandleMsgSetup(
		HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
	) noexcept;
	static LRESULT CALLBACK HandleMsgMain(
		HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
	) noexcept;
	LRESULT HandleMsg(
		HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
	) noexcept;

public:
	Input input;
	Keyboard kb;

private:
	int m_width, m_height;
	HWND m_hWnd;
	std::unique_ptr<AudioPlayer> m_pAudio;
	std::unique_ptr<Graphics> m_pGfx;
};

