#pragma once
#include "Utility\Renderer.h"
#include <array>
class NowLoading
{
public:
	NowLoading();
	~NowLoading();
public:
	void draw(Renderer& renderer);
private:
	int m_frame;
	int m_backHandle;
	std::array<int, 3> m_texNum;
};

