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

//SE���Đ�
void SE::playSE(const std::string& name)
{
	SE& se = instance();

	//�������g����ݒ�
	SetFrequencySoundMem(se.m_seData[name].frequency, se.m_seData[name].seNum);
	//�����{�����[����ݒ�(0�`255)
	ChangeVolumeSoundMem(se.m_seData[name].volume, se.m_seData[name].seNum);
	//SE���Đ�
	PlaySoundMem(
		se.m_seData[name].seNum,
		se.m_seData[name].loopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
		true);
}

//SE���~
void SE::stopSE(const std::string& name)
{
	SE& se = instance();
	StopSoundMem(se.m_seData[name].seNum);
}

//SE���Đ������ǂ���
void SE::isPlaySE(const std::string& name)
{
	SE& se = instance();
	CheckSoundMem(se.m_seData[name].seNum);
}

//���ʒ���
void SE::changeVolumeSE(std::string name,int volume)
{
	SE& se = instance();
	//�{�����[����ݒ�(0�`255)
	ChangeVolumeSoundMem(se.m_seData[name].volume = volume, se.m_seData[name].seNum);
}

//���g������
void SE::changeFrequencySE(std::string name, int frequency)
{
	SE& se = instance();
	//���g����ݒ�(100�`100,000 : -1�̓f�t�H���g���g��)
	SetFrequencySoundMem(se.m_seData[name].frequency = frequency, se.m_seData[name].seNum);
}

//SE�̏�����(������������S�폜)
void SE::initSE()
{
	SE& se = instance();
	InitSoundMem();
}

//SE�̎擾
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