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
	//‰Šúü”g”‚ğİ’è
	int r1 = SetFrequencySoundMem(m_seData[name].frequency, m_seData[name].seNum);
	//‰Šúƒ{ƒŠƒ…[ƒ€‚ğİ’è(0`255)
	int r2 = ChangeVolumeSoundMem(m_seData[name].volume, m_seData[name].seNum);
	//SE‚ğÄ¶
	int r3 = PlaySoundMem(
		m_seData[name].seNum,
		m_seData[name].loopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
		true);
}

//SE‚ğ’â~
void SE::stopSE(const std::string& name)
{
	StopSoundMem(m_seData[name].seNum);
}

//SE‚ªÄ¶’†‚©‚Ç‚¤‚©
void SE::isPlaySE(const std::string& name)
{
	CheckSoundMem(m_seData[name].seNum);
}

//‰¹—Ê’²®
void SE::changeVolumeSE(std::string name,int volume)
{
	//ƒ{ƒŠƒ…[ƒ€‚ğİ’è(0`255)
	ChangeVolumeSoundMem(m_seData[name].volume = volume, m_seData[name].seNum);
}

//ü”g”’²®
void SE::changeFrequencySE(std::string name, int frequency)
{
	//ü”g”‚ğİ’è(100`100,000 : -1‚ÍƒfƒtƒHƒ‹ƒgü”g”)
	SetFrequencySoundMem(m_seData[name].frequency = frequency, m_seData[name].seNum);
}

//SE‚Ì‰Šú‰»(ƒƒ‚ƒŠ“à‚©‚ç‘Síœ)
void SE::initSE()
{
	InitSoundMem();
}

//SE‚Ìæ“¾
void SE::setSEData(const ContentMap& seData)
{
	for (auto &data : seData)
	{
		m_seData.emplace(std::piecewise_construct,
			std::forward_as_tuple(data.first),
			std::forward_as_tuple(data.second.handle, false, 255, -1));
	}
}