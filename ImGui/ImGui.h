#pragma once

#include "resource.h"
#include "thunk.hpp"
#include "IO.hpp"
#include "DrawData.h"
#include "DrawContext.h"

class ImGui
{
public:
	ImGui(HWND hWnd);
	~ImGui();
	LRESULT subProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//窗口需要调用这个回调
	bool initD3d9();//初始化D3D
	void begin(); //新的帧
	void end();  //帧结束
	void render();//渲染帧
	void button(std::string text);
	auto getFont() { return font; };

	inline const IO* getIO() {return &io;}//获取io
	inline IO* setIO() {return &io;}//设置io
	inline void setUserWndProc(WNDPROC w) {wndProc = w;}
	inline void setBackColor(ImColor col) { dc.backColor = col.color; }
private:
	void D3DRender();
private:
	Win32Thunk<WNDPROC, ImGui> _subThunk;//thunk对象
	//Win32Thunk<LPTHREAD_START_ROUTINE, ImGui> threadThunk;
	PDIRECT3D9 oD3dObject = nullptr; // D3D对象  
	PDIRECT3DDEVICE9 oD3d9 = nullptr; // D3D设备对象  
	WNDPROC wndProc;//用户定义的自定义消息处理函数
	HWND hWnd;//窗口句柄
	IO io;//io处理函数
	DrawData drawData;
	DrawContext dc;
	IDirect3DVertexBuffer9* vertexBuffer = nullptr;
	PDIRECT3DINDEXBUFFER9 indexBuffer = nullptr;
	Font* font = nullptr;
	int vertexBufferSize = 0;
	int indexBufferSize = 0;

};
