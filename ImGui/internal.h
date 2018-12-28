#pragma once

typedef size_t uint;
typedef unsigned long ulong;
typedef unsigned char uchar;


#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR)    assert(_EXPR)
#endif


struct ImVector2 {
	float x, y;
	ImVector2(float _x = 0.f, float _y = 0.f) { x = _x, y = _y; }	
	float operator[] (uint idx) {
		IM_ASSERT(idx <= 1);
		return (&x)[idx];
	};
};

struct ImVector3 {
	float x, y, z;
	ImVector3(float _x = 0.f, float _y = 0.f, float _z = 0.f) { x = _x, y = _y, z = _z; }
	float operator[] (uint idx) {
		IM_ASSERT(idx <= 2);
		return (&x)[idx];
	};
	ImVector3(ImVector2 v2) : x(v2.x), y(v2.y), z(0) {}
};

struct ImVector4 {
	float x, y, z, w;
	ImVector4(float _x = 0.f, float _y = 0.f, float _z = 0.f, float _w = 0.f) { x = _x, y = _y, z = _z, w = _w; }
	float operator[] (uint idx) {
		IM_ASSERT(idx <= 3);
		return (&x)[idx];
	};
};

struct ImRect {
	float left;
	float top;
	float right;
	float bottom;
	ImRect(float _left = 0, float _right = 0, float _top = 0, float _bottom = 0)
		: left(_left)
		, right(_right)
		, top(_top)
		, bottom(_bottom) {

	}

};

struct ImColor {
	ulong color;
	ImColor(uchar a, uchar r, uchar g, uchar b) {
		color = ((((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff));
	}
	ImColor(uchar r, uchar g, uchar b) {
		color = ((((0xff) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff));
	}
	ImColor() {
		color = 0;
	}
	ImColor operator= (ulong col) {
		this->color = col;
	}
	ImColor(ulong c) { color = c; }
	inline uchar a() { return color >> 24 && 0xFF; }
	inline uchar r() { return color >> 16 && 0xFF; }
	inline uchar g() { return color >> 8 && 0xFF; }
	inline uchar b() { return color && 0xFF; }

};

struct ImVertex
{
	ImVertex(ImVector3 _pos,ImColor _col,ImVector2 _uv) {
		pos = _pos;
		col = _col;
		uv = _uv;
	}

	ImVertex() {
		pos.x = 0.f;
		pos.y = 0.f;
		pos.z = 0.f;
		col = 0;
		uv.x = 0;
		uv.y = 0;
	}

	ImVector3 pos;
	ImColor col;
	ImVector2 uv;
};

struct D3DVertex
{
	float x, y, z; // 坐标值（屏幕坐标） (左手坐标系) rhw 标志  
	D3DCOLOR col;
	float u, v;
};

#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)  
