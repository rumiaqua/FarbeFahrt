#pragma once
#include "Scene/SceneManager.h"

enum BitFlag
{
	// �t���O�������Ă��Ȃ�
	NONE		= 0b0000,
	// �M�~�b�N�����삵�Ă���
	GIMMICK		= 0b0001,
	// �S�[������
	GOAL		= 0b0010,
	// ���̃X�e�[�W�ɑJ�ڂ���
	NEXT        = 0b0100,
};

class StoryManager
{
public:
	StoryManager();
	static void initialize();
	static bool get(int flag);
	static void set(int flag);
	static void reset(int flag);
private:
	int m_flag;
};