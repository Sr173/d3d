#pragma once
class DrawContext
{
public:
	DrawContext() {
		backColor = ImColor(0xFF, 0xFF, 0x00);
		margin.x = 10;//�м��
		margin.y = 5;//�м��
		cursorPos = margin;
	}
	~DrawContext() {};
	ImVector2 cursorPos;//�¸��ؼ�Ҫ���Ƶ�λ��
	ImColor backColor;//���ڵı�����ɫ
	ImVector2 margin; //���м��
private:

};
