#pragma once

enum BitFlag
{
	// �t���O�������Ă��Ȃ�
	NONE		= 0b000000000,
	// �M�~�b�N�����삵�Ă���
	GIMMICK		= 0b000000001,
	// �S�[������
	GOAL		= 0b000000010,
	// ���̃X�e�[�W�ɑJ�ڂ���
	NEXT        = 0b000000100,
	// �o�b�h�G���h
	BADEND      = 0b000010000,
	// �N���A
	CLEAR       = 0b000100000,
	// �g�D���[�G���h
	TRUEEND     = 0b001000000,
	// �����
	RIDEON		= 0b010000000,
	// �A�f�[��
	ADELE		= 0b100000000,
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