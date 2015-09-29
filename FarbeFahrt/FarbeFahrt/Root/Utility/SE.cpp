#include "SE.h"

SE::SE()
{
}

SE::~SE()
{
}

SE & SE::instance()
{
	static SE instance;
	return instance;
}

//SEを再生
void SE::playSE(const std::string& name)
{
	//初期周波数を設定
	int r1 = SetFrequencySoundMem(m_seData[name].frequency, m_seData[name].seNum);
	//初期ボリュームを設定(0〜255)
	int r2 = ChangeVolumeSoundMem(m_seData[name].volume, m_seData[name].seNum);
	//SEを再生
	int r3 = PlaySoundMem(
		m_seData[name].seNum,
		m_seData[name].loopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
		true);
}

//SEを停止
void SE::stopSE(const std::string& name)
{
	StopSoundMem(m_seData[name].seNum);
}

//SEが再生中かどうか
void SE::isPlaySE(const std::string& name)
{
	CheckSoundMem(m_seData[name].seNum);
}

//音量調整
void SE::changeVolumeSE(std::string name,int volume)
{
	//ボリュームを設定(0〜255)
	ChangeVolumeSoundMem(m_seData[name].volume = volume, m_seData[name].seNum);
}

//周波数調整
void SE::changeFrequencySE(std::string name, int frequency)
{
	//周波数を設定(100〜100,000 : -1はデフォルト周波数)
	SetFrequencySoundMem(m_seData[name].frequency = frequency, m_seData[name].seNum);
}

//SEの初期化(メモリ内から全削除)
void SE::initSE()
{
	InitSoundMem();
}

//SEの取得
void SE::setSEData(const ContentMap& seData)
{
	for (auto &data : seData)
	{
		m_seData.emplace(std::piecewise_construct,
			std::forward_as_tuple(data.first),
			std::forward_as_tuple(data.second.handle, false, 255, -1));
	}
}