# pragma once

# include <array>

typedef struct tagPOINT POINT;

/// <summary>マウスクラス</summary>
class Mouse
{
private:

	/// <summary>デフォルトコンストラクタ</summary>
	Mouse();

	/// <summary>コピーコンストラクタの削除</summary>
	Mouse(const Mouse&) = delete;

	/// <summary>代入演算子の削除</summary>
	Mouse& operator = (const Mouse&) = delete;

	/// <summary>静的インスタンスを返す</summary>
	static Mouse& instance();

public:

	/// <summary>更新処理</summary>
	static void update();

	/// <summary>マウスの座標を返す</summary>
	static POINT Position();

	/// <summary>押された瞬間かどうかを返す</summary>
	/// <param name="mouseCode">DxLibのマウスコード</param>
	static bool isClicked(int mouseCode);

	/// <summary>押されているかどうかを返す</summary>
	/// <param name="mouseCode">DxLibのマウスコード</param>
	static bool isPressed(int mouseCode);

	/// <summary>離された瞬間かどうかを返す</summary>
	/// <param name="mouseCode">DxLibのマウスコード</param>
	static bool isReleased(int mouseCode);

	/// <summary>ホイールの変化量を返す</summary>
	static int scrollValue();

private:

	POINT m_position;

	int m_scrollValue;

	int m_previousBuffer;

	int m_currentBuffer;
};
