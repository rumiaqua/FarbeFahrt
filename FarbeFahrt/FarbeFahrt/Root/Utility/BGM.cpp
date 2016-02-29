#include "BGM.h"
#include <chrono>
#include <thread>


BGM::BGM()
	: m_oldBGMhandle(-1)
	, m_oldBGMvolume(0)
	, m_playBGMhandle(-1)
	, m_playBGMvolume(0)
{

}

BGM::~BGM()
{
}
BGM& BGM::instance()
{
	static BGM instance;
	return instance;
}
void BGM::set(const ContentMap& contentMap)
{
	BGM& bgm = instance();
	bgm.m_BGMList = contentMap;
}
void BGM::play(const std::string& name)
{
	BGM& bgm = instance();

	bgm.m_playBGMhandle = bgm.m_BGMList.at(name).handle;
	if (bgm.m_playBGMhandle == bgm.m_oldBGMhandle)
	{
		return;
	}

	std::thread fadeOut(fadeOut);
	std::thread fadeIn(fadeIn);
	fadeOut.detach();
	fadeIn.detach();
	PlaySoundMem(bgm.m_playBGMhandle, DX_PLAYTYPE_LOOP);
	bgm.m_oldBGMhandle = bgm.m_playBGMhandle;
}
void BGM::fadeOut()
{
	BGM& bgm = instance();
	int handle = bgm.m_oldBGMhandle;
	int volume = BGM_MAX_VOLUME;
	while (volume >= 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		--volume;
		ChangeVolumeSoundMem(volume, handle);
	}
	volume = 0;
		StopSoundMem(handle);
}
void BGM::fadeIn()
{
	BGM& bgm = instance();
	int handle = bgm.m_playBGMhandle;

	int volume = 0;
	while (volume <= BGM_MAX_VOLUME)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		++volume;
		ChangeVolumeSoundMem(volume, handle);
	}
	volume = BGM_MAX_VOLUME;
}