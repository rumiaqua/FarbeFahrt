#pragma once

enum BitFlag
{
	// �t���O�������Ă��Ȃ�
	NONE		= 0b00000000,
	// �M�~�b�N�����삵�Ă���
	GIMMICK		= 0b00000001,
	// �S�[������
	GOAL		= 0b00000010,
	// ���̃X�e�[�W�ɑJ�ڂ���
	NEXT        = 0b00000100,
	// �o�b�h�G���h
	BADEND      = 0b00010000,
	// �N���A
	CLEAR       = 0b00100000,
	// �g�D���[�G���h
	TRUEEND     = 0b01000000,
};

class StoryManager
{
public:
	StoryManager();
	static void initialize();
	static bool get(unsigned int flag);
	static void set(unsigned int flag);
	static void reset(unsigned int flag);
private:
	unsigned int m_flag;
};