#pragma once
#include <string>
#include <thread>
#include "Utility\Def.h"
#include "DxLib.h"
class BGM
{
public:
	BGM();
	~BGM();
	static BGM& instance();
public:
	static void set(const ContentMap& contentMap);
	static void play(const std::string& name);
private:
	static void fadeOut();
	static void fadeIn();
private:
	ContentMap m_BGMList;
	int m_playBGMhandle;//現在再生中のBGM
	int m_oldBGMhandle;
	int m_playBGMvolume;
	int m_oldBGMvolume;
};

