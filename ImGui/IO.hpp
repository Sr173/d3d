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
	ImVector2 displaySize;//�ͻ�����С
	ImVector2 mousePos;//���λ��
	float	deltaTime;//��֡�ļ��ʱ��
	bool	mouseDown[5];
	bool	mouseRelease[5];
	bool	mouseClicked[5];
	//float	mouseDownDuration[5];
	bool	mouseDoubleClick[5];
	bool	keysDown[256];
	bool	keysUp[256];
	float	mouseDoubleClickTime = 0.5f;
	float   mouseDownDuration[5];//������ĳ���ʱ��
	int		tickCount;

private:
};

