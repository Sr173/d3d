#pragma once
#include "stdafx.h"

class IO
{
public:
	IO() {
		tickCount = GetTickCount();
	};
	~IO() {

	};

public:
	ImVector2 displaySize;//客户区大小
	ImVector2 mousePos;//鼠标位置
	float	deltaTime;//两帧的间隔时间
	bool	mouseDown[5];
	bool	mouseRelease[5];
	bool	mouseClicked[5];
	//float	mouseDownDuration[5];
	bool	mouseDoubleClick[5];
	bool	keysDown[256];
	bool	keysUp[256];
	float	mouseDoubleClickTime = 0.5f;
	float   mouseDownDuration[5];//鼠标点击的持续时间
	int		tickCount;

private:
};

