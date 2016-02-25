#pragma once

enum BitFlag
{
	// フラグが立っていない
	NONE		= 0b000000000,
	// ギミックが動作している
	GIMMICK		= 0b000000001,
	// ゴールした
	GOAL		= 0b000000010,
	// 次のステージに遷移した
	NEXT        = 0b000000100,
	// バッドエンド
	BADEND      = 0b000010000,
	// クリア
	CLEAR       = 0b000100000,
	// トゥルーエンド
	TRUEEND     = 0b001000000,
	// おんぶ
	RIDEON		= 0b010000000,
	// アデーレ
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