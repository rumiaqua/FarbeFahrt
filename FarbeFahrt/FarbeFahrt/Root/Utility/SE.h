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
public:
	SE();
	~SE();
	static SE& instance();
public:
	//SEを再生する
	void playSE(const std::string& name);
	//SEを停止する
	void stopSE(const std::string& name);
	//SEが再生中かどうか調べる
	void isPlaySE(const std::string& name);
	//SEのボリュームを変更する(0～255)
	void changeVolumeSE(std::string name,int volume);
	//SEの周波数を変更する(100～100,000 : -1はデフォルト周波数)
	void changeFrequencySE(std::string name, int frequency);
	//SEの初期化(メモリ内から全消去)
	void initSE();
	//SEの取得
	void setSEData(const ContentMap& seData);
private:
	std::unordered_map<std::string, SEData> m_seData;
};