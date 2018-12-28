#include "stdafx.h"
#include "ImGui.h"
#include "iostream"


ImGui* imGui;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	imGui->subProc(hwnd, message, wParam, lParam);

	switch (message) {
	case WM_CLOSE:
		PostMessage(hwnd, WM_QUIT, 0, 0);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void Init() {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindow(_T("ImGui Example"), _T("ImGui DirectX9 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL);


	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
	imGui = new ImGui(hwnd);
	//imGui->initD3d9();

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		imGui->begin();
		{
			imGui->button("123");
		}

		imGui->end();
		imGui->render();
		//std::cout << "µ±Ç°FPS:" << 1000 / (imGui->getIO()->deltaTime) << std::endl;
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Init();
	return 0;
}

int main() {
	Init();
	return 0;
}
