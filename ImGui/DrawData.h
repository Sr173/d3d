#pragma once
#include "Font.h"
class DrawData
{
public:
	DrawData();
	~DrawData();
	//void drawRect();
	std::vector<ImVertex>& getDrawList();
	std::vector<short>& getDrawIndex() { return drawIndex; };
	void clear();
	void drawRect(ImVector3 o, int w, int h, std::initializer_list<ImColor> iColor);
	void drawSector();
	void addVertex(ImVertex vertex);
	void addIndex(short index);

private:
	std::vector<ImVertex> drawList;
	std::vector<short> drawIndex;
};
