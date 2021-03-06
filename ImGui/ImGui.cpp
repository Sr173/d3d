//ImGui.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "ImGui.h"

ImGui::ImGui(HWND _hWnd)
	:_subThunk(&ImGui::subProc,this)
	//,threadThunk(&ImGui::mainThread,this)
	,hWnd(_hWnd)
{
	initD3d9();
	font = new Font(oD3d9);
}


ImGui::~ImGui()
{
	if (font) delete font;
	if (vertexBuffer) vertexBuffer->Release();
	if (indexBuffer) indexBuffer->Release();
	if (oD3d9) oD3d9->Release();
	if (oD3dObject) oD3dObject->Release();
}

LRESULT ImGui::subProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (ImGui::GetCurrentContext() == NULL)
	//	return 0;

	//ImGuiIO& io = ImGui::GetIO();

	//wndProc(hwnd, message, wParam, lParam);

	uint msg = message;

	switch (message)
	{
	case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
	{
		int button = 0;
		if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) button = 0;
		if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) button = 1;
		if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) button = 2;
		io.mouseDown[button] = true;
		return 0;
	}
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	{
		int button = 0;
		if (msg == WM_LBUTTONUP) button = 0;
		if (msg == WM_RBUTTONUP) button = 1;
		if (msg == WM_MBUTTONUP) button = 2;
		
		io.mouseDown[button] = false;
		return 0;
	}
	case WM_MOUSEWHEEL:
		//io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		return 0;
	case WM_MOUSEHWHEEL:
		//io.MouseWheelH += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		return 0;
	case WM_MOUSEMOVE:
		io.mousePos.x = (signed short)(lParam);
		io.mousePos.y = (signed short)(lParam >> 16);
		return 0;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (wParam < 256)
			io.keysDown[wParam] = 1;
		return 0;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (wParam < 256)
			io.keysDown[wParam] = 0;
		return 0;
	case WM_CHAR:
		// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
		//if (wParam > 0 && wParam < 0x10000)
		//	io.AddInputCharacter((unsigned short)wParam);
		return 0;
	case WM_SETCURSOR:
		return 0;
	}

	return true;
}

bool ImGui::initD3d9()
{
	D3DDISPLAYMODE displayMode;
	oD3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (oD3dObject == nullptr)return false;
	if (FAILED(oD3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))return false;

	D3DPRESENT_PARAMETERS g_d3dpp;
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));

	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; 

	if (FAILED(oD3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &oD3d9))) return false;
	

	return true;
}

void ImGui::begin()
{
	drawData.clear();
	RECT rect;
	GetClientRect(hWnd, &rect);
	io.displaySize = ImVector2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
	int tick = GetTickCount();
	io.deltaTime = tick - io.tickCount;
	io.tickCount = tick;
	
	for (int i = 0; i < 5; i++) {
		io.mouseClicked[i] = io.mouseDown[i] && io.mouseDownDuration[i] < 0.0f;

		io.mouseRelease[i] = !io.mouseDown[i] && io.mouseDownDuration[i] >= 0.f;
		io.mouseDownDuration[i] = io.mouseDown[i] ? (io.mouseDownDuration[i] < 0.0f ? 0.0f : io.mouseDownDuration[i] + io.deltaTime) : -1.0f;

		if (io.mouseDown[i]) {
			io.mouseDownDuration[i] += io.deltaTime;
		}
	}
}

void ImGui::end()
{
	//drawData.drawRect(ImVector3(0, 0, 0), IO.displaySize.x - 1, IO.displaySize.y - 1, { ImColor(0xFF000000) });
}

void ImGui::render()
{
	
	D3DRender();
}


