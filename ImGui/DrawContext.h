#pragma once
class DrawContext
{
public:
	DrawContext() {
		backColor = ImColor(0xFF, 0xFF, 0x00);
		margin.x = 10;//行间距
		margin.y = 5;//列间距
		cursorPos = margin;
	}
	~DrawContext() {};
	ImVector2 cursorPos;//下个控件要绘制的位置
	ImColor backColor;//窗口的背景颜色
	ImVector2 margin; //行列间距
private:

};
