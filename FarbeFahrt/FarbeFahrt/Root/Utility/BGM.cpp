#include "BGM.h"



BGM::BGM()
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
	bgm.BGMList = contentMap;
}
void BGM::play(const std::string& name)
{
	BGM& bgm = instance();

	bgm.playBGMhandle = bgm.BGMList.at(name).handle;
	if (bgm.playBGMhandle == bgm.oldBGMhandle)
	{
		return;
	}
	StopSoundMem(bgm.oldBGMhandle);
	PlaySoundMem(bgm.playBGMhandle, DX_PLAYTYPE_BACK);
	SetVolumeSound(128);
	bgm.oldBGMhandle = bgm.playBGMhandle;
}
void BGM::stop()
{
	BGM& bgm = instance();
	StopSoundMem(bgm.playBGMhandle);
}