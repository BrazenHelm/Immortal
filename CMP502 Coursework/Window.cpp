#include "Window.h"
#include "resource.h"

// WindowClass

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept :
	hInst(GetModuleHandleA(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = static_cast<HICON>(LoadImageA(
		hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0)
	);
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImageA(
		hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0)
	);
	RegisterClassExA(&wc);
}


Window::WindowClass::~WindowClass()
{
	UnregisterClassA(wndClassName, GetInstance());
}



// Window

Window::Window(int width, int height, const char* name) noexcept :
	input(&kb)
{
	RECT wr;
	wr.left = 100;
	wr.right = wr.left + width;
	wr.top = 100;
	wr.bottom = wr.top + height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	m_hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);

	m_pGfx = std::make_unique<Graphics>(m_hWnd, width, height);
	m_pAudio = std::make_unique<AudioPlayer>();
	m_pAudio->Initialize(m_hWnd, "Assets/the-medieval-banquet.wav");
}


Window::~Window()
{
	DestroyWindow(m_hWnd);
}


std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};
}


void Window::SetTitle(const std::string& newTitle)
{
	SetWindowTextA(m_hWnd, newTitle.c_str());
}


LRESULT CALLBACK Window::HandleMsgSetup(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&HandleMsgMain));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


LRESULT CALLBACK Window::HandleMsgMain(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}


LRESULT Window::HandleMsg(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
) noexcept
{
	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;

		case WM_KILLFOCUS:
			kb.ClearState();
			break;

		// Keyboard Messages
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			if (!(lParam & 0x40000000) || kb.AutoRepeatIsEnabled())
				kb.OnKeyPressed(static_cast<unsigned char>(wParam));
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			kb.OnKeyReleased(static_cast<unsigned char>(wParam));
			break;
		case WM_CHAR:
			kb.OnChar(static_cast<unsigned char>(wParam));
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

