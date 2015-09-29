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
	//�������g����ݒ�
	int r1 = SetFrequencySoundMem(m_seData[name].frequency, m_seData[name].seNum);
	//�����{�����[����ݒ�(0�`255)
	int r2 = ChangeVolumeSoundMem(m_seData[name].volume, m_seData[name].seNum);
	//SE���Đ�
	int r3 = PlaySoundMem(
		m_seData[name].seNum,
		m_seData[name].loopFlag ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
		true);
}

//SE���~
void SE::stopSE(const std::string& name)
{
	StopSoundMem(m_seData[name].seNum);
}

//SE���Đ������ǂ���
void SE::isPlaySE(const std::string& name)
{
	CheckSoundMem(m_seData[name].seNum);
}

//���ʒ���
void SE::changeVolumeSE(std::string name,int volume)
{
	//�{�����[����ݒ�(0�`255)
	ChangeVolumeSoundMem(m_seData[name].volume = volume, m_seData[name].seNum);
}

//���g������
void SE::changeFrequencySE(std::string name, int frequency)
{
	//���g����ݒ�(100�`100,000 : -1�̓f�t�H���g���g��)
	SetFrequencySoundMem(m_seData[name].frequency = frequency, m_seData[name].seNum);
}

//SE�̏�����(������������S�폜)
void SE::initSE()
{
	InitSoundMem();
}

//SE�̎擾
void SE::setSEData(const ContentMap& seData)
{
	for (auto &data : seData)
	{
		m_seData.emplace(std::piecewise_construct,
			std::forward_as_tuple(data.first),
			std::forward_as_tuple(data.second.handle, false, 255, -1));
	}
}