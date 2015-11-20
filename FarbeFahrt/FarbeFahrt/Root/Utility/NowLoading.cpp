#include "NowLoading.h"



NowLoading::NowLoading()
{
	m_frame = 0;
	m_backHandle = LoadGraph("Resources/Texture/NowLoading/loading_back.png");
	m_texNum[0] = LoadGraph("Resources/Texture/NowLoading/loading_1.png");
	m_texNum[1] = LoadGraph("Resources/Texture/NowLoading/loading_2.png");
	m_texNum[2] = LoadGraph("Resources/Texture/NowLoading/loading_3.png");
}

void NowLoading::draw()
{
	constexpr int drawPos_x = 1024 - 350;
	constexpr int drawPos_y = 768 - 300;

	ClearDrawScreen();
	DrawGraph(0, 0, m_backHandle, TRUE);
	DrawGraph(drawPos_x, drawPos_y, m_texNum[m_frame / 10], TRUE);
	ScreenFlip();
	m_frame++;
	m_frame %= 30;
}

NowLoading::~NowLoading()
{
}
