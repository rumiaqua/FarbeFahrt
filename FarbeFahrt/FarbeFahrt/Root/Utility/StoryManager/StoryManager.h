#pragma once

enum BitFlag
{
	// フラグが立っていない
	NONE		= 0b00000000,
	// ギミックが動作している
	GIMMICK		= 0b00000001,
	// ゴールした
	GOAL		= 0b00000010,
	// 次のステージに遷移した
	NEXT        = 0b00000100,
	// バッドエンド
	BADEND      = 0b00010000,
	// クリア
	CLEAR       = 0b00100000,
	// トゥルーエンド
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