void ImGui::D3DRender()
{
	oD3d9->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, dc.backColor.color, 1.0f, 0);
	oD3d9->BeginScene();


	const float L = 0.f, R = io.displaySize.x + 0.f, T = 0.f, B = io.displaySize.y + 0.f;

	if (!vertexBuffer || vertexBufferSize < drawData.getDrawList().size()) {
		if (vertexBuffer) vertexBuffer->Release();
		vertexBufferSize = drawData.getDrawList().size() + 5000;
		oD3d9->CreateVertexBuffer(sizeof(D3DVertex) * vertexBufferSize, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &vertexBuffer, nullptr);
	}
		
	if (!indexBuffer || indexBufferSize < drawData.getDrawIndex().size()) {
		if (indexBuffer) indexBuffer->Release();
		indexBufferSize = drawData.getDrawIndex().size() + 10000;
		oD3d9->CreateIndexBuffer(indexBufferSize * sizeof(short), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFORMAT::D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, nullptr);
	}
	//font->DrawSimpleText();
	oD3d9->SetStreamSource(0, vertexBuffer, 0, sizeof(D3DVertex));
	oD3d9->SetIndices(indexBuffer);
	oD3d9->SetFVF(D3DFVF_VERTEX);
	short* pIndex = nullptr;
	D3DVertex* pVertex = nullptr;
	indexBuffer->Lock(0, drawData.getDrawIndex().size() * sizeof(short), (void**)&pIndex, D3DLOCK_DISCARD);
	vertexBuffer->Lock(0, sizeof(D3DVertex) * (drawData.getDrawList().size()), (void**)&pVertex, D3DLOCK_DISCARD);
	for (int i = 0; i < drawData.getDrawList().size(); i++) {
		ImVertex& vertex = drawData.getDrawList()[i];
		pVertex[i].x = vertex.pos.x;
		pVertex[i].y = vertex.pos.y;
		pVertex[i].z = vertex.pos.z;
		pVertex[i].col = vertex.col.color;
		pVertex[i].u = vertex.uv.x;
		pVertex[i].v = vertex.uv.y;
	}
	for (int i = 0; i < drawData.getDrawIndex().size(); i++) {
		pIndex[i] = drawData.getDrawIndex()[i];
	}
	indexBuffer->Unlock();
	vertexBuffer->Unlock();




	D3DVIEWPORT9 vp;
	vp.X = vp.Y = 0;
	vp.Width = (DWORD)io.displaySize.x;
	vp.Height = (DWORD)io.displaySize.y;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	oD3d9->SetViewport(&vp);
	oD3d9->SetPixelShader(NULL);
	oD3d9->SetVertexShader(NULL);
	oD3d9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	oD3d9->SetRenderState(D3DRS_LIGHTING, false);
	oD3d9->SetRenderState(D3DRS_ZENABLE, false);
	oD3d9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	oD3d9->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	oD3d9->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	oD3d9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	oD3d9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	oD3d9->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	oD3d9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	oD3d9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	oD3d9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	oD3d9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	oD3d9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	oD3d9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	oD3d9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	oD3d9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);


	D3DMATRIX mat_projection =
	{
		2.0f / (R - L),   0.0f,         0.0f,  0.0f,
		0.0f,         2.0f / (T - B),   0.0f,  0.0f,
		0.0f,         0.0f,         0.5f,  0.0f,
		(L + R) / (L - R),  (T + B) / (B - T),  0.5f, 1.0f,
	};

	D3DXMATRIX mat_identity = { {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		} };

	oD3d9->SetTransform(D3DTS_WORLD, &mat_identity);
	oD3d9->SetTransform(D3DTS_VIEW, &mat_identity);
	oD3d9->SetTransform(D3DTS_PROJECTION, &mat_projection);
	oD3d9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, drawData.getDrawList().size(), 0, drawData.getDrawIndex().size() / 3);

	oD3d9->EndScene();
	oD3d9->Present(nullptr, nullptr, nullptr, nullptr);
}

void ImGui::button(std::string text)
{
	
	ImVector2 size = { 100,20 };
	bool isInState = (io.mousePos.x >= dc.cursorPos.x && io.mousePos.x <= dc.cursorPos.x + size.x) && (io.mousePos.y >= dc.cursorPos.y && io.mousePos.y <= dc.cursorPos.y + size.y);
	ImColor col = ImColor(0x50, 0x50, 0x50);
	if (isInState) {
		col = ImColor(0x70, 0x50, 0x50);
	}

	drawData.drawRect(dc.cursorPos, 100, 20, { col });
	//font->DrawSimpleText("我爱你", 8, ImVector2(10, 10), 0xFF0000FF);
	if (io.mouseClicked[0] && isInState) {
		MessageBox(0, 0, 0, 0);
	}

}