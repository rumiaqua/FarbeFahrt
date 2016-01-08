# pragma once

# include <array>

# include "Point2.h"
# include "Vector3.h"
#include "Utility/Def.h"

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

private:

	/// <summary>静的インスタンスを返す</summary>
	static Mouse& Instance();

public:

	/// <summary>更新処理</summary>
	static void Update();

	/// <summary>マウスの座標を返す</summary>
	static Point2 Position();

	/// <summary>押された瞬間かどうかを返す</summary>
	/// <param name="mouseCode">DxLibのマウスコード</param>
	static bool IsClicked(int mouseCode);

	/// <summary>押されているかどうかを返す</summary>
	/// <param name="mouseCode">DxLibのマウスコード</param>
	static bool IsPressed(int mouseCode);

	/// <summary>離された瞬間かどうかを返す</summary>
	/// <param name="mouseCode">DxLibのマウスコード</param>
	static bool IsReleased(int mouseCode);

	/// <summary>ホイールの変化量を返す</summary>
	static int ScrollValue();

	static Vector3 ScreenPointToWorld(float z);

private:

	Point2 m_position;

	int m_scrollValue;

	int m_previousBuffer;

	int m_currentBuffer;

	Vector3 m_initPosition;
};
