#include "stdafx.h"
#include "DrawData.h"


DrawData::DrawData()
{
}


DrawData::~DrawData()
{
}

void DrawData::drawRect(ImVector3 o,int w,int h, std::initializer_list<ImColor> iColor)
{
	ImColor color[4];
	switch (iColor.size())
	{
	case 0:
		break;
	case 1:
		for (int i = 0; i < 4; i++)
			color[i] = iColor.begin()[0];
		break;
	case 2:
		color[0] = iColor.begin()[0];
		color[1] = iColor.begin()[0];
		color[2] = iColor.begin()[1];
		color[3] = iColor.begin()[1];
		break;
	case 3:
		color[0] = iColor.begin()[0];
		color[1] = iColor.begin()[1];
		color[2] = iColor.begin()[2];
		color[3] = iColor.begin()[0];
		break;
	default:
		color[0] = iColor.begin()[0];
		color[1] = iColor.begin()[1];
		color[2] = iColor.begin()[2];
		color[3] = iColor.begin()[3];
		break;
	}

	int index = drawList.size();
	drawList.push_back(ImVertex{ ImVector3(o.x + 0.f,o.y + 0.f, 0.f), color[0], ImVector2(1.f, 1.f )});
	drawList.push_back(ImVertex{ ImVector3(o.x + w + 0.f, o.y + 0.f, 0.f), color[1],ImVector2(1.f, 1.f) });
	drawList.push_back(ImVertex{ ImVector3(o.x + w + 0.f, o.y + h + 0.f, 0.f), color[2], ImVector2(1.f, 1.f) });
	drawList.push_back(ImVertex{ ImVector3(o.x + 0.f, o.y + h + 0.f, 0.f), color[3],ImVector2(1.f, 1.f) });

	drawIndex.push_back(0 + index);
	drawIndex.push_back(1 + index);
	drawIndex.push_back(2 + index);

	drawIndex.push_back(0 + index);
	drawIndex.push_back(2 + index);
	drawIndex.push_back(3 + index);
}

void DrawData::drawSector()
{
}

void DrawData::addVertex(ImVertex vertex)
{
	drawList.push_back(vertex);
}

void DrawData::addIndex(short index)
{
	drawIndex.push_back(index);
}

std::vector<ImVertex>& DrawData::getDrawList()
{
	return drawList;
}

void DrawData::clear()
{
	drawList.clear();
	drawIndex.clear();
}
