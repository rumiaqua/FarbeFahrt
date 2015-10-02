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
	static void playSE(const std::string& name);
	//SE���~����
	static void stopSE(const std::string& name);
	//SE���Đ������ǂ������ׂ�
	static void isPlaySE(const std::string& name);
	//SE�̃{�����[����ύX����(0�`255)
	static void changeVolumeSE(std::string name, int volume);
	//SE�̎��g����ύX����(100�`100,000 : -1�̓f�t�H���g���g��)
	static void changeFrequencySE(std::string name, int frequency);
	//SE�̏�����(������������S����)
	static void initSE();
	//SE�̎擾
	static void setSEData(const ContentMap& seData);
private:
	std::unordered_map<std::string, SEData> m_seData;
};