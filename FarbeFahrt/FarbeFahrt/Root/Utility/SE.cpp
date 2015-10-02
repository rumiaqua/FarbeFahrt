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

//SE‚ğÄ¶
void SE::playSE(const std::string& name)
{
	SE& se = instance();

	//‰Šúü”g”‚ğİ’è
	SetFrequencySoundMem(se.m_seData[name].frequency, se.m_seData[name].seNum);
	//‰Šúƒ{ƒŠƒ…[ƒ€‚ğİ’è(0`255)
	ChangeVolumeSoundMem(se.m_seData[name].volume, se.m_seData[name].seNum);
	//SE‚ğÄ¶
	PlaySoundMem(
		se.m_seData[name].seNum,
		se.m_seData[name].loopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
		true);
}

//SE‚ğ’â~
void SE::stopSE(const std::string& name)
{
	SE& se = instance();
	StopSoundMem(se.m_seData[name].seNum);
}

//SE‚ªÄ¶’†‚©‚Ç‚¤‚©
void SE::isPlaySE(const std::string& name)
{
	SE& se = instance();
	CheckSoundMem(se.m_seData[name].seNum);
}

//‰¹—Ê’²®
void SE::changeVolumeSE(std::string name,int volume)
{
	SE& se = instance();
	//ƒ{ƒŠƒ…[ƒ€‚ğİ’è(0`255)
	ChangeVolumeSoundMem(se.m_seData[name].volume = volume, se.m_seData[name].seNum);
}

//ü”g”’²®
void SE::changeFrequencySE(std::string name, int frequency)
{
	SE& se = instance();
	//ü”g”‚ğİ’è(100`100,000 : -1‚ÍƒfƒtƒHƒ‹ƒgü”g”)
	SetFrequencySoundMem(se.m_seData[name].frequency = frequency, se.m_seData[name].seNum);
}

//SE‚Ì‰Šú‰»(ƒƒ‚ƒŠ“à‚©‚ç‘Síœ)
void SE::initSE()
{
	SE& se = instance();
	InitSoundMem();
}

//SE‚Ìæ“¾
void SE::setSEData(const ContentMap& seData)
{
	SE& se = instance();
	for (auto &data : seData)
	{
		se.m_seData.emplace(std::piecewise_construct,
			std::forward_as_tuple(data.first),
			std::forward_as_tuple(data.second.handle, false, 255, -1));
	}
}