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

	//���g��
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
	//SE���Đ�����
	void playSE(const std::string& name);
	//SE���~����
	void stopSE(const std::string& name);
	//SE���Đ������ǂ������ׂ�
	void isPlaySE(const std::string& name);
	//SE�̃{�����[����ύX����(0�`255)
	void changeVolumeSE(std::string name,int volume);
	//SE�̎��g����ύX����(100�`100,000 : -1�̓f�t�H���g���g��)
	void changeFrequencySE(std::string name, int frequency);
	//SE�̏�����(������������S����)
	void initSE();
	//SE�̎擾
	void setSEData(const ContentMap& seData);
private:
	std::unordered_map<std::string, SEData> m_seData;
};