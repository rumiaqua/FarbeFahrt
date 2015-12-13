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
	static void stop();
private:
	ContentMap BGMList;
	int playBGMhandle;//åªç›çƒê∂íÜÇÃBGM
	int oldBGMhandle;
};

