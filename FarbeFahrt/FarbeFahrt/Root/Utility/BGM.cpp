#include "BGM.h"
#include <chrono>
#include <thread>


BGM::BGM()
{
	m_playBGMvolume = 0;
	m_oldBGMvolume = 0;
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
	std::thread fade(fade);
	fade.detach();
	PlaySoundMem(bgm.m_playBGMhandle, DX_PLAYTYPE_LOOP);
	bgm.m_oldBGMhandle = bgm.m_playBGMhandle;
}
void BGM::fade()
{
	BGM& bgm = instance();
	int oldhandle = bgm.m_oldBGMhandle;
	int playhandle = bgm.m_playBGMhandle;
	int oldvolume = BGM_MAX_VOLUME;
	while (oldvolume >= 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		--oldvolume;
		ChangeVolumeSoundMem(oldvolume, oldhandle);
		ChangeVolumeSoundMem(BGM_MAX_VOLUME-oldvolume, playhandle);
	}
	oldvolume = 0;
		StopSoundMem(oldhandle);
}
void BGM::stop()
{
	BGM& bgm = instance();
	StopSoundMem(bgm.m_playBGMhandle);
}