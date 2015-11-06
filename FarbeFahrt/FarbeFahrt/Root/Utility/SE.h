#pragma once
#include "Dxlib.h"
#include <string>
#include <unordered_map>
#include "Utility/Def.h"

struct SEData
{
	int seNum;
	bool loopFlag;
	int volume;

	//周波数
	int frequency;

	SEData(int seNum, bool loopFlag, int volume,int frequency)
	{
		this->seNum = seNum;
		this->loopFlag = loopFlag;
		this->volume = volume;
		this->frequency = frequency;
	}
	SEData(){}
};

class SE
{
private:
	SE();
public:
	~SE();
	static SE& instance();
public:
	//SEを再生する
	static void Play(const std::string& name);
	//SEを停止する
	static void Stop(const std::string& name);
	//SEが再生中かどうか調べる
	static void IsPlay(const std::string& name);
	//SEのボリュームを変更する(0～255)
	static void ChangeVolume(std::string name, int volume);
	//SEの周波数を変更する(100～100,000 : -1はデフォルト周波数)
	static void ChangeFrequency(std::string name, int frequency);
	//SEの初期化(メモリ内から全消去)
	static void Init();
	//SEの取得
	static void SetData(const ContentMap& seData);
private:
	std::unordered_map<std::string, SEData> m_seData;
};