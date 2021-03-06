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
void SE::Play(const std::string& name)
{
	SE& se = instance();

	//初期周波数を設定
	SetFrequencySoundMem(se.m_seData[name].frequency, se.m_seData[name].seNum);
	//初期ボリュームを設定(0〜255)
	ChangeVolumeSoundMem(se.m_seData[name].volume, se.m_seData[name].seNum);
	//SEを再生
	PlaySoundMem(
		se.m_seData[name].seNum,
		se.m_seData[name].loopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
		true);
}

//SEを停止
void SE::Stop(const std::string& name)
{
	SE& se = instance();
	StopSoundMem(se.m_seData[name].seNum);
}

//SEが再生中かどうか
void SE::IsPlay(const std::string& name)
{
	SE& se = instance();
	CheckSoundMem(se.m_seData[name].seNum);
}

//音量調整
void SE::ChangeVolume(const std::string& name,int volume)
{
	SE& se = instance();
	//ボリュームを設定(0〜255)
	ChangeVolumeSoundMem(se.m_seData[name].volume = volume, se.m_seData[name].seNum);
}

//周波数調整
void SE::ChangeFrequency(const std::string& name, int frequency)
{
	SE& se = instance();
	//周波数を設定(100〜100,000 : -1はデフォルト周波数)
	SetFrequencySoundMem(se.m_seData[name].frequency = frequency, se.m_seData[name].seNum);
}

//SEの初期化(メモリ内から全削除)
void SE::Init()
{
	InitSoundMem();
}

//SEの取得
void SE::SetData(const ContentMap& seData)
{
	SE& se = instance();
	for (auto &data : seData)
	{
		se.m_seData.emplace(std::piecewise_construct,
			std::forward_as_tuple(data.first),
			std::forward_as_tuple(data.second.handle, false, 255, -1));
	}
}